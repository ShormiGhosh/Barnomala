# বর্ণমালা (Barnomala) — Symbol Table Header Detailed Explanation (symtable.h)

This header defines the runtime type system and symbol-table API contract.

---

## Header guard

```c
#ifndef SYMTABLE_H
#define SYMTABLE_H
...
#endif
```
Purpose:
- Prevents duplicate declarations.

---

## Includes

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```
Purpose:
- Needed for FILE types and string/memory helpers used by declarations.

---

## `VarType` enum

```c
typedef enum {
    TYPE_NUMBER,
    TYPE_DECIMAL,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_ARRAY,
    TYPE_UNKNOWN
} VarType;
```
Purpose:
- Defines language runtime type tags.

---

## `Value` tagged-union model

```c
typedef struct Value Value;
struct Value {
    VarType type;
    union { ... } data;
};
```
Purpose:
- Stores one runtime value with type tag.
- Supports scalars and arrays.

Array payload fields:
- `elems`: heap array of `Value`.
- `size`: number of elements.
- `elem_type`: declared array element type.

---

## Value constructor API

```c
Value make_int(int v);
...
Value make_unknown(void);
```
Purpose:
- Standard constructors for all runtime value categories.

---

## Value helper API

```c
Value coerce(Value v, VarType target);
int   types_compatible(VarType declared, VarType given);
...
```
Purpose:
- conversion + compatibility checks.
- display/print.
- deep copy and deep free.

---

## Symbol-entry model

```c
typedef struct SymbolEntry {
    char *name;
    VarType type;
    Value value;
    int is_initialized;
    struct SymbolEntry *next;
} SymbolEntry;
```
Purpose:
- One variable binding record in hash-chain bucket.

---

## Scope model

```c
typedef struct Scope {
    SymbolEntry *table[SYMTABLE_SIZE];
    struct Scope *parent;
} Scope;
```
Purpose:
- One lexical scope with hash buckets and parent pointer for outward lookup.

---

## Core API

- init/push/pop/free scope stack.
- declare/declare_assign/assign/lookup symbol entries.
- debug dump.

---

## Semantic wrapper API

These wrap raw operations with semantic error meaning:
- `declare_variable`: redeclaration guard.
- `assign_variable`: undeclared/type mismatch checks.
- `lookup_variable`: undeclared/uninitialized diagnostics.

---

## `suppress_execution`

```c
extern int suppress_execution;
```
Purpose:
- Allows parser/runtime to silence side effects/messages in untaken branches.
