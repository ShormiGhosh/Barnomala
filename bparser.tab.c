/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "bparser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <fcntl.h>
#ifdef _WIN32
/* Declare only what we need — including <windows.h> clashes with the
   Bison INPUT token because winuser.h also typedef-s a struct INPUT. */
extern unsigned int __stdcall SetConsoleCP(unsigned int wCodePageID);
extern unsigned int __stdcall SetConsoleOutputCP(unsigned int wCodePageID);
#endif
#include "symtable.h"   /* needed here so Value is visible in this prologue */

/* Op-code constants for eval_binop */
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

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern void init_indent();

/* Forward declaration — defined after the second %% */
static Value eval_binop(Value a, int op, Value b);

/* ------------------------------------------------------------------ */
/*  Execution suppression for if/else branching                        */
/*  suppress_execution > 0  →  all side effects are no-ops.           */
/*  nested ifs increment/decrement the counter, so nesting is safe.   */
/* ------------------------------------------------------------------ */
int suppress_execution = 0;          /* definition; extern in symtable.h */
static int cond_stack[256];
static int cond_top = 0;

static int is_truthy(Value v) {
    if (v.type == TYPE_DECIMAL) return v.data.floatval != 0.0;
    return v.data.intval != 0;
}

/* ------------------------------------------------------------------ */
/*  Bengali digit → ASCII conversion for runtime input                 */
/*  Bengali digits U+09E6–U+09EF are encoded as 3-byte UTF-8 sequences */
/*  E0 A7 A6 … E0 A7 AF. Replace each with its ASCII equivalent.      */
/* ------------------------------------------------------------------ */
static void bengali_digits_to_ascii(char *buf) {
    unsigned char *s = (unsigned char *)buf;
    unsigned char tmp[1024];
    int j = 0;
    for (int i = 0; s[i]; ) {
        /* Bengali digit: E0 A7 (A6..AF) */
        if (s[i] == 0xE0 && s[i+1] == 0xA7 && s[i+2] >= 0xA6 && s[i+2] <= 0xAF) {
            tmp[j++] = '0' + (s[i+2] - 0xA6);
            i += 3;
        } else {
            tmp[j++] = s[i++];
        }
    }
    tmp[j] = '\0';
    memcpy(buf, tmp, j + 1);
}

#line 147 "bparser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bparser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM_START = 3,              /* PROGRAM_START  */
  YYSYMBOL_PROGRAM_END = 4,                /* PROGRAM_END  */
  YYSYMBOL_NUMBER_TYPE = 5,                /* NUMBER_TYPE  */
  YYSYMBOL_DECIMAL_TYPE = 6,               /* DECIMAL_TYPE  */
  YYSYMBOL_BOOL_TYPE = 7,                  /* BOOL_TYPE  */
  YYSYMBOL_CHAR_TYPE = 8,                  /* CHAR_TYPE  */
  YYSYMBOL_STRING_TYPE = 9,                /* STRING_TYPE  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR_RANGE = 13,                 /* FOR_RANGE  */
  YYSYMBOL_FROM = 14,                      /* FROM  */
  YYSYMBOL_FUNCTION = 15,                  /* FUNCTION  */
  YYSYMBOL_BREAK = 16,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 17,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_PRINT = 19,                     /* PRINT  */
  YYSYMBOL_INPUT = 20,                     /* INPUT  */
  YYSYMBOL_LPAREN = 21,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 22,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 23,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 24,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_COLON = 26,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 27,                 /* SEMICOLON  */
  YYSYMBOL_ARRAY = 28,                     /* ARRAY  */
  YYSYMBOL_POW = 29,                       /* POW  */
  YYSYMBOL_SQRT = 30,                      /* SQRT  */
  YYSYMBOL_FLOOR = 31,                     /* FLOOR  */
  YYSYMBOL_CEIL = 32,                      /* CEIL  */
  YYSYMBOL_ABS = 33,                       /* ABS  */
  YYSYMBOL_INC = 34,                       /* INC  */
  YYSYMBOL_DEC = 35,                       /* DEC  */
  YYSYMBOL_BOOL_TRUE = 36,                 /* BOOL_TRUE  */
  YYSYMBOL_BOOL_FALSE = 37,                /* BOOL_FALSE  */
  YYSYMBOL_INCLUDE = 38,                   /* INCLUDE  */
  YYSYMBOL_INDENT = 39,                    /* INDENT  */
  YYSYMBOL_DEDENT = 40,                    /* DEDENT  */
  YYSYMBOL_NEWLINE = 41,                   /* NEWLINE  */
  YYSYMBOL_INT_LITERAL = 42,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 43,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 44,            /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 45,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 46,                /* IDENTIFIER  */
  YYSYMBOL_LOWER_THAN_ELSE = 47,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 48,                    /* UMINUS  */
  YYSYMBOL_PLUS = 49,                      /* PLUS  */
  YYSYMBOL_MINUS = 50,                     /* MINUS  */
  YYSYMBOL_MULT = 51,                      /* MULT  */
  YYSYMBOL_DIV = 52,                       /* DIV  */
  YYSYMBOL_MOD = 53,                       /* MOD  */
  YYSYMBOL_AND = 54,                       /* AND  */
  YYSYMBOL_OR = 55,                        /* OR  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_ASSIGN = 57,                    /* ASSIGN  */
  YYSYMBOL_EQUAL = 58,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 59,                 /* NOT_EQUAL  */
  YYSYMBOL_GREATER = 60,                   /* GREATER  */
  YYSYMBOL_LESS = 61,                      /* LESS  */
  YYSYMBOL_GREATER_EQUAL = 62,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 63,                /* LESS_EQUAL  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_program = 65,                   /* program  */
  YYSYMBOL_newlines = 66,                  /* newlines  */
  YYSYMBOL_optional_newlines = 67,         /* optional_newlines  */
  YYSYMBOL_statements = 68,                /* statements  */
  YYSYMBOL_statement = 69,                 /* statement  */
  YYSYMBOL_simple_statement = 70,          /* simple_statement  */
  YYSYMBOL_compound_statement = 71,        /* compound_statement  */
  YYSYMBOL_declaration = 72,               /* declaration  */
  YYSYMBOL_type = 73,                      /* type  */
  YYSYMBOL_assignment = 74,                /* assignment  */
  YYSYMBOL_input_statement = 75,           /* input_statement  */
  YYSYMBOL_print_statement = 76,           /* print_statement  */
  YYSYMBOL_suite = 77,                     /* suite  */
  YYSYMBOL_if_header = 78,                 /* if_header  */
  YYSYMBOL_else_header = 79,               /* else_header  */
  YYSYMBOL_if_statement = 80,              /* if_statement  */
  YYSYMBOL_while_statement = 81,           /* while_statement  */
  YYSYMBOL_for_statement = 82,             /* for_statement  */
  YYSYMBOL_function_definition = 83,       /* function_definition  */
  YYSYMBOL_parameter_list = 84,            /* parameter_list  */
  YYSYMBOL_function_call = 85,             /* function_call  */
  YYSYMBOL_argument_list = 86,             /* argument_list  */
  YYSYMBOL_return_statement = 87,          /* return_statement  */
  YYSYMBOL_break_statement = 88,           /* break_statement  */
  YYSYMBOL_continue_statement = 89,        /* continue_statement  */
  YYSYMBOL_increment_statement = 90,       /* increment_statement  */
  YYSYMBOL_decrement_statement = 91,       /* decrement_statement  */
  YYSYMBOL_array_declaration = 92,         /* array_declaration  */
  YYSYMBOL_array_elements = 93,            /* array_elements  */
  YYSYMBOL_array_access = 94,              /* array_access  */
  YYSYMBOL_expression = 95,                /* expression  */
  YYSYMBOL_primary_expression = 96,        /* primary_expression  */
  YYSYMBOL_math_function = 97              /* math_function  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   691

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  205

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   138,   145,   146,   149,   151,   154,   156,
     157,   161,   162,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   180,   181,   182,   183,   187,   192,
     204,   205,   206,   207,   208,   212,   221,   272,   283,   284,
     288,   298,   307,   312,   320,   327,   338,   342,   349,   353,
     360,   365,   373,   374,   378,   385,   392,   399,   417,   435,
     440,   447,   448,   452,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     485,   494,   495,   496,   497,   498,   505,   506,   507,   508,
     509,   510,   514,   521,   527,   533,   539
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM_START",
  "PROGRAM_END", "NUMBER_TYPE", "DECIMAL_TYPE", "BOOL_TYPE", "CHAR_TYPE",
  "STRING_TYPE", "IF", "ELSE", "WHILE", "FOR_RANGE", "FROM", "FUNCTION",
  "BREAK", "CONTINUE", "RETURN", "PRINT", "INPUT", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "COMMA", "COLON", "SEMICOLON", "ARRAY", "POW",
  "SQRT", "FLOOR", "CEIL", "ABS", "INC", "DEC", "BOOL_TRUE", "BOOL_FALSE",
  "INCLUDE", "INDENT", "DEDENT", "NEWLINE", "INT_LITERAL", "FLOAT_LITERAL",
  "STRING_LITERAL", "CHAR_LITERAL", "IDENTIFIER", "LOWER_THAN_ELSE",
  "UMINUS", "PLUS", "MINUS", "MULT", "DIV", "MOD", "AND", "OR", "NOT",
  "ASSIGN", "EQUAL", "NOT_EQUAL", "GREATER", "LESS", "GREATER_EQUAL",
  "LESS_EQUAL", "$accept", "program", "newlines", "optional_newlines",
  "statements", "statement", "simple_statement", "compound_statement",
  "declaration", "type", "assignment", "input_statement",
  "print_statement", "suite", "if_header", "else_header", "if_statement",
  "while_statement", "for_statement", "function_definition",
  "parameter_list", "function_call", "argument_list", "return_statement",
  "break_statement", "continue_statement", "increment_statement",
  "decrement_statement", "array_declaration", "array_elements",
  "array_access", "expression", "primary_expression", "math_function", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      17,   -29,    37,   -77,     2,   527,   -77,   -77,   544,   -77,
     -77,   -77,   -77,   -77,   -77,   635,   635,    25,     4,    14,
      24,   635,   635,    31,    32,   -77,   -13,   -77,    16,   -77,
     -77,    18,   -77,   -77,   -77,     8,   -77,   -77,   -77,   -77,
      28,   -77,   -77,   -77,   -77,   -77,   -77,   -77,    33,   635,
      52,    54,    61,    62,    85,   -77,   -77,   -77,   -77,   -77,
     -77,    10,   635,   635,   -77,   -77,   140,   -77,   -77,   158,
      65,    86,   -77,   -77,   200,   215,    66,   130,   607,    81,
      87,   635,   -77,   -18,    76,    75,   107,   -77,    33,   -77,
     234,   635,   635,   635,   635,   635,   635,   105,   105,   635,
     -77,   635,   635,   635,   635,   635,   635,   635,   635,   635,
     635,   635,   635,   635,     8,   103,   -11,   -77,   -77,   104,
     106,   -77,     7,   425,   -77,   -77,   276,   -77,   635,   -77,
     -77,   115,     8,   -77,   257,   291,   310,   333,   352,   375,
     -77,    91,    91,   105,   105,   105,     9,   467,    71,    71,
      51,    51,    51,    51,   -77,   635,   119,   -77,    20,   121,
      84,   -77,   635,   -77,   394,   586,   -77,   -77,   635,   -77,
     -77,   -77,   -77,   -77,   451,     8,   120,   109,   -77,   126,
     425,   -77,   -77,   409,   635,   -77,     8,   -77,   108,   -77,
     125,   -77,   128,     8,   -17,   -77,   -77,   133,   635,    -6,
     425,   131,   635,   -77,   425
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,     0,     4,     8,     0,     1,     5,     0,     6,
      30,    31,    32,    33,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     9,     0,    12,
      13,     0,    14,    15,    16,     0,    24,    25,    26,    27,
       0,    17,    18,    19,    20,    21,    22,     6,     3,     0,
       0,     0,     0,     0,     0,    86,    87,    81,    82,    83,
      84,    85,     0,     0,    89,    88,     0,    64,    90,     0,
       0,     0,    55,    56,     0,     0,     0,     0,     0,     0,
       0,     0,    11,     0,     0,     0,    42,    23,     2,     7,
       0,     0,     0,     0,     0,     0,     0,    80,    79,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    37,     0,
       0,    51,     0,    52,    57,    58,     0,    28,     0,     8,
      38,     0,     0,    91,     0,     0,     0,     0,     0,     0,
      78,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    44,     0,     0,    48,     0,     0,
       0,    50,     0,    35,     0,     0,    41,    43,     0,    93,
      94,    95,    96,    63,     0,     0,     0,     0,    36,     0,
      53,    29,    39,     0,     0,    47,     0,    49,     0,    92,
      78,    46,     0,     0,     0,    45,    59,     0,     0,     0,
      61,     0,     0,    60,    62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -77,   110,     0,   -77,    -3,   -77,   -77,    82,
     -77,   -77,   -77,   -76,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,    -5,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -15,   -77,   -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     4,    48,     5,    27,    85,    29,    30,    31,
      32,    33,    34,    86,    35,   132,    36,    37,    38,    39,
     158,    64,   122,    41,    42,    43,    44,    45,    46,   199,
      65,    66,    67,    68
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    69,    28,    40,     8,    28,    74,    75,    78,   127,
     196,   156,     3,    10,    11,    12,    13,    14,   201,   202,
       1,    79,    80,    99,    19,    20,    21,    22,    23,   161,
      40,    78,   162,    96,    90,   157,    24,     6,   154,   128,
     197,    72,   176,     7,    81,   177,    70,    97,    98,    84,
      71,    73,    76,    77,    26,    87,   167,    82,   101,   102,
     103,   104,   105,   123,    83,    99,   126,   108,   109,   110,
     111,   112,   113,    91,    89,    92,   134,   135,   136,   137,
     138,   139,    93,    94,   140,    99,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   185,
     101,   102,   103,   104,   105,    99,    95,   116,   124,    40,
     191,   115,   119,   164,   125,   129,   130,   195,   131,    99,
     101,   102,   103,   104,   105,   155,   159,    40,   160,   165,
     179,   110,   111,   112,   113,    10,    11,    12,    13,    14,
     174,   166,   103,   104,   105,   175,   186,   180,   178,   188,
     192,   193,   194,   183,    99,   187,   198,    88,   203,   120,
      40,     0,    28,     0,     0,     0,   100,     0,     0,   190,
      40,     0,    99,     0,     0,     0,     0,     0,     0,     0,
       0,    40,     0,   200,   114,     0,     0,   204,    40,   101,
     102,   103,   104,   105,   106,   107,     0,     0,   108,   109,
     110,   111,   112,   113,     0,     0,     0,   101,   102,   103,
     104,   105,   106,   107,    99,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,     0,     0,   117,     0,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,     0,     0,     0,     0,     0,    99,   101,
     102,   103,   104,   105,   106,   107,   133,     0,   108,   109,
     110,   111,   112,   113,   101,   102,   103,   104,   105,   106,
     107,    99,     0,   108,   109,   110,   111,   112,   113,     0,
       0,     0,   168,   101,   102,   103,   104,   105,   106,   107,
      99,     0,   108,   109,   110,   111,   112,   113,     0,     0,
       0,     0,     0,   163,     0,    99,   101,   102,   103,   104,
     105,   106,   107,   169,     0,   108,   109,   110,   111,   112,
     113,     0,     0,     0,    99,   101,   102,   103,   104,   105,
     106,   107,   170,     0,   108,   109,   110,   111,   112,   113,
     101,   102,   103,   104,   105,   106,   107,    99,     0,   108,
     109,   110,   111,   112,   113,   171,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,    99,     0,   108,   109,
     110,   111,   112,   113,   172,     0,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,    99,
       0,   108,   109,   110,   111,   112,   113,     0,     0,   173,
       0,   101,   102,   103,   104,   105,   106,   107,    99,     0,
     108,   109,   110,   111,   112,   113,     0,     0,     0,     0,
       0,   181,     0,    99,   101,   102,   103,   104,   105,   106,
     107,   189,     0,   108,   109,   110,   111,   112,   113,    99,
       0,     0,     0,   101,   102,   103,   104,   105,   106,   107,
       0,     0,   108,   109,   110,   111,   112,   113,   101,   102,
     103,   104,   105,   106,   107,   184,     0,   108,   109,   110,
     111,   112,   113,     0,   101,   102,   103,   104,   105,   106,
     107,    99,     0,   108,   109,   110,   111,   112,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,   112,   113,     0,   101,   102,   103,   104,
     105,   106,     0,     0,     0,   108,   109,   110,   111,   112,
     113,     9,    10,    11,    12,    13,    14,    15,     0,    16,
      17,     0,    18,    19,    20,    21,    22,    23,    47,    10,
      11,    12,    13,    14,    15,    24,    16,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,    25,     0,
       0,     0,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,     0,     0,     0,     0,
      26,    10,    11,    12,    13,    14,    15,     0,    16,    17,
       0,    18,    19,    20,    21,    22,    23,     0,     0,     0,
       0,     0,     0,     0,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,    25,    49,   121,
       0,     0,    26,     0,     0,     0,    50,    51,    52,    53,
      54,     0,     0,    55,    56,     0,     0,     0,     0,    57,
      58,    59,    60,    61,     0,     0,    49,    62,     0,     0,
       0,     0,     0,    63,    50,    51,    52,    53,    54,     0,
       0,    55,    56,     0,     0,     0,     0,    57,    58,    59,
      60,    61,     0,     0,     0,    62,     0,     0,     0,     0,
       0,    63
};

static const yytype_int16 yycheck[] =
{
       5,    16,     5,     8,     4,     8,    21,    22,    21,    27,
      27,    22,    41,     5,     6,     7,     8,     9,    24,    25,
       3,    34,    35,    14,    16,    17,    18,    19,    20,    22,
      35,    21,    25,    23,    49,    46,    28,     0,   114,    57,
      57,    27,    22,    41,    57,    25,    21,    62,    63,    41,
      46,    27,    21,    21,    46,    27,   132,    41,    49,    50,
      51,    52,    53,    78,    46,    14,    81,    58,    59,    60,
      61,    62,    63,    21,    41,    21,    91,    92,    93,    94,
      95,    96,    21,    21,    99,    14,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   175,
      49,    50,    51,    52,    53,    14,    21,    21,    27,   114,
     186,    46,    46,   128,    27,    39,    41,   193,    11,    14,
      49,    50,    51,    52,    53,    22,    22,   132,    22,   129,
      46,    60,    61,    62,    63,     5,     6,     7,     8,     9,
     155,    26,    51,    52,    53,    26,    26,   162,    27,    23,
      42,    26,    24,   168,    14,    46,    23,    47,    27,    77,
     165,    -1,   165,    -1,    -1,    -1,    26,    -1,    -1,   184,
     175,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   186,    -1,   198,    26,    -1,    -1,   202,   193,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    14,    -1,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    27,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    14,    49,
      50,    51,    52,    53,    54,    55,    22,    -1,    58,    59,
      60,    61,    62,    63,    49,    50,    51,    52,    53,    54,
      55,    14,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    25,    49,    50,    51,    52,    53,    54,    55,
      14,    -1,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    14,    49,    50,    51,    52,
      53,    54,    55,    22,    -1,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    14,    49,    50,    51,    52,    53,
      54,    55,    22,    -1,    58,    59,    60,    61,    62,    63,
      49,    50,    51,    52,    53,    54,    55,    14,    -1,    58,
      59,    60,    61,    62,    63,    22,    -1,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    14,    -1,    58,    59,
      60,    61,    62,    63,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    14,
      -1,    58,    59,    60,    61,    62,    63,    -1,    -1,    24,
      -1,    49,    50,    51,    52,    53,    54,    55,    14,    -1,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    14,    49,    50,    51,    52,    53,    54,
      55,    22,    -1,    58,    59,    60,    61,    62,    63,    14,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    58,    59,    60,    61,    62,    63,    49,    50,
      51,    52,    53,    54,    55,    14,    -1,    58,    59,    60,
      61,    62,    63,    -1,    49,    50,    51,    52,    53,    54,
      55,    14,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,     4,     5,
       6,     7,     8,     9,    10,    28,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    28,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      46,     5,     6,     7,     8,     9,    10,    -1,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    21,    22,
      -1,    -1,    46,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    42,
      43,    44,    45,    46,    -1,    -1,    21,    50,    -1,    -1,
      -1,    -1,    -1,    56,    29,    30,    31,    32,    33,    -1,
      -1,    36,    37,    -1,    -1,    -1,    -1,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    56
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    65,    41,    66,    68,     0,    41,    68,     4,
       5,     6,     7,     8,     9,    10,    12,    13,    15,    16,
      17,    18,    19,    20,    28,    41,    46,    69,    70,    71,
      72,    73,    74,    75,    76,    78,    80,    81,    82,    83,
      85,    87,    88,    89,    90,    91,    92,     4,    67,    21,
      29,    30,    31,    32,    33,    36,    37,    42,    43,    44,
      45,    46,    50,    56,    85,    94,    95,    96,    97,    95,
      21,    46,    27,    27,    95,    95,    21,    21,    21,    34,
      35,    57,    41,    46,    41,    70,    77,    27,    67,    41,
      95,    21,    21,    21,    21,    21,    23,    95,    95,    14,
      26,    49,    50,    51,    52,    53,    54,    55,    58,    59,
      60,    61,    62,    63,    26,    46,    21,    27,    27,    46,
      73,    22,    86,    95,    27,    27,    95,    27,    57,    39,
      41,    11,    79,    22,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    77,    22,    22,    46,    84,    22,
      22,    22,    25,    27,    95,    68,    26,    77,    25,    22,
      22,    22,    22,    24,    95,    26,    22,    25,    27,    46,
      95,    27,    40,    95,    14,    77,    26,    46,    23,    22,
      95,    77,    42,    26,    24,    77,    27,    57,    23,    93,
      95,    24,    25,    27,    95
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    72,    72,
      73,    73,    73,    73,    73,    74,    75,    76,    77,    77,
      78,    79,    80,    80,    81,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    88,    89,    90,    91,    92,
      92,    93,    93,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    97,    97,    97,    97,    97
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     1,     2,     0,     2,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     3,     5,
       1,     1,     1,     1,     1,     4,     5,     3,     2,     4,
       3,     2,     2,     4,     4,     9,     7,     6,     1,     3,
       4,     3,     1,     3,     3,     2,     2,     3,     3,     9,
      13,     1,     3,     4,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     6,     4,     4,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: PROGRAM_START newlines statements PROGRAM_END optional_newlines  */
#line 135 "bparser.y"
    {
        printf("✓ Program parsed successfully!\n");
    }
#line 1473 "bparser.tab.c"
    break;

  case 3: /* program: PROGRAM_START statements PROGRAM_END optional_newlines  */
#line 139 "bparser.y"
    {
        printf("✓ Program parsed successfully!\n");
    }
#line 1481 "bparser.tab.c"
    break;

  case 28: /* declaration: type IDENTIFIER SEMICOLON  */
#line 188 "bparser.y"
    {
        if (!suppress_execution) declare_variable((yyvsp[-1].strval), (yyvsp[-2].vtype));
        free((yyvsp[-1].strval));
    }
#line 1490 "bparser.tab.c"
    break;

  case 29: /* declaration: type IDENTIFIER ASSIGN expression SEMICOLON  */
#line 193 "bparser.y"
    {
        if (!suppress_execution) {
            declare_variable((yyvsp[-3].strval), (yyvsp[-4].vtype));
            assign_variable((yyvsp[-3].strval), (yyvsp[-1].val));
        }
        free_value((yyvsp[-1].val));
        free((yyvsp[-3].strval));
    }
#line 1503 "bparser.tab.c"
    break;

  case 30: /* type: NUMBER_TYPE  */
#line 204 "bparser.y"
                 { (yyval.vtype) = TYPE_NUMBER;  }
#line 1509 "bparser.tab.c"
    break;

  case 31: /* type: DECIMAL_TYPE  */
#line 205 "bparser.y"
                   { (yyval.vtype) = TYPE_DECIMAL; }
#line 1515 "bparser.tab.c"
    break;

  case 32: /* type: BOOL_TYPE  */
#line 206 "bparser.y"
                   { (yyval.vtype) = TYPE_BOOL;    }
#line 1521 "bparser.tab.c"
    break;

  case 33: /* type: CHAR_TYPE  */
#line 207 "bparser.y"
                   { (yyval.vtype) = TYPE_CHAR;    }
#line 1527 "bparser.tab.c"
    break;

  case 34: /* type: STRING_TYPE  */
#line 208 "bparser.y"
                   { (yyval.vtype) = TYPE_STRING;  }
#line 1533 "bparser.tab.c"
    break;

  case 35: /* assignment: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 213 "bparser.y"
    {
        if (!suppress_execution) assign_variable((yyvsp[-3].strval), (yyvsp[-1].val));
        free_value((yyvsp[-1].val));
        free((yyvsp[-3].strval));
    }
#line 1543 "bparser.tab.c"
    break;

  case 36: /* input_statement: INPUT LPAREN IDENTIFIER RPAREN SEMICOLON  */
#line 222 "bparser.y"
    {
        if (!suppress_execution) {
        /* Use raw lookup — this is write access (initialization), not a read.
           lookup_variable would emit a spurious "uninitialized" warning here. */
        SymbolEntry *e = symtable_lookup((yyvsp[-2].strval));
        if (!e) {
            fprintf(stderr, "ত্রুটি (লাইন %d): '%s' ঘোষণা করা হয়নি।\n", yylineno, (yyvsp[-2].strval));
        } else {
            switch (e->type) {
                case TYPE_NUMBER: {
                    char buf[64];
                    if (fgets(buf, sizeof(buf), stdin)) {
                        buf[strcspn(buf, "\n")] = '\0';
                        bengali_digits_to_ascii(buf);
                        assign_variable((yyvsp[-2].strval), make_int(atoi(buf)));
                    }
                    break;
                }
                case TYPE_DECIMAL: {
                    char buf[64];
                    if (fgets(buf, sizeof(buf), stdin)) {
                        buf[strcspn(buf, "\n")] = '\0';
                        bengali_digits_to_ascii(buf);
                        assign_variable((yyvsp[-2].strval), make_float(atof(buf)));
                    }
                    break;
                }
                case TYPE_STRING: {
                    char buf[1024];
                    if (fgets(buf, sizeof(buf), stdin)) {
                        buf[strcspn(buf, "\n")] = '\0';
                        assign_variable((yyvsp[-2].strval), make_string(buf));
                    }
                    break;
                }
                case TYPE_BOOL: {
                    int v = 0;
                    if (scanf("%d", &v) == 1)
                        assign_variable((yyvsp[-2].strval), make_bool(v));
                    break;
                }
                default: break;
            }
        }
        } /* end if (!suppress_execution) */
        free((yyvsp[-2].strval));
    }
#line 1595 "bparser.tab.c"
    break;

  case 37: /* print_statement: PRINT expression SEMICOLON  */
#line 273 "bparser.y"
    {
        if (!suppress_execution) {
            print_value((yyvsp[-1].val));
            printf("\n");
        }
        free_value((yyvsp[-1].val));
    }
#line 1607 "bparser.tab.c"
    break;

  case 40: /* if_header: IF expression COLON  */
#line 289 "bparser.y"
    {
        int cond = is_truthy((yyvsp[-1].val));
        free_value((yyvsp[-1].val));
        cond_stack[cond_top++] = cond;
        if (!cond) suppress_execution++;
    }
#line 1618 "bparser.tab.c"
    break;

  case 41: /* else_header: ELSE COLON  */
#line 299 "bparser.y"
    {
        int cond = cond_stack[cond_top - 1];   /* peek — do NOT pop yet */
        if (!cond) suppress_execution--;        /* undo then-suppression  */
        if ( cond) suppress_execution++;        /* start else-suppression */
    }
#line 1628 "bparser.tab.c"
    break;

  case 42: /* if_statement: if_header suite  */
#line 308 "bparser.y"
    {
        int cond = cond_stack[--cond_top];
        if (!cond) suppress_execution--;
    }
#line 1637 "bparser.tab.c"
    break;

  case 43: /* if_statement: if_header suite else_header suite  */
#line 313 "bparser.y"
    {
        int cond = cond_stack[--cond_top];
        if ( cond) suppress_execution--;        /* undo else-suppression  */
    }
#line 1646 "bparser.tab.c"
    break;

  case 44: /* while_statement: WHILE expression COLON suite  */
#line 321 "bparser.y"
    {
        free_value((yyvsp[-2].val));
    }
#line 1654 "bparser.tab.c"
    break;

  case 45: /* for_statement: FOR_RANGE LPAREN IDENTIFIER RPAREN expression FROM expression COLON suite  */
#line 328 "bparser.y"
    {
        /* auto-declare loop variable if it wasn't declared by the user */
        if (!symtable_lookup((yyvsp[-6].strval)))
            declare_variable((yyvsp[-6].strval), TYPE_NUMBER);
        free_value((yyvsp[-4].val)); free_value((yyvsp[-2].val));
        free((yyvsp[-6].strval));
    }
#line 1666 "bparser.tab.c"
    break;

  case 46: /* function_definition: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN COLON suite  */
#line 339 "bparser.y"
    {
        free((yyvsp[-5].strval));
    }
#line 1674 "bparser.tab.c"
    break;

  case 47: /* function_definition: FUNCTION IDENTIFIER LPAREN RPAREN COLON suite  */
#line 343 "bparser.y"
    {
        free((yyvsp[-4].strval));
    }
#line 1682 "bparser.tab.c"
    break;

  case 48: /* parameter_list: IDENTIFIER  */
#line 350 "bparser.y"
    {
        free((yyvsp[0].strval));
    }
#line 1690 "bparser.tab.c"
    break;

  case 49: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 354 "bparser.y"
    {
        free((yyvsp[0].strval));
    }
#line 1698 "bparser.tab.c"
    break;

  case 50: /* function_call: IDENTIFIER LPAREN argument_list RPAREN  */
#line 361 "bparser.y"
    {
        free((yyvsp[-3].strval));
        (yyval.val) = make_unknown();  /* function execution not yet implemented */
    }
#line 1707 "bparser.tab.c"
    break;

  case 51: /* function_call: IDENTIFIER LPAREN RPAREN  */
#line 366 "bparser.y"
    {
        free((yyvsp[-2].strval));
        (yyval.val) = make_unknown();
    }
#line 1716 "bparser.tab.c"
    break;

  case 52: /* argument_list: expression  */
#line 373 "bparser.y"
                                     { free_value((yyvsp[0].val)); }
#line 1722 "bparser.tab.c"
    break;

  case 53: /* argument_list: argument_list COMMA expression  */
#line 374 "bparser.y"
                                     { free_value((yyvsp[0].val)); }
#line 1728 "bparser.tab.c"
    break;

  case 54: /* return_statement: RETURN expression SEMICOLON  */
#line 379 "bparser.y"
    {
        free_value((yyvsp[-1].val));
    }
#line 1736 "bparser.tab.c"
    break;

  case 55: /* break_statement: BREAK SEMICOLON  */
#line 386 "bparser.y"
    {
        if (!suppress_execution) printf("Break statement\n");
    }
#line 1744 "bparser.tab.c"
    break;

  case 56: /* continue_statement: CONTINUE SEMICOLON  */
#line 393 "bparser.y"
    {
        if (!suppress_execution) printf("Continue statement\n");
    }
#line 1752 "bparser.tab.c"
    break;

  case 57: /* increment_statement: IDENTIFIER INC SEMICOLON  */
#line 400 "bparser.y"
    {
        if (!suppress_execution) {
            SymbolEntry *e = lookup_variable((yyvsp[-2].strval));
            if (e) {
                if (e->type == TYPE_NUMBER)
                    assign_variable((yyvsp[-2].strval), make_int(e->value.data.intval + 1));
                else if (e->type == TYPE_DECIMAL)
                    assign_variable((yyvsp[-2].strval), make_float(e->value.data.floatval + 1.0));
                else
                    fprintf(stderr, "ত্রুটি (লাইন %d): '%s' সংখ্যা বা দশমিক নয়, বাড়ানো যাবে না।\n", yylineno, (yyvsp[-2].strval));
            }
        }
        free((yyvsp[-2].strval));
    }
#line 1771 "bparser.tab.c"
    break;

  case 58: /* decrement_statement: IDENTIFIER DEC SEMICOLON  */
#line 418 "bparser.y"
    {
        if (!suppress_execution) {
            SymbolEntry *e = lookup_variable((yyvsp[-2].strval));
            if (e) {
                if (e->type == TYPE_NUMBER)
                    assign_variable((yyvsp[-2].strval), make_int(e->value.data.intval - 1));
                else if (e->type == TYPE_DECIMAL)
                    assign_variable((yyvsp[-2].strval), make_float(e->value.data.floatval - 1.0));
                else
                    fprintf(stderr, "ত্রুটি (লাইন %d): '%s' সংখ্যা বা দশমিক নয়, কমানো যাবে না।\n", yylineno, (yyvsp[-2].strval));
            }
        }
        free((yyvsp[-2].strval));
    }
#line 1790 "bparser.tab.c"
    break;

  case 59: /* array_declaration: ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET SEMICOLON  */
#line 436 "bparser.y"
    {
        /* Arrays not yet backed by runtime storage — parsed only */
        free((yyvsp[-4].strval));
    }
#line 1799 "bparser.tab.c"
    break;

  case 60: /* array_declaration: ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET ASSIGN LBRACKET array_elements RBRACKET SEMICOLON  */
#line 441 "bparser.y"
    {
        free((yyvsp[-8].strval));
    }
#line 1807 "bparser.tab.c"
    break;

  case 61: /* array_elements: expression  */
#line 447 "bparser.y"
                                     { free_value((yyvsp[0].val)); }
#line 1813 "bparser.tab.c"
    break;

  case 62: /* array_elements: array_elements COMMA expression  */
#line 448 "bparser.y"
                                      { free_value((yyvsp[0].val)); }
#line 1819 "bparser.tab.c"
    break;

  case 63: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 453 "bparser.y"
    {
        free_value((yyvsp[-1].val));
        free((yyvsp[-3].strval));
        (yyval.val) = make_unknown();  /* array runtime not yet implemented */
    }
#line 1829 "bparser.tab.c"
    break;

  case 64: /* expression: primary_expression  */
#line 461 "bparser.y"
                                          { (yyval.val) = (yyvsp[0].val); }
#line 1835 "bparser.tab.c"
    break;

  case 65: /* expression: expression PLUS expression  */
#line 462 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_PLUS,  (yyvsp[0].val)); }
#line 1841 "bparser.tab.c"
    break;

  case 66: /* expression: expression MINUS expression  */
#line 463 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_MINUS, (yyvsp[0].val)); }
#line 1847 "bparser.tab.c"
    break;

  case 67: /* expression: expression MULT expression  */
#line 464 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_MULT,  (yyvsp[0].val)); }
#line 1853 "bparser.tab.c"
    break;

  case 68: /* expression: expression DIV expression  */
#line 465 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_DIV,   (yyvsp[0].val)); }
#line 1859 "bparser.tab.c"
    break;

  case 69: /* expression: expression MOD expression  */
#line 466 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_MOD,   (yyvsp[0].val)); }
#line 1865 "bparser.tab.c"
    break;

  case 70: /* expression: expression AND expression  */
#line 467 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_AND,   (yyvsp[0].val)); }
#line 1871 "bparser.tab.c"
    break;

  case 71: /* expression: expression OR expression  */
#line 468 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_OR,    (yyvsp[0].val)); }
#line 1877 "bparser.tab.c"
    break;

  case 72: /* expression: expression EQUAL expression  */
#line 469 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_EQ,    (yyvsp[0].val)); }
#line 1883 "bparser.tab.c"
    break;

  case 73: /* expression: expression NOT_EQUAL expression  */
#line 470 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_NEQ,   (yyvsp[0].val)); }
#line 1889 "bparser.tab.c"
    break;

  case 74: /* expression: expression GREATER expression  */
#line 471 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_GT,    (yyvsp[0].val)); }
#line 1895 "bparser.tab.c"
    break;

  case 75: /* expression: expression LESS expression  */
#line 472 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_LT,    (yyvsp[0].val)); }
#line 1901 "bparser.tab.c"
    break;

  case 76: /* expression: expression GREATER_EQUAL expression  */
#line 473 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_GTE,   (yyvsp[0].val)); }
#line 1907 "bparser.tab.c"
    break;

  case 77: /* expression: expression LESS_EQUAL expression  */
#line 474 "bparser.y"
                                          { (yyval.val) = eval_binop((yyvsp[-2].val), OP_LTE,   (yyvsp[0].val)); }
#line 1913 "bparser.tab.c"
    break;

  case 78: /* expression: expression FROM expression  */
#line 475 "bparser.y"
                                          { free_value((yyvsp[0].val)); (yyval.val) = (yyvsp[-2].val); }
#line 1919 "bparser.tab.c"
    break;

  case 79: /* expression: NOT expression  */
#line 477 "bparser.y"
    {
        int bval;
        if      ((yyvsp[0].val).type == TYPE_DECIMAL) bval = ((yyvsp[0].val).data.floatval == 0.0) ? 1 : 0;
        else if ((yyvsp[0].val).type == TYPE_BOOL)    bval = ((yyvsp[0].val).data.intval   == 0)   ? 1 : 0;
        else                              bval = ((yyvsp[0].val).data.intval   == 0)   ? 1 : 0;
        free_value((yyvsp[0].val));
        (yyval.val) = make_bool(bval);
    }
#line 1932 "bparser.tab.c"
    break;

  case 80: /* expression: MINUS expression  */
#line 486 "bparser.y"
    {
        if ((yyvsp[0].val).type == TYPE_DECIMAL) (yyval.val) = make_float(-(yyvsp[0].val).data.floatval);
        else                         (yyval.val) = make_int  (-(yyvsp[0].val).data.intval);
        free_value((yyvsp[0].val));
    }
#line 1942 "bparser.tab.c"
    break;

  case 81: /* primary_expression: INT_LITERAL  */
#line 494 "bparser.y"
                             { (yyval.val) = make_int((yyvsp[0].intval)); }
#line 1948 "bparser.tab.c"
    break;

  case 82: /* primary_expression: FLOAT_LITERAL  */
#line 495 "bparser.y"
                             { (yyval.val) = make_float((yyvsp[0].floatval)); }
#line 1954 "bparser.tab.c"
    break;

  case 83: /* primary_expression: STRING_LITERAL  */
#line 496 "bparser.y"
                             { (yyval.val) = make_string((yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 1960 "bparser.tab.c"
    break;

  case 84: /* primary_expression: CHAR_LITERAL  */
#line 497 "bparser.y"
                             { (yyval.val) = make_char((yyvsp[0].strval));   free((yyvsp[0].strval)); }
#line 1966 "bparser.tab.c"
    break;

  case 85: /* primary_expression: IDENTIFIER  */
#line 499 "bparser.y"
    {
        /* lookup_variable reports undeclared-use and uninitialized-read errors */
        SymbolEntry *e = lookup_variable((yyvsp[0].strval));
        (yyval.val) = e ? copy_value(e->value) : make_unknown();
        free((yyvsp[0].strval));
    }
#line 1977 "bparser.tab.c"
    break;

  case 86: /* primary_expression: BOOL_TRUE  */
#line 505 "bparser.y"
                             { (yyval.val) = make_bool(1); }
#line 1983 "bparser.tab.c"
    break;

  case 87: /* primary_expression: BOOL_FALSE  */
#line 506 "bparser.y"
                             { (yyval.val) = make_bool(0); }
#line 1989 "bparser.tab.c"
    break;

  case 88: /* primary_expression: array_access  */
#line 507 "bparser.y"
                             { (yyval.val) = (yyvsp[0].val); }
#line 1995 "bparser.tab.c"
    break;

  case 89: /* primary_expression: function_call  */
#line 508 "bparser.y"
                             { (yyval.val) = (yyvsp[0].val); }
#line 2001 "bparser.tab.c"
    break;

  case 90: /* primary_expression: math_function  */
#line 509 "bparser.y"
                             { (yyval.val) = (yyvsp[0].val); }
#line 2007 "bparser.tab.c"
    break;

  case 91: /* primary_expression: LPAREN expression RPAREN  */
#line 510 "bparser.y"
                               { (yyval.val) = (yyvsp[-1].val); }
#line 2013 "bparser.tab.c"
    break;

  case 92: /* math_function: POW LPAREN expression COMMA expression RPAREN  */
#line 515 "bparser.y"
    {
        double base = ((yyvsp[-3].val).type == TYPE_DECIMAL) ? (yyvsp[-3].val).data.floatval : (double)(yyvsp[-3].val).data.intval;
        double exp  = ((yyvsp[-1].val).type == TYPE_DECIMAL) ? (yyvsp[-1].val).data.floatval : (double)(yyvsp[-1].val).data.intval;
        free_value((yyvsp[-3].val)); free_value((yyvsp[-1].val));
        (yyval.val) = make_float(pow(base, exp));
    }
#line 2024 "bparser.tab.c"
    break;

  case 93: /* math_function: SQRT LPAREN expression RPAREN  */
#line 522 "bparser.y"
    {
        double v = ((yyvsp[-1].val).type == TYPE_DECIMAL) ? (yyvsp[-1].val).data.floatval : (double)(yyvsp[-1].val).data.intval;
        free_value((yyvsp[-1].val));
        (yyval.val) = make_float(sqrt(v));
    }
#line 2034 "bparser.tab.c"
    break;

  case 94: /* math_function: FLOOR LPAREN expression RPAREN  */
#line 528 "bparser.y"
    {
        double v = ((yyvsp[-1].val).type == TYPE_DECIMAL) ? (yyvsp[-1].val).data.floatval : (double)(yyvsp[-1].val).data.intval;
        free_value((yyvsp[-1].val));
        (yyval.val) = make_int((int)floor(v));
    }
#line 2044 "bparser.tab.c"
    break;

  case 95: /* math_function: CEIL LPAREN expression RPAREN  */
#line 534 "bparser.y"
    {
        double v = ((yyvsp[-1].val).type == TYPE_DECIMAL) ? (yyvsp[-1].val).data.floatval : (double)(yyvsp[-1].val).data.intval;
        free_value((yyvsp[-1].val));
        (yyval.val) = make_int((int)ceil(v));
    }
#line 2054 "bparser.tab.c"
    break;

  case 96: /* math_function: ABS LPAREN expression RPAREN  */
#line 540 "bparser.y"
    {
        if ((yyvsp[-1].val).type == TYPE_DECIMAL) {
            (yyval.val) = make_float(fabs((yyvsp[-1].val).data.floatval));
        } else {
            (yyval.val) = make_int(abs((yyvsp[-1].val).data.intval));
        }
        free_value((yyvsp[-1].val));
    }
#line 2067 "bparser.tab.c"
    break;


#line 2071 "bparser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 550 "bparser.y"


/* ================================================================== */
/*  Runtime binary-operator evaluator                                  */
/* ================================================================== */
static Value eval_binop(Value a, int op, Value b)
{
    /* ---- String concatenation for PLUS ---- */
    if (op == OP_PLUS &&
        (a.type == TYPE_STRING || b.type == TYPE_STRING ||
         a.type == TYPE_CHAR   || b.type == TYPE_CHAR)) {
        char buf[4096] = {0};

        /* Helper: append a Value's text to buf */
        #define APPEND_VAL(v)  do {                                    \
            if ((v).type == TYPE_STRING || (v).type == TYPE_CHAR) {    \
                const char *s = (v).data.strval ? (v).data.strval : "";\
                size_t len = strlen(s);                                 \
                if (len >= 2 && (s[0]=='"'||s[0]=='\''))               \
                    strncat(buf, s+1, len-2);                          \
                else strcat(buf, s);                                    \
            } else if ((v).type == TYPE_DECIMAL) {                     \
                char tmp[64]; snprintf(tmp,sizeof(tmp),"%g",(v).data.floatval); strcat(buf,tmp); \
            } else {                                                    \
                char tmp[64]; snprintf(tmp,sizeof(tmp),"%d",(v).data.intval);   strcat(buf,tmp); \
            }                                                           \
        } while(0)

        APPEND_VAL(a);
        APPEND_VAL(b);
        #undef APPEND_VAL
        free_value(a); free_value(b);
        return make_string(buf);
    }

    /* ---- Numeric promotion ---- */
    int   use_float = (a.type == TYPE_DECIMAL || b.type == TYPE_DECIMAL);
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
                if (bv == 0.0) { fprintf(stderr, "ত্রুটি: শূন্য দিয়ে ভাগ।\n"); return make_float(0); }
                return make_float(av / bv);
            } else {
                if (bi == 0) { fprintf(stderr, "ত্রুটি: শূন্য দিয়ে ভাগ।\n"); return make_int(0); }
                return make_int(ai / bi);
            }
        case OP_MOD:
            if (bi == 0) { fprintf(stderr, "ত্রুটি: শূন্য দিয়ে মডুলাস।\n"); return make_int(0); }
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

void yyerror(const char *s) {
    fprintf(stderr, "✗ Syntax error at line %d: %s\n", yylineno, s);
}

/* Normalize precomposed Bengali characters to decomposed form */
/* This ensures য় (U+09DF = E0 A7 9F) is always represented as য + ় (E0 A6 AF + E0 A6 BC) */
FILE* normalize_input(FILE *input) {
    fseek(input, 0, SEEK_END);
    long fsize = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    unsigned char *buf = malloc(fsize + 1);
    long actual = fread(buf, 1, fsize, input);
    fclose(input);
    
    /* Output buffer: worst case each 3-byte char becomes 6 bytes */
    unsigned char *out = malloc(actual * 2 + 1);
    long olen = 0;
    
    for (long i = 0; i < actual; ) {
        /* Check for E0 A7 9F (য় U+09DF) -> E0 A6 AF E0 A6 BC */
        if (i + 2 < fsize && buf[i] == 0xE0 && buf[i+1] == 0xA7 && buf[i+2] == 0x9F) {
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xAF;  /* য */
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xBC;  /* ় */
            i += 3;
        }
        /* Check for E0 A7 9C (ড় U+09DC) -> E0 A6 A1 E0 A6 BC */
        else if (i + 2 < fsize && buf[i] == 0xE0 && buf[i+1] == 0xA7 && buf[i+2] == 0x9C) {
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xA1;  /* ড */
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xBC;  /* ় */
            i += 3;
        }
        /* Check for E0 A7 9D (ঢ় U+09DD) -> E0 A6 A2 E0 A6 BC */
        else if (i + 2 < fsize && buf[i] == 0xE0 && buf[i+1] == 0xA7 && buf[i+2] == 0x9D) {
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xA2;  /* ঢ */
            out[olen++] = 0xE0; out[olen++] = 0xA6; out[olen++] = 0xBC;  /* ় */
            i += 3;
        }
        else {
            out[olen++] = buf[i++];
        }
    }
    
    free(buf);
    
    FILE *tmp = tmpfile();
    fwrite(out, 1, olen, tmp);
    fseek(tmp, 0, SEEK_SET);
    free(out);
    
    return tmp;
}

int main(int argc, char *argv[]) {
    /* Switch the Windows console to UTF-8 so Bengali input/output is not
       mangled into '?' by the default ANSI code page. Works in both
       Windows Terminal and MSYS2 mintty. */
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    setlocale(LC_ALL, "en_US.UTF-8");
    /* Keep stdout/stderr in binary mode to prevent \r\n mangling.
       Do NOT set stdin to binary — let the console CP handle encoding. */
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stderr), _O_BINARY);

    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    
    /* Normalize Unicode before parsing */
    yyin = normalize_input(fp);  /* fp is closed inside normalize_input */
    init_indent();  /* Initialize indentation tracking */
    
    printf("=== Parsing Bangla Program ===\n\n");

    symtable_init();   /* initialise global symbol table */

    int result = yyparse();

    symtable_free();   /* release all symbol table memory */
    fclose(yyin);

    if (result == 0) {
        printf("\n=== Parsing Complete ===\n");
        return 0;
    } else {
        printf("\n=== Parsing Failed ===\n");
        return 1;
    }
}
