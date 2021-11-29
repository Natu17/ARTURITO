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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "grammar.y"

        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        #include "../SyntaxTree/include/node.h"
        #include "../SyntaxTree/include/resolution.h"
        #include "../SymbolTable/symbolTable.h"

        extern int yylineno;
        int yylex();
        void yyerror(Node* root, const char* msg);

#line 63 "y.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    STATEMENT_LIST = 258,          /* STATEMENT_LIST  */
    NAME = 259,                    /* NAME  */
    VALUE = 260,                   /* VALUE  */
    NEW = 261,                     /* NEW  */
    INT_TYPE = 262,                /* INT_TYPE  */
    DOUBLE = 263,                  /* DOUBLE  */
    STR = 264,                     /* STR  */
    SELECTOR = 265,                /* SELECTOR  */
    DIV = 266,                     /* DIV  */
    P = 267,                       /* P  */
    BODY = 268,                    /* BODY  */
    H1 = 269,                      /* H1  */
    H2 = 270,                      /* H2  */
    CLASS = 271,                   /* CLASS  */
    VOID = 272,                    /* VOID  */
    ID_TYPE = 273,                 /* ID_TYPE  */
    IF = 274,                      /* IF  */
    WHILE = 275,                   /* WHILE  */
    REASSIGNMENT = 276,            /* REASSIGNMENT  */
    INT_LITERAL = 277,             /* INT_LITERAL  */
    DOUBLE_LITERAL = 278,          /* DOUBLE_LITERAL  */
    STR_LITERAL = 279,             /* STR_LITERAL  */
    AND = 281,                     /* AND  */
    OR = 282,                      /* OR  */
    LE = 283,                      /* LE  */
    GE = 284,                      /* GE  */
    EQ = 285,                      /* EQ  */
    NE = 286,                      /* NE  */
    NOT = 287,                     /* NOT  */
    ID = 288                       /* ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define STATEMENT_LIST 258
#define NAME 259
#define VALUE 260
#define NEW 261
#define INT_TYPE 262
#define DOUBLE 263
#define STR 264
#define SELECTOR 265
#define DIV 266
#define P 267
#define BODY 268
#define H1 269
#define H2 270
#define CLASS 271
#define VOID 272
#define ID_TYPE 273
#define IF 274
#define WHILE 275
#define REASSIGNMENT 276
#define INT_LITERAL 277
#define DOUBLE_LITERAL 278
#define STR_LITERAL 279
#define AND 281
#define OR 282
#define LE 283
#define GE 284
#define EQ 285
#define NE 286
#define NOT 287
#define ID 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "grammar.y"

  char * string;
  int operation;
  int int_value;
  double double_value;
  Node* node;
  Node* root_node;

#line 156 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (Node* root);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
