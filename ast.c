#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ------------------------------------------------------------------ */
/*  Forward declarations                                                */
/* ------------------------------------------------------------------ */
static Value eval_binop(Value a, int op, Value b);

/* ================================================================== */
/*  Function Table                                                      */
/* ================================================================== */
#define FUNC_TABLE_SIZE 64
static FuncEntry *func_table[FUNC_TABLE_SIZE];  /* zero-init at start  */

static unsigned int func_hash(const char *key)
{
    unsigned int h = 2166136261u;
    while (*key) { h ^= (unsigned char)(*key++); h *= 16777619u; }
    return h % FUNC_TABLE_SIZE;
}

void func_table_init(void)
{
    /* Called once at startup; static zero-init is sufficient on first
       run, but explicit clear allows re-init if ever needed. */
    memset(func_table, 0, sizeof(func_table));
}

void func_table_free(void)
{
    for (int i = 0; i < FUNC_TABLE_SIZE; i++) {
        FuncEntry *e = func_table[i];
        while (e) {
            FuncEntry *nxt = e->next;
            free(e->name);
            node_free(e->params);
            node_free(e->body);
            free(e);
            e = nxt;
        }
        func_table[i] = NULL;
    }
}

int func_table_define(char *name, AstNode *params, AstNode *body)
{
    unsigned int h = func_hash(name);
    for (FuncEntry *e = func_table[h]; e; e = e->next) {
        if (strcmp(e->name, name) == 0) {
            fprintf(stderr, "ত্রুটি: '%s' ফাংশন ইতোমধ্যে সংজ্ঞায়িত।\n", name);
            return -1;
        }
    }
    FuncEntry *e  = calloc(1, sizeof(FuncEntry));
    e->name       = name;    /* ownership taken — caller must NULLify */
    e->params     = params;  /* ownership taken */
    e->body       = body;    /* ownership taken */
    e->next       = func_table[h];
    func_table[h] = e;
    return 0;
}

FuncEntry *func_table_lookup(const char *name)
{
    unsigned int h = func_hash(name);
    for (FuncEntry *e = func_table[h]; e; e = e->next)
        if (strcmp(e->name, name) == 0) return e;
    return NULL;
}

/* ------------------------------------------------------------------ */
/*  Helpers                                                             */
/* ------------------------------------------------------------------ */
static int is_truthy(Value v)
{
    if (v.type == TYPE_DECIMAL) return v.data.floatval != 0.0;
    return v.data.intval != 0;
}

/* Bengali digit → ASCII digit conversion for runtime scanf/atoi use */
static void bengali_digits_to_ascii(char *buf)
{
    unsigned char *s = (unsigned char *)buf;
    unsigned char tmp[1024];
    int j = 0;
    for (int i = 0; s[i]; ) {
        /* Bengali digit: E0 A7 A6..AF */
        if (s[i] == 0xE0 && s[i+1] == 0xA7 &&
            s[i+2] >= 0xA6 && s[i+2] <= 0xAF) {
            tmp[j++] = '0' + (s[i+2] - 0xA6);
            i += 3;
        } else {
            tmp[j++] = s[i++];
        }
    }
    tmp[j] = '\0';
    memcpy(buf, tmp, j + 1);
}

/* ================================================================== */
/*  Constructor / Destructor                                            */
/* ================================================================== */
AstNode *node_new(NodeKind kind, int lineno)
{
    AstNode *n = calloc(1, sizeof(AstNode));
    n->kind   = kind;
    n->lineno = lineno;
    return n;
}

void node_free(AstNode *n)
{
    if (!n) return;
    node_free(n->left);
    node_free(n->right);
    node_free(n->extra);
    if (n->sval) free(n->sval);
    free(n);
}

/* ================================================================== */
/*  Expression evaluator                                                */
/* ================================================================== */
Value eval_expr(AstNode *n)
{
    if (!n) return make_unknown();

    switch (n->kind) {

    case N_INT_LIT:    return make_int(n->ival);
    case N_FLOAT_LIT:  return make_float(n->fval);
    case N_STRING_LIT: return make_string(n->sval);
    case N_CHAR_LIT:   return make_char(n->sval);
    case N_BOOL_LIT:   return make_bool(n->ival);

    case N_IDENT: {
        SymbolEntry *e = lookup_variable(n->sval);
        return e ? copy_value(e->value) : make_unknown();
    }

    case N_BINOP: {
        Value a = eval_expr(n->left);
        Value b = eval_expr(n->right);
        return eval_binop(a, n->ival, b);
    }

    case N_UNARY_NOT: {
        Value v = eval_expr(n->left);
        int bval;
        if (v.type == TYPE_DECIMAL) bval = (v.data.floatval == 0.0) ? 1 : 0;
        else                        bval = (v.data.intval   == 0)   ? 1 : 0;
        free_value(v);
        return make_bool(bval);
    }

    case N_UNARY_NEG: {
        Value v = eval_expr(n->left);
        if (v.type == TYPE_DECIMAL) {
            double x = -v.data.floatval; free_value(v); return make_float(x);
        } else {
            int    x = -v.data.intval;   free_value(v); return make_int(x);
        }
    }

    case N_MATH_POW: {
        Value base = eval_expr(n->left);
        Value exp  = eval_expr(n->right);
        double b = (base.type == TYPE_DECIMAL) ? base.data.floatval : (double)base.data.intval;
        double e = (exp.type  == TYPE_DECIMAL) ? exp.data.floatval  : (double)exp.data.intval;
        free_value(base); free_value(exp);
        return make_float(pow(b, e));
    }

    case N_MATH_SQRT: {
        Value v = eval_expr(n->left);
        double x = (v.type == TYPE_DECIMAL) ? v.data.floatval : (double)v.data.intval;
        free_value(v);
        return make_float(sqrt(x));
    }

    case N_MATH_FLOOR: {
        Value v = eval_expr(n->left);
        double x = (v.type == TYPE_DECIMAL) ? v.data.floatval : (double)v.data.intval;
        free_value(v);
        return make_int((int)floor(x));
    }

    case N_MATH_CEIL: {
        Value v = eval_expr(n->left);
        double x = (v.type == TYPE_DECIMAL) ? v.data.floatval : (double)v.data.intval;
        free_value(v);
        return make_int((int)ceil(x));
    }

    case N_MATH_ABS: {
        Value v = eval_expr(n->left);
        if (v.type == TYPE_DECIMAL) {
            double x = fabs(v.data.floatval); free_value(v); return make_float(x);
        } else {
            int    x = abs(v.data.intval);    free_value(v); return make_int(x);
        }
    }

    case N_ARRAY_ACCESS:
        /* array runtime not yet implemented */
        return make_unknown();

    case N_CALL: {
        FuncEntry *fn = func_table_lookup(n->sval);
        if (!fn) {
            fprintf(stderr, "ত্রুটি: '%s' ফাংশন সংজ্ঞায়িত নয়।\n", n->sval);
            return make_unknown();
        }

        /* Evaluate all argument expressions BEFORE pushing the new scope
           (so refs to caller's variables resolve correctly) */
        /* Count params and args; both chains are right-linked, built
           in reverse (last item at head), so we walk them together. */

        /* Build a flat array of evaluated arg values */
        #define MAX_PARAMS 64
        Value argv_vals[MAX_PARAMS];
        int argc_actual = 0;
        for (AstNode *a = n->left; a; a = a->right) {
            if (argc_actual >= MAX_PARAMS) break;
            argv_vals[argc_actual++] = eval_expr(a->left);
        }

        /* Push a fresh scope for the function call */
        symtable_push_scope();

        /* Bind parameters — param list and arg list are both in the
           same (reversed) order, so walk them together. */
        AstNode *param = fn->params;
        int pi = 0;
        while (param) {
            Value v = (pi < argc_actual) ? argv_vals[pi] : make_unknown();
            symtable_declare_assign(param->sval, v.type == TYPE_UNKNOWN
                                                   ? TYPE_NUMBER : v.type, v);
            if (pi < argc_actual) free_value(argv_vals[pi]);
            param = param->right;
            pi++;
        }
        /* free any surplus evaluated args */
        while (pi < argc_actual) { free_value(argv_vals[pi]); pi++; }
        #undef MAX_PARAMS

        /* Execute body */
        ExecResult r = exec_stmt(fn->body);

        /* Pop the function scope */
        symtable_pop_scope();

        /* Extract return value (EXEC_RETURN → caller gets the value) */
        Value retval;
        if (r.signal == EXEC_RETURN) {
            retval = r.retval;   /* ownership passed to us */
        } else {
            free_value(r.retval);
            retval = make_int(0);  /* void function — return 0 */
        }
        return retval;
    }

    default:
        return make_unknown();
    }
}

/* ================================================================== */
/*  Statement executor                                                  */
/* ================================================================== */
ExecResult exec_stmt(AstNode *n)
{
    ExecResult ok = {EXEC_NORMAL, {TYPE_NUMBER, {0}}};

    if (!n) return ok;

    switch (n->kind) {

    case N_NOP:
        return ok;

    /* N_SEQ: left=all-previous-stmts (left-recursive chain), right=this-stmt */
    case N_SEQ: {
        ExecResult r = exec_stmt(n->left);
        if (r.signal != EXEC_NORMAL) return r;
        return exec_stmt(n->right);
    }

    case N_DECL: {
        declare_variable(n->sval, n->vtype);
        if (n->left) {
            Value v = eval_expr(n->left);
            assign_variable(n->sval, v);
            free_value(v);
        }
        return ok;
    }

    case N_ASSIGN: {
        Value v = eval_expr(n->left);
        assign_variable(n->sval, v);
        free_value(v);
        return ok;
    }

    case N_PRINT: {
        Value v = eval_expr(n->left);
        print_value(v);
        printf("\n");
        free_value(v);
        return ok;
    }

    case N_INPUT: {
        SymbolEntry *e = symtable_lookup(n->sval);
        if (!e) {
            fprintf(stderr, "ত্রুটি: '%s' ঘোষণা করা হয়নি।\n", n->sval);
            return ok;
        }
        switch (e->type) {
        case TYPE_NUMBER: {
            char buf[64];
            if (fgets(buf, sizeof(buf), stdin)) {
                buf[strcspn(buf, "\n")] = '\0';
                bengali_digits_to_ascii(buf);
                assign_variable(n->sval, make_int(atoi(buf)));
            }
            break;
        }
        case TYPE_DECIMAL: {
            char buf[64];
            if (fgets(buf, sizeof(buf), stdin)) {
                buf[strcspn(buf, "\n")] = '\0';
                bengali_digits_to_ascii(buf);
                assign_variable(n->sval, make_float(atof(buf)));
            }
            break;
        }
        case TYPE_STRING: {
            char buf[1024];
            if (fgets(buf, sizeof(buf), stdin)) {
                buf[strcspn(buf, "\n")] = '\0';
                assign_variable(n->sval, make_string(buf));
            }
            break;
        }
        case TYPE_BOOL: {
            int v = 0;
            if (scanf("%d", &v) == 1)
                assign_variable(n->sval, make_bool(v));
            break;
        }
        default: break;
        }
        return ok;
    }

    case N_IF: {
        Value cond = eval_expr(n->left);
        int go = is_truthy(cond);
        free_value(cond);
        if (go)
            return exec_stmt(n->right);
        else if (n->extra)
            return exec_stmt(n->extra);
        return ok;
    }

    case N_WHILE: {
        ExecResult r = ok;
        while (1) {
            Value cond = eval_expr(n->left);
            int go = is_truthy(cond);
            free_value(cond);
            if (!go) break;

            r = exec_stmt(n->right);

            if (r.signal == EXEC_BREAK) {
                free_value(r.retval);
                r = ok;
                break;
            }
            if (r.signal == EXEC_RETURN) break;   /* propagate return */
            if (r.signal == EXEC_CONTINUE) {
                free_value(r.retval);
                r = ok;
                continue;
            }
        }
        return r;
    }

    case N_FOR_RANGE: {
        /* ঘুরতে_থাক(var) start থেকে end */
        if (!symtable_lookup(n->sval))
            declare_variable(n->sval, TYPE_NUMBER);

        Value sv = eval_expr(n->left);
        Value ev = eval_expr(n->right);
        int s = (sv.type == TYPE_DECIMAL) ? (int)sv.data.floatval : sv.data.intval;
        int e = (ev.type == TYPE_DECIMAL) ? (int)ev.data.floatval : ev.data.intval;
        free_value(sv); free_value(ev);

        ExecResult r = ok;
        for (int i = s; i <= e; i++) {
            assign_variable(n->sval, make_int(i));
            r = exec_stmt(n->extra);

            if (r.signal == EXEC_BREAK) {
                free_value(r.retval);
                r = ok;
                break;
            }
            if (r.signal == EXEC_RETURN) break;
            if (r.signal == EXEC_CONTINUE) {
                free_value(r.retval);
                r = ok;
                continue;
            }
        }
        return r;
    }

    case N_BREAK: {
        ExecResult br = {EXEC_BREAK, {TYPE_NUMBER, {0}}};
        return br;
    }

    case N_CONTINUE: {
        ExecResult cr = {EXEC_CONTINUE, {TYPE_NUMBER, {0}}};
        return cr;
    }

    case N_RETURN: {
        ExecResult ret;
        ret.signal = EXEC_RETURN;
        ret.retval = n->left ? eval_expr(n->left) : make_int(0);
        return ret;
    }

    case N_INC: {
        SymbolEntry *e = lookup_variable(n->sval);
        if (e) {
            if (e->type == TYPE_NUMBER)
                assign_variable(n->sval, make_int(e->value.data.intval + 1));
            else if (e->type == TYPE_DECIMAL)
                assign_variable(n->sval, make_float(e->value.data.floatval + 1.0));
            else
                fprintf(stderr, "ত্রুটি: '%s' সংখ্যা বা দশমিক নয়, বাড়ানো যাবে না।\n",
                        n->sval);
        }
        return ok;
    }

    case N_DEC: {
        SymbolEntry *e = lookup_variable(n->sval);
        if (e) {
            if (e->type == TYPE_NUMBER)
                assign_variable(n->sval, make_int(e->value.data.intval - 1));
            else if (e->type == TYPE_DECIMAL)
                assign_variable(n->sval, make_float(e->value.data.floatval - 1.0));
            else
                fprintf(stderr, "ত্রুটি: '%s' সংখ্যা বা দশমিক নয়, কমানো যাবে না।\n",
                        n->sval);
        }
        return ok;
    }

    case N_FUNCDEF: {
        /* Transfer ownership of name/params/body to the function table.
           Setting the pointers to NULL prevents node_free() from
           double-freeing them when the program AST is freed later. */
        func_table_define(n->sval, n->left, n->right);
        n->sval  = NULL;
        n->left  = NULL;
        n->right = NULL;
        return ok;
    }

    case N_ARRAY_DECL:
        /* declare the variable; array storage not yet implemented */
        declare_variable(n->sval, n->vtype);
        return ok;

    case N_CALL_STMT: {
        Value v = eval_expr(n->left);
        free_value(v);
        return ok;
    }

    default:
        return ok;
    }
}

/* ================================================================== */
/*  Binary operator evaluator                                           */
/* ================================================================== */
static Value eval_binop(Value a, int op, Value b)
{
    /* ---- String concatenation for PLUS ---- */
    if (op == OP_PLUS &&
        (a.type == TYPE_STRING || b.type == TYPE_STRING ||
         a.type == TYPE_CHAR   || b.type == TYPE_CHAR)) {
        char buf[4096] = {0};

        #define APPEND_VAL(v)  do {                                        \
            if ((v).type == TYPE_STRING || (v).type == TYPE_CHAR) {        \
                const char *s = (v).data.strval ? (v).data.strval : "";    \
                size_t len = strlen(s);                                     \
                if (len >= 2 && (s[0] == '"' || s[0] == '\''))             \
                    strncat(buf, s + 1, len - 2);                          \
                else strcat(buf, s);                                        \
            } else if ((v).type == TYPE_DECIMAL) {                         \
                char tmp[64];                                               \
                snprintf(tmp, sizeof(tmp), "%g", (v).data.floatval);       \
                strcat(buf, tmp);                                           \
            } else {                                                        \
                char tmp[64];                                               \
                snprintf(tmp, sizeof(tmp), "%d", (v).data.intval);         \
                strcat(buf, tmp);                                           \
            }                                                               \
        } while (0)

        APPEND_VAL(a);
        APPEND_VAL(b);
        #undef APPEND_VAL
        free_value(a); free_value(b);
        return make_string(buf);
    }

    /* ---- Numeric promotion ---- */
    int    use_float = (a.type == TYPE_DECIMAL || b.type == TYPE_DECIMAL);
    double av = (a.type == TYPE_DECIMAL) ? a.data.floatval : (double)a.data.intval;
    double bv = (b.type == TYPE_DECIMAL) ? b.data.floatval : (double)b.data.intval;
    int    ai = (a.type == TYPE_BOOL || a.type == TYPE_NUMBER) ? a.data.intval : (int)av;
    int    bi = (b.type == TYPE_BOOL || b.type == TYPE_NUMBER) ? b.data.intval : (int)bv;
    free_value(a); free_value(b);

    switch (op) {
        case OP_PLUS:
            return use_float ? make_float(av + bv) : make_int(ai + bi);
        case OP_MINUS:
            return use_float ? make_float(av - bv) : make_int(ai - bi);
        case OP_MULT:
            return use_float ? make_float(av * bv) : make_int(ai * bi);
        case OP_DIV:
            if (use_float) {
                if (bv == 0.0) {
                    fprintf(stderr, "ত্রুটি: শূন্য দিয়ে ভাগ।\n");
                    return make_float(0);
                }
                return make_float(av / bv);
            } else {
                if (bi == 0) {
                    fprintf(stderr, "ত্রুটি: শূন্য দিয়ে ভাগ।\n");
                    return make_int(0);
                }
                return make_int(ai / bi);
            }
        case OP_MOD:
            if (bi == 0) {
                fprintf(stderr, "ত্রুটি: শূন্য দিয়ে মডুলাস।\n");
                return make_int(0);
            }
            return make_int(ai % bi);
        case OP_AND:  return make_bool(ai != 0 && bi != 0);
        case OP_OR:   return make_bool(ai != 0 || bi != 0);
        case OP_EQ:   return use_float ? make_bool(av == bv) : make_bool(ai == bi);
        case OP_NEQ:  return use_float ? make_bool(av != bv) : make_bool(ai != bi);
        case OP_GT:   return use_float ? make_bool(av >  bv) : make_bool(ai >  bi);
        case OP_LT:   return use_float ? make_bool(av <  bv) : make_bool(ai <  bi);
        case OP_GTE:  return use_float ? make_bool(av >= bv) : make_bool(ai >= bi);
        case OP_LTE:  return use_float ? make_bool(av <= bv) : make_bool(ai <= bi);
        default:      return make_unknown();
    }
}
