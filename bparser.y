%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern void init_indent();
%}

%union {
    int intval;
    double floatval;
    char *strval;
}

%token PROGRAM_START PROGRAM_END
%token NUMBER_TYPE DECIMAL_TYPE BOOL_TYPE CHAR_TYPE STRING_TYPE
%token IF ELSE WHILE FOR_RANGE FROM
%token FUNCTION BREAK CONTINUE RETURN
%token PRINT INPUT
%token LPAREN RPAREN LBRACKET RBRACKET
%token COMMA COLON SEMICOLON
%token ARRAY
%token POW SQRT FLOOR CEIL ABS
%token INC DEC
%token BOOL_TRUE BOOL_FALSE
%token INCLUDE
%token INDENT DEDENT NEWLINE

%token <intval> INT_LITERAL
%token <floatval> FLOAT_LITERAL
%token <strval> STRING_LITERAL CHAR_LITERAL IDENTIFIER

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right ASSIGN
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left GREATER LESS GREATER_EQUAL LESS_EQUAL
%left PLUS MINUS
%left MULT DIV MOD
%right NOT
%right UMINUS
%left FROM

%token PLUS MINUS MULT DIV MOD
%token AND OR NOT
%token ASSIGN EQUAL NOT_EQUAL
%token GREATER LESS GREATER_EQUAL LESS_EQUAL

%%

program:
    PROGRAM_START newlines statements PROGRAM_END optional_newlines
    {
        printf("✓ Program parsed successfully!\n");
    }
    | PROGRAM_START statements PROGRAM_END optional_newlines
    {
        printf("✓ Program parsed successfully!\n");
    }
    ;

newlines:
    NEWLINE
    | newlines NEWLINE
    ;

optional_newlines:
    /* empty */
    | optional_newlines NEWLINE
    ;

statements:
    /* empty */
    | statements statement
    | statements NEWLINE
    ;

statement:
    simple_statement NEWLINE
    | compound_statement
    ;

simple_statement:
    declaration
    | assignment
    | input_statement
    | print_statement
    | return_statement
    | break_statement
    | continue_statement
    | increment_statement
    | decrement_statement
    | array_declaration
    | function_call SEMICOLON
    ;

compound_statement:
    if_statement
    | while_statement
    | for_statement
    | function_definition
    ;

declaration:
    type IDENTIFIER SEMICOLON
    {
        printf("Declaration: %s\n", $2);
        free($2);
    }
    | type IDENTIFIER ASSIGN expression SEMICOLON
    {
        printf("Declaration with assignment: %s\n", $2);
        free($2);
    }
    ;

type:
    NUMBER_TYPE
    | DECIMAL_TYPE
    | BOOL_TYPE
    | CHAR_TYPE
    | STRING_TYPE
    ;

assignment:
    IDENTIFIER ASSIGN expression SEMICOLON
    {
        printf("Assignment: %s\n", $1);
        free($1);
    }
    ;

input_statement:
    INPUT LPAREN IDENTIFIER RPAREN SEMICOLON
    {
        printf("Input statement for: %s\n", $3);
        free($3);
    }
    ;

print_statement:
    PRINT expression SEMICOLON
    {
        printf("Print statement\n");
    }
    ;

suite:
    simple_statement NEWLINE
    | NEWLINE INDENT statements DEDENT
    ;

if_statement:
    IF expression COLON suite %prec LOWER_THAN_ELSE
    {
        printf("If statement\n");
    }
    | IF expression COLON suite ELSE COLON suite
    {
        printf("If-Else statement\n");
    }
    ;

while_statement:
    WHILE expression COLON suite
    {
        printf("While loop\n");
    }
    ;

for_statement:
    FOR_RANGE LPAREN IDENTIFIER RPAREN expression FROM expression COLON suite
    {
        printf("For loop\n");
        free($3);
    }
    ;

function_definition:
    FUNCTION IDENTIFIER LPAREN parameter_list RPAREN COLON suite
    {
        printf("Function definition: %s\n", $2);
        free($2);
    }
    | FUNCTION IDENTIFIER LPAREN RPAREN COLON suite
    {
        printf("Function definition (no params): %s\n", $2);
        free($2);
    }
    ;

parameter_list:
    IDENTIFIER
    {
        free($1);
    }
    | parameter_list COMMA IDENTIFIER
    {
        free($3);
    }
    ;

function_call:
    IDENTIFIER LPAREN argument_list RPAREN
    {
        printf("Function call: %s\n", $1);
        free($1);
    }
    | IDENTIFIER LPAREN RPAREN
    {
        printf("Function call (no args): %s\n", $1);
        free($1);
    }
    ;

argument_list:
    expression
    | argument_list COMMA expression
    ;

return_statement:
    RETURN expression SEMICOLON
    {
        printf("Return statement\n");
    }
    ;

break_statement:
    BREAK SEMICOLON
    {
        printf("Break statement\n");
    }
    ;

continue_statement:
    CONTINUE SEMICOLON
    {
        printf("Continue statement\n");
    }
    ;

increment_statement:
    IDENTIFIER INC SEMICOLON
    {
        printf("Increment: %s\n", $1);
        free($1);
    }
    ;

decrement_statement:
    IDENTIFIER DEC SEMICOLON
    {
        printf("Decrement: %s\n", $1);
        free($1);
    }
    ;

array_declaration:
    ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET SEMICOLON
    {
        printf("Array declaration: %s[%d]\n", $5, $7);
        free($5);
    }
    | ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET ASSIGN LBRACKET array_elements RBRACKET SEMICOLON
    {
        printf("Array declaration with initialization: %s[%d]\n", $5, $7);
        free($5);
    }
    ;

array_elements:
    expression
    | array_elements COMMA expression
    ;

array_access:
    IDENTIFIER LBRACKET expression RBRACKET
    {
        printf("Array access: %s\n", $1);
        free($1);
    }
    ;

expression:
    primary_expression
    | expression PLUS expression
    | expression MINUS expression
    | expression MULT expression
    | expression DIV expression
    | expression MOD expression
    | expression AND expression
    | expression OR expression
    | expression EQUAL expression
    | expression NOT_EQUAL expression
    | expression GREATER expression
    | expression LESS expression
    | expression GREATER_EQUAL expression
    | expression LESS_EQUAL expression
    | expression FROM expression
    | NOT expression
    | MINUS expression %prec UMINUS
    ;

primary_expression:
    INT_LITERAL
    | FLOAT_LITERAL
    | STRING_LITERAL
    {
        free($1);
    }
    | CHAR_LITERAL
    {
        free($1);
    }
    | IDENTIFIER
    {
        free($1);
    }
    | BOOL_TRUE
    | BOOL_FALSE
    | array_access
    | function_call
    | math_function
    | LPAREN expression RPAREN
    ;

math_function:
    POW LPAREN expression COMMA expression RPAREN
    | SQRT LPAREN expression RPAREN
    | FLOOR LPAREN expression RPAREN
    | CEIL LPAREN expression RPAREN
    | ABS LPAREN expression RPAREN
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "✗ Syntax error at line %d: %s\n", yylineno, s);
}

/* Normalize precomposed Bengali characters to decomposed form */
/* This ensures য় (U+09DF = E0 A7 9F) is always represented as য + ় (E0 A6 AF + E0 A6 BC) */
FILE* normalize_input(FILE *input) {
    fseek(input, 0, SEEK_END);
    long fsize = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    unsigned char *buf = malloc(fsize + 1);
    long actual = fread(buf, 1, fsize, input);
    fclose(input);
    
    /* Output buffer: worst case each 3-byte char becomes 6 bytes */
    unsigned char *out = malloc(actual * 2 + 1);
    long olen = 0;
    
    for (long i = 0; i < actual; ) {
        /* Check for E0 A7 9F (য় U+09DF) -> E0 A6 AF E0 A6 BC */
        if (i + 2 < fsize && buf[i] == 0xE0 && buf[i+1] == 0xA7 && buf[i+2] == 0x9F) {
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xAF;  /* য */
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xBC;  /* ় */
            i += 3;
        }
        /* Check for E0 A7 9C (ড় U+09DC) -> E0 A6 A1 E0 A6 BC */
        else if (i + 2 < fsize && buf[i] == 0xE0 && buf[i+1] == 0xA7 && buf[i+2] == 0x9C) {
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xA1;  /* ড */
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xBC;  /* ় */
            i += 3;
        }
        /* Check for E0 A7 9D (ঢ় U+09DD) -> E0 A6 A2 E0 A6 BC */
        else if (i + 2 < fsize && buf[i] == 0xE0 && buf[i+1] == 0xA7 && buf[i+2] == 0x9D) {
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xA2;  /* ঢ */
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xBC;  /* ় */
            i += 3;
        }
        else {
            out[olen++] = buf[i++];
        }
    }
    
    free(buf);
    
    FILE *tmp = tmpfile();
    fwrite(out, 1, olen, tmp);
    fseek(tmp, 0, SEEK_SET);
    free(out);
    
    return tmp;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    
    /* Normalize Unicode before parsing */
    yyin = normalize_input(fp);  /* fp is closed inside normalize_input */
    init_indent();  /* Initialize indentation tracking */
    
    printf("=== Parsing Bangla Program ===\n\n");
    
    int result = yyparse();
    
    fclose(yyin);
    
    if (result == 0) {
        printf("\n=== Parsing Complete ===\n");
        return 0;
    } else {
        printf("\n=== Parsing Failed ===\n");
        return 1;
    }
}
