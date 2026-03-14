%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <fcntl.h>
#ifdef _WIN32
extern unsigned int __stdcall SetConsoleCP(unsigned int wCodePageID);
extern unsigned int __stdcall SetConsoleOutputCP(unsigned int wCodePageID);
#endif
#include "ast.h"   /* brings in symtable.h, AstNode, OP_*, eval_expr, exec_stmt */
#include "irgen.h"

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern void init_indent();

/* suppress_execution referenced by symtable.c; always 0 in AST mode */
int suppress_execution = 0;

static int   g_emit_ir = 0;
static FILE *g_ir_out = NULL;
static const char *g_ir_path = NULL;
%}

/* ast.h (which includes symtable.h) must also appear in bparser.tab.h
   so blexer.l sees Value / VarType / AstNode. */
%code requires {
#include "ast.h"
}

%union {
    int      intval;
    double   floatval;
    char    *strval;
    VarType  vtype;
    AstNode *node;
}

%token PROGRAM_START PROGRAM_END
%token NUMBER_TYPE DECIMAL_TYPE BOOL_TYPE CHAR_TYPE STRING_TYPE
%token IF ELSE WHILE FOR_RANGE FROM
%token FUNCTION BREAK CONTINUE RETURN
%token PRINT INPUT
%token LPAREN RPAREN LBRACKET RBRACKET
%token COMMA COLON SEMICOLON
%token ARRAY
%token POW SQRT FLOOR CEIL ABS LENGTH
%token INC DEC
%token BOOL_TRUE BOOL_FALSE
%token INCLUDE
%token INDENT DEDENT NEWLINE

%token <intval> INT_LITERAL
%token <floatval> FLOAT_LITERAL
%token <strval> STRING_LITERAL CHAR_LITERAL IDENTIFIER

%type <node>  expression primary_expression math_function array_access function_call
%type <node>  statements statement simple_statement compound_statement
%type <node>  suite
%type <node>  declaration assignment print_statement input_statement
%type <node>  return_statement break_statement continue_statement
%type <node>  increment_statement decrement_statement
%type <node>  array_declaration array_elements array_assignment
%type <node>  if_statement while_statement for_statement function_definition
%type <node>  if_header parameter_list argument_list
%type <vtype> type

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
        if (g_emit_ir && g_ir_out) {
            TacProgram final_tac;
            tac_program_init(&final_tac);
            tac_generate_from_ast($3, &final_tac);
            fprintf(g_ir_out, "=== Generated TAC ===\n");
            tac_program_print(g_ir_out, &final_tac);
            tac_program_free(&final_tac);
        }

        ExecResult r = exec_stmt($3);
        free_value(r.retval);
        node_free($3);
        printf("✓ Program parsed successfully!\n");
    }
    | PROGRAM_START statements PROGRAM_END optional_newlines
    {
        if (g_emit_ir && g_ir_out) {
            TacProgram final_tac;
            tac_program_init(&final_tac);
            tac_generate_from_ast($2, &final_tac);
            fprintf(g_ir_out, "=== Generated TAC ===\n");
            tac_program_print(g_ir_out, &final_tac);
            tac_program_free(&final_tac);
        }

        ExecResult r = exec_stmt($2);
        free_value(r.retval);
        node_free($2);
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

/* statements builds a left-recursive SEQ chain;
   NULL means empty block (exec_stmt handles NULL as N_NOP). */
statements:
    /* empty */
    {
        $$ = NULL;
    }
    | statements statement
    {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            AstNode *seq = node_new(N_SEQ, yylineno);
            seq->left  = $1;
            seq->right = $2;
            $$ = seq;
        }
    }
    | statements NEWLINE
    {
        $$ = $1;
    }
    ;

statement:
    simple_statement NEWLINE  { $$ = $1; }
    | compound_statement      { $$ = $1; }
    ;

simple_statement:
    declaration           { $$ = $1; }
    | assignment          { $$ = $1; }
    | array_assignment    { $$ = $1; }
    | input_statement     { $$ = $1; }
    | print_statement     { $$ = $1; }
    | return_statement    { $$ = $1; }
    | break_statement     { $$ = $1; }
    | continue_statement  { $$ = $1; }
    | increment_statement { $$ = $1; }
    | decrement_statement { $$ = $1; }
    | array_declaration   { $$ = $1; }
    | function_call SEMICOLON
    {
        AstNode *n = node_new(N_CALL_STMT, yylineno);
        n->left = $1;
        $$ = n;
    }
    ;

compound_statement:
    if_statement          { $$ = $1; }
    | while_statement     { $$ = $1; }
    | for_statement       { $$ = $1; }
    | function_definition { $$ = $1; }
    ;

declaration:
    type IDENTIFIER SEMICOLON
    {
        AstNode *n = node_new(N_DECL, yylineno);
        n->sval  = $2;
        n->vtype = $1;
        n->left  = NULL;
        $$ = n;
    }
    | type IDENTIFIER ASSIGN expression SEMICOLON
    {
        AstNode *n = node_new(N_DECL, yylineno);
        n->sval  = $2;
        n->vtype = $1;
        n->left  = $4;
        $$ = n;
    }
    ;

type:
    NUMBER_TYPE  { $$ = TYPE_NUMBER;  }
    | DECIMAL_TYPE { $$ = TYPE_DECIMAL; }
    | BOOL_TYPE    { $$ = TYPE_BOOL;    }
    | CHAR_TYPE    { $$ = TYPE_CHAR;    }
    | STRING_TYPE  { $$ = TYPE_STRING;  }
    ;

assignment:
    IDENTIFIER ASSIGN expression SEMICOLON
    {
        AstNode *n = node_new(N_ASSIGN, yylineno);
        n->sval = $1;
        n->left = $3;
        $$ = n;
    }
    ;

input_statement:
    INPUT LPAREN IDENTIFIER RPAREN SEMICOLON
    {
        AstNode *n = node_new(N_INPUT, yylineno);
        n->sval = $3;
        $$ = n;
    }
    ;

print_statement:
    PRINT expression SEMICOLON
    {
        AstNode *n = node_new(N_PRINT, yylineno);
        n->left = $2;
        $$ = n;
    }
    ;

suite:
    simple_statement NEWLINE       { $$ = $1; }
    | NEWLINE INDENT statements DEDENT { $$ = $3; }
    ;

if_header:
    IF expression COLON { $$ = $2; }
    ;

if_statement:
    if_header suite %prec LOWER_THAN_ELSE
    {
        AstNode *n = node_new(N_IF, yylineno);
        n->left  = $1;
        n->right = $2;
        n->extra = NULL;
        $$ = n;
    }
    | if_header suite ELSE COLON suite
    {
        AstNode *n = node_new(N_IF, yylineno);
        n->left  = $1;
        n->right = $2;
        n->extra = $5;
        $$ = n;
    }
    ;

while_statement:
    WHILE expression COLON suite
    {
        AstNode *n = node_new(N_WHILE, yylineno);
        n->left  = $2;   /* condition — re-evaluated every iteration */
        n->right = $4;   /* body */
        $$ = n;
    }
    ;

for_statement:
    FOR_RANGE LPAREN IDENTIFIER RPAREN expression FROM expression COLON suite
    {
        AstNode *n = node_new(N_FOR_RANGE, yylineno);
        n->sval  = $3;
        n->left  = $5;
        n->right = $7;
        n->extra = $9;
        $$ = n;
    }
    ;

function_definition:
    FUNCTION IDENTIFIER LPAREN parameter_list RPAREN COLON suite
    {
        AstNode *n = node_new(N_FUNCDEF, yylineno);
        n->sval  = $2;
        n->left  = $4;
        n->right = $7;
        $$ = n;
    }
    | FUNCTION IDENTIFIER LPAREN RPAREN COLON suite
    {
        AstNode *n = node_new(N_FUNCDEF, yylineno);
        n->sval  = $2;
        n->left  = NULL;
        n->right = $6;
        $$ = n;
    }
    ;

parameter_list:
    IDENTIFIER
    {
        AstNode *n = node_new(N_PARAM_LIST, yylineno);
        n->sval  = $1;
        n->right = NULL;
        $$ = n;
    }
    | parameter_list COMMA IDENTIFIER
    {
        AstNode *n = node_new(N_PARAM_LIST, yylineno);
        n->sval  = $3;
        n->right = $1;
        $$ = n;
    }
    ;

function_call:
    IDENTIFIER LPAREN argument_list RPAREN
    {
        AstNode *n = node_new(N_CALL, yylineno);
        n->sval = $1;
        n->left = $3;
        $$ = n;
    }
    | IDENTIFIER LPAREN RPAREN
    {
        AstNode *n = node_new(N_CALL, yylineno);
        n->sval = $1;
        n->left = NULL;
        $$ = n;
    }
    ;

argument_list:
    expression
    {
        AstNode *n = node_new(N_ARG_LIST, yylineno);
        n->left  = $1;
        n->right = NULL;
        $$ = n;
    }
    | argument_list COMMA expression
    {
        AstNode *n = node_new(N_ARG_LIST, yylineno);
        n->left  = $3;
        n->right = $1;
        $$ = n;
    }
    ;

return_statement:
    RETURN expression SEMICOLON
    {
        AstNode *n = node_new(N_RETURN, yylineno);
        n->left = $2;
        $$ = n;
    }
    ;

break_statement:
    BREAK SEMICOLON
    {
        $$ = node_new(N_BREAK, yylineno);
    }
    ;

continue_statement:
    CONTINUE SEMICOLON
    {
        $$ = node_new(N_CONTINUE, yylineno);
    }
    ;

increment_statement:
    IDENTIFIER INC SEMICOLON
    {
        AstNode *n = node_new(N_INC, yylineno);
        n->sval = $1;
        $$ = n;
    }
    ;

decrement_statement:
    IDENTIFIER DEC SEMICOLON
    {
        AstNode *n = node_new(N_DEC, yylineno);
        n->sval = $1;
        $$ = n;
    }
    ;

array_assignment:
    IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON
    {
        AstNode *n = node_new(N_ARRAY_ASSIGN, yylineno);
        n->sval  = $1;
        n->left  = $3;   /* index */
        n->right = $6;   /* new value */
        $$ = n;
    }
    ;

array_declaration:
    ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET SEMICOLON
    {
        AstNode *n = node_new(N_ARRAY_DECL, yylineno);
        n->sval  = $5;
        n->vtype = $3;
        n->ival  = $7;
        n->left  = NULL;
        $$ = n;
    }
    | ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET ASSIGN LBRACKET array_elements RBRACKET SEMICOLON
    {
        AstNode *n = node_new(N_ARRAY_DECL, yylineno);
        n->sval  = $5;
        n->vtype = $3;
        n->ival  = $7;
        n->left  = $11;
        $$ = n;
    }
    ;

array_elements:
    expression
    {
        AstNode *n = node_new(N_INIT_LIST, yylineno);
        n->left  = $1;
        n->right = NULL;
        $$ = n;
    }
    | array_elements COMMA expression
    {
        AstNode *n = node_new(N_INIT_LIST, yylineno);
        n->left  = $3;
        n->right = $1;
        $$ = n;
    }
    ;

array_access:
    IDENTIFIER LBRACKET expression RBRACKET
    {
        AstNode *n = node_new(N_ARRAY_ACCESS, yylineno);
        n->sval = $1;
        n->left = $3;
        $$ = n;
    }
    ;

expression:
    primary_expression                    { $$ = $1; }
    | expression PLUS  expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_PLUS;  n->left=$1; n->right=$3; $$=n; }
    | expression MINUS expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_MINUS; n->left=$1; n->right=$3; $$=n; }
    | expression MULT  expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_MULT;  n->left=$1; n->right=$3; $$=n; }
    | expression DIV   expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_DIV;   n->left=$1; n->right=$3; $$=n; }
    | expression MOD   expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_MOD;   n->left=$1; n->right=$3; $$=n; }
    | expression AND   expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_AND;   n->left=$1; n->right=$3; $$=n; }
    | expression OR    expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_OR;    n->left=$1; n->right=$3; $$=n; }
    | expression EQUAL         expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_EQ;    n->left=$1; n->right=$3; $$=n; }
    | expression NOT_EQUAL     expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_NEQ;   n->left=$1; n->right=$3; $$=n; }
    | expression GREATER       expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_GT;    n->left=$1; n->right=$3; $$=n; }
    | expression LESS          expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_LT;    n->left=$1; n->right=$3; $$=n; }
    | expression GREATER_EQUAL expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_GTE;   n->left=$1; n->right=$3; $$=n; }
    | expression LESS_EQUAL    expression
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_LTE;   n->left=$1; n->right=$3; $$=n; }
    | expression FROM expression
    {
        node_free($3);
        $$ = $1;
    }
    | NOT expression
    {
        AstNode *n = node_new(N_UNARY_NOT, yylineno);
        n->left = $2;
        $$ = n;
    }
    | MINUS expression %prec UMINUS
    {
        AstNode *n = node_new(N_UNARY_NEG, yylineno);
        n->left = $2;
        $$ = n;
    }
    ;

primary_expression:
    INT_LITERAL
    {
        AstNode *n = node_new(N_INT_LIT, yylineno);
        n->ival = $1;
        $$ = n;
    }
    | FLOAT_LITERAL
    {
        AstNode *n = node_new(N_FLOAT_LIT, yylineno);
        n->fval = $1;
        $$ = n;
    }
    | STRING_LITERAL
    {
        AstNode *n = node_new(N_STRING_LIT, yylineno);
        n->sval = $1;
        $$ = n;
    }
    | CHAR_LITERAL
    {
        AstNode *n = node_new(N_CHAR_LIT, yylineno);
        n->sval = $1;
        $$ = n;
    }
    | IDENTIFIER
    {
        AstNode *n = node_new(N_IDENT, yylineno);
        n->sval = $1;
        $$ = n;
    }
    | BOOL_TRUE
    {
        AstNode *n = node_new(N_BOOL_LIT, yylineno);
        n->ival = 1;
        $$ = n;
    }
    | BOOL_FALSE
    {
        AstNode *n = node_new(N_BOOL_LIT, yylineno);
        n->ival = 0;
        $$ = n;
    }
    | array_access             { $$ = $1; }
    | function_call            { $$ = $1; }
    | math_function            { $$ = $1; }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

math_function:
    POW LPAREN expression COMMA expression RPAREN
    {
        AstNode *n = node_new(N_MATH_POW, yylineno);
        n->left  = $3;
        n->right = $5;
        $$ = n;
    }
    | SQRT LPAREN expression RPAREN
    {
        AstNode *n = node_new(N_MATH_SQRT, yylineno);
        n->left = $3;
        $$ = n;
    }
    | FLOOR LPAREN expression RPAREN
    {
        AstNode *n = node_new(N_MATH_FLOOR, yylineno);
        n->left = $3;
        $$ = n;
    }
    | CEIL LPAREN expression RPAREN
    {
        AstNode *n = node_new(N_MATH_CEIL, yylineno);
        n->left = $3;
        $$ = n;
    }
    | ABS LPAREN expression RPAREN
    {
        AstNode *n = node_new(N_MATH_ABS, yylineno);
        n->left = $3;
        $$ = n;
    }
    | LENGTH LPAREN IDENTIFIER RPAREN
    {
        AstNode *n = node_new(N_ARRAY_LEN, yylineno);
        n->sval = $3;
        $$ = n;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "ত্রুটি (লাইন %d): সিনট্যাক্স ত্রুটি (%s)\n", yylineno, s);
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
    const char *input_path = NULL;
    const char *ir_path = "ir.out.txt";

    /* Switch the Windows console to UTF-8 so Bengali input/output is not
       mangled into '?' by the default ANSI code page. Works in both
       Windows Terminal and MSYS2 mintty. */
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    setlocale(LC_ALL, "en_US.UTF-8");
    /* Keep stdout/stderr in binary mode to prevent \r\n mangling.
       Do NOT set stdin to binary — let the console CP handle encoding. */
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stderr), _O_BINARY);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ir") == 0) {
            g_emit_ir = 1;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                ir_path = argv[i + 1];
                i++;
            }
            continue;
        }

        if (!input_path) {
            input_path = argv[i];
            continue;
        }

        fprintf(stderr, "ত্রুটি: অপ্রত্যাশিত আর্গুমেন্ট '%s'\n", argv[i]);
        fprintf(stderr, "ব্যবহার: %s <input_file> [--ir [ir_output_file]]\n", argv[0]);
        return 1;
    }

    if (!input_path) {
        fprintf(stderr, "ব্যবহার: %s <input_file> [--ir [ir_output_file]]\n", argv[0]);
        return 1;
    }

    if (g_emit_ir) {
        g_ir_path = ir_path;
        g_ir_out = fopen(g_ir_path, "w");
        if (!g_ir_out) {
            fprintf(stderr, "ত্রুটি: IR আউটপুট ফাইল '%s' খোলা যায়নি।\n", g_ir_path);
            return 1;
        }
    }
    
    FILE *fp = fopen(input_path, "r");
    if (!fp) {
        fprintf(stderr, "ত্রুটি: ইনপুট ফাইল '%s' খোলা যায়নি।\n", input_path);
        if (g_ir_out) {
            fclose(g_ir_out);
            g_ir_out = NULL;
        }
        return 1;
    }
    
    /* Normalize Unicode before parsing */
    yyin = normalize_input(fp);  /* fp is closed inside normalize_input */
    init_indent();  /* Initialize indentation tracking */
    
    printf("=== Parsing Bangla Program ===\n\n");

    symtable_init();   /* initialise global symbol table */
    func_table_init(); /* initialise user-defined function table */

    int result = yyparse();

    symtable_free();   /* release all symbol table memory */
    func_table_free(); /* release all function table memory */
    fclose(yyin);

    if (g_ir_out) {
        fclose(g_ir_out);
        g_ir_out = NULL;
        printf("IR লেখা হয়েছে: %s\n", g_ir_path ? g_ir_path : "ir.out.txt");
    }

    if (result == 0) {
        printf("\n=== Parsing Complete ===\n");
        return 0;
    } else {
        printf("\n=== Parsing Failed ===\n");
        return 1;
    }
}
