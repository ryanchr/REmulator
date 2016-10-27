
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_NUM_CONTEXT = 258,
     TK_CONTEXT = 259,
     TK_FLAG_PIPELINE = 260,
     TK_NUM_GOLABAL_VAR_IN = 261,
     TK_NUM_GOLABAL_VAR_OUT = 262,
     TK_PORT_INDEX_GOLABAL_IN = 263,
     TK_NAME_GLOABAL_IN = 264,
     TK_NAME_GLOABAL_OUT = 265,
     TK_DATA_SOURCE_ROW = 266,
     TK_OP_ROW = 267,
     TK_DATA_DES_ROW = 268,
     TK_JUMP_MODULAR_SOURCE = 269,
     TK_JUMP_MODULAR_OP = 270,
     TK_JUMP_MODULAR_DES = 271,
     TK_NUM_DATA_CONFIG = 272,
     TK_DATA_CONFIG = 273,
     TK_READ_VGRF_CFG = 274,
     TK_WRITE_VGRF_CFG = 275,
     TK_DATA_ADDR_IN_ROW = 276,
     TK_DATA_ADDR_OUT_ROW = 277,
     TK_JUMP_MODULAR_ADDR_IN = 278,
     TK_JUMP_MODULAR_ADDR_OUT = 279,
     TK_JUMP_MODULAR_MODE = 280,
     TK_DATA_INPUT = 281,
     TK_DIGIT = 282,
     TK_CHAR = 283
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 47 "../../src/parser/parse.y"

        unsigned int        uival;
        int                 ival;
        char *              char_ptr;  
        int *               int_vec;
        char **             char_vec;



/* Line 1676 of yacc.c  */
#line 90 "../../src/parser/parse.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


