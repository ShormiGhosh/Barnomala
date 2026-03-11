#include "symtable.h"

/* ================================================================== */
/*  FNV-1a hash — handles arbitrary UTF-8 bytes correctly              */
/* ================================================================== */
static unsigned int sym_hash(const char *key)
{
    unsigned int h = 2166136261u;
    while (*key) {
        h ^= (unsigned char)(*key++);
        h *= 16777619u;
    }
    return h % SYMTABLE_SIZE;
}

/* ================================================================== */
/*  Value constructors                                                  */
/* ================================================================== */
Value make_int(int v)
{
    Value val;
    memset(&val, 0, sizeof(val));
    val.type        = TYPE_NUMBER;
    val.data.intval = v;
    return val;
}

Value make_float(double v)
{
    Value val;
    memset(&val, 0, sizeof(val));
    val.type           = TYPE_DECIMAL;
    val.data.floatval  = v;
    return val;
}

Value make_bool(int v)
{
    Value val;
    memset(&val, 0, sizeof(val));
    val.type        = TYPE_BOOL;
    val.data.intval = (v != 0) ? 1 : 0;
    return val;
}

Value make_char(const char *v)
{
    Value val;
    memset(&val, 0, sizeof(val));
    val.type         = TYPE_CHAR;
    val.data.strval  = v ? strdup(v) : NULL;
    return val;
}

Value make_string(const char *v)
{
    Value val;
    memset(&val, 0, sizeof(val));
    val.type        = TYPE_STRING;
    val.data.strval = v ? strdup(v) : NULL;
    return val;
}

Value make_unknown(void)
{
    Value val;
    memset(&val, 0, sizeof(val));
    val.type        = TYPE_UNKNOWN;
    return val;
}

/* ================================================================== */
/*  Value helpers                                                       */
/* ================================================================== */
void free_value(Value v)
{
    if ((v.type == TYPE_STRING || v.type == TYPE_CHAR) && v.data.strval)
        free(v.data.strval);
}

Value copy_value(Value v)
{
    if (v.type == TYPE_STRING || v.type == TYPE_CHAR) {
        Value c;
        c.type        = v.type;
        c.data.strval = v.data.strval ? strdup(v.data.strval) : NULL;
        return c;
    }
    return v;   /* numeric types are trivially copyable */
}

const char *type_name(VarType t)
{
    switch (t) {
        case TYPE_NUMBER:  return "সংখ্যা";
        case TYPE_DECIMAL: return "দশমিক";
        case TYPE_BOOL:    return "বুলিয়ান";
        case TYPE_CHAR:    return "অক্ষর";
        case TYPE_STRING:  return "বাক্য";
        default:           return "অজানা";
    }
}

/*
 * Compatible pairs (declared ← given):
 *   NUMBER  ← BOOL    (bool treated as 0/1 integer)
 *   BOOL    ← NUMBER  (any non-zero int → true)
 *   DECIMAL ← NUMBER  (int promoted to double)
 *   Anything ← same type (trivially compatible)
 */
int types_compatible(VarType declared, VarType given)
{
    if (declared == given)                                return 1;
    if (declared == TYPE_DECIMAL && given == TYPE_NUMBER) return 1;
    if (declared == TYPE_NUMBER  && given == TYPE_DECIMAL) return 1;  /* truncate */
    if (declared == TYPE_BOOL    && given == TYPE_NUMBER) return 1;
    if (declared == TYPE_NUMBER  && given == TYPE_BOOL)   return 1;
    return 0;
}

/*
 * Coerce v to target_type.
 * If no valid coercion exists the original value is returned unchanged
 * and the caller is responsible for reporting the type error.
 */
Value coerce(Value v, VarType target)
{
    if (v.type == target)
        return copy_value(v);

    switch (target) {
        case TYPE_DECIMAL:
            if (v.type == TYPE_NUMBER)
                return make_float((double)v.data.intval);
            break;
        case TYPE_NUMBER:
            if (v.type == TYPE_DECIMAL)
                return make_int((int)v.data.floatval);
            if (v.type == TYPE_BOOL)
                return make_int(v.data.intval);
            break;
        case TYPE_BOOL:
            if (v.type == TYPE_NUMBER)
                return make_bool(v.data.intval != 0);
            if (v.type == TYPE_DECIMAL)
                return make_bool(v.data.floatval != 0.0);
            break;
        default:
            break;
    }
    /* No valid coercion — return a copy as-is */
    return copy_value(v);
}

void print_value(Value v)
{
    switch (v.type) {
        case TYPE_NUMBER:
            printf("%d", v.data.intval);
            break;
        case TYPE_DECIMAL:
            /* Print without trailing zeros when possible */
            if (v.data.floatval == (int)v.data.floatval)
                printf("%.1f", v.data.floatval);
            else
                printf("%g", v.data.floatval);
            break;
        case TYPE_BOOL:
            printf("%s", v.data.intval ? "সত্য" : "মিথ্যা");
            break;
        case TYPE_CHAR:
        case TYPE_STRING:
            /* Strip surrounding quotes if the lexer left them in */
            if (v.data.strval) {
                const char *s = v.data.strval;
                size_t len = strlen(s);
                if (len >= 2 && s[0] == '"' && s[len-1] == '"') {
                    fwrite(s + 1, 1, len - 2, stdout);
                } else if (len >= 2 && s[0] == '\'' && s[len-1] == '\'') {
                    fwrite(s + 1, 1, len - 2, stdout);
                } else {
                    printf("%s", s);
                }
            }
            break;
        default:
            printf("<অজানা>");
            break;
    }
}

/* ================================================================== */
/*  Scope stack                                                         */
/* ================================================================== */
static Scope *current_scope = NULL;

void symtable_init(void)
{
    /* If already initialised, free first */
    symtable_free();
    symtable_push_scope();   /* global scope */
}

void symtable_push_scope(void)
{
    Scope *s   = calloc(1, sizeof(Scope));
    if (!s) {
        fprintf(stderr, "মেমরি বরাদ্দ ব্যর্থ হয়েছে।\n");
        exit(1);
    }
    s->parent    = current_scope;
    current_scope = s;
}

/* Free every entry in a single bucket chain */
static void free_chain(SymbolEntry *e)
{
    while (e) {
        SymbolEntry *next = e->next;
        free(e->name);
        free_value(e->value);
        free(e);
        e = next;
    }
}

void symtable_pop_scope(void)
{
    if (!current_scope) return;

    Scope *old    = current_scope;
    current_scope = old->parent;

    for (int i = 0; i < SYMTABLE_SIZE; i++)
        free_chain(old->table[i]);

    free(old);
}

void symtable_free(void)
{
    while (current_scope)
        symtable_pop_scope();
}

/* ================================================================== */
/*  Core API                                                            */
/* ================================================================== */

int symtable_declare(const char *name, VarType type)
{
    if (!current_scope) {
        fprintf(stderr, "অভ্যন্তরীণ ত্রুটি: কোনো সক্রিয় স্কোপ নেই।\n");
        return -1;
    }

    unsigned int h = sym_hash(name);

    /* Redeclaration check — only in the CURRENT scope */
    for (SymbolEntry *e = current_scope->table[h]; e; e = e->next) {
        if (strcmp(e->name, name) == 0) {
            fprintf(stderr, "ত্রুটি (লাইন ?): '%s' ইতিমধ্যে এই ব্লকে ঘোষণা করা হয়েছে।\n",
                    name);
            return -1;
        }
    }

    SymbolEntry *entry      = calloc(1, sizeof(SymbolEntry));
    if (!entry) {
        fprintf(stderr, "মেমরি বরাদ্দ ব্যর্থ হয়েছে।\n");
        exit(1);
    }
    entry->name             = strdup(name);
    entry->type             = type;
    entry->value            = make_unknown();
    entry->is_initialized   = 0;
    /* Prepend to bucket chain */
    entry->next             = current_scope->table[h];
    current_scope->table[h] = entry;

    return 0;
}

int symtable_declare_assign(const char *name, VarType type, Value val)
{
    int rc = symtable_declare(name, type);
    if (rc != 0) return rc;
    return symtable_assign(name, val);
}

SymbolEntry *symtable_lookup(const char *name)
{
    unsigned int h = sym_hash(name);

    /* Walk from innermost scope outward */
    for (Scope *s = current_scope; s; s = s->parent) {
        for (SymbolEntry *e = s->table[h]; e; e = e->next) {
            if (strcmp(e->name, name) == 0)
                return e;
        }
    }
    return NULL;
}

int symtable_assign(const char *name, Value val)
{
    SymbolEntry *e = symtable_lookup(name);
    if (!e) {
        fprintf(stderr, "ত্রুটি: '%s' ঘোষণা করা হয়নি।\n", name);
        return -1;
    }

    if (!types_compatible(e->type, val.type)) {
        fprintf(stderr,
                "ত্রুটি: '%s' এ '%s' মান দেওয়া যাবে না। প্রত্যাশিত: '%s'।\n",
                name, type_name(val.type), type_name(e->type));
        return -2;
    }

    /* Free old heap string before overwriting */
    if ((e->type == TYPE_STRING || e->type == TYPE_CHAR) && e->value.data.strval)
        free(e->value.data.strval);

    e->value          = coerce(val, e->type);
    e->is_initialized = 1;
    return 0;
}

/* ================================================================== */
/*  Debug dump                                                          */
/* ================================================================== */
void symtable_dump(void)
{
    if (!current_scope) {
        printf("(কোনো সক্রিয় স্কোপ নেই)\n");
        return;
    }

    printf("\n========= Symbol Table Dump =========\n");
    int found = 0;
    for (int i = 0; i < SYMTABLE_SIZE; i++) {
        for (SymbolEntry *e = current_scope->table[i]; e; e = e->next) {
            printf("  %-24s  %-10s  ", e->name, type_name(e->type));
            if (e->is_initialized)
                print_value(e->value);
            else
                printf("<অনির্ধারিত>");
            printf("\n");
            found = 1;
        }
    }
    if (!found)
        printf("  (খালি)\n");
    printf("=====================================\n\n");
}

/* ================================================================== */
/*  Named Semantic Operations                                          */
/* ================================================================== */

/*
 * declare_variable
 * ----------------
 * Introduces `name` with `type` into the current scope.
 * Catches REDECLARATION: the same name in the same scope is an error.
 */
int declare_variable(const char *name, VarType type)
{
    if (!name || *name == '\0') {
        fprintf(stderr, "অভ্যন্তরীণ ত্রুটি: খালি ভেরিয়েবল নাম।\n");
        return -1;
    }

    /* symtable_declare already checks for redeclaration and prints the
       appropriate Bangla error message; just surface its return code. */
    int rc = symtable_declare(name, type);
    /* rc == -1  →  REDECLARATION (message already printed)  */
    return rc;
}

/*
 * assign_variable
 * ---------------
 * Stores `val` in the nearest visible binding of `name`.
 * Catches UNDECLARED USE (name not found) and TYPE MISMATCH.
 */
int assign_variable(const char *name, Value val)
{
    if (!name || *name == '\0') {
        fprintf(stderr, "অভ্যন্তরীণ ত্রুটি: খালি ভেরিয়েবল নাম।\n");
        return -1;
    }

    /* symtable_assign walks the scope chain, checks undeclared use   */
    /* (-1) and type mismatch (-2), and prints Bangla error messages. */
    int rc = symtable_assign(name, val);
    /* rc == -1  →  UNDECLARED USE    (message already printed)       */
    /* rc == -2  →  TYPE MISMATCH     (message already printed)       */
    return rc;
}

/*
 * lookup_variable
 * ---------------
 * Finds and returns the SymbolEntry for `name` (read access).
 * Catches UNDECLARED USE (returns NULL + error) and
 * UNINITIALIZED READ (returns entry + warning).
 */
SymbolEntry *lookup_variable(const char *name)
{
    if (!name || *name == '\0') {
        fprintf(stderr, "অভ্যন্তরীণ ত্রুটি: খালি ভেরিয়েবল নাম।\n");
        return NULL;
    }

    SymbolEntry *e = symtable_lookup(name);

    if (!e) {
        /* ── UNDECLARED USE ───────────────────────────────────────── */
        fprintf(stderr,
                "ত্রুটি: '%s' ব্যবহার করা হয়েছে কিন্তু ঘোষণা করা হয়নি।\n",
                name);
        return NULL;
    }

    if (!e->is_initialized) {
        /* ── UNINITIALIZED READ ───────────────────────────────────── */
        fprintf(stderr,
                "সতর্কতা: '%s' পড়া হচ্ছে কিন্তু এখনও কোনো মান দেওয়া হয়নি।\n",
                name);
        /* Return the entry anyway; caller may handle the warning. */
    }

    return e;
}
