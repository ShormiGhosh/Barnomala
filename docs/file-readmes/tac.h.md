# বর্ণমালা (Barnomala) — TAC Header Detailed Explanation (tac.h)

This header defines the Three-Address Code representation used by IR generation.

---

## Header and includes

```c
#ifndef TAC_H
#define TAC_H
#include <stdio.h>
#include <stddef.h>
...
#endif
```
Purpose:
- include guard and required standard types (`FILE`, `size_t`).

---

## Opcode enum

```c
typedef enum {
    TAC_NOP = 0,
    TAC_ASSIGN,
    TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV, TAC_MOD,
    TAC_NEG, TAC_NOT,
    TAC_EQ, TAC_NEQ, TAC_GT, TAC_LT, TAC_GTE, TAC_LTE,
    TAC_AND, TAC_OR,
    TAC_GOTO, TAC_IF_GOTO, TAC_LABEL,
    TAC_PARAM, TAC_CALL, TAC_RETURN
} TacOpcode;
```
Purpose:
- Single instruction vocabulary for IR stream.

Groups:
- arithmetic/logical
- compare
- control-flow
- call protocol

---

## `TacInstr` structure

```c
typedef struct {
    TacOpcode op;
    char *result;
    char *arg1;
    char *arg2;
} TacInstr;
```
Purpose:
- Generic 3-address instruction payload.

Convention examples:
- binary: `result = arg1 op arg2`
- unary: `result = op arg1`
- if_goto: `IF arg1 GOTO result`

---

## `TacProgram` container

```c
typedef struct {
    TacInstr *items;
    size_t count;
    size_t cap;
} TacProgram;
```
Purpose:
- Dynamic array holding linear TAC stream.

---

## `TacContext`

```c
typedef struct {
    int temp_counter;
    int label_counter;
} TacContext;
```
Purpose:
- Name allocator state for temporaries and labels.

---

## API declarations

### Context
- tac_context_init
- tac_new_temp
- tac_new_label

### Program lifecycle
- tac_program_init
- tac_program_free
- tac_program_emit

### Builder helpers
- tac_make_assign
- tac_make_binary
- tac_make_unary
- tac_make_if_goto
- tac_make_goto
- tac_make_label
- tac_make_param
- tac_make_call
- tac_make_return

### Printing
- tac_instr_print
- tac_program_print
