#include "tac.h"

#include <stdlib.h>
#include <string.h>

static char *xstrdup(const char *s)
{
    size_t n;
    char *p;
    if (!s) return NULL;
    n = strlen(s) + 1;
    p = (char *)malloc(n);
    if (!p) return NULL;
    memcpy(p, s, n);
    return p;
}

static char *format_id(const char *prefix, int index)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%s%d", prefix, index);
    return xstrdup(buf);
}

static TacInstr tac_instr_new(TacOpcode op, const char *result, const char *arg1, const char *arg2)
{
    TacInstr in;
    in.op = op;
    in.result = xstrdup(result);
    in.arg1 = xstrdup(arg1);
    in.arg2 = xstrdup(arg2);
    return in;
}

static void tac_instr_free(TacInstr *in)
{
    if (!in) return;
    free(in->result);
    free(in->arg1);
    free(in->arg2);
    in->result = NULL;
    in->arg1 = NULL;
    in->arg2 = NULL;
}

static const char *opcode_text(TacOpcode op)
{
    switch (op) {
        case TAC_ADD: return "+";
        case TAC_SUB: return "-";
        case TAC_MUL: return "*";
        case TAC_DIV: return "/";
        case TAC_MOD: return "%";
        case TAC_EQ:  return "==";
        case TAC_NEQ: return "!=";
        case TAC_GT:  return ">";
        case TAC_LT:  return "<";
        case TAC_GTE: return ">=";
        case TAC_LTE: return "<=";
        case TAC_AND: return "&&";
        case TAC_OR:  return "||";
        case TAC_NEG: return "-";
        case TAC_NOT: return "!";
        default:      return "?";
    }
}

void tac_context_init(TacContext *ctx)
{
    if (!ctx) return;
    ctx->temp_counter = 1;
    ctx->label_counter = 1;
}

char *tac_new_temp(TacContext *ctx)
{
    if (!ctx) return NULL;
    return format_id("t", ctx->temp_counter++);
}

char *tac_new_label(TacContext *ctx)
{
    if (!ctx) return NULL;
    return format_id("L", ctx->label_counter++);
}

void tac_program_init(TacProgram *p)
{
    if (!p) return;
    p->items = NULL;
    p->count = 0;
    p->cap = 0;
}

void tac_program_free(TacProgram *p)
{
    size_t i;
    if (!p) return;
    for (i = 0; i < p->count; i++) {
        tac_instr_free(&p->items[i]);
    }
    free(p->items);
    p->items = NULL;
    p->count = 0;
    p->cap = 0;
}

void tac_program_emit(TacProgram *p, TacInstr instr)
{
    TacInstr *new_items;
    size_t new_cap;

    if (!p) return;

    if (p->count == p->cap) {
        new_cap = (p->cap == 0) ? 16u : p->cap * 2u;
        new_items = (TacInstr *)realloc(p->items, new_cap * sizeof(TacInstr));
        if (!new_items) {
            tac_instr_free(&instr);
            return;
        }
        p->items = new_items;
        p->cap = new_cap;
    }
    p->items[p->count++] = instr;
}

TacInstr tac_make_assign(const char *dst, const char *src)
{
    return tac_instr_new(TAC_ASSIGN, dst, src, NULL);
}

TacInstr tac_make_binary(TacOpcode op, const char *dst, const char *lhs, const char *rhs)
{
    return tac_instr_new(op, dst, lhs, rhs);
}

TacInstr tac_make_unary(TacOpcode op, const char *dst, const char *operand)
{
    return tac_instr_new(op, dst, operand, NULL);
}

TacInstr tac_make_if_goto(const char *cond, const char *label)
{
    return tac_instr_new(TAC_IF_GOTO, label, cond, NULL);
}

TacInstr tac_make_goto(const char *label)
{
    return tac_instr_new(TAC_GOTO, label, NULL, NULL);
}

TacInstr tac_make_label(const char *label)
{
    return tac_instr_new(TAC_LABEL, label, NULL, NULL);
}

TacInstr tac_make_param(const char *arg)
{
    return tac_instr_new(TAC_PARAM, arg, NULL, NULL);
}

TacInstr tac_make_call(const char *ret_temp, const char *func_name, int argc)
{
    char argc_buf[32];
    snprintf(argc_buf, sizeof(argc_buf), "%d", argc);
    return tac_instr_new(TAC_CALL, ret_temp, func_name, argc_buf);
}

TacInstr tac_make_return(const char *value)
{
    return tac_instr_new(TAC_RETURN, value, NULL, NULL);
}

void tac_instr_print(FILE *out, const TacInstr *in)
{
    if (!out || !in) return;

    switch (in->op) {
    case TAC_ASSIGN:
        fprintf(out, "%s = %s\n", in->result ? in->result : "_", in->arg1 ? in->arg1 : "_");
        break;

    case TAC_ADD:
    case TAC_SUB:
    case TAC_MUL:
    case TAC_DIV:
    case TAC_MOD:
    case TAC_EQ:
    case TAC_NEQ:
    case TAC_GT:
    case TAC_LT:
    case TAC_GTE:
    case TAC_LTE:
    case TAC_AND:
    case TAC_OR:
        fprintf(out, "%s = %s %s %s\n",
                in->result ? in->result : "_",
                in->arg1 ? in->arg1 : "_",
                opcode_text(in->op),
                in->arg2 ? in->arg2 : "_");
        break;

    case TAC_NEG:
    case TAC_NOT:
        fprintf(out, "%s = %s%s\n",
                in->result ? in->result : "_",
                opcode_text(in->op),
                in->arg1 ? in->arg1 : "_");
        break;

    case TAC_GOTO:
        fprintf(out, "GOTO %s\n", in->result ? in->result : "_");
        break;

    case TAC_IF_GOTO:
        fprintf(out, "IF %s GOTO %s\n",
                in->arg1 ? in->arg1 : "_",
                in->result ? in->result : "_");
        break;

    case TAC_LABEL:
        fprintf(out, "LABEL %s\n", in->result ? in->result : "_");
        break;

    case TAC_PARAM:
        fprintf(out, "PARAM %s\n", in->result ? in->result : "_");
        break;

    case TAC_CALL:
        if (in->result && in->result[0] != '\0') {
            fprintf(out, "%s = CALL %s, %s\n",
                    in->result,
                    in->arg1 ? in->arg1 : "_",
                    in->arg2 ? in->arg2 : "0");
        } else {
            fprintf(out, "CALL %s, %s\n",
                    in->arg1 ? in->arg1 : "_",
                    in->arg2 ? in->arg2 : "0");
        }
        break;

    case TAC_RETURN:
        if (in->result && in->result[0] != '\0')
            fprintf(out, "RETURN %s\n", in->result);
        else
            fprintf(out, "RETURN\n");
        break;

    case TAC_NOP:
    default:
        fprintf(out, "NOP\n");
        break;
    }
}

void tac_program_print(FILE *out, const TacProgram *p)
{
    size_t i;
    if (!out || !p) return;
    for (i = 0; i < p->count; i++) {
        tac_instr_print(out, &p->items[i]);
    }
}
