#ifndef AST_H
#define AST_H

#include "symtable.h"

/* ================================================================== */
/*  Op-code constants (shared by bparser.y and ast.c)                 */
/* ================================================================== */
#define OP_PLUS  1
#define OP_MINUS 2
#define OP_MULT  3
#define OP_DIV   4
#define OP_MOD   5
#define OP_AND   6
#define OP_OR    7
#define OP_EQ    8
#define OP_NEQ   9
#define OP_GT   10
#define OP_LT   11
#define OP_GTE  12
#define OP_LTE  13

/* ================================================================== */
/*  AST Node Kinds                                                      */
/* ================================================================== */
typedef enum {
    /* --- Expressions --- */
    N_INT_LIT,       /* ival                                          */
    N_FLOAT_LIT,     /* fval                                          */
    N_STRING_LIT,    /* sval (heap)                                   */
    N_CHAR_LIT,      /* sval (heap)                                   */
    N_BOOL_LIT,      /* ival: 1=সত্য, 0=মিথ্যা                       */
    N_IDENT,         /* sval = variable name                          */
    N_BINOP,         /* ival=op, left, right                          */
    N_UNARY_NOT,     /* left = operand                                */
    N_UNARY_NEG,     /* left = operand                                */
    N_CALL,          /* sval=funcname, left=arg_list (N_ARG_LIST)     */
    N_MATH_POW,      /* left=base, right=exponent                     */
    N_MATH_SQRT,     /* left=operand                                  */
    N_MATH_FLOOR,    /* left=operand                                  */
    N_MATH_CEIL,     /* left=operand                                  */
    N_MATH_ABS,      /* left=operand                                  */
    N_ARRAY_ACCESS,  /* sval=array name, left=index expr              */
    N_ARG_LIST,      /* left=expr, right=next N_ARG_LIST (prepended)  */

    /* --- Statements --- */
    N_SEQ,           /* left=prev stmts, right=this stmt              */
    N_DECL,          /* sval=name, vtype=type, left=init_expr/NULL    */
    N_ASSIGN,        /* sval=name, left=expr                          */
    N_PRINT,         /* left=expr                                      */
    N_INPUT,         /* sval=varname                                   */
    N_IF,            /* left=cond, right=then_body, extra=else_body   */
    N_WHILE,         /* left=cond, right=body                         */
    N_FOR_RANGE,     /* sval=varname, left=start, right=end, extra=body */
    N_BREAK,
    N_CONTINUE,
    N_RETURN,        /* left=expr                                      */
    N_INC,           /* sval=varname                                   */
    N_DEC,           /* sval=varname                                   */
    N_FUNCDEF,       /* sval=funcname, left=param_list, right=body    */
    N_PARAM_LIST,    /* sval=paramname, right=next N_PARAM_LIST        */
    N_ARRAY_DECL,    /* sval=name, vtype=elem_type, ival=size,
                        left=init_list (N_INIT_LIST) or NULL          */
    N_INIT_LIST,     /* left=expr, right=next N_INIT_LIST (prepended) */
    N_CALL_STMT,     /* left = N_CALL used as a statement              */
    N_NOP,           /* empty / no-op                                  */
} NodeKind;

/* ================================================================== */
/*  AST Node                                                            */
/* ================================================================== */
typedef struct AstNode {
    NodeKind kind;
    int      ival;        /* int literal, bool value, op code          */
    double   fval;        /* float literal                              */
    char    *sval;        /* heap-allocated identifier/string literal  */
    VarType  vtype;       /* declared type for N_DECL / N_ARRAY_DECL  */
    int      lineno;      /* source line number (for diagnostics)      */
    struct AstNode *left;
    struct AstNode *right;
    struct AstNode *extra; /* else-body (N_IF), for-body (N_FOR_RANGE) */
} AstNode;

/* ================================================================== */
/*  Execution signal — propagates break / continue / return upwards   */
/* ================================================================== */
typedef enum {
    EXEC_NORMAL   = 0,
    EXEC_BREAK    = 1,
    EXEC_CONTINUE = 2,
    EXEC_RETURN   = 3,
} ExecSignal;

typedef struct {
    ExecSignal signal;
    Value      retval;   /* meaningful only when signal == EXEC_RETURN */
} ExecResult;

/* ================================================================== */
/*  Constructor / Destructor                                            */
/* ================================================================== */
AstNode *node_new  (NodeKind kind, int lineno);
void     node_free (AstNode *n);

/* ================================================================== */
/*  Function Table                                                      */
/*  Stores user-defined function bodies at runtime.                     */
/*  Each entry takes OWNERSHIP of name, params, and body.              */
/* ================================================================== */
typedef struct FuncEntry {
    char             *name;    /* heap-allocated function name         */
    AstNode          *params;  /* N_PARAM_LIST chain (right-linked)    */
    AstNode          *body;    /* statement body                       */
    struct FuncEntry *next;    /* hash-chain collision list            */
} FuncEntry;

void       func_table_init   (void);
void       func_table_free   (void);
int        func_table_define (char *name, AstNode *params, AstNode *body);
FuncEntry *func_table_lookup (const char *name);

/* ================================================================== */
/*  Interpreter entry points                                            */
/* ================================================================== */
Value      eval_expr (AstNode *n);   /* evaluate an expression node  */
ExecResult exec_stmt (AstNode *n);   /* execute a statement node     */

#endif /* AST_H */
