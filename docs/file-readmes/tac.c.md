# বর্ণমালা (Barnomala) — TAC Runtime Detailed Explanation (tac.c)

This file implements all declared TAC utilities from tac.h.

---

## Includes

```c
#include "tac.h"
#include <stdlib.h>
#include <string.h>
```
Purpose:
- header API plus allocation/string helpers.

---

## Local helpers

### `xstrdup`
- duplicates nullable string input.
- returns NULL if source is NULL.

### `format_id`
- formats `{prefix}{index}` using local buffer then duplicates.
- used by temp/label generators.

### `tac_instr_new`
- creates instruction with deep-copied operand strings.

### `tac_instr_free`
- frees result/arg1/arg2 and nulls pointers.

### `opcode_text`
- maps opcode to printable operator symbol.

---

## Context functions

### `tac_context_init`
- initializes temp and label counters to 1.

### `tac_new_temp`
- returns heap string like `t1`, `t2`, ...

### `tac_new_label`
- returns heap string like `L1`, `L2`, ...

---

## Program lifecycle

### `tac_program_init`
- clears program array fields.

### `tac_program_free`
- deep-frees every instruction then frees items array.

### `tac_program_emit`
Flow:
1. grow array when `count == cap`.
2. realloc with doubling growth policy.
3. on realloc failure, frees incoming instruction to prevent leak.
4. appends instruction.

---

## Builder functions

Each function wraps `tac_instr_new` with opcode-specific argument placement:
- assign
- binary
- unary
- if-goto
- goto
- label
- param
- call
- return

`tac_make_call` also converts integer argc to string operand.

---

## Printing functions

### `tac_instr_print`
Print format by opcode:
- assignment: `x = y`
- binary: `t1 = a + b`
- unary: `t2 = !p`
- goto: `GOTO L1`
- if-goto: `IF t3 GOTO L2`
- label: `LABEL L3`
- param: `PARAM x`
- call with return: `t4 = CALL f, 2`
- call without return: `CALL f, 2`
- return with/without value.

### `tac_program_print`
- sequentially prints each instruction in order.
