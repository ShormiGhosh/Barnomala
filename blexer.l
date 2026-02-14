%{
#include <stdio.h>
%}
%x COMMENT 
%option noyywrap
%option yylineno


%%

[ \t\n\r]+          { /* skip whitespace */ }

"("                 { printf("TOKEN: LPAREN (%s)\n", yytext); }
")"                 { printf("TOKEN: RPAREN (%s)\n", yytext); }
"["                 { printf("TOKEN: LBRACKET (%s)\n", yytext); }
"]"                 { printf("TOKEN: RBRACKET (%s)\n", yytext); }
","                 { printf("TOKEN: COMMA (%s)\n", yytext); }
"ঃ"                 { printf("TOKEN: COLON (%s)\n", yytext); }
"।"                 { printf("TOKEN: SEMICOLON (%s)\n", yytext); }

"শুরু_প্রোগ্রাম"    { printf("TOKEN: PROGRAM_START (%s)\n", yytext); }
"শেষ_প্রোগ্রাম"     { printf("TOKEN: PROGRAM_END (%s)\n", yytext); }

"প্রয়োজন"<[^>]+>   { printf("TOKEN: INCLUDE (%s)\n", yytext); }

"সংখ্যা"             { printf("TOKEN: NUMBER_TYPE (%s)\n", yytext); }
"দশমিক"             { printf("TOKEN: DECIMAL_TYPE (%s)\n", yytext); }
"বুলিয়ান"            { printf("TOKEN: BOOL_TYPE (%s)\n", yytext); }
"অক্ষর"             { printf("TOKEN: CHAR_TYPE (%s)\n", yytext); }
"বাক্য"             { printf("TOKEN: STRING_TYPE (%s)\n", yytext); }

"যদি"               { printf("TOKEN: IF (%s)\n", yytext); }
"নাহলে"             { printf("TOKEN: ELSE (%s)\n", yytext); }
"যতক্ষণ"           { printf("TOKEN: WHILE (%s)\n", yytext); }
"ঘুরতে_থাক"         { printf("TOKEN: FOR_RANGE (%s)\n", yytext); }
"থেকে"             { printf("TOKEN: FROM (%s)\n", yytext); }
"প্রক্রিয়া"          { printf("TOKEN: FUNCTION (%s)\n", yytext); }
"থামো"              { printf("TOKEN: BREAK (%s)\n", yytext); }
"চালিয়ে_যাও"        { printf("TOKEN: CONTINUE (%s)\n", yytext); }
"ফিরিয়ে_দাও"        { printf("TOKEN: RETURN (%s)\n", yytext); }
"দেখাও"             { printf("TOKEN: PRINT (%s)\n", yytext); }
"নাও"               { printf("TOKEN: INPUT (%s)\n", yytext); }

"ধারক"             { printf("TOKEN: ARRAY (%s)\n", yytext); }

"শক্তি"             { printf("TOKEN: POW (%s)\n", yytext); }
"বর্গমূল"           { printf("TOKEN: SQRT (%s)\n", yytext); }
"ফ্লোর"             { printf("TOKEN: FLOOR (%s)\n", yytext); }
"সিল"               { printf("TOKEN: CEIL (%s)\n", yytext); }
"পরম"               { printf("TOKEN: ABS (%s)\n", yytext); }

"+"                 { printf("TOKEN: PLUS (%s)\n", yytext); }
"যোগ"               { printf("TOKEN: PLUS (%s)\n", yytext); }
"-"                 { printf("TOKEN: MINUS (%s)\n", yytext); }
"বিয়োগ"            { printf("TOKEN: MINUS (%s)\n", yytext); }
"*"                 { printf("TOKEN: MULT (%s)\n", yytext); }
"গুণ"               { printf("TOKEN: MULT (%s)\n", yytext); }
"/"                 { printf("TOKEN: DIV (%s)\n", yytext); }
"ভাগ"               { printf("TOKEN: DIV (%s)\n", yytext); }
"%"                 { printf("TOKEN: MOD (%s)\n", yytext); }
"ভাগশেষ"           { printf("TOKEN: MOD (%s)\n", yytext); }
"&&"                { printf("TOKEN: AND (%s)\n", yytext); }
"এবং"              { printf("TOKEN: AND (%s)\n", yytext); }
"||"                { printf("TOKEN: OR (%s)\n", yytext); }
"অথবা"             { printf("TOKEN: OR (%s)\n", yytext); }
"!"                 { printf("TOKEN: NOT (%s)\n", yytext); }
"নয়"               { printf("TOKEN: NOT (%s)\n", yytext); }
"++"                { printf("TOKEN: INC (%s)\n", yytext); }
"বাড়াও"             { printf("TOKEN: INC (%s)\n", yytext); }
"--"                { printf("TOKEN: DEC (%s)\n", yytext); }
"কমাও"             { printf("TOKEN: DEC (%s)\n", yytext); }
"=="                { printf("TOKEN: EQUAL (%s)\n", yytext); }
"!="                { printf("TOKEN: NOT_EQUAL (%s)\n", yytext); }
">="                { printf("TOKEN: GREATER_EQUAL (%s)\n", yytext); }
"<="                { printf("TOKEN: LESS_EQUAL (%s)\n", yytext); }
">"                 { printf("TOKEN: GREATER (%s)\n", yytext); }
"<"                 { printf("TOKEN: LESS (%s)\n", yytext); }
"="                 { printf("TOKEN: ASSIGN (%s)\n", yytext); }
"সমান"             { printf("TOKEN: EQUAL (%s)\n", yytext); }
"অসমান"            { printf("TOKEN: NOT_EQUAL (%s)\n", yytext); }
"বড়_সমান"         { printf("TOKEN: GREATER_EQUAL (%s)\n", yytext); }
"ছোট_সমান"        { printf("TOKEN: LESS_EQUAL (%s)\n", yytext); }
"বড়"               { printf("TOKEN: GREATER (%s)\n", yytext); }
"ছোট"              { printf("TOKEN: LESS (%s)\n", yytext); }

"সত্য"             { printf("TOKEN: BOOL_TRUE (%s)\n", yytext); }
"মিথ্যা"           { printf("TOKEN: BOOL_FALSE (%s)\n", yytext); }

\"([^\"]|\\\")*\"   { printf("TOKEN: STRING_LITERAL (%s)\n", yytext); }
\'(\xE0[\xA6\xA7][\x80-\xBF]|[^'\n\\]|\\.)\'  { printf("TOKEN: CHAR_LITERAL (%s)\n", yytext); }

(\xE0\xA7[\xA6-\xAF])+"."(\xE0\xA7[\xA6-\xAF])+ { printf("TOKEN: FLOAT_LITERAL (%s)\n", yytext); }
(\xE0\xA7[\xA6-\xAF])+ { printf("TOKEN: INT_LITERAL (%s)\n", yytext); }

"মন্তব্য"              { BEGIN(COMMENT); }   

<COMMENT>{
    "মন্তব্য_শেষ"           { BEGIN(INITIAL); }  
    .|\n                 { }
}

(\xE0\xA6[\x80-\x82\x84-\xBF]|\xE0\xA7[\x80-\xBF]|_)(\xE0\xA6[\x80-\x82\x84-\xBF]|\xE0\xA7[\x80-\xBF]|\xE0\xA7[\xA6-\xAF]|_)* { printf("TOKEN: IDENTIFIER (%s)\n", yytext); }

.                    { printf("TOKEN: UNKNOWN (%s)\n", yytext); }

%%

int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if(!fp) {
        printf("File open error\n");
        return 1;
    }

    yyin = fp;
    yylex();
    fclose(fp);
    return 0;
}

