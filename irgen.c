#include "irgen.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOOP_DEPTH 64
#define MAX_LIST_ITEMS 256

typedef struct {
    TacProgram *out;
    TacContext tac_ctx;
    const char *break_labels[MAX_LOOP_DEPTH];
    const char *continue_labels[MAX_LOOP_DEPTH];
    int loop_top;
} IrGenCtx;

static char *xstrdup(const char *s)
{
    size_t n;
    char *p;
    if (!s) return NULL;
    n = strlen(s) + 1u;
    p = (char *)malloc(n);
    if (!p) return NULL;
    memcpy(p, s, n);
    return p;
}

static char *strdup_printf(const char *fmt, ...)
{
    va_list ap;
    va_list ap2;
    int len;
    char *buf;

    va_start(ap, fmt);
    va_copy(ap2, ap);
    len = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);
    if (len < 0) {
        va_end(ap2);
        return NULL;
    }

    buf = (char *)malloc((size_t)len + 1u);
    if (!buf) {
        va_end(ap2);
        return NULL;
    }

    vsnprintf(buf, (size_t)len + 1u, fmt, ap2);
    va_end(ap2);
    return buf;
}

static TacOpcode tac_from_binop(int op)
{
    switch (op) {
    case OP_PLUS:  return TAC_ADD;
    case OP_MINUS: return TAC_SUB;
    case OP_MULT:  return TAC_MUL;
    case OP_DIV:   return TAC_DIV;
    case OP_MOD:   return TAC_MOD;
    case OP_AND:   return TAC_AND;
    case OP_OR:    return TAC_OR;
    case OP_EQ:    return TAC_EQ;
    case OP_NEQ:   return TAC_NEQ;
    case OP_GT:    return TAC_GT;
    case OP_LT:    return TAC_LT;
    case OP_GTE:   return TAC_GTE;
    case OP_LTE:   return TAC_LTE;
    default:       return TAC_NOP;
    }
}

static void gen_stmt(IrGenCtx *ctx, const AstNode *n);
static char *gen_expr(IrGenCtx *ctx, const AstNode *n);

static char *gen_call_expr(IrGenCtx *ctx, const AstNode *n)
{
    const AstNode *arg_nodes[MAX_LIST_ITEMS];
    char *arg_places[MAX_LIST_ITEMS];
    int argc = 0;
    int i;
    char *ret;

    for (const AstNode *it = n->left; it && argc < MAX_LIST_ITEMS; it = it->right)
        arg_nodes[argc++] = it->left;

    for (i = argc - 1; i >= 0; i--) {
        arg_places[i] = NULL;
        arg_places[i] = gen_expr(ctx, arg_nodes[i]);
        tac_program_emit(ctx->out, tac_make_param(arg_places[i] ? arg_places[i] : "_"));
    }

    ret = tac_new_temp(&ctx->tac_ctx);
    tac_program_emit(ctx->out, tac_make_call(ret, n->sval ? n->sval : "_", argc));

    for (i = 0; i < argc; i++)
        free(arg_places[i]);

    return ret;
}

static char *gen_math_call(IrGenCtx *ctx, const char *name, const AstNode *a, const AstNode *b)
{
    char *pa = NULL;
    char *pb = NULL;
    char *ret;
    int argc = 0;

    if (a) {
        pa = gen_expr(ctx, a);
        tac_program_emit(ctx->out, tac_make_param(pa ? pa : "_"));
        argc++;
    }
    if (b) {
        pb = gen_expr(ctx, b);
        tac_program_emit(ctx->out, tac_make_param(pb ? pb : "_"));
        argc++;
    }

    ret = tac_new_temp(&ctx->tac_ctx);
    tac_program_emit(ctx->out, tac_make_call(ret, name, argc));

    free(pa);
    free(pb);
    return ret;
}

static char *gen_expr(IrGenCtx *ctx, const AstNode *n)
{
    char *a;
    char *b;
    char *t;
    char *repr;

    if (!n) return xstrdup("0");

    switch (n->kind) {
    case N_INT_LIT:
        return strdup_printf("%d", n->ival);

    case N_FLOAT_LIT:
        return strdup_printf("%g", n->fval);

    case N_STRING_LIT:
    case N_CHAR_LIT:
        return xstrdup(n->sval ? n->sval : "");

    case N_BOOL_LIT:
        return xstrdup(n->ival ? "1" : "0");

    case N_IDENT:
        return xstrdup(n->sval ? n->sval : "_");

    case N_BINOP:
        a = gen_expr(ctx, n->left);
        b = gen_expr(ctx, n->right);
        t = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_binary(tac_from_binop(n->ival), t,
                                                    a ? a : "_", b ? b : "_"));
        free(a);
        free(b);
        return t;

    case N_UNARY_NOT:
        a = gen_expr(ctx, n->left);
        t = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_unary(TAC_NOT, t, a ? a : "_"));
        free(a);
        return t;

    case N_UNARY_NEG:
        a = gen_expr(ctx, n->left);
        t = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_unary(TAC_NEG, t, a ? a : "_"));
        free(a);
        return t;

    case N_CALL:
        return gen_call_expr(ctx, n);

    case N_MATH_POW:
        return gen_math_call(ctx, "pow", n->left, n->right);

    case N_MATH_SQRT:
        return gen_math_call(ctx, "sqrt", n->left, NULL);

    case N_MATH_FLOOR:
        return gen_math_call(ctx, "floor", n->left, NULL);

    case N_MATH_CEIL:
        return gen_math_call(ctx, "ceil", n->left, NULL);

    case N_MATH_ABS:
        return gen_math_call(ctx, "abs", n->left, NULL);

    case N_ARRAY_LEN:
        tac_program_emit(ctx->out, tac_make_param(n->sval ? n->sval : "_"));
        t = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_call(t, "length", 1));
        return t;

    case N_ARRAY_ACCESS:
        a = gen_expr(ctx, n->left);
        repr = strdup_printf("%s[%s]", n->sval ? n->sval : "_", a ? a : "_");
        t = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_assign(t, repr ? repr : "_"));
        free(a);
        free(repr);
        return t;

    default:
        return xstrdup("0");
    }
}

static void push_loop(IrGenCtx *ctx, const char *break_label, const char *continue_label)
{
    if (ctx->loop_top + 1 >= MAX_LOOP_DEPTH) return;
    ctx->loop_top++;
    ctx->break_labels[ctx->loop_top] = break_label;
    ctx->continue_labels[ctx->loop_top] = continue_label;
}

static void pop_loop(IrGenCtx *ctx)
{
    if (ctx->loop_top < 0) return;
    ctx->break_labels[ctx->loop_top] = NULL;
    ctx->continue_labels[ctx->loop_top] = NULL;
    ctx->loop_top--;
}

static void gen_stmt(IrGenCtx *ctx, const AstNode *n)
{
    char *cond;
    char *value;
    char *idx;
    char *lhs;
    char *start;
    char *end;
    char *cmp;
    char *inc;
    char *lbl_then;
    char *lbl_else;
    char *lbl_end;
    char *lbl_cond;
    char *lbl_body;
    char *lbl_step;

    if (!n) return;

    switch (n->kind) {
    case N_SEQ:
        gen_stmt(ctx, n->left);
        gen_stmt(ctx, n->right);
        break;

    case N_DECL:
        if (n->left) {
            value = gen_expr(ctx, n->left);
            tac_program_emit(ctx->out, tac_make_assign(n->sval ? n->sval : "_", value ? value : "_"));
            free(value);
        }
        break;

    case N_ASSIGN:
        value = gen_expr(ctx, n->left);
        tac_program_emit(ctx->out, tac_make_assign(n->sval ? n->sval : "_", value ? value : "_"));
        free(value);
        break;

    case N_ARRAY_ASSIGN:
        idx = gen_expr(ctx, n->left);
        value = gen_expr(ctx, n->right);
        lhs = strdup_printf("%s[%s]", n->sval ? n->sval : "_", idx ? idx : "_");
        tac_program_emit(ctx->out, tac_make_assign(lhs ? lhs : "_", value ? value : "_"));
        free(idx);
        free(value);
        free(lhs);
        break;

    case N_PRINT:
        value = gen_expr(ctx, n->left);
        tac_program_emit(ctx->out, tac_make_param(value ? value : "_"));
        tac_program_emit(ctx->out, tac_make_call(NULL, "print", 1));
        free(value);
        break;

    case N_INPUT:
        value = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_call(value, "input", 0));
        tac_program_emit(ctx->out, tac_make_assign(n->sval ? n->sval : "_", value ? value : "_"));
        free(value);
        break;

    case N_IF:
        lbl_then = tac_new_label(&ctx->tac_ctx);
        lbl_end = tac_new_label(&ctx->tac_ctx);
        cond = gen_expr(ctx, n->left);

        if (n->extra) {
            lbl_else = tac_new_label(&ctx->tac_ctx);
            tac_program_emit(ctx->out, tac_make_if_goto(cond ? cond : "_", lbl_then));
            tac_program_emit(ctx->out, tac_make_goto(lbl_else));
            tac_program_emit(ctx->out, tac_make_label(lbl_then));
            gen_stmt(ctx, n->right);
            tac_program_emit(ctx->out, tac_make_goto(lbl_end));
            tac_program_emit(ctx->out, tac_make_label(lbl_else));
            gen_stmt(ctx, n->extra);
            tac_program_emit(ctx->out, tac_make_label(lbl_end));
            free(lbl_else);
        } else {
            tac_program_emit(ctx->out, tac_make_if_goto(cond ? cond : "_", lbl_then));
            tac_program_emit(ctx->out, tac_make_goto(lbl_end));
            tac_program_emit(ctx->out, tac_make_label(lbl_then));
            gen_stmt(ctx, n->right);
            tac_program_emit(ctx->out, tac_make_label(lbl_end));
        }

        free(cond);
        free(lbl_then);
        free(lbl_end);
        break;

    case N_WHILE:
        lbl_cond = tac_new_label(&ctx->tac_ctx);
        lbl_body = tac_new_label(&ctx->tac_ctx);
        lbl_end = tac_new_label(&ctx->tac_ctx);

        tac_program_emit(ctx->out, tac_make_label(lbl_cond));
        cond = gen_expr(ctx, n->left);
        tac_program_emit(ctx->out, tac_make_if_goto(cond ? cond : "_", lbl_body));
        tac_program_emit(ctx->out, tac_make_goto(lbl_end));
        tac_program_emit(ctx->out, tac_make_label(lbl_body));
        free(cond);

        push_loop(ctx, lbl_end, lbl_cond);
        gen_stmt(ctx, n->right);
        pop_loop(ctx);

        tac_program_emit(ctx->out, tac_make_goto(lbl_cond));
        tac_program_emit(ctx->out, tac_make_label(lbl_end));

        free(lbl_cond);
        free(lbl_body);
        free(lbl_end);
        break;

    case N_FOR_RANGE:
        start = gen_expr(ctx, n->left);
        end = gen_expr(ctx, n->right);
        tac_program_emit(ctx->out, tac_make_assign(n->sval ? n->sval : "_", start ? start : "_"));

        lbl_cond = tac_new_label(&ctx->tac_ctx);
        lbl_body = tac_new_label(&ctx->tac_ctx);
        lbl_step = tac_new_label(&ctx->tac_ctx);
        lbl_end = tac_new_label(&ctx->tac_ctx);

        tac_program_emit(ctx->out, tac_make_label(lbl_cond));
        cmp = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_binary(TAC_LTE, cmp, n->sval ? n->sval : "_", end ? end : "_"));
        tac_program_emit(ctx->out, tac_make_if_goto(cmp, lbl_body));
        tac_program_emit(ctx->out, tac_make_goto(lbl_end));
        tac_program_emit(ctx->out, tac_make_label(lbl_body));

        push_loop(ctx, lbl_end, lbl_step);
        gen_stmt(ctx, n->extra);
        pop_loop(ctx);

        tac_program_emit(ctx->out, tac_make_label(lbl_step));
        inc = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_binary(TAC_ADD, inc, n->sval ? n->sval : "_", "1"));
        tac_program_emit(ctx->out, tac_make_assign(n->sval ? n->sval : "_", inc));
        tac_program_emit(ctx->out, tac_make_goto(lbl_cond));
        tac_program_emit(ctx->out, tac_make_label(lbl_end));

        free(start);
        free(end);
        free(cmp);
        free(inc);
        free(lbl_cond);
        free(lbl_body);
        free(lbl_step);
        free(lbl_end);
        break;

    case N_BREAK:
        if (ctx->loop_top >= 0 && ctx->break_labels[ctx->loop_top])
            tac_program_emit(ctx->out, tac_make_goto(ctx->break_labels[ctx->loop_top]));
        break;

    case N_CONTINUE:
        if (ctx->loop_top >= 0 && ctx->continue_labels[ctx->loop_top])
            tac_program_emit(ctx->out, tac_make_goto(ctx->continue_labels[ctx->loop_top]));
        break;

    case N_RETURN:
        if (n->left) {
            value = gen_expr(ctx, n->left);
            tac_program_emit(ctx->out, tac_make_return(value ? value : "_"));
            free(value);
        } else {
            tac_program_emit(ctx->out, tac_make_return(NULL));
        }
        break;

    case N_INC:
        inc = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_binary(TAC_ADD, inc, n->sval ? n->sval : "_", "1"));
        tac_program_emit(ctx->out, tac_make_assign(n->sval ? n->sval : "_", inc));
        free(inc);
        break;

    case N_DEC:
        inc = tac_new_temp(&ctx->tac_ctx);
        tac_program_emit(ctx->out, tac_make_binary(TAC_SUB, inc, n->sval ? n->sval : "_", "1"));
        tac_program_emit(ctx->out, tac_make_assign(n->sval ? n->sval : "_", inc));
        free(inc);
        break;

    case N_FUNCDEF:
        tac_program_emit(ctx->out, tac_make_label(n->sval ? n->sval : "func"));
        gen_stmt(ctx, n->right);
        tac_program_emit(ctx->out, tac_make_return(NULL));
        break;

    case N_CALL_STMT:
        value = gen_expr(ctx, n->left);
        free(value);
        break;

    case N_ARRAY_DECL:
        if (n->left) {
            const AstNode *init_nodes[MAX_LIST_ITEMS];
            int count = 0;
            int i;

            for (const AstNode *it = n->left; it && count < MAX_LIST_ITEMS; it = it->right)
                init_nodes[count++] = it->left;

            for (i = count - 1; i >= 0; i--) {
                idx = strdup_printf("%d", count - 1 - i);
                value = gen_expr(ctx, init_nodes[i]);
                lhs = strdup_printf("%s[%s]", n->sval ? n->sval : "_", idx ? idx : "_");
                tac_program_emit(ctx->out, tac_make_assign(lhs ? lhs : "_", value ? value : "_"));
                free(idx);
                free(value);
                free(lhs);
            }
        }
        break;

    case N_NOP:
    default:
        break;
    }
}

void tac_generate_from_ast(const AstNode *root, TacProgram *out)
{
    IrGenCtx ctx;

    if (!out) return;

    memset(&ctx, 0, sizeof(ctx));
    ctx.out = out;
    ctx.loop_top = -1;
    tac_context_init(&ctx.tac_ctx);

    gen_stmt(&ctx, root);
}
