#ifndef TAC_H
#define TAC_H

#include <stdio.h>
#include <stddef.h>

/* ------------------------------------------------------------------ */
/*  Three-Address Code (TAC)                                           */
/*  Examples:                                                          */
/*    t1 = a + b                                                       */
/*    IF t1 GOTO L1                                                    */
/*    LABEL L1                                                         */
/*    CALL foo                                                         */
/* ------------------------------------------------------------------ */

typedef enum {
    TAC_NOP = 0,
    TAC_ASSIGN,
    TAC_ADD,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,
    TAC_MOD,
    TAC_NEG,
    TAC_NOT,
    TAC_EQ,
    TAC_NEQ,
    TAC_GT,
    TAC_LT,
    TAC_GTE,
    TAC_LTE,
    TAC_AND,
    TAC_OR,
    TAC_GOTO,
    TAC_IF_GOTO,
    TAC_LABEL,
    TAC_PARAM,
    TAC_CALL,
    TAC_RETURN
} TacOpcode;

typedef struct {
    TacOpcode op;
    char *result;
    char *arg1;
    char *arg2;
} TacInstr;

typedef struct {
    TacInstr *items;
    size_t    count;
    size_t    cap;
} TacProgram;

typedef struct {
    int temp_counter;
    int label_counter;
} TacContext;

void tac_context_init(TacContext *ctx);
char *tac_new_temp(TacContext *ctx);
char *tac_new_label(TacContext *ctx);

void tac_program_init(TacProgram *p);
void tac_program_free(TacProgram *p);
void tac_program_emit(TacProgram *p, TacInstr instr);

TacInstr tac_make_assign(const char *dst, const char *src);
TacInstr tac_make_binary(TacOpcode op, const char *dst, const char *lhs, const char *rhs);
TacInstr tac_make_unary(TacOpcode op, const char *dst, const char *operand);
TacInstr tac_make_if_goto(const char *cond, const char *label);
TacInstr tac_make_goto(const char *label);
TacInstr tac_make_label(const char *label);
TacInstr tac_make_param(const char *arg);
TacInstr tac_make_call(const char *ret_temp, const char *func_name, int argc);
TacInstr tac_make_return(const char *value);

void tac_instr_print(FILE *out, const TacInstr *in);
void tac_program_print(FILE *out, const TacProgram *p);

#endif /* TAC_H */
