%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bparser.tab.h"

/* Indentation tracking */
#define MAX_INDENT_DEPTH 100
int indent_stack[MAX_INDENT_DEPTH];
int indent_top = 0;
int pending_dedents = 0;
int pending_indent = 0;
int paren_depth = 0;

void push_indent(int level) {
    if (indent_top < MAX_INDENT_DEPTH - 1) {
        indent_stack[++indent_top] = level;
    }
}

int pop_indent() {
    if (indent_top > 0) {
        return indent_stack[indent_top--];
    }
    return 0;
}

int get_current_indent() {
    return indent_top > 0 ? indent_stack[indent_top] : 0;
}

void init_indent() {
    indent_top = 0;
    indent_stack[0] = 0;
    pending_dedents = 0;
    pending_indent = 0;
    paren_depth = 0;
}

/* Rename flex's generated scanner so we can wrap it */
#define YY_DECL int internal_yylex(void)

%}
%x COMMENT
%option noyywrap
%option yylineno

%%

\n {
    /* Skip newlines inside parentheses/brackets */
    if (paren_depth > 0) {
        /* ignore newlines inside parens */
    } else {
        /* Look ahead: skip blank lines, count indentation of next real line */
        int c;
        int indent;

        while (1) {
            indent = 0;
            while ((c = input()) == ' ') {
                indent++;
            }
            if (c == '\t') {
                /* treat tab as 4 spaces */
                indent += 4;
                continue;
            }
            if (c == '\r') continue;
            if (c == '\n') continue;  /* blank line, try next */
            break;  /* found real content or EOF */
        }

        /* Put back the non-space character we just read */
        if (c != EOF && c != 0) {
            unput(c);
        }

        /* Compare indentation with current level */
        int current = get_current_indent();

        if (indent > current) {
            push_indent(indent);
            pending_indent = 1;
        } else if (indent < current) {
            while (indent_top > 0 && get_current_indent() > indent) {
                pop_indent();
                pending_dedents++;
            }
        }
        /* indent == current: no INDENT/DEDENT needed */

        return NEWLINE;
    }
}

\r { /* Skip carriage return */ }

[ \t]+ { /* Skip whitespace within lines */ }

"("                 { paren_depth++; return LPAREN; }
")"                 { paren_depth--; return RPAREN; }
"["                 { paren_depth++; return LBRACKET; }
"]"                 { paren_depth--; return RBRACKET; }
","                 { return COMMA; }
"ঃ"                 { return COLON; }
"।"                 { return SEMICOLON; }

"শুরু_প্রোগ্রাম"    { return PROGRAM_START; }
"শেষ_প্রোগ্রাম"     { return PROGRAM_END; }

"প্রয়োজন"<[^>]+>   { yylval.strval = strdup(yytext); return INCLUDE; }

"সংখ্যা"             { return NUMBER_TYPE; }
"দশমিক"             { return DECIMAL_TYPE; }
"বুলিয়ান"            { return BOOL_TYPE; }
"অক্ষর"             { return CHAR_TYPE; }
"বাক্য"             { return STRING_TYPE; }

"যদি"               { return IF; }
"নাহলে"             { return ELSE; }
"যতক্ষণ"           { return WHILE; }
"ঘুরতে_থাক"         { return FOR_RANGE; }
"থেকে"             { return FROM; }
"প্রক্রিয়া"          { return FUNCTION; }
"থামো"              { return BREAK; }
"চালিয়ে_যাও"        { return CONTINUE; }
"ফিরিয়ে_দাও"        { return RETURN; }
"দেখাও"             { return PRINT; }
"নাও"               { return INPUT; }

"ধারক"             { return ARRAY; }

"শক্তি"             { return POW; }
"বর্গমূল"           { return SQRT; }
"ফ্লোর"             { return FLOOR; }
"সিল"               { return CEIL; }
"পরম"               { return ABS; }

"+"                 { return PLUS; }
"যোগ"               { return PLUS; }
"-"                 { return MINUS; }
"বিয়োগ"            { return MINUS; }
"*"                 { return MULT; }
"গুণ"               { return MULT; }
"/"                 { return DIV; }
"ভাগ"               { return DIV; }
"%"                 { return MOD; }
"ভাগশেষ"           { return MOD; }
"&&"                { return AND; }
"এবং"              { return AND; }
"||"                { return OR; }
"অথবা"             { return OR; }
"!"                 { return NOT; }
"নয়"               { return NOT; }
"++"                { return INC; }
"বাড়াও"             { return INC; }
"--"                { return DEC; }
"কমাও"             { return DEC; }
"=="                { return EQUAL; }
"!="                { return NOT_EQUAL; }
">="                { return GREATER_EQUAL; }
"<="                { return LESS_EQUAL; }
">"                 { return GREATER; }
"<"                 { return LESS; }
"="                 { return ASSIGN; }
"সমান"             { return EQUAL; }
"অসমান"            { return NOT_EQUAL; }
"বড়_সমান"         { return GREATER_EQUAL; }
"ছোট_সমান"        { return LESS_EQUAL; }
"বড়"               { return GREATER; }
"ছোট"              { return LESS; }

"সত্য"             { return BOOL_TRUE; }
"মিথ্যা"           { return BOOL_FALSE; }

\"([^\"]|\\\")*\"   { yylval.strval = strdup(yytext); return STRING_LITERAL; }
\'(\xE0[\xA6\xA7][\x80-\xBF]|[^'\n\\]|\\.)\'  { yylval.strval = strdup(yytext); return CHAR_LITERAL; }

(\xE0\xA7[\xA6-\xAF])+"."(\xE0\xA7[\xA6-\xAF])+ {
    /* Convert Bangla digits to English and parse as float */
    char *english = strdup(yytext);
    int len = strlen(yytext);
    int pos = 0;
    for(int i = 0; i < len; ) {
        if(i + 2 < len && (unsigned char)english[i] == 0xE0 &&
           (unsigned char)english[i+1] == 0xA7 &&
           (unsigned char)english[i+2] >= 0xA6 &&
           (unsigned char)english[i+2] <= 0xAF) {
            int digit = (unsigned char)english[i+2] - 0xA6;
            english[pos++] = '0' + digit;
            i += 3;
        } else {
            english[pos++] = english[i++];
        }
    }
    english[pos] = '\0';
    yylval.floatval = atof(english);
    free(english);
    return FLOAT_LITERAL;
}

(\xE0\xA7[\xA6-\xAF])+ {
    /* Convert Bangla digits to English and parse as int */
    char *english = strdup(yytext);
    int len = strlen(yytext);
    int pos = 0;
    for(int i = 0; i < len; ) {
        if(i + 2 < len && (unsigned char)english[i] == 0xE0 &&
           (unsigned char)english[i+1] == 0xA7 &&
           (unsigned char)english[i+2] >= 0xA6 &&
           (unsigned char)english[i+2] <= 0xAF) {
            int digit = (unsigned char)english[i+2] - 0xA6;
            english[pos++] = '0' + digit;
            i += 3;
        } else {
            english[pos++] = english[i++];
        }
    }
    english[pos] = '\0';
    yylval.intval = atoi(english);
    free(english);
    return INT_LITERAL;
}

"মন্তব্য"              { BEGIN(COMMENT); }

<COMMENT>{
    "মন্তব্য_শেষ"           { BEGIN(INITIAL); }
    .|\n                 { }
}

(\xE0\xA6[\x80-\x82\x84-\xBF]|\xE0\xA7[\x80-\xBF]|_)(\xE0\xA6[\x80-\x82\x84-\xBF]|\xE0\xA7[\x80-\xBF]|\xE0\xA7[\xA6-\xAF]|_)* { yylval.strval = strdup(yytext); return IDENTIFIER; }

.                    { fprintf(stderr, "Unknown character: %s at line %d\n", yytext, yylineno); }

<<EOF>> {
    /* Emit remaining dedents at end of file */
    if (pending_dedents > 0) {
        pending_dedents--;
        return DEDENT;
    }
    if (indent_top > 0) {
        pop_indent();
        return DEDENT;
    }
    yyterminate();
}

%%

/* Wrapper: emits pending INDENT/DEDENT tokens before calling the real scanner */
int yylex(void) {
    /* First drain any pending INDENT */
    if (pending_indent) {
        pending_indent = 0;
        return INDENT;
    }
    /* Then drain any pending DEDENTs */
    if (pending_dedents > 0) {
        pending_dedents--;
        return DEDENT;
    }
    /* Otherwise get the next token from flex */
    return internal_yylex();
}
