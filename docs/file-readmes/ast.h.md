# বর্ণমালা (Barnomala) — AST Header Detailed Explanation (ast.h)

This guide explains ast.h in the same style as the lexer reference: snippet first, then exact purpose.

---

## Header skeleton

```c
#ifndef AST_H
#define AST_H
...
#endif /* AST_H */
```
Purpose:
- Prevents duplicate declarations from repeated includes.

```c
#include "symtable.h"
```
Purpose:
- Imports Value and VarType used by AST execution interfaces.

---

## Shared operator constants

```c
#define OP_PLUS  1
...
#define OP_LTE  13
```
Purpose:
- Compact operator IDs shared between parser-created AST and runtime evaluator.
- Parser writes these IDs to `N_BINOP.ival`.
- Runtime switches on these IDs in binary evaluation.

---

## `NodeKind` enum

```c
typedef enum { ... } NodeKind;
```
Purpose:
- Enumerates all legal AST node kinds.

Expression kinds:
- literals (int/float/string/char/bool)
- identifier
- binary/unary operators
- function call
- math builtins
- array length/access
- argument list nodes

Statement kinds:
- sequence
- declaration/assignment
- print/input
- if/while/for
- break/continue/return
- inc/dec
- function definition + param list
- array declaration/init/assignment
- call-as-statement
- no-op

Comments in enum describe where each node stores payload.

---

## `AstNode` struct

```c
typedef struct AstNode {
    NodeKind kind;
    int      ival;
    double   fval;
    char    *sval;
    VarType  vtype;
    int      lineno;
    struct AstNode *left;
    struct AstNode *right;
    struct AstNode *extra;
} AstNode;
```

Field meanings:
- `kind`: identifies node semantics.
- `ival`: int literal / bool literal / OP_* code.
- `fval`: float literal.
- `sval`: heap string for identifiers and text literals.
- `vtype`: declaration type metadata.
- `lineno`: parser line for diagnostics.
- `left`, `right`, `extra`: generic tree links; semantics depend on `kind`.

---

## Execution signal model

```c
typedef enum {
    EXEC_NORMAL,
    EXEC_BREAK,
    EXEC_CONTINUE,
    EXEC_RETURN,
} ExecSignal;
```
Purpose:
- Encodes control transfer for recursive statement execution.

```c
typedef struct {
    ExecSignal signal;
    Value      retval;
} ExecResult;
```
Purpose:
- Carries signal and optional return value up the call chain.

---

## AST lifecycle API

```c
AstNode *node_new(NodeKind kind, int lineno);
void     node_free(AstNode *n);
```
Purpose:
- Standardized creation/freeing of AST nodes.

---

## Function table types and API

```c
typedef struct FuncEntry {
    char             *name;
    AstNode          *params;
    AstNode          *body;
    struct FuncEntry *next;
} FuncEntry;
```
Purpose:
- Runtime storage record for user-defined functions.

API:
- init/free table
- define function
- lookup function by name

Ownership note:
- function entries own name/params/body pointers once inserted.

---

## Interpreter APIs

```c
Value      eval_expr (AstNode *n);
ExecResult exec_stmt (AstNode *n);
```
Purpose:
- `eval_expr`: compute expression value.
- `exec_stmt`: execute statement subtree and propagate control-flow events.

