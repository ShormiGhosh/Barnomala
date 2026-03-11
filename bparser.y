%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <fcntl.h>
#ifdef _WIN32
/* Declare only what we need — including <windows.h> clashes with the
   Bison INPUT token because winuser.h also typedef-s a struct INPUT. */
extern unsigned int __stdcall SetConsoleCP(unsigned int wCodePageID);
extern unsigned int __stdcall SetConsoleOutputCP(unsigned int wCodePageID);
#endif
#include "symtable.h"   /* needed here so Value is visible in this prologue */

/* Op-code constants for eval_binop */
#define OP_PLUS  1
#define OP_MINUS 2
#define OP_MULT  3
#define OP_DIV   4
#define OP_MOD   5
#define OP_AND   6
#define OP_OR    7
#define OP_EQ    8
#define OP_NEQ   9
#define OP_GT   10
#define OP_LT   11
#define OP_GTE  12
#define OP_LTE  13

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern void init_indent();

/* Forward declaration — defined after the second %% */
static Value eval_binop(Value a, int op, Value b);

/* ------------------------------------------------------------------ */
/*  Execution suppression for if/else branching                        */
/*  suppress_execution > 0  →  all side effects are no-ops.           */
/*  nested ifs increment/decrement the counter, so nesting is safe.   */
/* ------------------------------------------------------------------ */
int suppress_execution = 0;          /* definition; extern in symtable.h */
static int cond_stack[256];
static int cond_top = 0;

static int is_truthy(Value v) {
    if (v.type == TYPE_DECIMAL) return v.data.floatval != 0.0;
    return v.data.intval != 0;
}

/* ------------------------------------------------------------------ */
/*  Bengali digit → ASCII conversion for runtime input                 */
/*  Bengali digits U+09E6–U+09EF are encoded as 3-byte UTF-8 sequences */
/*  E0 A7 A6 … E0 A7 AF. Replace each with its ASCII equivalent.      */
/* ------------------------------------------------------------------ */
static void bengali_digits_to_ascii(char *buf) {
    unsigned char *s = (unsigned char *)buf;
    unsigned char tmp[1024];
    int j = 0;
    for (int i = 0; s[i]; ) {
        /* Bengali digit: E0 A7 (A6..AF) */
        if (s[i] == 0xE0 && s[i+1] == 0xA7 && s[i+2] >= 0xA6 && s[i+2] <= 0xAF) {
            tmp[j++] = '0' + (s[i+2] - 0xA6);
            i += 3;
        } else {
            tmp[j++] = s[i++];
        }
    }
    tmp[j] = '\0';
    memcpy(buf, tmp, j + 1);
}
%}

/* symtable.h must also go into bparser.tab.h so blexer.l can see Value/VarType */
%code requires {
#include "symtable.h"
}

%union {
    int    intval;
    double floatval;
    char  *strval;
    Value   val;    /* runtime value  — used by expression rules */
    VarType vtype;  /* declared type  — used by the 'type' rule   */
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

/* Non-terminal semantic types */
%type <val>   expression primary_expression math_function array_access function_call
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
        if (!suppress_execution) declare_variable($2, $1);
        free($2);
    }
    | type IDENTIFIER ASSIGN expression SEMICOLON
    {
        if (!suppress_execution) {
            declare_variable($2, $1);
            assign_variable($2, $4);
        }
        free_value($4);
        free($2);
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
        if (!suppress_execution) assign_variable($1, $3);
        free_value($3);
        free($1);
    }
    ;

input_statement:
    INPUT LPAREN IDENTIFIER RPAREN SEMICOLON
    {
        if (!suppress_execution) {
        /* Use raw lookup — this is write access (initialization), not a read.
           lookup_variable would emit a spurious "uninitialized" warning here. */
        SymbolEntry *e = symtable_lookup($3);
        if (!e) {
            fprintf(stderr, "ত্রুটি (লাইন %d): '%s' ঘোষণা করা হয়নি।\n", yylineno, $3);
        } else {
            switch (e->type) {
                case TYPE_NUMBER: {
                    char buf[64];
                    if (fgets(buf, sizeof(buf), stdin)) {
                        buf[strcspn(buf, "\n")] = '\0';
                        bengali_digits_to_ascii(buf);
                        assign_variable($3, make_int(atoi(buf)));
                    }
                    break;
                }
                case TYPE_DECIMAL: {
                    char buf[64];
                    if (fgets(buf, sizeof(buf), stdin)) {
                        buf[strcspn(buf, "\n")] = '\0';
                        bengali_digits_to_ascii(buf);
                        assign_variable($3, make_float(atof(buf)));
                    }
                    break;
                }
                case TYPE_STRING: {
                    char buf[1024];
                    if (fgets(buf, sizeof(buf), stdin)) {
                        buf[strcspn(buf, "\n")] = '\0';
                        assign_variable($3, make_string(buf));
                    }
                    break;
                }
                case TYPE_BOOL: {
                    int v = 0;
                    if (scanf("%d", &v) == 1)
                        assign_variable($3, make_bool(v));
                    break;
                }
                default: break;
            }
        }
        } /* end if (!suppress_execution) */
        free($3);
    }
    ;

print_statement:
    PRINT expression SEMICOLON
    {
        if (!suppress_execution) {
            print_value($2);
            printf("\n");
        }
        free_value($2);
    }
    ;

suite:
    simple_statement NEWLINE
    | NEWLINE INDENT statements DEDENT
    ;

if_header:
    IF expression COLON
    {
        int cond = is_truthy($2);
        free_value($2);
        cond_stack[cond_top++] = cond;
        if (!cond) suppress_execution++;
    }
    ;

else_header:
    ELSE COLON
    {
        int cond = cond_stack[cond_top - 1];   /* peek — do NOT pop yet */
        if (!cond) suppress_execution--;        /* undo then-suppression  */
        if ( cond) suppress_execution++;        /* start else-suppression */
    }
    ;

if_statement:
    if_header suite %prec LOWER_THAN_ELSE
    {
        int cond = cond_stack[--cond_top];
        if (!cond) suppress_execution--;
    }
    | if_header suite else_header suite
    {
        int cond = cond_stack[--cond_top];
        if ( cond) suppress_execution--;        /* undo else-suppression  */
    }
    ;

while_statement:
    WHILE expression COLON suite
    {
        free_value($2);
    }
    ;

for_statement:
    FOR_RANGE LPAREN IDENTIFIER RPAREN expression FROM expression COLON suite
    {
        /* auto-declare loop variable if it wasn't declared by the user */
        if (!symtable_lookup($3))
            declare_variable($3, TYPE_NUMBER);
        free_value($5); free_value($7);
        free($3);
    }
    ;

function_definition:
    FUNCTION IDENTIFIER LPAREN parameter_list RPAREN COLON suite
    {
        free($2);
    }
    | FUNCTION IDENTIFIER LPAREN RPAREN COLON suite
    {
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
        free($1);
        $$ = make_unknown();  /* function execution not yet implemented */
    }
    | IDENTIFIER LPAREN RPAREN
    {
        free($1);
        $$ = make_unknown();
    }
    ;

argument_list:
    expression                       { free_value($1); }
    | argument_list COMMA expression { free_value($3); }
    ;

return_statement:
    RETURN expression SEMICOLON
    {
        free_value($2);
    }
    ;

break_statement:
    BREAK SEMICOLON
    {
        if (!suppress_execution) printf("Break statement\n");
    }
    ;

continue_statement:
    CONTINUE SEMICOLON
    {
        if (!suppress_execution) printf("Continue statement\n");
    }
    ;

increment_statement:
    IDENTIFIER INC SEMICOLON
    {
        if (!suppress_execution) {
            SymbolEntry *e = lookup_variable($1);
            if (e) {
                if (e->type == TYPE_NUMBER)
                    assign_variable($1, make_int(e->value.data.intval + 1));
                else if (e->type == TYPE_DECIMAL)
                    assign_variable($1, make_float(e->value.data.floatval + 1.0));
                else
                    fprintf(stderr, "ত্রুটি (লাইন %d): '%s' সংখ্যা বা দশমিক নয়, বাড়ানো যাবে না।\n", yylineno, $1);
            }
        }
        free($1);
    }
    ;

decrement_statement:
    IDENTIFIER DEC SEMICOLON
    {
        if (!suppress_execution) {
            SymbolEntry *e = lookup_variable($1);
            if (e) {
                if (e->type == TYPE_NUMBER)
                    assign_variable($1, make_int(e->value.data.intval - 1));
                else if (e->type == TYPE_DECIMAL)
                    assign_variable($1, make_float(e->value.data.floatval - 1.0));
                else
                    fprintf(stderr, "ত্রুটি (লাইন %d): '%s' সংখ্যা বা দশমিক নয়, কমানো যাবে না।\n", yylineno, $1);
            }
        }
        free($1);
    }
    ;

array_declaration:
    ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET SEMICOLON
    {
        /* Arrays not yet backed by runtime storage — parsed only */
        free($5);
    }
    | ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET ASSIGN LBRACKET array_elements RBRACKET SEMICOLON
    {
        free($5);
    }
    ;

array_elements:
    expression                       { free_value($1); }
    | array_elements COMMA expression { free_value($3); }
    ;

array_access:
    IDENTIFIER LBRACKET expression RBRACKET
    {
        free_value($3);
        free($1);
        $$ = make_unknown();  /* array runtime not yet implemented */
    }
    ;

expression:
    primary_expression                    { $$ = $1; }
    | expression PLUS  expression         { $$ = eval_binop($1, OP_PLUS,  $3); }
    | expression MINUS expression         { $$ = eval_binop($1, OP_MINUS, $3); }
    | expression MULT  expression         { $$ = eval_binop($1, OP_MULT,  $3); }
    | expression DIV   expression         { $$ = eval_binop($1, OP_DIV,   $3); }
    | expression MOD   expression         { $$ = eval_binop($1, OP_MOD,   $3); }
    | expression AND   expression         { $$ = eval_binop($1, OP_AND,   $3); }
    | expression OR    expression         { $$ = eval_binop($1, OP_OR,    $3); }
    | expression EQUAL         expression { $$ = eval_binop($1, OP_EQ,    $3); }
    | expression NOT_EQUAL     expression { $$ = eval_binop($1, OP_NEQ,   $3); }
    | expression GREATER       expression { $$ = eval_binop($1, OP_GT,    $3); }
    | expression LESS          expression { $$ = eval_binop($1, OP_LT,    $3); }
    | expression GREATER_EQUAL expression { $$ = eval_binop($1, OP_GTE,   $3); }
    | expression LESS_EQUAL    expression { $$ = eval_binop($1, OP_LTE,   $3); }
    | expression FROM expression          { free_value($3); $$ = $1; }
    | NOT expression
    {
        int bval;
        if      ($2.type == TYPE_DECIMAL) bval = ($2.data.floatval == 0.0) ? 1 : 0;
        else if ($2.type == TYPE_BOOL)    bval = ($2.data.intval   == 0)   ? 1 : 0;
        else                              bval = ($2.data.intval   == 0)   ? 1 : 0;
        free_value($2);
        $$ = make_bool(bval);
    }
    | MINUS expression %prec UMINUS
    {
        if ($2.type == TYPE_DECIMAL) $$ = make_float(-$2.data.floatval);
        else                         $$ = make_int  (-$2.data.intval);
        free_value($2);
    }
    ;

primary_expression:
    INT_LITERAL              { $$ = make_int($1); }
    | FLOAT_LITERAL          { $$ = make_float($1); }
    | STRING_LITERAL         { $$ = make_string($1); free($1); }
    | CHAR_LITERAL           { $$ = make_char($1);   free($1); }
    | IDENTIFIER
    {
        /* lookup_variable reports undeclared-use and uninitialized-read errors */
        SymbolEntry *e = lookup_variable($1);
        $$ = e ? copy_value(e->value) : make_unknown();
        free($1);
    }
    | BOOL_TRUE              { $$ = make_bool(1); }
    | BOOL_FALSE             { $$ = make_bool(0); }
    | array_access           { $$ = $1; }
    | function_call          { $$ = $1; }
    | math_function          { $$ = $1; }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

math_function:
    POW LPAREN expression COMMA expression RPAREN
    {
        double base = ($3.type == TYPE_DECIMAL) ? $3.data.floatval : (double)$3.data.intval;
        double exp  = ($5.type == TYPE_DECIMAL) ? $5.data.floatval : (double)$5.data.intval;
        free_value($3); free_value($5);
        $$ = make_float(pow(base, exp));
    }
    | SQRT LPAREN expression RPAREN
    {
        double v = ($3.type == TYPE_DECIMAL) ? $3.data.floatval : (double)$3.data.intval;
        free_value($3);
        $$ = make_float(sqrt(v));
    }
    | FLOOR LPAREN expression RPAREN
    {
        double v = ($3.type == TYPE_DECIMAL) ? $3.data.floatval : (double)$3.data.intval;
        free_value($3);
        $$ = make_int((int)floor(v));
    }
    | CEIL LPAREN expression RPAREN
    {
        double v = ($3.type == TYPE_DECIMAL) ? $3.data.floatval : (double)$3.data.intval;
        free_value($3);
        $$ = make_int((int)ceil(v));
    }
    | ABS LPAREN expression RPAREN
    {
        if ($3.type == TYPE_DECIMAL) {
            $$ = make_float(fabs($3.data.floatval));
        } else {
            $$ = make_int(abs($3.data.intval));
        }
        free_value($3);
    }
    ;

%%

/* ================================================================== */
/*  Runtime binary-operator evaluator                                  */
/* ================================================================== */
static Value eval_binop(Value a, int op, Value b)
{
    /* ---- String concatenation for PLUS ---- */
    if (op == OP_PLUS &&
        (a.type == TYPE_STRING || b.type == TYPE_STRING ||
         a.type == TYPE_CHAR   || b.type == TYPE_CHAR)) {
        char buf[4096] = {0};

        /* Helper: append a Value's text to buf */
        #define APPEND_VAL(v)  do {                                    \
            if ((v).type == TYPE_STRING || (v).type == TYPE_CHAR) {    \
                const char *s = (v).data.strval ? (v).data.strval : "";\
                size_t len = strlen(s);                                 \
                if (len >= 2 && (s[0]=='"'||s[0]=='\''))               \
                    strncat(buf, s+1, len-2);                          \
                else strcat(buf, s);                                    \
            } else if ((v).type == TYPE_DECIMAL) {                     \
                char tmp[64]; snprintf(tmp,sizeof(tmp),"%g",(v).data.floatval); strcat(buf,tmp); \
            } else {                                                    \
                char tmp[64]; snprintf(tmp,sizeof(tmp),"%d",(v).data.intval);   strcat(buf,tmp); \
            }                                                           \
        } while(0)

        APPEND_VAL(a);
        APPEND_VAL(b);
        #undef APPEND_VAL
        free_value(a); free_value(b);
        return make_string(buf);
    }

    /* ---- Numeric promotion ---- */
    int   use_float = (a.type == TYPE_DECIMAL || b.type == TYPE_DECIMAL);
    double av = (a.type == TYPE_DECIMAL) ? a.data.floatval : (double)a.data.intval;
    double bv = (b.type == TYPE_DECIMAL) ? b.data.floatval : (double)b.data.intval;
    int    ai = (a.type == TYPE_BOOL || a.type == TYPE_NUMBER) ? a.data.intval : (int)av;
    int    bi = (b.type == TYPE_BOOL || b.type == TYPE_NUMBER) ? b.data.intval : (int)bv;
    free_value(a); free_value(b);

    switch (op) {
        case OP_PLUS:
            return use_float ? make_float(av + bv) : make_int(ai + bi);
        case OP_MINUS:
            return use_float ? make_float(av - bv) : make_int(ai - bi);
        case OP_MULT:
            return use_float ? make_float(av * bv) : make_int(ai * bi);
        case OP_DIV:
            if (use_float) {
                if (bv == 0.0) { fprintf(stderr, "ত্রুটি: শূন্য দিয়ে ভাগ।\n"); return make_float(0); }
                return make_float(av / bv);
            } else {
                if (bi == 0) { fprintf(stderr, "ত্রুটি: শূন্য দিয়ে ভাগ।\n"); return make_int(0); }
                return make_int(ai / bi);
            }
        case OP_MOD:
            if (bi == 0) { fprintf(stderr, "ত্রুটি: শূন্য দিয়ে মডুলাস।\n"); return make_int(0); }
            return make_int(ai % bi);
        case OP_AND:  return make_bool(ai != 0 && bi != 0);
        case OP_OR:   return make_bool(ai != 0 || bi != 0);
        case OP_EQ:   return use_float ? make_bool(av == bv) : make_bool(ai == bi);
        case OP_NEQ:  return use_float ? make_bool(av != bv) : make_bool(ai != bi);
        case OP_GT:   return use_float ? make_bool(av >  bv) : make_bool(ai >  bi);
        case OP_LT:   return use_float ? make_bool(av <  bv) : make_bool(ai <  bi);
        case OP_GTE:  return use_float ? make_bool(av >= bv) : make_bool(ai >= bi);
        case OP_LTE:  return use_float ? make_bool(av <= bv) : make_bool(ai <= bi);
        default:      return make_unknown();
    }
}

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

    symtable_init();   /* initialise global symbol table */

    int result = yyparse();

    symtable_free();   /* release all symbol table memory */
    fclose(yyin);

    if (result == 0) {
        printf("\n=== Parsing Complete ===\n");
        return 0;
    } else {
        printf("\n=== Parsing Failed ===\n");
        return 1;
    }
}
