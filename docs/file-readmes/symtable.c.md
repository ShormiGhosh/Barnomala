# বর্ণমালা (Barnomala) — Symbol Table Runtime Detailed Explanation (symtable.c)

This file implements runtime value handling and scoped variable storage.

---

## Includes

```c
#include "symtable.h"
```
Purpose:
- Uses declarations/types from the symbol-table header.

---

## Hash function

```c
static unsigned int sym_hash(const char *key)
```
Purpose:
- Hashes UTF-8 variable names to bucket indexes.
- Uses FNV-1a steps for stable distribution.

Key lines:
- `h ^= (unsigned char)(*key++);`
- `h *= 16777619u;`
- `return h % SYMTABLE_SIZE;`

---

## Value constructors

### make_int / make_float / make_bool / make_char / make_string / make_unknown

Pattern in each function:
1. declare `Value val`.
2. `memset` to zero.
3. set `val.type`.
4. set active payload field.
5. return by value.

Notable behavior:
- `make_bool` normalizes any non-zero input to 1.
- `make_char` and `make_string` duplicate input strings.

---

## Value memory helpers

### free_value
- frees string/char heap memory.
- for arrays:
  - recursively frees each element value,
  - frees element array memory.

### copy_value
- deep-copies string/char types.
- deep-copies arrays element-by-element.
- returns numeric values directly for scalar types.

---

## Type display helper

### type_name
Maps internal VarType values to Bengali display names for diagnostics.

---

## Type compatibility rules

```c
int types_compatible(VarType declared, VarType given)
```

Current policy:
- same type: allowed.
- DECIMAL <- NUMBER: allowed (int to float promotion).
- BOOL <- NUMBER: allowed.
- NUMBER <- BOOL: allowed.
- ARRAY <- ARRAY: allowed.

Important restriction:
- NUMBER <- DECIMAL is not allowed (prevents silent truncation).

---

## Coercion rules

```c
Value coerce(Value v, VarType target)
```

Behavior by target:
- DECIMAL target: NUMBER promoted to float.
- NUMBER target: BOOL converted to int.
- BOOL target:
  - NUMBER -> bool,
  - DECIMAL -> bool.
- ARRAY target: deep copy.

If no coercion rule applies:
- returns deep copy as-is (caller reports mismatch).

---

## Output formatting helpers

### print_bengali
- rewrites ASCII digits in output strings to Bengali UTF-8 digits.

### print_value
Case behavior:
- TYPE_NUMBER: format int and print with Bengali digits.
- TYPE_DECIMAL: pretty formatting, then Bengali digits.
- TYPE_BOOL: prints সত্য or মিথ্যা.
- TYPE_CHAR/TYPE_STRING: prints text, stripping surrounding quotes if present.
- TYPE_ARRAY: recursive `[v1, v2, ...]` print.
- default: prints `<অজানা>`.

---

## Scope stack storage

```c
static Scope *current_scope = NULL;
```
Purpose:
- Points to active innermost scope.

### symtable_init
- frees any existing scopes,
- pushes fresh global scope.

### symtable_push_scope
- allocates new Scope,
- links parent to old current scope,
- updates current pointer.

### free_chain
- frees all entries in a single bucket linked list.

### symtable_pop_scope
- detaches current scope,
- frees all bucket chains,
- restores parent as current scope.

### symtable_free
- repeatedly pops until no scope remains.

---

## Core symbol-table operations

### symtable_declare
Flow:
1. ensure active scope exists.
2. hash variable name.
3. check current scope bucket for redeclaration.
4. allocate and initialize SymbolEntry.
5. prepend entry into bucket chain.

### symtable_declare_assign
- convenience composition: declare then assign.

### symtable_lookup
- hash name once,
- search from current scope outward via parent chain,
- return nearest visible entry.

### symtable_assign
Flow:
1. lookup symbol.
2. if missing -> undeclared error.
3. check type compatibility.
4. free previous value.
5. store coerced new value.
6. set initialized flag.

---

## Debug function

### symtable_dump
- prints current scope content:
  - symbol name
  - type
  - value or `<অনির্ধারিত>`

---

## Named semantic wrappers

### declare_variable
- optional no-op when `suppress_execution` is active.
- validates non-empty name.
- delegates to `symtable_declare`.

### assign_variable
- optional no-op under suppression.
- validates non-empty name.
- delegates to `symtable_assign`.

### lookup_variable
- validates name.
- delegates to `symtable_lookup`.
- emits undeclared-use error if missing.
- emits uninitialized-read warning if not initialized.
- suppression flag silences diagnostics in untaken branches.

---

## Final summary

symtable.c provides:
- runtime value lifecycle,
- assignment type policy and coercion,
- lexical scope stack,
- variable declaration/use enforcement,
- and user-facing diagnostics in Bengali.
