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

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern void init_indent();

#line 83 "bparser.tab.c"

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
  YYSYMBOL_if_statement = 78,              /* if_statement  */
  YYSYMBOL_while_statement = 79,           /* while_statement  */
  YYSYMBOL_for_statement = 80,             /* for_statement  */
  YYSYMBOL_function_definition = 81,       /* function_definition  */
  YYSYMBOL_parameter_list = 82,            /* parameter_list  */
  YYSYMBOL_function_call = 83,             /* function_call  */
  YYSYMBOL_argument_list = 84,             /* argument_list  */
  YYSYMBOL_return_statement = 85,          /* return_statement  */
  YYSYMBOL_break_statement = 86,           /* break_statement  */
  YYSYMBOL_continue_statement = 87,        /* continue_statement  */
  YYSYMBOL_increment_statement = 88,       /* increment_statement  */
  YYSYMBOL_decrement_statement = 89,       /* decrement_statement  */
  YYSYMBOL_array_declaration = 90,         /* array_declaration  */
  YYSYMBOL_array_elements = 91,            /* array_elements  */
  YYSYMBOL_array_access = 92,              /* array_access  */
  YYSYMBOL_expression = 93,                /* expression  */
  YYSYMBOL_primary_expression = 94,        /* primary_expression  */
  YYSYMBOL_math_function = 95              /* math_function  */
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
#define YYLAST   689

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  203

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
       0,    59,    59,    63,    70,    71,    74,    76,    79,    81,
      82,    86,    87,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   105,   106,   107,   108,   112,   117,
     125,   126,   127,   128,   129,   133,   141,   149,   156,   157,
     161,   165,   172,   179,   187,   192,   200,   204,   211,   216,
     224,   225,   229,   236,   243,   250,   258,   266,   271,   279,
     280,   284,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   312,
     313,   314,   318,   322,   326,   327,   328,   329,   330,   331,
     335,   336,   337,   338,   339
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
  "print_statement", "suite", "if_statement", "while_statement",
  "for_statement", "function_definition", "parameter_list",
  "function_call", "argument_list", "return_statement", "break_statement",
  "continue_statement", "increment_statement", "decrement_statement",
  "array_declaration", "array_elements", "array_access", "expression",
  "primary_expression", "math_function", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -32,    16,  -107,   -23,   525,  -107,  -107,   542,  -107,
    -107,  -107,  -107,  -107,  -107,   633,   633,     1,   -27,    -1,
       0,   633,   633,    14,    40,  -107,    -6,  -107,   -17,  -107,
    -107,    26,  -107,  -107,  -107,  -107,  -107,  -107,  -107,    47,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,    34,   633,    56,
      57,    58,    59,    61,  -107,  -107,  -107,  -107,  -107,  -107,
      -9,   633,   633,  -107,  -107,   -13,  -107,  -107,    76,    35,
      62,  -107,  -107,   164,   179,    38,    60,   605,    65,    66,
     633,  -107,     5,  -107,    34,  -107,   198,   633,   633,   633,
     633,   633,   633,    73,    73,   633,   135,   633,   633,   633,
     633,   633,   633,   633,   633,   633,   633,   633,   633,   633,
     135,    72,   -12,  -107,  -107,    81,    97,  -107,   -14,   389,
    -107,  -107,   240,  -107,   633,  -107,   221,   255,   274,   297,
     316,   339,  -107,    49,    54,   109,     7,     7,    73,    73,
      73,   446,   431,   465,   465,     3,     3,     3,     3,  -107,
     633,    95,  -107,    -2,    96,    78,  -107,   633,  -107,   358,
     633,  -107,  -107,  -107,  -107,  -107,  -107,  -107,   106,   415,
     135,   119,   100,  -107,    99,   389,  -107,   373,   584,   135,
     633,  -107,   135,  -107,   105,  -107,  -107,  -107,   122,  -107,
     125,   135,     6,  -107,  -107,   127,   633,    19,   389,   129,
     633,  -107,   389
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,     0,     4,     8,     0,     1,     5,     0,     6,
      30,    31,    32,    33,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     9,     0,    12,
      13,     0,    14,    15,    16,    24,    25,    26,    27,     0,
      17,    18,    19,    20,    21,    22,     6,     3,     0,     0,
       0,     0,     0,     0,    84,    85,    79,    80,    81,    82,
      83,     0,     0,    87,    86,     0,    62,    88,     0,     0,
       0,    53,    54,     0,     0,     0,     0,     0,     0,     0,
       0,    11,     0,    23,     2,     7,     0,     0,     0,     0,
       0,     0,     0,    78,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    52,    37,     0,     0,    49,     0,    50,
      55,    56,     0,    28,     0,    89,     0,     0,     0,     0,
       0,     0,    76,     0,     0,    40,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    42,
       0,     0,    46,     0,     0,     0,    48,     0,    35,     0,
       0,    91,    92,    93,    94,    61,     8,    38,     0,     0,
       0,     0,     0,    36,     0,    51,    29,     0,     0,     0,
       0,    45,     0,    47,     0,    90,    39,    41,    76,    44,
       0,     0,     0,    43,    57,     0,     0,     0,    59,     0,
       0,    58,    60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,  -107,  -107,   111,     2,  -107,    -3,  -107,  -107,    82,
    -107,  -107,  -107,  -106,  -107,  -107,  -107,  -107,  -107,    -5,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,     9,
    -107,  -107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     4,    47,     5,    27,   134,    29,    30,    31,
      32,    33,    34,   135,    35,    36,    37,    38,   153,    63,
     118,    40,    41,    42,    43,    44,    45,   197,    64,    65,
      66,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      39,    95,    28,    39,   149,    28,     8,     1,   156,     3,
     151,   157,    77,    96,    92,    77,     6,    95,     7,    70,
     171,    95,    69,   172,    81,    68,    71,    72,    78,    79,
      73,    74,   123,   194,   152,    75,    97,    98,    99,   100,
     101,   102,   103,   199,   200,   104,   105,   106,   107,   108,
     109,    80,    97,    98,    99,   100,   101,    86,    99,   100,
     101,    76,   124,   195,   181,    10,    11,    12,    13,    14,
      93,    94,    82,   187,    83,    85,   189,    87,    88,    89,
      90,   111,    91,   112,   115,   193,   119,    95,   166,   122,
      95,    39,   120,   121,   150,   167,   126,   127,   128,   129,
     130,   131,   110,   154,   132,    39,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   155,
     168,   170,   184,   173,   174,    97,    98,    99,   100,   101,
     102,   103,   179,   159,   104,   105,   106,   107,   108,   109,
      10,    11,    12,    13,    14,   182,   183,   190,   191,   192,
     196,    19,    20,    21,    22,    23,   201,    84,   116,   169,
       0,     0,     0,    24,     0,    39,   175,     0,   178,   177,
       0,     0,     0,    39,    39,    28,   133,    39,    95,     0,
       0,    26,     0,     0,     0,     0,    39,     0,     0,   188,
       0,   113,     0,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   198,   114,     0,     0,   202,
       0,     0,    95,    97,    98,    99,   100,   101,   102,   103,
     125,     0,   104,   105,   106,   107,   108,   109,    97,    98,
      99,   100,   101,   102,   103,    95,     0,   104,   105,   106,
     107,   108,   109,     0,     0,     0,   160,    97,    98,    99,
     100,   101,   102,   103,    95,     0,   104,   105,   106,   107,
     108,   109,     0,     0,     0,     0,     0,   158,     0,    95,
      97,    98,    99,   100,   101,   102,   103,   161,     0,   104,
     105,   106,   107,   108,   109,     0,     0,     0,    95,    97,
      98,    99,   100,   101,   102,   103,   162,     0,   104,   105,
     106,   107,   108,   109,    97,    98,    99,   100,   101,   102,
     103,    95,     0,   104,   105,   106,   107,   108,   109,   163,
       0,     0,     0,    97,    98,    99,   100,   101,   102,   103,
      95,     0,   104,   105,   106,   107,   108,   109,   164,     0,
       0,     0,     0,     0,     0,     0,    97,    98,    99,   100,
     101,   102,   103,    95,     0,   104,   105,   106,   107,   108,
     109,     0,     0,   165,     0,    97,    98,    99,   100,   101,
     102,   103,    95,     0,   104,   105,   106,   107,   108,   109,
       0,     0,     0,     0,     0,   176,     0,    95,    97,    98,
      99,   100,   101,   102,   103,   185,     0,   104,   105,   106,
     107,   108,   109,    95,     0,     0,     0,    97,    98,    99,
     100,   101,   102,   103,     0,     0,   104,   105,   106,   107,
     108,   109,    97,    98,    99,   100,   101,   102,   103,   180,
       0,   104,   105,   106,   107,   108,   109,     0,    97,    98,
      99,   100,   101,   102,   103,    95,     0,   104,   105,   106,
     107,   108,   109,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,     0,     0,   104,   105,   106,   107,   108,   109,    95,
      97,    98,    99,   100,   101,   102,     0,     0,     0,   104,
     105,   106,   107,   108,   109,    97,    98,    99,   100,   101,
       0,     0,     0,     0,   104,   105,   106,   107,   108,   109,
       0,     0,     0,     0,    97,    98,    99,   100,   101,     0,
       0,     0,     0,     0,     0,   106,   107,   108,   109,     9,
      10,    11,    12,    13,    14,    15,     0,    16,    17,     0,
      18,    19,    20,    21,    22,    23,    46,    10,    11,    12,
      13,    14,    15,    24,    16,    17,     0,    18,    19,    20,
      21,    22,    23,     0,     0,     0,    25,     0,     0,     0,
      24,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     0,     0,     0,    26,    10,
      11,    12,    13,    14,    15,     0,    16,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   186,    25,    48,   117,     0,     0,
      26,     0,     0,     0,    49,    50,    51,    52,    53,     0,
       0,    54,    55,     0,     0,     0,     0,    56,    57,    58,
      59,    60,     0,     0,    48,    61,     0,     0,     0,     0,
       0,    62,    49,    50,    51,    52,    53,     0,     0,    54,
      55,     0,     0,     0,     0,    56,    57,    58,    59,    60,
       0,     0,     0,    61,     0,     0,     0,     0,     0,    62
};

static const yytype_int16 yycheck[] =
{
       5,    14,     5,     8,   110,     8,     4,     3,    22,    41,
      22,    25,    21,    26,    23,    21,     0,    14,    41,    46,
      22,    14,    21,    25,    41,    16,    27,    27,    34,    35,
      21,    22,    27,    27,    46,    21,    49,    50,    51,    52,
      53,    54,    55,    24,    25,    58,    59,    60,    61,    62,
      63,    57,    49,    50,    51,    52,    53,    48,    51,    52,
      53,    21,    57,    57,   170,     5,     6,     7,     8,     9,
      61,    62,    46,   179,    27,    41,   182,    21,    21,    21,
      21,    46,    21,    21,    46,   191,    77,    14,    39,    80,
      14,    96,    27,    27,    22,    41,    87,    88,    89,    90,
      91,    92,    26,    22,    95,   110,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    22,
      11,    26,    23,    27,    46,    49,    50,    51,    52,    53,
      54,    55,    26,   124,    58,    59,    60,    61,    62,    63,
       5,     6,     7,     8,     9,    26,    46,    42,    26,    24,
      23,    16,    17,    18,    19,    20,    27,    46,    76,   150,
      -1,    -1,    -1,    28,    -1,   170,   157,    -1,   166,   160,
      -1,    -1,    -1,   178,   179,   178,    41,   182,    14,    -1,
      -1,    46,    -1,    -1,    -1,    -1,   191,    -1,    -1,   180,
      -1,    27,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,    27,    -1,    -1,   200,
      -1,    -1,    14,    49,    50,    51,    52,    53,    54,    55,
      22,    -1,    58,    59,    60,    61,    62,    63,    49,    50,
      51,    52,    53,    54,    55,    14,    -1,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    25,    49,    50,    51,
      52,    53,    54,    55,    14,    -1,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    27,    -1,    14,
      49,    50,    51,    52,    53,    54,    55,    22,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    14,    49,
      50,    51,    52,    53,    54,    55,    22,    -1,    58,    59,
      60,    61,    62,    63,    49,    50,    51,    52,    53,    54,
      55,    14,    -1,    58,    59,    60,    61,    62,    63,    22,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      14,    -1,    58,    59,    60,    61,    62,    63,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    14,    -1,    58,    59,    60,    61,    62,
      63,    -1,    -1,    24,    -1,    49,    50,    51,    52,    53,
      54,    55,    14,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    14,    49,    50,
      51,    52,    53,    54,    55,    22,    -1,    58,    59,    60,
      61,    62,    63,    14,    -1,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    58,    59,    60,    61,
      62,    63,    49,    50,    51,    52,    53,    54,    55,    14,
      -1,    58,    59,    60,    61,    62,    63,    -1,    49,    50,
      51,    52,    53,    54,    55,    14,    -1,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    58,    59,    60,    61,    62,    63,    14,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,     4,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,     4,     5,     6,     7,
       8,     9,    10,    28,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      28,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    46,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    21,    22,    -1,    -1,
      46,    -1,    -1,    -1,    29,    30,    31,    32,    33,    -1,
      -1,    36,    37,    -1,    -1,    -1,    -1,    42,    43,    44,
      45,    46,    -1,    -1,    21,    50,    -1,    -1,    -1,    -1,
      -1,    56,    29,    30,    31,    32,    33,    -1,    -1,    36,
      37,    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    65,    41,    66,    68,     0,    41,    68,     4,
       5,     6,     7,     8,     9,    10,    12,    13,    15,    16,
      17,    18,    19,    20,    28,    41,    46,    69,    70,    71,
      72,    73,    74,    75,    76,    78,    79,    80,    81,    83,
      85,    86,    87,    88,    89,    90,     4,    67,    21,    29,
      30,    31,    32,    33,    36,    37,    42,    43,    44,    45,
      46,    50,    56,    83,    92,    93,    94,    95,    93,    21,
      46,    27,    27,    93,    93,    21,    21,    21,    34,    35,
      57,    41,    46,    27,    67,    41,    93,    21,    21,    21,
      21,    21,    23,    93,    93,    14,    26,    49,    50,    51,
      52,    53,    54,    55,    58,    59,    60,    61,    62,    63,
      26,    46,    21,    27,    27,    46,    73,    22,    84,    93,
      27,    27,    93,    27,    57,    22,    93,    93,    93,    93,
      93,    93,    93,    41,    70,    77,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    77,
      22,    22,    46,    82,    22,    22,    22,    25,    27,    93,
      25,    22,    22,    22,    22,    24,    39,    41,    11,    93,
      26,    22,    25,    27,    46,    93,    27,    93,    68,    26,
      14,    77,    26,    46,    23,    22,    40,    77,    93,    77,
      42,    26,    24,    77,    27,    57,    23,    91,    93,    24,
      25,    27,    93
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    72,    72,
      73,    73,    73,    73,    73,    74,    75,    76,    77,    77,
      78,    78,    79,    80,    81,    81,    82,    82,    83,    83,
      84,    84,    85,    86,    87,    88,    89,    90,    90,    91,
      91,    92,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    95,    95,    95,    95
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     1,     2,     0,     2,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     3,     5,
       1,     1,     1,     1,     1,     4,     5,     3,     2,     4,
       4,     7,     4,     9,     7,     6,     1,     3,     4,     3,
       1,     3,     3,     2,     2,     3,     3,     9,    13,     1,
       3,     4,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       6,     4,     4,     4,     4
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
#line 60 "bparser.y"
    {
        printf("✓ Program parsed successfully!\n");
    }
#line 1405 "bparser.tab.c"
    break;

  case 3: /* program: PROGRAM_START statements PROGRAM_END optional_newlines  */
#line 64 "bparser.y"
    {
        printf("✓ Program parsed successfully!\n");
    }
#line 1413 "bparser.tab.c"
    break;

  case 28: /* declaration: type IDENTIFIER SEMICOLON  */
#line 113 "bparser.y"
    {
        printf("Declaration: %s\n", (yyvsp[-1].strval));
        free((yyvsp[-1].strval));
    }
#line 1422 "bparser.tab.c"
    break;

  case 29: /* declaration: type IDENTIFIER ASSIGN expression SEMICOLON  */
#line 118 "bparser.y"
    {
        printf("Declaration with assignment: %s\n", (yyvsp[-3].strval));
        free((yyvsp[-3].strval));
    }
#line 1431 "bparser.tab.c"
    break;

  case 35: /* assignment: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 134 "bparser.y"
    {
        printf("Assignment: %s\n", (yyvsp[-3].strval));
        free((yyvsp[-3].strval));
    }
#line 1440 "bparser.tab.c"
    break;

  case 36: /* input_statement: INPUT LPAREN IDENTIFIER RPAREN SEMICOLON  */
#line 142 "bparser.y"
    {
        printf("Input statement for: %s\n", (yyvsp[-2].strval));
        free((yyvsp[-2].strval));
    }
#line 1449 "bparser.tab.c"
    break;

  case 37: /* print_statement: PRINT expression SEMICOLON  */
#line 150 "bparser.y"
    {
        printf("Print statement\n");
    }
#line 1457 "bparser.tab.c"
    break;

  case 40: /* if_statement: IF expression COLON suite  */
#line 162 "bparser.y"
    {
        printf("If statement\n");
    }
#line 1465 "bparser.tab.c"
    break;

  case 41: /* if_statement: IF expression COLON suite ELSE COLON suite  */
#line 166 "bparser.y"
    {
        printf("If-Else statement\n");
    }
#line 1473 "bparser.tab.c"
    break;

  case 42: /* while_statement: WHILE expression COLON suite  */
#line 173 "bparser.y"
    {
        printf("While loop\n");
    }
#line 1481 "bparser.tab.c"
    break;

  case 43: /* for_statement: FOR_RANGE LPAREN IDENTIFIER RPAREN expression FROM expression COLON suite  */
#line 180 "bparser.y"
    {
        printf("For loop\n");
        free((yyvsp[-6].strval));
    }
#line 1490 "bparser.tab.c"
    break;

  case 44: /* function_definition: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN COLON suite  */
#line 188 "bparser.y"
    {
        printf("Function definition: %s\n", (yyvsp[-5].strval));
        free((yyvsp[-5].strval));
    }
#line 1499 "bparser.tab.c"
    break;

  case 45: /* function_definition: FUNCTION IDENTIFIER LPAREN RPAREN COLON suite  */
#line 193 "bparser.y"
    {
        printf("Function definition (no params): %s\n", (yyvsp[-4].strval));
        free((yyvsp[-4].strval));
    }
#line 1508 "bparser.tab.c"
    break;

  case 46: /* parameter_list: IDENTIFIER  */
#line 201 "bparser.y"
    {
        free((yyvsp[0].strval));
    }
#line 1516 "bparser.tab.c"
    break;

  case 47: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 205 "bparser.y"
    {
        free((yyvsp[0].strval));
    }
#line 1524 "bparser.tab.c"
    break;

  case 48: /* function_call: IDENTIFIER LPAREN argument_list RPAREN  */
#line 212 "bparser.y"
    {
        printf("Function call: %s\n", (yyvsp[-3].strval));
        free((yyvsp[-3].strval));
    }
#line 1533 "bparser.tab.c"
    break;

  case 49: /* function_call: IDENTIFIER LPAREN RPAREN  */
#line 217 "bparser.y"
    {
        printf("Function call (no args): %s\n", (yyvsp[-2].strval));
        free((yyvsp[-2].strval));
    }
#line 1542 "bparser.tab.c"
    break;

  case 52: /* return_statement: RETURN expression SEMICOLON  */
#line 230 "bparser.y"
    {
        printf("Return statement\n");
    }
#line 1550 "bparser.tab.c"
    break;

  case 53: /* break_statement: BREAK SEMICOLON  */
#line 237 "bparser.y"
    {
        printf("Break statement\n");
    }
#line 1558 "bparser.tab.c"
    break;

  case 54: /* continue_statement: CONTINUE SEMICOLON  */
#line 244 "bparser.y"
    {
        printf("Continue statement\n");
    }
#line 1566 "bparser.tab.c"
    break;

  case 55: /* increment_statement: IDENTIFIER INC SEMICOLON  */
#line 251 "bparser.y"
    {
        printf("Increment: %s\n", (yyvsp[-2].strval));
        free((yyvsp[-2].strval));
    }
#line 1575 "bparser.tab.c"
    break;

  case 56: /* decrement_statement: IDENTIFIER DEC SEMICOLON  */
#line 259 "bparser.y"
    {
        printf("Decrement: %s\n", (yyvsp[-2].strval));
        free((yyvsp[-2].strval));
    }
#line 1584 "bparser.tab.c"
    break;

  case 57: /* array_declaration: ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET SEMICOLON  */
#line 267 "bparser.y"
    {
        printf("Array declaration: %s[%d]\n", (yyvsp[-4].strval), (yyvsp[-2].intval));
        free((yyvsp[-4].strval));
    }
#line 1593 "bparser.tab.c"
    break;

  case 58: /* array_declaration: ARRAY LPAREN type RPAREN IDENTIFIER LBRACKET INT_LITERAL RBRACKET ASSIGN LBRACKET array_elements RBRACKET SEMICOLON  */
#line 272 "bparser.y"
    {
        printf("Array declaration with initialization: %s[%d]\n", (yyvsp[-8].strval), (yyvsp[-6].intval));
        free((yyvsp[-8].strval));
    }
#line 1602 "bparser.tab.c"
    break;

  case 61: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 285 "bparser.y"
    {
        printf("Array access: %s\n", (yyvsp[-3].strval));
        free((yyvsp[-3].strval));
    }
#line 1611 "bparser.tab.c"
    break;

  case 81: /* primary_expression: STRING_LITERAL  */
#line 315 "bparser.y"
    {
        free((yyvsp[0].strval));
    }
#line 1619 "bparser.tab.c"
    break;

  case 82: /* primary_expression: CHAR_LITERAL  */
#line 319 "bparser.y"
    {
        free((yyvsp[0].strval));
    }
#line 1627 "bparser.tab.c"
    break;

  case 83: /* primary_expression: IDENTIFIER  */
#line 323 "bparser.y"
    {
        free((yyvsp[0].strval));
    }
#line 1635 "bparser.tab.c"
    break;


#line 1639 "bparser.tab.c"

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

#line 342 "bparser.y"


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
    
    int result = yyparse();
    
    fclose(yyin);
    
    if (result == 0) {
        printf("\n=== Parsing Complete ===\n");
        return 0;
    } else {
        printf("\n=== Parsing Failed ===\n");
        return 1;
    }
}
