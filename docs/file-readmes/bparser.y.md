# বর্ণমালা (Barnomala) — Parser Explanation (bparser.y)

This document explains the bparser.y file in the same deep style as the lexer reference: code snippets plus exact purpose.

A parser's job is to consume tokens from the lexer, validate grammar, build AST nodes, and drive execution/IR generation.

---

## File Structure Overview

A Bison file has three major regions:

1. Prologue (`%{ ... %}`): C includes, globals, declarations.
2. Bison declarations: `%token`, `%type`, `%union`, precedence.
3. Grammar rules (`%% ... %%`): productions and AST actions.
4. User code: `yyerror`, normalization helper, `main`.

---

## Section 1: Prologue (`%{ ... %}`)

```c
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <fcntl.h>
```
Purpose:
- Imports C runtime features needed by parser actions and `main`.
- `math.h` supports runtime math builtins.
- `locale.h` + `fcntl.h` support UTF-8 console setup behavior.

```c
#ifdef _WIN32
extern unsigned int __stdcall SetConsoleCP(unsigned int wCodePageID);
extern unsigned int __stdcall SetConsoleOutputCP(unsigned int wCodePageID);
#endif
```
Purpose:
- Declares Windows console API functions for UTF-8 input/output code pages.

```c
#include "ast.h"
#include "irgen.h"
```
Purpose:
- `ast.h`: node types, constructors, eval/exec APIs.
- `irgen.h`: AST -> TAC lowering API used by `--ir` flow.

```c
void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern void init_indent();
```
Purpose:
- Declares parser callback and lexer globals/functions used by parser runtime.

```c
int suppress_execution = 0;
```
Purpose:
- Shared semantic flag used by symbol-table wrappers.

```c
static int   g_emit_ir = 0;
static FILE *g_ir_out = NULL;
static const char *g_ir_path = NULL;
%}
```
Purpose:
- CLI-driven IR output state.
- `g_emit_ir` enables IR emission path.
- `g_ir_out` and `g_ir_path` hold destination file stream/path.

---

## `%code requires` block

```c
%code requires {
#include "ast.h"
}
```
Purpose:
- Injects `ast.h` into generated parser header so lexer-side shared types remain compatible.

---

## `%union` semantic value model

```c
%union {
    int      intval;
    double   floatval;
    char    *strval;
    VarType  vtype;
    AstNode *node;
}
```
Purpose:
- Defines all semantic payload types carried by tokens/non-terminals.

---

## Token declarations

```c
%token PROGRAM_START PROGRAM_END
...
%token <intval> INT_LITERAL
%token <floatval> FLOAT_LITERAL
%token <strval> STRING_LITERAL CHAR_LITERAL IDENTIFIER
```
Purpose:
- Declares full token vocabulary from lexer.
- Typed tokens carry semantic payload into parser rules.

---

## Non-terminal type declarations

```c
%type <node> expression primary_expression ...
%type <vtype> type
```
Purpose:
- Tells Bison which `%union` field each non-terminal uses.

---

## Precedence and associativity

```c
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
...
%left PLUS MINUS
%left MULT DIV MOD
%right NOT
%right UMINUS
```
Purpose:
- Resolves expression ambiguity and dangling-else behavior.
- Ensures operator parse tree shape matches language intent.

---

## Section 2: Grammar rules

### `program` rule

```c
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
```
Purpose:
- Top-level orchestration when grammar accepts full program.
- Optional IR generation path from AST.
- Runtime AST execution.
- Resource cleanup.

Second variant allows missing leading `newlines` non-terminal path.

---

### `newlines` / `optional_newlines`

These normalize leading/trailing blank lines so parser remains robust to file formatting differences.

---

### `statements`

```c
statements:
    /* empty */ { $$ = NULL; }
    | statements statement
```
Purpose:
- Builds left-recursive sequence chain.
- Converts statement list into nested `N_SEQ` nodes.

---

### `statement`, `simple_statement`, `compound_statement`

Purpose:
- Splits line-terminated statements from block statements.
- Makes grammar cleaner and supports indentation suites.

`function_call SEMICOLON` becomes `N_CALL_STMT` (discarding return value semantics at statement level).

---

### Declaration and assignment rules

`declaration`:
- `type IDENTIFIER` -> `N_DECL` with no initializer.
- `type IDENTIFIER ASSIGN expression` -> `N_DECL` with initializer in `left`.

`assignment`:
- `IDENTIFIER ASSIGN expression` -> `N_ASSIGN`.

---

### Input/print rules

- `INPUT LPAREN IDENTIFIER RPAREN` -> `N_INPUT`.
- `PRINT expression` -> `N_PRINT`.

---

### `suite` rule

```c
suite:
    simple_statement NEWLINE
    | NEWLINE INDENT statements DEDENT
```
Purpose:
- Supports one-line suite or indented multi-line block.
- Consumes lexer-generated INDENT/DEDENT tokens.

---

### If/else rules

`if_header` captures condition node only.

`if_statement`:
- without else -> `N_IF` with `extra = NULL`.
- with else -> `N_IF` with `extra = else-body`.

---

### Loop rules

- `while_statement` -> `N_WHILE` with condition and body.
- `for_statement` -> `N_FOR_RANGE` with loop var, start, end, body.

---

### Function rules

- `function_definition` builds `N_FUNCDEF`.
- `parameter_list` builds right-linked `N_PARAM_LIST` chain.
- `function_call` builds `N_CALL` with right-linked argument list.
- `argument_list` uses `N_ARG_LIST` nodes.

---

### Flow control statement rules

- `RETURN expression` -> `N_RETURN`.
- `BREAK` -> `N_BREAK`.
- `CONTINUE` -> `N_CONTINUE`.
- increment/decrement rules -> `N_INC` / `N_DEC`.

---

### Array rules

- `array_declaration` builds `N_ARRAY_DECL` including element type and size.
- initializer list becomes `N_INIT_LIST` chain.
- `array_access` builds `N_ARRAY_ACCESS`.
- `array_assignment` builds `N_ARRAY_ASSIGN`.

---

### Expression rules

Binary operations:
- each production constructs `N_BINOP` and sets `ival = OP_*`.

Unary operations:
- `NOT expression` -> `N_UNARY_NOT`.
- `MINUS expression %prec UMINUS` -> `N_UNARY_NEG`.

`expression FROM expression`:
- grammar convenience path used by range syntax; drops right side in expression context.

---

### Primary expressions

- literal tokens map to corresponding AST literal nodes.
- identifier maps to `N_IDENT`.
- array/function/math dispatch to specialized non-terminals.
- parenthesized expression returns inner node.

---

### Math function rules

- `POW(...)` -> `N_MATH_POW`
- `SQRT(...)` -> `N_MATH_SQRT`
- `FLOOR(...)` -> `N_MATH_FLOOR`
- `CEIL(...)` -> `N_MATH_CEIL`
- `ABS(...)` -> `N_MATH_ABS`
- `LENGTH(IDENTIFIER)` -> `N_ARRAY_LEN`

---

## Section 3: User C code (after second `%%`)

### `yyerror`

```c
void yyerror(const char *s) {
    fprintf(stderr, "ত্রুটি (লাইন %d): সিনট্যাক্স ত্রুটি (%s)\n", yylineno, s);
}
```
Purpose:
- Standardized Bengali syntax error diagnostics with line number.

---

### `normalize_input`

Purpose:
- Reads full source bytes.
- Rewrites selected precomposed Bengali characters into decomposed forms.
- Returns temp-file stream containing normalized bytes.

Why:
- Keeps lexer/parser behavior stable across equivalent Unicode representations.

---

### `main`

Key flow:
1. Parse args (`<input_file> [--ir [ir_output_file]]`).
2. Configure UTF-8 console behavior on Windows.
3. Open IR output stream if requested.
4. Open input file; normalize to temp stream.
5. Init indentation state + runtime tables.
6. Call `yyparse()`.
7. Free tables/streams.
8. Print final success/failure and IR-path message.

---

## Summary

bparser.y is both:
- grammar definition
- runtime coordinator

It builds AST from Bangla source, optionally lowers AST to TAC file, then executes the AST interpreter path.
