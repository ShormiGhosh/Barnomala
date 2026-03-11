#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================== */
/*  Variable Types                                                      */
/*  Mirrors the 5 Bangla data types declared in bparser.y              */
/* ================================================================== */
typedef enum {
    TYPE_NUMBER,    /* সংখ্যা  — integer                  */
    TYPE_DECIMAL,   /* দশমিক   — double                   */
    TYPE_BOOL,      /* বুলিয়ান — 0 (মিথ্যা) / 1 (সত্য)  */
    TYPE_CHAR,      /* অক্ষর   — single UTF-8 character   */
    TYPE_STRING,    /* বাক্য   — heap-allocated string    */
    TYPE_UNKNOWN    /* sentinel / unresolved               */
} VarType;

/* ================================================================== */
/*  Runtime Value                                                       */
/*  A tagged union — type field always indicates which member is live  */
/* ================================================================== */
typedef struct {
    VarType type;
    union {
        int    intval;    /* TYPE_NUMBER, TYPE_BOOL             */
        double floatval;  /* TYPE_DECIMAL                       */
        char  *strval;    /* TYPE_CHAR, TYPE_STRING  (heap ptr) */
    } data;
} Value;

/* ------------------------------------------------------------------ */
/*  Value constructors  (all return by value, strings are deep-copied) */
/* ------------------------------------------------------------------ */
Value make_int   (int v);
Value make_float (double v);
Value make_bool  (int v);           /* 0 = মিথ্যা, non-zero = সত্য */
Value make_char  (const char *v);   /* copies the UTF-8 string      */
Value make_string(const char *v);   /* copies the UTF-8 string      */
Value make_unknown(void);           /* placeholder uninitialized val */

/* ------------------------------------------------------------------ */
/*  Value helpers                                                       */
/* ------------------------------------------------------------------ */
Value       coerce(Value v, VarType target);          /* implicit cast     */
int         types_compatible(VarType declared,
                             VarType given);          /* 1 = ok, 0 = error */
const char *type_name(VarType t);                     /* Bangla type name  */
void        print_value(Value v);                     /* prints to stdout  */
void        free_value(Value v);                      /* frees strval heap */
Value       copy_value(Value v);                      /* deep copy         */

/* ================================================================== */
/*  Symbol Table Entry                                                  */
/* ================================================================== */
#define SYMTABLE_SIZE 256   /* hash-table bucket count (power of 2)  */

typedef struct SymbolEntry {
    char              *name;            /* heap-allocated variable name */
    VarType            type;            /* declared type                */
    Value              value;           /* current runtime value        */
    int                is_initialized;  /* 0 until first assignment     */
    struct SymbolEntry *next;           /* linked list for chaining     */
} SymbolEntry;

/* ================================================================== */
/*  Scope                                                               */
/*  Each function call (and global level) owns one Scope.              */
/*  Scopes are chained as a stack; lookup walks the parent chain.      */
/* ================================================================== */
typedef struct Scope {
    SymbolEntry  *table[SYMTABLE_SIZE]; /* hash buckets                 */
    struct Scope *parent;               /* enclosing scope (NULL=global)*/
} Scope;

/* ================================================================== */
/*  Symbol Table API                                                    */
/* ================================================================== */

/* Initialise — must be called once before any other function */
void symtable_init(void);

/* Scope management */
void symtable_push_scope(void);   /* enter new block / function  */
void symtable_pop_scope(void);    /* leave current block / func  */

/*
 * Declare a variable in the CURRENT scope.
 * Returns  0  on success.
 * Returns -1  if the name already exists in the current scope
 *             (redeclaration error — message printed to stderr).
 */
int  symtable_declare(const char *name, VarType type);

/*
 * Declare AND immediately assign in one step (e.g. সংখ্যা x = 5।)
 * Returns  0  on success.
 * Returns -1  on redeclaration.
 * Returns -2  on type mismatch.
 */
int  symtable_declare_assign(const char *name, VarType type, Value val);

/*
 * Assign a new value to an ALREADY-DECLARED variable.
 * Walks the scope chain — the nearest visible binding is updated.
 * Returns  0  on success.
 * Returns -1  if the variable is not declared anywhere.
 * Returns -2  on type mismatch.
 */
int  symtable_assign(const char *name, Value val);

/*
 * Look up a variable.  Walks the scope chain (inner → outer).
 * Returns a pointer to the SymbolEntry, or NULL if not found.
 * The caller must NOT free the returned pointer.
 */
SymbolEntry *symtable_lookup(const char *name);

/* Release all memory (all scopes popped and freed) */
void symtable_free(void);

/* Debug: print contents of current scope to stdout */
void symtable_dump(void);

/* ================================================================== */
/*  Named Semantic Operations                                          */
/*  Parser / interpreter call-sites should use these rather than the  */
/*  raw symtable_* primitives; they carry explicit error semantics.   */
/* ================================================================== */

/*
 * declare_variable — introduce a new name into the current scope.
 *
 * Error caught:
 *   REDECLARATION : name already exists in the current scope.
 *
 * Returns  0 on success.
 * Returns -1 on redeclaration (message printed to stderr).
 */
int declare_variable(const char *name, VarType type);

/*
 * assign_variable — store a value into an already-declared variable.
 * Walks the full scope chain to find the binding.
 *
 * Errors caught:
 *   UNDECLARED USE : variable not found in any enclosing scope.
 *   TYPE MISMATCH  : value type incompatible with the declared type.
 *
 * Returns  0 on success.
 * Returns -1 if undeclared (message printed to stderr).
 * Returns -2 on type mismatch (message printed to stderr).
 */
int assign_variable(const char *name, Value val);

/*
 * lookup_variable — retrieve a variable's entry for reading.
 * Walks the full scope chain (inner → outer).
 *
 * Errors caught:
 *   UNDECLARED USE  : variable not found in any scope    → error,   returns NULL.
 *   UNINITIALIZED   : declared but never assigned a value → warning, returns entry.
 *
 * Returns a pointer to the SymbolEntry, or NULL if not found.
 * The caller must NOT free the returned pointer.
 */
SymbolEntry *lookup_variable(const char *name);

#endif /* SYMTABLE_H */
