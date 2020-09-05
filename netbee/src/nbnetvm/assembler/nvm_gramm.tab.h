/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_NVMPARSER_ASSEMBLER_NVM_GRAMM_TAB_H_INCLUDED
# define YY_NVMPARSER_ASSEMBLER_NVM_GRAMM_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int nvmparser_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_DB = 258,
    T_DW = 259,
    T_DD = 260,
    T_EQU = 261,
    SEGMENT = 262,
    ENDS = 263,
    S_PORT = 264,
    S_DATA = 265,
    S_METADATA = 266,
    T_HOST = 267,
    T_PORT = 268,
    T_ADDR = 269,
    NUMBER = 270,
    STRING = 271,
    IDENTIFIER = 272,
    LABEL = 273,
    PORT_TYPE = 274,
    COPRO_DECL = 275,
    DATAMEMSIZE = 276,
    NETPENAME = 277,
    INFOPARTSIZE = 278,
    LOCALS = 279,
    STACKSIZE = 280,
    BYTEORDER = 281,
    DEFAULTCASE = 282,
    T_NO_ARG_INST = 283,
    T_1BYTE_ARG_INST = 284,
    T_1WORD_ARG_INST = 285,
    T_1INT_ARG_INST = 286,
    T_2INT_ARG_INST = 287,
    T_1LABEL_INST = 288,
    T_1_SHORT_LABEL_INST = 289,
    T_1LABEL_1BYTE_ARG_INST = 290,
    T_1LABEL_1WORD_ARG_INST = 291,
    T_1LABEL_1INT_ARG_INST = 292,
    T_1_PUSH_PORT_ARG_INST = 293,
    T_1_PULL_PORT_ARG_INST = 294,
    T_JMP_TBL_LKUP_INST = 295,
    T_COPRO_INIT_INST = 296,
    T_2_COPRO_IO_ARG_INST = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 589 "../../assembler/nvm_gramm.y" /* yacc.c:1909  */

int	number;
char	id[1024];

#line 102 "../../assembler/nvm_gramm.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE nvmparser_lval;

int nvmparser_parse (void);

#endif /* !YY_NVMPARSER_ASSEMBLER_NVM_GRAMM_TAB_H_INCLUDED  */
