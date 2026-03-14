/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BPARSER_TAB_H_INCLUDED
# define YY_YY_BPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 31 "bparser.y"

#include "ast.h"

#line 53 "bparser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM_START = 258,           /* PROGRAM_START  */
    PROGRAM_END = 259,             /* PROGRAM_END  */
    NUMBER_TYPE = 260,             /* NUMBER_TYPE  */
    DECIMAL_TYPE = 261,            /* DECIMAL_TYPE  */
    BOOL_TYPE = 262,               /* BOOL_TYPE  */
    CHAR_TYPE = 263,               /* CHAR_TYPE  */
    STRING_TYPE = 264,             /* STRING_TYPE  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    WHILE = 267,                   /* WHILE  */
    FOR_RANGE = 268,               /* FOR_RANGE  */
    FROM = 269,                    /* FROM  */
    FUNCTION = 270,                /* FUNCTION  */
    BREAK = 271,                   /* BREAK  */
    CONTINUE = 272,                /* CONTINUE  */
    RETURN = 273,                  /* RETURN  */
    PRINT = 274,                   /* PRINT  */
    INPUT = 275,                   /* INPUT  */
    LPAREN = 276,                  /* LPAREN  */
    RPAREN = 277,                  /* RPAREN  */
    LBRACKET = 278,                /* LBRACKET  */
    RBRACKET = 279,                /* RBRACKET  */
    COMMA = 280,                   /* COMMA  */
    COLON = 281,                   /* COLON  */
    SEMICOLON = 282,               /* SEMICOLON  */
    ARRAY = 283,                   /* ARRAY  */
    POW = 284,                     /* POW  */
    SQRT = 285,                    /* SQRT  */
    FLOOR = 286,                   /* FLOOR  */
    CEIL = 287,                    /* CEIL  */
    ABS = 288,                     /* ABS  */
    LENGTH = 289,                  /* LENGTH  */
    INC = 290,                     /* INC  */
    DEC = 291,                     /* DEC  */
    BOOL_TRUE = 292,               /* BOOL_TRUE  */
    BOOL_FALSE = 293,              /* BOOL_FALSE  */
    INCLUDE = 294,                 /* INCLUDE  */
    INDENT = 295,                  /* INDENT  */
    DEDENT = 296,                  /* DEDENT  */
    NEWLINE = 297,                 /* NEWLINE  */
    INT_LITERAL = 298,             /* INT_LITERAL  */
    FLOAT_LITERAL = 299,           /* FLOAT_LITERAL  */
    STRING_LITERAL = 300,          /* STRING_LITERAL  */
    CHAR_LITERAL = 301,            /* CHAR_LITERAL  */
    IDENTIFIER = 302,              /* IDENTIFIER  */
    LOWER_THAN_ELSE = 303,         /* LOWER_THAN_ELSE  */
    UMINUS = 304,                  /* UMINUS  */
    PLUS = 305,                    /* PLUS  */
    MINUS = 306,                   /* MINUS  */
    MULT = 307,                    /* MULT  */
    DIV = 308,                     /* DIV  */
    MOD = 309,                     /* MOD  */
    AND = 310,                     /* AND  */
    OR = 311,                      /* OR  */
    NOT = 312,                     /* NOT  */
    ASSIGN = 313,                  /* ASSIGN  */
    EQUAL = 314,                   /* EQUAL  */
    NOT_EQUAL = 315,               /* NOT_EQUAL  */
    GREATER = 316,                 /* GREATER  */
    LESS = 317,                    /* LESS  */
    GREATER_EQUAL = 318,           /* GREATER_EQUAL  */
    LESS_EQUAL = 319               /* LESS_EQUAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "bparser.y"

    int      intval;
    double   floatval;
    char    *strval;
    VarType  vtype;
    AstNode *node;

#line 142 "bparser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BPARSER_TAB_H_INCLUDED  */
