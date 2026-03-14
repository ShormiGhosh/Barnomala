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
extern unsigned int __stdcall SetConsoleCP(unsigned int wCodePageID);
extern unsigned int __stdcall SetConsoleOutputCP(unsigned int wCodePageID);
#endif
#include "ast.h"   /* brings in symtable.h, AstNode, OP_*, eval_expr, exec_stmt */
#include "irgen.h"

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern void init_indent();

/* suppress_execution referenced by symtable.c; always 0 in AST mode */
int suppress_execution = 0;

static int   g_emit_ir = 0;
static FILE *g_ir_out = NULL;
static const char *g_ir_path = NULL;

#line 99 "bparser.tab.c"

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
  YYSYMBOL_LENGTH = 34,                    /* LENGTH  */
  YYSYMBOL_INC = 35,                       /* INC  */
  YYSYMBOL_DEC = 36,                       /* DEC  */
  YYSYMBOL_BOOL_TRUE = 37,                 /* BOOL_TRUE  */
  YYSYMBOL_BOOL_FALSE = 38,                /* BOOL_FALSE  */
  YYSYMBOL_INCLUDE = 39,                   /* INCLUDE  */
  YYSYMBOL_INDENT = 40,                    /* INDENT  */
  YYSYMBOL_DEDENT = 41,                    /* DEDENT  */
  YYSYMBOL_NEWLINE = 42,                   /* NEWLINE  */
  YYSYMBOL_INT_LITERAL = 43,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 44,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 45,            /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 46,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 47,                /* IDENTIFIER  */
  YYSYMBOL_LOWER_THAN_ELSE = 48,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 49,                    /* UMINUS  */
  YYSYMBOL_PLUS = 50,                      /* PLUS  */
  YYSYMBOL_MINUS = 51,                     /* MINUS  */
  YYSYMBOL_MULT = 52,                      /* MULT  */
  YYSYMBOL_DIV = 53,                       /* DIV  */
  YYSYMBOL_MOD = 54,                       /* MOD  */
  YYSYMBOL_AND = 55,                       /* AND  */
  YYSYMBOL_OR = 56,                        /* OR  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_ASSIGN = 58,                    /* ASSIGN  */
  YYSYMBOL_EQUAL = 59,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 60,                 /* NOT_EQUAL  */
  YYSYMBOL_GREATER = 61,                   /* GREATER  */
  YYSYMBOL_LESS = 62,                      /* LESS  */
  YYSYMBOL_GREATER_EQUAL = 63,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 64,                /* LESS_EQUAL  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_program = 66,                   /* program  */
  YYSYMBOL_newlines = 67,                  /* newlines  */
  YYSYMBOL_optional_newlines = 68,         /* optional_newlines  */
  YYSYMBOL_statements = 69,                /* statements  */
  YYSYMBOL_statement = 70,                 /* statement  */
  YYSYMBOL_simple_statement = 71,          /* simple_statement  */
  YYSYMBOL_compound_statement = 72,        /* compound_statement  */
  YYSYMBOL_declaration = 73,               /* declaration  */
  YYSYMBOL_type = 74,                      /* type  */
  YYSYMBOL_assignment = 75,                /* assignment  */
  YYSYMBOL_input_statement = 76,           /* input_statement  */
  YYSYMBOL_print_statement = 77,           /* print_statement  */
  YYSYMBOL_suite = 78,                     /* suite  */
  YYSYMBOL_if_header = 79,                 /* if_header  */
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
  YYSYMBOL_array_assignment = 92,          /* array_assignment  */
  YYSYMBOL_array_declaration = 93,         /* array_declaration  */
  YYSYMBOL_array_elements = 94,            /* array_elements  */
  YYSYMBOL_array_access = 95,              /* array_access  */
  YYSYMBOL_expression = 96,                /* expression  */
  YYSYMBOL_primary_expression = 97,        /* primary_expression  */
  YYSYMBOL_math_function = 98              /* math_function  */
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
#define YYLAST   722

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  215

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   319


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    94,    94,   110,   129,   130,   133,   135,   142,   145,
     156,   163,   164,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   188,   189,   190,   191,   195,
     203,   214,   215,   216,   217,   218,   222,   232,   241,   250,
     251,   255,   259,   267,   278,   288,   300,   308,   319,   326,
     336,   343,   353,   360,   370,   379,   386,   393,   402,   411,
     422,   431,   443,   450,   460,   470,   471,   473,   475,   477,
     479,   481,   483,   485,   487,   489,   491,   493,   495,   497,
     502,   508,   517,   523,   529,   535,   541,   547,   553,   559,
     560,   561,   562,   566,   573,   579,   585,   591,   597
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
  "SQRT", "FLOOR", "CEIL", "ABS", "LENGTH", "INC", "DEC", "BOOL_TRUE",
  "BOOL_FALSE", "INCLUDE", "INDENT", "DEDENT", "NEWLINE", "INT_LITERAL",
  "FLOAT_LITERAL", "STRING_LITERAL", "CHAR_LITERAL", "IDENTIFIER",
  "LOWER_THAN_ELSE", "UMINUS", "PLUS", "MINUS", "MULT", "DIV", "MOD",
  "AND", "OR", "NOT", "ASSIGN", "EQUAL", "NOT_EQUAL", "GREATER", "LESS",
  "GREATER_EQUAL", "LESS_EQUAL", "$accept", "program", "newlines",
  "optional_newlines", "statements", "statement", "simple_statement",
  "compound_statement", "declaration", "type", "assignment",
  "input_statement", "print_statement", "suite", "if_header",
  "if_statement", "while_statement", "for_statement",
  "function_definition", "parameter_list", "function_call",
  "argument_list", "return_statement", "break_statement",
  "continue_statement", "increment_statement", "decrement_statement",
  "array_assignment", "array_declaration", "array_elements",
  "array_access", "expression", "primary_expression", "math_function", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-68)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,   -32,    19,   -68,   -16,   554,   -68,   -68,   571,   -68,
     -68,   -68,   -68,   -68,   -68,   665,   665,    10,   -23,    12,
      16,   665,   665,    13,    31,   -68,     6,   -68,    25,   -68,
     -68,   -10,   -68,   -68,   -68,   123,   -68,   -68,   -68,   -68,
      59,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,    45,
     665,    68,    82,    83,    88,    89,    90,   -68,   -68,   -68,
     -68,   -68,   -68,    -1,   665,   665,   -68,   -68,   149,   -68,
     -68,   164,    65,    95,   -68,   -68,   180,   223,    70,     7,
     636,   665,    92,    93,   665,   -68,   -18,    81,    80,   112,
     -68,    45,   -68,   207,   665,   665,   665,   665,   665,    77,
     665,   111,   111,   665,   -68,   665,   665,   665,   665,   665,
     665,   665,   665,   665,   665,   665,   665,   665,   123,   104,
     -11,   -68,   -68,   113,   115,   -68,    -4,   462,   240,   -68,
     -68,   283,   -68,   665,   -68,   -68,   107,   -68,   298,   266,
     318,   341,   361,   116,   384,   -68,    54,    54,   111,   111,
     111,    -6,   493,     9,     9,    24,    24,    24,    24,   -68,
     665,   118,   -68,     3,   119,   100,   -68,   665,    91,   -68,
     404,   614,   123,   665,   -68,   -68,   -68,   -68,   -68,   -68,
     478,   123,   122,   103,   -68,   130,   462,   665,   -68,   -68,
     -68,   419,   665,   -68,   123,   -68,   114,   435,   -68,   128,
     -68,   131,   -68,   123,    57,   -68,   -68,   133,   665,     8,
     462,   132,   665,   -68,   462
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,     0,     4,     8,     0,     1,     5,     0,     6,
      31,    32,    33,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     9,     0,    12,
      13,     0,    14,    16,    17,     0,    25,    26,    27,    28,
       0,    18,    19,    20,    21,    22,    15,    23,     6,     3,
       0,     0,     0,     0,     0,     0,     0,    87,    88,    82,
      83,    84,    85,    86,     0,     0,    90,    89,     0,    65,
      91,     0,     0,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,    42,
      24,     2,     7,     0,     0,     0,     0,     0,     0,     0,
       0,    81,    80,     0,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    38,     0,     0,    51,     0,    52,     0,    57,
      58,     0,    29,     0,     8,    39,     0,    92,     0,     0,
       0,     0,     0,     0,     0,    79,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    44,
       0,     0,    48,     0,     0,     0,    50,     0,     0,    36,
       0,     0,     0,     0,    94,    95,    96,    97,    98,    64,
       0,     0,     0,     0,    37,     0,    53,     0,    30,    40,
      43,     0,     0,    47,     0,    49,     0,     0,    93,    79,
      46,     0,    59,     0,     0,    45,    60,     0,     0,     0,
      62,     0,     0,    61,    63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,   -68,   121,     0,   -68,    -3,   -68,   -68,    85,
     -68,   -68,   -68,   -67,   -68,   -68,   -68,   -68,   -68,   -68,
      -5,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -15,   -68,   -68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     4,    49,     5,    27,    88,    29,    30,    31,
      32,    33,    34,    89,    35,    36,    37,    38,    39,   163,
      66,   126,    41,    42,    43,    44,    45,    46,    47,   209,
      67,    68,    69,    70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    71,    28,    40,     8,    28,    76,    77,   103,   132,
       3,   161,    10,    11,    12,    13,    14,     1,   166,     6,
      80,   167,   100,   103,    73,   182,     7,    80,   183,    81,
      40,    72,   211,   212,    78,    93,   162,    86,   103,    74,
     133,    82,    83,    75,   105,   106,   107,   108,   109,   101,
     102,   159,    79,   112,   113,   114,   115,   116,   117,   105,
     106,   107,   108,   109,    84,   127,   128,    85,   103,   131,
     114,   115,   116,   117,   105,   106,   107,   108,   109,   138,
     139,   140,   141,   142,   206,   144,    90,    92,   145,    94,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,    95,    96,   190,   107,   108,   109,    97,
      98,    99,   119,    40,   193,   207,   120,   123,   170,   129,
     130,   134,   135,   136,   143,   103,   160,   200,    10,    11,
      12,    13,    14,   172,   171,   164,   205,   165,   178,    19,
      20,    21,    22,    23,   181,   180,   184,   185,   194,   187,
     195,    24,   186,   196,   203,   204,   208,   201,   191,   213,
       0,     0,     0,   103,   124,    87,    40,    40,    28,    91,
      26,     0,   197,     0,     0,   104,    40,   199,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    40,
     118,     0,     0,   210,   103,     0,     0,   214,    40,   105,
     106,   107,   108,   109,   110,   111,     0,   121,   112,   113,
     114,   115,   116,   117,   105,   106,   107,   108,   109,   110,
     111,   103,     0,   112,   113,   114,   115,   116,   117,   137,
     105,   106,   107,   108,   109,   110,   111,   103,     0,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,     0,
     122,     0,     0,     0,   103,     0,     0,   105,   106,   107,
     108,   109,   110,   111,   168,     0,   112,   113,   114,   115,
     116,   117,     0,   105,   106,   107,   108,   109,   110,   111,
     103,     0,   112,   113,   114,   115,   116,   117,   174,     0,
     105,   106,   107,   108,   109,   110,   111,   103,     0,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,     0,
     169,     0,   103,     0,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   173,     0,   112,   113,   114,   115,   116,
     117,     0,   103,   105,   106,   107,   108,   109,   110,   111,
     175,     0,   112,   113,   114,   115,   116,   117,   105,   106,
     107,   108,   109,   110,   111,   103,     0,   112,   113,   114,
     115,   116,   117,   176,     0,     0,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   103,     0,   112,   113,   114,
     115,   116,   117,   177,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,   111,   103,     0,
     112,   113,   114,   115,   116,   117,     0,     0,   179,     0,
       0,   105,   106,   107,   108,   109,   110,   111,   103,     0,
     112,   113,   114,   115,   116,   117,     0,     0,     0,     0,
       0,   188,     0,   103,   105,   106,   107,   108,   109,   110,
     111,   198,     0,   112,   113,   114,   115,   116,   117,   103,
       0,     0,     0,     0,   105,   106,   107,   108,   109,   110,
     111,     0,   202,   112,   113,   114,   115,   116,   117,   105,
     106,   107,   108,   109,   110,   111,   103,     0,   112,   113,
     114,   115,   116,   117,     0,   105,   106,   107,   108,   109,
     110,   111,   192,     0,   112,   113,   114,   115,   116,   117,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
       0,     0,   105,   106,   107,   108,   109,   110,   111,     0,
       0,   112,   113,   114,   115,   116,   117,     0,   105,   106,
     107,   108,   109,   110,   111,     0,     0,   112,   113,   114,
     115,   116,   117,   105,   106,   107,   108,   109,   110,     0,
       0,     0,   112,   113,   114,   115,   116,   117,     9,    10,
      11,    12,    13,    14,    15,     0,    16,    17,     0,    18,
      19,    20,    21,    22,    23,    48,    10,    11,    12,    13,
      14,    15,    24,    16,    17,     0,    18,    19,    20,    21,
      22,    23,     0,     0,     0,     0,    25,     0,     0,    24,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     0,     0,     0,    26,    10,
      11,    12,    13,    14,    15,     0,    16,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   189,    25,    50,   125,     0,
       0,    26,     0,     0,     0,    51,    52,    53,    54,    55,
      56,     0,     0,    57,    58,     0,     0,     0,     0,    59,
      60,    61,    62,    63,     0,     0,    50,    64,     0,     0,
       0,     0,     0,    65,    51,    52,    53,    54,    55,    56,
       0,     0,    57,    58,     0,     0,     0,     0,    59,    60,
      61,    62,    63,     0,     0,     0,    64,     0,     0,     0,
       0,     0,    65
};

static const yytype_int16 yycheck[] =
{
       5,    16,     5,     8,     4,     8,    21,    22,    14,    27,
      42,    22,     5,     6,     7,     8,     9,     3,    22,     0,
      21,    25,    23,    14,    47,    22,    42,    21,    25,    23,
      35,    21,    24,    25,    21,    50,    47,    47,    14,    27,
      58,    35,    36,    27,    50,    51,    52,    53,    54,    64,
      65,   118,    21,    59,    60,    61,    62,    63,    64,    50,
      51,    52,    53,    54,    58,    80,    81,    42,    14,    84,
      61,    62,    63,    64,    50,    51,    52,    53,    54,    94,
      95,    96,    97,    98,    27,   100,    27,    42,   103,    21,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,    21,    21,   172,    52,    53,    54,    21,
      21,    21,    47,   118,   181,    58,    21,    47,   133,    27,
      27,    40,    42,    11,    47,    14,    22,   194,     5,     6,
       7,     8,     9,    26,   134,    22,   203,    22,    22,    16,
      17,    18,    19,    20,    26,   160,    27,    47,    26,    58,
      47,    28,   167,    23,    26,    24,    23,    43,   173,    27,
      -1,    -1,    -1,    14,    79,    42,   171,   172,   171,    48,
      47,    -1,   187,    -1,    -1,    26,   181,   192,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   194,
      26,    -1,    -1,   208,    14,    -1,    -1,   212,   203,    50,
      51,    52,    53,    54,    55,    56,    -1,    27,    59,    60,
      61,    62,    63,    64,    50,    51,    52,    53,    54,    55,
      56,    14,    -1,    59,    60,    61,    62,    63,    64,    22,
      50,    51,    52,    53,    54,    55,    56,    14,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    14,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    24,    -1,    59,    60,    61,    62,
      63,    64,    -1,    50,    51,    52,    53,    54,    55,    56,
      14,    -1,    59,    60,    61,    62,    63,    64,    22,    -1,
      50,    51,    52,    53,    54,    55,    56,    14,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    14,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    25,    -1,    59,    60,    61,    62,    63,
      64,    -1,    14,    50,    51,    52,    53,    54,    55,    56,
      22,    -1,    59,    60,    61,    62,    63,    64,    50,    51,
      52,    53,    54,    55,    56,    14,    -1,    59,    60,    61,
      62,    63,    64,    22,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    14,    -1,    59,    60,    61,
      62,    63,    64,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    14,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    24,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    14,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    14,    50,    51,    52,    53,    54,    55,
      56,    22,    -1,    59,    60,    61,    62,    63,    64,    14,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    -1,    27,    59,    60,    61,    62,    63,    64,    50,
      51,    52,    53,    54,    55,    56,    14,    -1,    59,    60,
      61,    62,    63,    64,    -1,    50,    51,    52,    53,    54,
      55,    56,    14,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    59,    60,    61,    62,    63,    64,    -1,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    59,    60,    61,
      62,    63,    64,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    64,     4,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,     4,     5,     6,     7,     8,
       9,    10,    28,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    42,    -1,    -1,    28,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    21,    22,    -1,
      -1,    47,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    -1,    -1,    37,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    21,    51,    -1,    -1,
      -1,    -1,    -1,    57,    29,    30,    31,    32,    33,    34,
      -1,    -1,    37,    38,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    57
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    66,    42,    67,    69,     0,    42,    69,     4,
       5,     6,     7,     8,     9,    10,    12,    13,    15,    16,
      17,    18,    19,    20,    28,    42,    47,    70,    71,    72,
      73,    74,    75,    76,    77,    79,    80,    81,    82,    83,
      85,    87,    88,    89,    90,    91,    92,    93,     4,    68,
      21,    29,    30,    31,    32,    33,    34,    37,    38,    43,
      44,    45,    46,    47,    51,    57,    85,    95,    96,    97,
      98,    96,    21,    47,    27,    27,    96,    96,    21,    21,
      21,    23,    35,    36,    58,    42,    47,    42,    71,    78,
      27,    68,    42,    96,    21,    21,    21,    21,    21,    21,
      23,    96,    96,    14,    26,    50,    51,    52,    53,    54,
      55,    56,    59,    60,    61,    62,    63,    64,    26,    47,
      21,    27,    27,    47,    74,    22,    86,    96,    96,    27,
      27,    96,    27,    58,    40,    42,    11,    22,    96,    96,
      96,    96,    96,    47,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    78,
      22,    22,    47,    84,    22,    22,    22,    25,    24,    27,
      96,    69,    26,    25,    22,    22,    22,    22,    22,    24,
      96,    26,    22,    25,    27,    47,    96,    58,    27,    41,
      78,    96,    14,    78,    26,    47,    23,    96,    22,    96,
      78,    43,    27,    26,    24,    78,    27,    58,    23,    94,
      96,    24,    25,    27,    96
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      69,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    72,    72,    72,    72,    73,
      73,    74,    74,    74,    74,    74,    75,    76,    77,    78,
      78,    79,    80,    80,    81,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    88,    89,    90,    91,    92,
      93,    93,    94,    94,    95,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    98,    98,    98,    98,    98,    98
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     1,     2,     0,     2,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     3,
       5,     1,     1,     1,     1,     1,     4,     5,     3,     2,
       4,     3,     2,     5,     4,     9,     7,     6,     1,     3,
       4,     3,     1,     3,     3,     2,     2,     3,     3,     7,
       9,    13,     1,     3,     4,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     6,     4,     4,     4,     4,     4
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
#line 95 "bparser.y"
    {
        if (g_emit_ir && g_ir_out) {
            TacProgram final_tac;
            tac_program_init(&final_tac);
            tac_generate_from_ast((yyvsp[-2].node), &final_tac);
            fprintf(g_ir_out, "=== Generated TAC ===\n");
            tac_program_print(g_ir_out, &final_tac);
            tac_program_free(&final_tac);
        }

        ExecResult r = exec_stmt((yyvsp[-2].node));
        free_value(r.retval);
        node_free((yyvsp[-2].node));
        printf("✓ Program parsed successfully!\n");
    }
#line 1448 "bparser.tab.c"
    break;

  case 3: /* program: PROGRAM_START statements PROGRAM_END optional_newlines  */
#line 111 "bparser.y"
    {
        if (g_emit_ir && g_ir_out) {
            TacProgram final_tac;
            tac_program_init(&final_tac);
            tac_generate_from_ast((yyvsp[-2].node), &final_tac);
            fprintf(g_ir_out, "=== Generated TAC ===\n");
            tac_program_print(g_ir_out, &final_tac);
            tac_program_free(&final_tac);
        }

        ExecResult r = exec_stmt((yyvsp[-2].node));
        free_value(r.retval);
        node_free((yyvsp[-2].node));
        printf("✓ Program parsed successfully!\n");
    }
#line 1468 "bparser.tab.c"
    break;

  case 8: /* statements: %empty  */
#line 142 "bparser.y"
    {
        (yyval.node) = NULL;
    }
#line 1476 "bparser.tab.c"
    break;

  case 9: /* statements: statements statement  */
#line 146 "bparser.y"
    {
        if ((yyvsp[-1].node) == NULL) {
            (yyval.node) = (yyvsp[0].node);
        } else {
            AstNode *seq = node_new(N_SEQ, yylineno);
            seq->left  = (yyvsp[-1].node);
            seq->right = (yyvsp[0].node);
            (yyval.node) = seq;
        }
    }
#line 1491 "bparser.tab.c"
    break;

  case 10: /* statements: statements NEWLINE  */
#line 157 "bparser.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1499 "bparser.tab.c"
    break;

  case 11: /* statement: simple_statement NEWLINE  */
#line 163 "bparser.y"
                              { (yyval.node) = (yyvsp[-1].node); }
#line 1505 "bparser.tab.c"
    break;

  case 12: /* statement: compound_statement  */
#line 164 "bparser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1511 "bparser.tab.c"
    break;

  case 13: /* simple_statement: declaration  */
#line 168 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1517 "bparser.tab.c"
    break;

  case 14: /* simple_statement: assignment  */
#line 169 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1523 "bparser.tab.c"
    break;

  case 15: /* simple_statement: array_assignment  */
#line 170 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1529 "bparser.tab.c"
    break;

  case 16: /* simple_statement: input_statement  */
#line 171 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1535 "bparser.tab.c"
    break;

  case 17: /* simple_statement: print_statement  */
#line 172 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1541 "bparser.tab.c"
    break;

  case 18: /* simple_statement: return_statement  */
#line 173 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1547 "bparser.tab.c"
    break;

  case 19: /* simple_statement: break_statement  */
#line 174 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1553 "bparser.tab.c"
    break;

  case 20: /* simple_statement: continue_statement  */
#line 175 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1559 "bparser.tab.c"
    break;

  case 21: /* simple_statement: increment_statement  */
#line 176 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1565 "bparser.tab.c"
    break;

  case 22: /* simple_statement: decrement_statement  */
#line 177 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1571 "bparser.tab.c"
    break;

  case 23: /* simple_statement: array_declaration  */
#line 178 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1577 "bparser.tab.c"
    break;

  case 24: /* simple_statement: function_call SEMICOLON  */
#line 180 "bparser.y"
    {
        AstNode *n = node_new(N_CALL_STMT, yylineno);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 1587 "bparser.tab.c"
    break;

  case 25: /* compound_statement: if_statement  */
#line 188 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1593 "bparser.tab.c"
    break;

  case 26: /* compound_statement: while_statement  */
#line 189 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1599 "bparser.tab.c"
    break;

  case 27: /* compound_statement: for_statement  */
#line 190 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1605 "bparser.tab.c"
    break;

  case 28: /* compound_statement: function_definition  */
#line 191 "bparser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1611 "bparser.tab.c"
    break;

  case 29: /* declaration: type IDENTIFIER SEMICOLON  */
#line 196 "bparser.y"
    {
        AstNode *n = node_new(N_DECL, yylineno);
        n->sval  = (yyvsp[-1].strval);
        n->vtype = (yyvsp[-2].vtype);
        n->left  = NULL;
        (yyval.node) = n;
    }
#line 1623 "bparser.tab.c"
    break;

  case 30: /* declaration: type IDENTIFIER ASSIGN expression SEMICOLON  */
#line 204 "bparser.y"
    {
        AstNode *n = node_new(N_DECL, yylineno);
        n->sval  = (yyvsp[-3].strval);
        n->vtype = (yyvsp[-4].vtype);
        n->left  = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 1635 "bparser.tab.c"
    break;

  case 31: /* type: NUMBER_TYPE  */
#line 214 "bparser.y"
                 { (yyval.vtype) = TYPE_NUMBER;  }
#line 1641 "bparser.tab.c"
    break;

  case 32: /* type: DECIMAL_TYPE  */
#line 215 "bparser.y"
                   { (yyval.vtype) = TYPE_DECIMAL; }
#line 1647 "bparser.tab.c"
    break;

  case 33: /* type: BOOL_TYPE  */
#line 216 "bparser.y"
                   { (yyval.vtype) = TYPE_BOOL;    }
#line 1653 "bparser.tab.c"
    break;

  case 34: /* type: CHAR_TYPE  */
#line 217 "bparser.y"
                   { (yyval.vtype) = TYPE_CHAR;    }
#line 1659 "bparser.tab.c"
    break;

  case 35: /* type: STRING_TYPE  */
#line 218 "bparser.y"
                   { (yyval.vtype) = TYPE_STRING;  }
#line 1665 "bparser.tab.c"
    break;

  case 36: /* assignment: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 223 "bparser.y"
    {
        AstNode *n = node_new(N_ASSIGN, yylineno);
        n->sval = (yyvsp[-3].strval);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 1676 "bparser.tab.c"
    break;

  case 37: /* input_statement: INPUT LPAREN IDENTIFIER RPAREN SEMICOLON  */
#line 233 "bparser.y"
    {
        AstNode *n = node_new(N_INPUT, yylineno);
        n->sval = (yyvsp[-2].strval);
        (yyval.node) = n;
    }
#line 1686 "bparser.tab.c"
    break;

  case 38: /* print_statement: PRINT expression SEMICOLON  */
#line 242 "bparser.y"
    {
        AstNode *n = node_new(N_PRINT, yylineno);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 1696 "bparser.tab.c"
    break;

  case 39: /* suite: simple_statement NEWLINE  */
#line 250 "bparser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 1702 "bparser.tab.c"
    break;

  case 40: /* suite: NEWLINE INDENT statements DEDENT  */
#line 251 "bparser.y"
                                       { (yyval.node) = (yyvsp[-1].node); }
#line 1708 "bparser.tab.c"
    break;

  case 41: /* if_header: IF expression COLON  */
#line 255 "bparser.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 1714 "bparser.tab.c"
    break;

  case 42: /* if_statement: if_header suite  */
#line 260 "bparser.y"
    {
        AstNode *n = node_new(N_IF, yylineno);
        n->left  = (yyvsp[-1].node);
        n->right = (yyvsp[0].node);
        n->extra = NULL;
        (yyval.node) = n;
    }
#line 1726 "bparser.tab.c"
    break;

  case 43: /* if_statement: if_header suite ELSE COLON suite  */
#line 268 "bparser.y"
    {
        AstNode *n = node_new(N_IF, yylineno);
        n->left  = (yyvsp[-4].node);
        n->right = (yyvsp[-3].node);
        n->extra = (yyvsp[0].node);
        (yyval.node) = n;
    }
#line 1738 "bparser.tab.c"
    break;

  case 44: /* while_statement: WHILE expression COLON suite  */
#line 279 "bparser.y"
    {
        AstNode *n = node_new(N_WHILE, yylineno);
        n->left  = (yyvsp[-2].node);   /* condition — re-evaluated every iteration */
        n->right = (yyvsp[0].node);   /* body */
        (yyval.node) = n;
    }
#line 1749 "bparser.tab.c"
    break;

  case 45: /* for_statement: FOR_RANGE LPAREN IDENTIFIER RPAREN expression FROM expression COLON suite  */
#line 289 "bparser.y"
    {
        AstNode *n = node_new(N_FOR_RANGE, yylineno);
        n->sval  = (yyvsp[-6].strval);
        n->left  = (yyvsp[-4].node);
        n->right = (yyvsp[-2].node);
        n->extra = (yyvsp[0].node);
        (yyval.node) = n;
    }
#line 1762 "bparser.tab.c"
    break;

  case 46: /* function_definition: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN COLON suite  */
#line 301 "bparser.y"
    {
        AstNode *n = node_new(N_FUNCDEF, yylineno);
        n->sval  = (yyvsp[-5].strval);
        n->left  = (yyvsp[-3].node);
        n->right = (yyvsp[0].node);
        (yyval.node) = n;
    }
#line 1774 "bparser.tab.c"
    break;

  case 47: /* function_definition: FUNCTION IDENTIFIER LPAREN RPAREN COLON suite  */
#line 309 "bparser.y"
    {
        AstNode *n = node_new(N_FUNCDEF, yylineno);
        n->sval  = (yyvsp[-4].strval);
        n->left  = NULL;
        n->right = (yyvsp[0].node);
        (yyval.node) = n;
    }
#line 1786 "bparser.tab.c"
    break;

  case 48: /* parameter_list: IDENTIFIER  */
#line 320 "bparser.y"
    {
        AstNode *n = node_new(N_PARAM_LIST, yylineno);
        n->sval  = (yyvsp[0].strval);
        n->right = NULL;
        (yyval.node) = n;
    }
#line 1797 "bparser.tab.c"
    break;

  case 49: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 327 "bparser.y"
    {
        AstNode *n = node_new(N_PARAM_LIST, yylineno);
        n->sval  = (yyvsp[0].strval);
        n->right = (yyvsp[-2].node);
        (yyval.node) = n;
    }
#line 1808 "bparser.tab.c"
    break;

  case 50: /* function_call: IDENTIFIER LPAREN argument_list RPAREN  */
#line 337 "bparser.y"
    {
        AstNode *n = node_new(N_CALL, yylineno);
        n->sval = (yyvsp[-3].strval);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 1819 "bparser.tab.c"
    break;

  case 51: /* function_call: IDENTIFIER LPAREN RPAREN  */
#line 344 "bparser.y"
    {
        AstNode *n = node_new(N_CALL, yylineno);
        n->sval = (yyvsp[-2].strval);
        n->left = NULL;
        (yyval.node) = n;
    }
#line 1830 "bparser.tab.c"
    break;

  case 52: /* argument_list: expression  */
#line 354 "bparser.y"
    {
        AstNode *n = node_new(N_ARG_LIST, yylineno);
        n->left  = (yyvsp[0].node);
        n->right = NULL;
        (yyval.node) = n;
    }
#line 1841 "bparser.tab.c"
    break;

  case 53: /* argument_list: argument_list COMMA expression  */
#line 361 "bparser.y"
    {
        AstNode *n = node_new(N_ARG_LIST, yylineno);
        n->left  = (yyvsp[0].node);
        n->right = (yyvsp[-2].node);
        (yyval.node) = n;
    }
#line 1852 "bparser.tab.c"
    break;

  case 54: /* return_statement: RETURN expression SEMICOLON  */
#line 371 "bparser.y"
    {
        AstNode *n = node_new(N_RETURN, yylineno);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 1862 "bparser.tab.c"
    break;

  case 55: /* break_statement: BREAK SEMICOLON  */
#line 380 "bparser.y"
    {
        (yyval.node) = node_new(N_BREAK, yylineno);
    }
#line 1870 "bparser.tab.c"
    break;

  case 56: /* continue_statement: CONTINUE SEMICOLON  */
#line 387 "bparser.y"
    {
        (yyval.node) = node_new(N_CONTINUE, yylineno);
    }
#line 1878 "bparser.tab.c"
    break;

  case 57: /* increment_statement: IDENTIFIER INC SEMICOLON  */
#line 394 "bparser.y"
    {
        AstNode *n = node_new(N_INC, yylineno);
        n->sval = (yyvsp[-2].strval);
        (yyval.node) = n;
    }
#line 1888 "bparser.tab.c"
    break;

  case 58: /* decrement_statement: IDENTIFIER DEC SEMICOLON  */
#line 403 "bparser.y"
    {
        AstNode *n = node_new(N_DEC, yylineno);
        n->sval = (yyvsp[-2].strval);
        (yyval.node) = n;
    }
#line 1898 "bparser.tab.c"
    break;

  case 59: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON  */
#line 412 "bparser.y"
    {
        AstNode *n = node_new(N_ARRAY_ASSIGN, yylineno);
        n->sval  = (yyvsp[-6].strval);
        n->left  = (yyvsp[-4].node);   /* index */
        n->right = (yyvsp[-1].node);   /* new value */
        (yyval.node) = n;
    }
#line 1910 "bparser.tab.c"
    break;

  case 60: /* array_declaration: ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET SEMICOLON  */
#line 423 "bparser.y"
    {
        AstNode *n = node_new(N_ARRAY_DECL, yylineno);
        n->sval  = (yyvsp[-4].strval);
        n->vtype = (yyvsp[-6].vtype);
        n->ival  = (yyvsp[-2].intval);
        n->left  = NULL;
        (yyval.node) = n;
    }
#line 1923 "bparser.tab.c"
    break;

  case 61: /* array_declaration: ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET ASSIGN LBRACKET array_elements RBRACKET SEMICOLON  */
#line 432 "bparser.y"
    {
        AstNode *n = node_new(N_ARRAY_DECL, yylineno);
        n->sval  = (yyvsp[-8].strval);
        n->vtype = (yyvsp[-10].vtype);
        n->ival  = (yyvsp[-6].intval);
        n->left  = (yyvsp[-2].node);
        (yyval.node) = n;
    }
#line 1936 "bparser.tab.c"
    break;

  case 62: /* array_elements: expression  */
#line 444 "bparser.y"
    {
        AstNode *n = node_new(N_INIT_LIST, yylineno);
        n->left  = (yyvsp[0].node);
        n->right = NULL;
        (yyval.node) = n;
    }
#line 1947 "bparser.tab.c"
    break;

  case 63: /* array_elements: array_elements COMMA expression  */
#line 451 "bparser.y"
    {
        AstNode *n = node_new(N_INIT_LIST, yylineno);
        n->left  = (yyvsp[0].node);
        n->right = (yyvsp[-2].node);
        (yyval.node) = n;
    }
#line 1958 "bparser.tab.c"
    break;

  case 64: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 461 "bparser.y"
    {
        AstNode *n = node_new(N_ARRAY_ACCESS, yylineno);
        n->sval = (yyvsp[-3].strval);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 1969 "bparser.tab.c"
    break;

  case 65: /* expression: primary_expression  */
#line 470 "bparser.y"
                                          { (yyval.node) = (yyvsp[0].node); }
#line 1975 "bparser.tab.c"
    break;

  case 66: /* expression: expression PLUS expression  */
#line 472 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_PLUS;  n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 1981 "bparser.tab.c"
    break;

  case 67: /* expression: expression MINUS expression  */
#line 474 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_MINUS; n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 1987 "bparser.tab.c"
    break;

  case 68: /* expression: expression MULT expression  */
#line 476 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_MULT;  n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 1993 "bparser.tab.c"
    break;

  case 69: /* expression: expression DIV expression  */
#line 478 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_DIV;   n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 1999 "bparser.tab.c"
    break;

  case 70: /* expression: expression MOD expression  */
#line 480 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_MOD;   n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2005 "bparser.tab.c"
    break;

  case 71: /* expression: expression AND expression  */
#line 482 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_AND;   n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2011 "bparser.tab.c"
    break;

  case 72: /* expression: expression OR expression  */
#line 484 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_OR;    n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2017 "bparser.tab.c"
    break;

  case 73: /* expression: expression EQUAL expression  */
#line 486 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_EQ;    n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2023 "bparser.tab.c"
    break;

  case 74: /* expression: expression NOT_EQUAL expression  */
#line 488 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_NEQ;   n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2029 "bparser.tab.c"
    break;

  case 75: /* expression: expression GREATER expression  */
#line 490 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_GT;    n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2035 "bparser.tab.c"
    break;

  case 76: /* expression: expression LESS expression  */
#line 492 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_LT;    n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2041 "bparser.tab.c"
    break;

  case 77: /* expression: expression GREATER_EQUAL expression  */
#line 494 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_GTE;   n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2047 "bparser.tab.c"
    break;

  case 78: /* expression: expression LESS_EQUAL expression  */
#line 496 "bparser.y"
    { AstNode *n=node_new(N_BINOP,yylineno); n->ival=OP_LTE;   n->left=(yyvsp[-2].node); n->right=(yyvsp[0].node); (yyval.node)=n; }
#line 2053 "bparser.tab.c"
    break;

  case 79: /* expression: expression FROM expression  */
#line 498 "bparser.y"
    {
        node_free((yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2062 "bparser.tab.c"
    break;

  case 80: /* expression: NOT expression  */
#line 503 "bparser.y"
    {
        AstNode *n = node_new(N_UNARY_NOT, yylineno);
        n->left = (yyvsp[0].node);
        (yyval.node) = n;
    }
#line 2072 "bparser.tab.c"
    break;

  case 81: /* expression: MINUS expression  */
#line 509 "bparser.y"
    {
        AstNode *n = node_new(N_UNARY_NEG, yylineno);
        n->left = (yyvsp[0].node);
        (yyval.node) = n;
    }
#line 2082 "bparser.tab.c"
    break;

  case 82: /* primary_expression: INT_LITERAL  */
#line 518 "bparser.y"
    {
        AstNode *n = node_new(N_INT_LIT, yylineno);
        n->ival = (yyvsp[0].intval);
        (yyval.node) = n;
    }
#line 2092 "bparser.tab.c"
    break;

  case 83: /* primary_expression: FLOAT_LITERAL  */
#line 524 "bparser.y"
    {
        AstNode *n = node_new(N_FLOAT_LIT, yylineno);
        n->fval = (yyvsp[0].floatval);
        (yyval.node) = n;
    }
#line 2102 "bparser.tab.c"
    break;

  case 84: /* primary_expression: STRING_LITERAL  */
#line 530 "bparser.y"
    {
        AstNode *n = node_new(N_STRING_LIT, yylineno);
        n->sval = (yyvsp[0].strval);
        (yyval.node) = n;
    }
#line 2112 "bparser.tab.c"
    break;

  case 85: /* primary_expression: CHAR_LITERAL  */
#line 536 "bparser.y"
    {
        AstNode *n = node_new(N_CHAR_LIT, yylineno);
        n->sval = (yyvsp[0].strval);
        (yyval.node) = n;
    }
#line 2122 "bparser.tab.c"
    break;

  case 86: /* primary_expression: IDENTIFIER  */
#line 542 "bparser.y"
    {
        AstNode *n = node_new(N_IDENT, yylineno);
        n->sval = (yyvsp[0].strval);
        (yyval.node) = n;
    }
#line 2132 "bparser.tab.c"
    break;

  case 87: /* primary_expression: BOOL_TRUE  */
#line 548 "bparser.y"
    {
        AstNode *n = node_new(N_BOOL_LIT, yylineno);
        n->ival = 1;
        (yyval.node) = n;
    }
#line 2142 "bparser.tab.c"
    break;

  case 88: /* primary_expression: BOOL_FALSE  */
#line 554 "bparser.y"
    {
        AstNode *n = node_new(N_BOOL_LIT, yylineno);
        n->ival = 0;
        (yyval.node) = n;
    }
#line 2152 "bparser.tab.c"
    break;

  case 89: /* primary_expression: array_access  */
#line 559 "bparser.y"
                               { (yyval.node) = (yyvsp[0].node); }
#line 2158 "bparser.tab.c"
    break;

  case 90: /* primary_expression: function_call  */
#line 560 "bparser.y"
                               { (yyval.node) = (yyvsp[0].node); }
#line 2164 "bparser.tab.c"
    break;

  case 91: /* primary_expression: math_function  */
#line 561 "bparser.y"
                               { (yyval.node) = (yyvsp[0].node); }
#line 2170 "bparser.tab.c"
    break;

  case 92: /* primary_expression: LPAREN expression RPAREN  */
#line 562 "bparser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2176 "bparser.tab.c"
    break;

  case 93: /* math_function: POW LPAREN expression COMMA expression RPAREN  */
#line 567 "bparser.y"
    {
        AstNode *n = node_new(N_MATH_POW, yylineno);
        n->left  = (yyvsp[-3].node);
        n->right = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 2187 "bparser.tab.c"
    break;

  case 94: /* math_function: SQRT LPAREN expression RPAREN  */
#line 574 "bparser.y"
    {
        AstNode *n = node_new(N_MATH_SQRT, yylineno);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 2197 "bparser.tab.c"
    break;

  case 95: /* math_function: FLOOR LPAREN expression RPAREN  */
#line 580 "bparser.y"
    {
        AstNode *n = node_new(N_MATH_FLOOR, yylineno);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 2207 "bparser.tab.c"
    break;

  case 96: /* math_function: CEIL LPAREN expression RPAREN  */
#line 586 "bparser.y"
    {
        AstNode *n = node_new(N_MATH_CEIL, yylineno);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 2217 "bparser.tab.c"
    break;

  case 97: /* math_function: ABS LPAREN expression RPAREN  */
#line 592 "bparser.y"
    {
        AstNode *n = node_new(N_MATH_ABS, yylineno);
        n->left = (yyvsp[-1].node);
        (yyval.node) = n;
    }
#line 2227 "bparser.tab.c"
    break;

  case 98: /* math_function: LENGTH LPAREN IDENTIFIER RPAREN  */
#line 598 "bparser.y"
    {
        AstNode *n = node_new(N_ARRAY_LEN, yylineno);
        n->sval = (yyvsp[-1].strval);
        (yyval.node) = n;
    }
#line 2237 "bparser.tab.c"
    break;


#line 2241 "bparser.tab.c"

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

#line 605 "bparser.y"


void yyerror(const char *s) {
    fprintf(stderr, "ত্রুটি (লাইন %d): সিনট্যাক্স ত্রুটি (%s)\n", yylineno, s);
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
    const char *input_path = NULL;
    const char *ir_path = "ir.out.txt";

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

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ir") == 0) {
            g_emit_ir = 1;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                ir_path = argv[i + 1];
                i++;
            }
            continue;
        }

        if (!input_path) {
            input_path = argv[i];
            continue;
        }

        fprintf(stderr, "ত্রুটি: অপ্রত্যাশিত আর্গুমেন্ট '%s'\n", argv[i]);
        fprintf(stderr, "ব্যবহার: %s <input_file> [--ir [ir_output_file]]\n", argv[0]);
        return 1;
    }

    if (!input_path) {
        fprintf(stderr, "ব্যবহার: %s <input_file> [--ir [ir_output_file]]\n", argv[0]);
        return 1;
    }

    if (g_emit_ir) {
        g_ir_path = ir_path;
        g_ir_out = fopen(g_ir_path, "w");
        if (!g_ir_out) {
            fprintf(stderr, "ত্রুটি: IR আউটপুট ফাইল '%s' খোলা যায়নি।\n", g_ir_path);
            return 1;
        }
    }
    
    FILE *fp = fopen(input_path, "r");
    if (!fp) {
        fprintf(stderr, "ত্রুটি: ইনপুট ফাইল '%s' খোলা যায়নি।\n", input_path);
        if (g_ir_out) {
            fclose(g_ir_out);
            g_ir_out = NULL;
        }
        return 1;
    }
    
    /* Normalize Unicode before parsing */
    yyin = normalize_input(fp);  /* fp is closed inside normalize_input */
    init_indent();  /* Initialize indentation tracking */
    
    printf("=== Parsing Bangla Program ===\n\n");

    symtable_init();   /* initialise global symbol table */
    func_table_init(); /* initialise user-defined function table */

    int result = yyparse();

    symtable_free();   /* release all symbol table memory */
    func_table_free(); /* release all function table memory */
    fclose(yyin);

    if (g_ir_out) {
        fclose(g_ir_out);
        g_ir_out = NULL;
        printf("IR লেখা হয়েছে: %s\n", g_ir_path ? g_ir_path : "ir.out.txt");
    }

    if (result == 0) {
        printf("\n=== Parsing Complete ===\n");
        return 0;
    } else {
        printf("\n=== Parsing Failed ===\n");
        return 1;
    }
}
