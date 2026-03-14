# বর্ণমালা (Barnomala) — AST Runtime Detailed Explanation (ast.c)

This file is the execution engine for AST nodes.

It is large, so this guide follows code order and explains each logical code block in the same snippet+purpose style.

---

## Includes and forward declarations

```c
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
```
Purpose:
- Imports AST/runtime interfaces and C utility/math APIs used by evaluator.

```c
static Value eval_binop(Value a, int op, Value b);
```
Purpose:
- Private binary-operator helper declared before use.

---

## Strict condition type checker

```c
static int eval_condition_bool(AstNode *cond_node, const char *ctx_name)
```
Purpose:
- Evaluates a condition expression and enforces boolean type.

Important lines:
- `Value cond = eval_expr(cond_node);` computes condition value.
- `if (cond.type != TYPE_BOOL)` rejects non-boolean conditions.
- Prints Bengali error with source line and context name (`যদি`, `যতক্ষণ`).
- Returns `-1` on type error, `0/1` on valid bool.

This block implements the requested boolean-condition enforcement fix.

---

## Function table implementation

### Table storage

```c
#define FUNC_TABLE_SIZE 64
static FuncEntry *func_table[FUNC_TABLE_SIZE];
```
Purpose:
- Hash table buckets for function definitions.

### Hashing

```c
static unsigned int func_hash(const char *key)
```
Purpose:
- FNV-1a hash over function name bytes.

### `func_table_init`
- Clears table buckets via `memset`.

### `func_table_free`
- Frees all function entries and owned AST subtrees.

### `func_table_define`
- Rejects duplicate function names.
- Stores ownership of `name`, `params`, and `body`.

### `func_table_lookup`
- Returns matching function entry or NULL.

---

## Helper functions

### `is_truthy`
- Legacy numeric truthiness helper retained in file.

### `bengali_digits_to_ascii`
- Converts UTF-8 Bengali digits in input buffers to ASCII digits before numeric parse.

---

## Node lifecycle

### `node_new`
- Allocates zeroed node.
- Sets kind and source line.

### `node_free`
- Recursive free of `left/right/extra`.
- Frees `sval` if owned.
- Frees node itself.

---

## Expression evaluator (`eval_expr`)

Entry behavior:
- NULL node returns `make_unknown()`.

### Literal cases
- `N_INT_LIT`: `make_int(ival)`
- `N_FLOAT_LIT`: `make_float(fval)`
- `N_STRING_LIT`: `make_string(sval)`
- `N_CHAR_LIT`: `make_char(sval)`
- `N_BOOL_LIT`: `make_bool(ival)`

### Identifier case

```c
case N_IDENT: {
    SymbolEntry *e = lookup_variable(n->sval);
    return e ? copy_value(e->value) : make_unknown();
}
```
Purpose:
- Symbol read with deep copy.
- Missing symbol maps to unknown.

### Binary case
- Recursively evaluates both sides and delegates to `eval_binop`.

### Unary NOT/NEG
- NOT: zero/non-zero mapped to bool.
- NEG: numeric sign inversion with type-preserving result.

### Math builtins
- `pow/sqrt/floor/ceil/abs` with numeric conversion from int/decimal values.

### Array builtins
- `N_ARRAY_LEN`: validates target is array and returns size.
- `N_ARRAY_ACCESS`: validates array existence/type, evaluates index, checks bounds, returns copied element.

### Function call (`N_CALL`)

Flow block:
1. Lookup function entry.
2. Evaluate argument expressions before scope push.
3. Push fresh scope.
4. Bind parameters to evaluated args.
5. Execute body (`exec_stmt`).
6. Pop scope.
7. Return function return value (or default 0 for no explicit return).

Ownership handling:
- evaluated argument values are freed after binding.
- return value ownership transferred carefully.

---

## Statement executor (`exec_stmt`)

Entry behavior:
- Initializes `ok = EXEC_NORMAL`.
- NULL node returns normal.

### Structural nodes
- `N_NOP`: no-op.
- `N_SEQ`: execute left then right; propagate non-normal signals.

### Variable and output/input
- `N_DECL`: declare variable and optional initializer assignment.
- `N_ASSIGN`: evaluate RHS then assign.
- `N_PRINT`: evaluate and print + newline.
- `N_INPUT`: type-based input parsing and assignment.

Input parsing per declared type:
- number/decimal: `fgets` + Bengali-digit normalization + `atoi/atof`.
- string: full line input.
- bool: integer scan then bool coercion.

### Conditionals and loops

#### `N_IF`
- condition evaluated via `eval_condition_bool` (strict bool).
- if type error: skip branch execution.
- executes then/else body accordingly.

#### `N_WHILE`
- per-iteration strict bool condition check.
- handles break/continue/return signal propagation.

#### `N_FOR_RANGE`
- ensures loop variable exists as number.
- evaluates start/end once.
- loops inclusively from start to end.
- executes body and handles break/continue/return.

### Jump statements
- `N_BREAK` returns `EXEC_BREAK`.
- `N_CONTINUE` returns `EXEC_CONTINUE`.
- `N_RETURN` returns `EXEC_RETURN` with optional expression value.

### Increment/decrement
- Supports number and decimal symbols.
- Emits Bengali error for non-numeric targets.

### Function definition
- Registers function via `func_table_define`.
- Transfers ownership by nulling pointers in AST node.

### Array declaration and assignment

`N_ARRAY_DECL` flow:
1. Allocate array Value and set element type/size.
2. Initialize default element values by element type.
3. Apply initializer list values if present.
4. Declare symbol and assign deep-copied array value.

`N_ARRAY_ASSIGN` flow:
- Validate target array.
- Evaluate and bounds-check index.
- Evaluate RHS and coerce to array element type.
- Replace element value safely.

### Call statement
- Evaluates call and discards result value.

---

## Binary operator evaluator (`eval_binop`)

### String concatenation special-case

When OP_PLUS and either side is string/char:
- converts both operands to text,
- strips wrapping quotes when present,
- concatenates into new string.

### Numeric path
- Determines float mode if any operand is decimal.
- Computes both float and int representations.
- Frees operand Values before switch return.

Supported ops:
- arithmetic: + - * / %
- logical: AND OR
- relational: == != > < >= <=

Safety checks:
- divide by zero and modulo by zero emit Bengali errors and return zero values.

---

## Final summary

ast.c is the semantic/runtime core:
- executes parsed AST directly,
- enforces condition type rules,
- implements function calls/scopes,
- handles arrays and builtins,
- and carries control-flow signals across nested statement execution.
