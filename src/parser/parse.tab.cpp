
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 15 "../../src/parser/parse.y"


#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
// #include <dlfcn.h>
#include <stdarg.h>
#include <vector>
using namespace std;

#include "parser.h"
#include "../parameter/parameter_arch.h"

unsigned int idx_cfg_parse,idx_data_cfg_parse;
unsigned int idx_jump_modular = 0;
int * int_array_temp;
vector<unsigned int> int_vec_temp;
char ** string_array_temp;
vector<string> string_vec_temp;

int  yylex( void );
void yyerror ( char const * );

extern FILE*   yyin;

extern ContextParser *parser_;



/* Line 189 of yacc.c  */
#line 106 "../../src/parser/parse.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 47 "../../src/parser/parse.y"

        unsigned int        uival;
        int                 ival;
        char *              char_ptr;  
        int *               int_vec;
        char **             char_vec;



/* Line 214 of yacc.c  */
#line 180 "../../src/parser/parse.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 192 "../../src/parser/parse.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   163

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  193

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    34,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    13,    17,    25,    30,    34,
      38,    42,    44,    47,    54,    56,    59,    66,    68,    71,
      78,    81,    83,    86,    90,    98,   106,   114,   116,   119,
     123,   130,   137,   144,   147,   151,   153,   156,   162,   165,
     168,   175,   182,   184,   187,   195,   197,   200,   208,   210,
     213,   217,   224,   231,   238,   242,   245,   248,   252,   254,
     258,   260,   264
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    39,    -1,    37,    39,    -1,     3,
      29,    27,    -1,    40,    51,    62,    -1,    41,    42,    43,
      44,    45,    47,    49,    -1,     4,    30,    27,    31,    -1,
       5,    29,    27,    -1,     6,    29,    27,    -1,     7,    29,
      27,    -1,    46,    -1,    45,    46,    -1,     8,    30,    27,
      31,    29,    79,    -1,    48,    -1,    47,    48,    -1,     9,
      30,    27,    31,    29,    80,    -1,    50,    -1,    49,    50,
      -1,    10,    30,    27,    31,    29,    80,    -1,    52,    57,
      -1,    53,    -1,    52,    53,    -1,    54,    55,    56,    -1,
      11,    27,    30,    27,    31,    29,    80,    -1,    12,    27,
      30,    27,    31,    29,    80,    -1,    13,    27,    30,    27,
      31,    29,    80,    -1,    58,    -1,    57,    58,    -1,    59,
      60,    61,    -1,    14,    30,    27,    31,    29,    80,    -1,
      15,    30,    27,    31,    29,    80,    -1,    16,    30,    27,
      31,    29,    80,    -1,    63,    64,    -1,    17,    29,    27,
      -1,    65,    -1,    64,    65,    -1,    66,    67,    70,    72,
      74,    -1,    18,    27,    -1,    68,    69,    -1,    19,    30,
      27,    31,    29,    79,    -1,    20,    30,    27,    31,    29,
      79,    -1,    71,    -1,    70,    71,    -1,    21,    27,    30,
      27,    31,    29,    79,    -1,    73,    -1,    72,    73,    -1,
      22,    27,    30,    27,    31,    29,    79,    -1,    75,    -1,
      74,    75,    -1,    76,    77,    78,    -1,    23,    30,    27,
      31,    29,    79,    -1,    24,    30,    27,    31,    29,    79,
      -1,    25,    30,    27,    31,    29,    79,    -1,    32,    81,
      33,    -1,    32,    33,    -1,    32,    33,    -1,    32,    82,
      33,    -1,    27,    -1,    81,    34,    27,    -1,    83,    -1,
      82,    34,    83,    -1,    35,    28,    35,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,   102,   111,   123,   132,   144,   154,   162,
     172,   182,   183,   192,   202,   203,   212,   222,   223,   232,
     245,   250,   251,   258,   265,   274,   283,   292,   293,   298,
     303,   313,   323,   335,   343,   354,   359,   365,   373,   382,
     386,   394,   402,   403,   410,   419,   420,   427,   437,   441,
     447,   452,   461,   470,   492,   493,   501,   502,   510,   515,
     524,   529,   533
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_NUM_CONTEXT", "TK_CONTEXT",
  "TK_FLAG_PIPELINE", "TK_NUM_GOLABAL_VAR_IN", "TK_NUM_GOLABAL_VAR_OUT",
  "TK_PORT_INDEX_GOLABAL_IN", "TK_NAME_GLOABAL_IN", "TK_NAME_GLOABAL_OUT",
  "TK_DATA_SOURCE_ROW", "TK_OP_ROW", "TK_DATA_DES_ROW",
  "TK_JUMP_MODULAR_SOURCE", "TK_JUMP_MODULAR_OP", "TK_JUMP_MODULAR_DES",
  "TK_NUM_DATA_CONFIG", "TK_DATA_CONFIG", "TK_READ_VGRF_CFG",
  "TK_WRITE_VGRF_CFG", "TK_DATA_ADDR_IN_ROW", "TK_DATA_ADDR_OUT_ROW",
  "TK_JUMP_MODULAR_ADDR_IN", "TK_JUMP_MODULAR_ADDR_OUT",
  "TK_JUMP_MODULAR_MODE", "TK_DATA_INPUT", "TK_DIGIT", "TK_CHAR", "'='",
  "'['", "']'", "'{'", "'}'", "','", "'\"'", "$accept", "contexts",
  "num_context", "context", "head_context", "index_context",
  "flag_pipeline", "num_gvar_in", "num_gvar_out", "index_port", "index",
  "name_port_in", "port_in", "name_port_out", "port_out", "route_context",
  "rca_route_config", "route_cofing_row", "data_source_row", "op_row",
  "data_des_row", "multi_jump_cfg", "jump_modular_cfg",
  "jump_modular_source", "jump_modular_op", "jump_modular_des",
  "data_context", "num_data_cfg", "multi_data_config", "data_config",
  "head_data_cfg", "vgrf_cfg", "read_vgrf_cfg", "write_vgrf_cfg",
  "multi_data_addr_in", "data_addr_in_row", "multi_data_addr_out",
  "data_addr_out_row", "multi_jump_data_cfg", "jump_data_cfg",
  "modular_addr_in", "modular_addr_out", "modular_mode", "int_array",
  "string_array", "digits", "strings", "chars", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    61,
      91,    93,   123,   125,    44,    34
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    45,    46,    47,    47,    48,    49,    49,    50,
      51,    52,    52,    53,    54,    55,    56,    57,    57,    58,
      59,    60,    61,    62,    63,    64,    64,    65,    66,    67,
      68,    69,    70,    70,    71,    72,    72,    73,    74,    74,
      75,    76,    77,    78,    79,    79,    80,    80,    81,    81,
      82,    82,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     3,     3,     7,     4,     3,     3,
       3,     1,     2,     6,     1,     2,     6,     1,     2,     6,
       2,     1,     2,     3,     7,     7,     7,     1,     2,     3,
       6,     6,     6,     2,     3,     1,     2,     5,     2,     2,
       6,     6,     1,     2,     7,     1,     2,     7,     1,     2,
       3,     6,     6,     6,     3,     2,     2,     3,     1,     3,
       1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     3,     0,     0,
       2,     4,     0,     0,     0,     0,    21,     0,     0,     0,
       0,     0,     0,     5,     0,     0,    22,    20,    27,     0,
       0,     0,     0,     0,     0,     7,     0,     0,     0,    33,
      35,     0,     0,    28,     0,     0,     0,     0,    23,     8,
       0,     0,     0,     0,    34,    38,    36,     0,     0,     0,
       0,     0,     0,    29,     0,     0,     9,     0,     0,     0,
      11,     0,     0,     0,     0,    42,     0,    39,     0,     0,
       0,     0,     0,    10,     0,     0,    12,     0,    14,     0,
       0,     0,     0,    43,     0,    45,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,     6,    17,     0,    24,
       0,     0,     0,     0,    46,    37,    48,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,    18,    56,     0,
       0,    60,     0,     0,     0,     0,    49,     0,     0,     0,
      31,     0,    25,     0,     0,     0,     0,     0,    57,     0,
       0,    40,     0,     0,     0,     0,     0,    50,     0,    32,
      26,    13,     0,     0,    62,    61,    58,    55,     0,     0,
       0,     0,     0,     0,    41,    16,     0,    54,     0,    44,
       0,     0,     0,     0,    19,    59,    47,    51,     0,     0,
      52,     0,    53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,     9,    19,    34,    52,    69,
      70,    87,    88,   106,   107,    14,    15,    16,    17,    31,
      48,    27,    28,    29,    45,    63,    23,    24,    39,    40,
      41,    58,    59,    77,    74,    75,    94,    95,   115,   116,
     117,   138,   157,   151,   109,   168,   130,   131
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -144
static const yytype_int16 yypact[] =
{
       8,   -11,     3,    20,     2,  -144,     0,  -144,    21,    26,
    -144,  -144,     6,     9,    17,    -5,  -144,    23,    10,    34,
      11,    13,    12,  -144,    29,    19,  -144,    36,  -144,    37,
      24,    40,    27,    28,    48,  -144,    31,    32,    33,    29,
    -144,    42,    35,  -144,    38,    47,    39,    43,  -144,  -144,
      44,    45,    56,    25,  -144,  -144,  -144,    46,    51,    53,
      49,    50,    52,  -144,    54,    55,  -144,    57,    58,    -4,
    -144,    60,    59,    63,    -8,  -144,    61,  -144,    64,    65,
      67,    66,    68,  -144,    71,    62,  -144,     7,  -144,    69,
      72,    70,    75,  -144,    -3,  -144,    77,    69,    76,    78,
      79,    80,    81,    83,    84,  -144,    73,  -144,   -23,  -144,
      86,    89,    87,    88,  -144,    90,  -144,    82,    91,  -144,
      69,    92,    69,    94,    95,    96,    93,  -144,  -144,    97,
     -12,  -144,    98,   100,    99,   101,  -144,   102,    41,   104,
    -144,    69,  -144,    69,    98,   105,   106,   103,  -144,   107,
     -25,  -144,   110,   109,   112,   108,   111,  -144,    98,  -144,
    -144,  -144,    69,   115,  -144,  -144,  -144,  -144,    -6,    98,
     116,   117,   118,   120,  -144,  -144,    69,  -144,   121,  -144,
      98,    98,   122,   119,  -144,  -144,  -144,  -144,    98,   123,
    -144,    98,  -144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,   126,  -144,  -144,  -144,  -144,  -144,  -144,
      -2,  -144,    -9,  -144,   -31,  -144,  -144,   138,  -144,  -144,
    -144,  -144,   127,  -144,  -144,  -144,  -144,  -144,  -144,   124,
    -144,  -144,  -144,  -144,  -144,    85,  -144,    -7,  -144,   -16,
    -144,  -144,  -144,  -143,   -97,  -144,  -144,   -42
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     119,   161,   166,     5,    68,    85,    13,     6,   167,    25,
     128,     1,   129,    73,    92,   174,    85,   104,     4,    92,
     113,   148,   149,   140,     6,   142,   179,   177,   178,    11,
      12,    18,    13,    20,    22,    30,    21,   186,   187,    32,
      33,    37,    35,    36,   159,   190,   160,    38,   192,    42,
      25,    46,    44,    47,    49,    51,    71,    50,    53,    54,
      55,    57,    60,    62,    68,   175,   156,    86,    61,    64,
      65,    66,    73,    76,    67,   127,    72,    79,   105,   184,
      78,    81,    80,   104,    83,    82,    90,   114,    84,    89,
      91,    96,   103,    97,    99,   101,    98,   100,   102,   136,
     111,   108,   112,   110,   118,   120,   137,   165,   122,   121,
     125,   123,   124,   113,   126,   132,   133,   134,   135,     0,
     146,   141,   139,   143,   144,   147,   153,   145,   154,    10,
     150,   152,   155,   158,   162,   172,     0,   163,   164,   169,
     170,   173,   129,   171,   176,   180,   181,   183,   185,   182,
     189,   188,   191,    26,    43,     0,     0,     0,     0,    93,
       0,     0,     0,    56
};

static const yytype_int16 yycheck[] =
{
      97,   144,    27,     0,     8,     9,    11,     4,    33,    14,
      33,     3,    35,    21,    22,   158,     9,    10,    29,    22,
      23,    33,    34,   120,     4,   122,   169,    33,    34,    27,
      30,     5,    11,    27,    17,    12,    27,   180,   181,    29,
       6,    29,    31,    30,   141,   188,   143,    18,   191,    30,
      14,    27,    15,    13,    27,     7,    31,    29,    27,    27,
      27,    19,    27,    16,     8,   162,    25,    69,    30,    30,
      27,    27,    21,    20,    29,   106,    30,    27,    87,   176,
      31,    27,    30,    10,    27,    30,    27,    94,    30,    29,
      27,    30,    30,    29,    27,    27,    31,    31,    27,   115,
      30,    32,    27,    31,    27,    29,    24,   149,    29,    31,
      27,    31,    31,    23,    30,    29,    27,    30,    30,    -1,
      27,    29,    31,    29,    29,    28,    27,    31,    27,     3,
      32,    31,    30,    29,    29,    27,    -1,    31,    35,    29,
      31,    30,    35,    31,    29,    29,    29,    27,    27,    31,
      31,    29,    29,    15,    27,    -1,    -1,    -1,    -1,    74,
      -1,    -1,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    37,    38,    29,     0,     4,    39,    40,    41,
      39,    27,    30,    11,    51,    52,    53,    54,     5,    42,
      27,    27,    17,    62,    63,    14,    53,    57,    58,    59,
      12,    55,    29,     6,    43,    31,    30,    29,    18,    64,
      65,    66,    30,    58,    15,    60,    27,    13,    56,    27,
      29,     7,    44,    27,    27,    27,    65,    19,    67,    68,
      27,    30,    16,    61,    30,    27,    27,    29,     8,    45,
      46,    31,    30,    21,    70,    71,    20,    69,    31,    27,
      30,    27,    30,    27,    30,     9,    46,    47,    48,    29,
      27,    27,    22,    71,    72,    73,    30,    29,    31,    27,
      31,    27,    27,    30,    10,    48,    49,    50,    32,    80,
      31,    30,    27,    23,    73,    74,    75,    76,    27,    80,
      29,    31,    29,    31,    31,    27,    30,    50,    33,    35,
      82,    83,    29,    27,    30,    30,    75,    24,    77,    31,
      80,    29,    80,    29,    29,    31,    27,    28,    33,    34,
      32,    79,    31,    27,    27,    30,    25,    78,    29,    80,
      80,    79,    29,    31,    35,    83,    27,    33,    81,    29,
      31,    31,    27,    30,    79,    80,    29,    33,    34,    79,
      29,    29,    31,    27,    80,    27,    79,    79,    29,    31,
      79,    29,    79
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 97 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cout<<"yyparse >> ************** Context["<<idx_cfg_parse<<"] Parse End **************"<<endl;
#endif
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 103 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cout<<"yyparse >> ************** Context["<<idx_cfg_parse<<"] Parse End **************"<<endl;
#endif
;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 112 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr <<endl;
	cerr << "yyparse >> ******************* Start Context Parse ******************* "<<endl;
	cerr << "yyparse >> The Number of Contexts is "<<(yyvsp[(3) - (3)].uival)<< endl;
#endif
	parser_->setNumOfContext((yyvsp[(3) - (3)].uival));
;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 124 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
#endif
;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 135 "../../src/parser/parse.y"
    { 
#if DEBUG_YACC
	cerr << "yyparse >> Head Context Parse End."<< endl<<endl;
	cerr << "yyparse >> Route Context Parse Start"<<endl;
#endif
//TODO
;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 145 "../../src/parser/parse.y"
    { 
#if DEBUG_YACC
	cerr << endl;
	cerr << "yyparse >> ************** Start Context"<<"["<<(yyvsp[(3) - (4)].uival)<<"] Parse **************"<< endl;
#endif
  idx_cfg_parse = (yyvsp[(3) - (4)].uival);
;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 155 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> Flag of Pipeline :"<<" "<<(yyvsp[(3) - (3)].uival)<<" "<< endl;
#endif
	parser_->setFlagPipeline((yyvsp[(3) - (3)].uival),idx_cfg_parse);
;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 163 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The Number of Input Golabal Variables is "<< (yyvsp[(3) - (3)].uival) << endl;
#endif
//TODO
	parser_->setNumOfGlobalIn((yyvsp[(3) - (3)].uival),idx_cfg_parse);
;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 173 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The number of Output Golabal Variables is " << (yyvsp[(3) - (3)].uival) << endl;
#endif
//TODO
	parser_->setNumOfGlobalOut((yyvsp[(3) - (3)].uival),idx_cfg_parse);
;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 184 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The Numbers of Port Indices are "<< endl;
#endif
//TODO
;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 193 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The Numbers of Port Indices are "<< endl;
#endif
//TODO
	parser_->setIndexOfGlobalPort((yyvsp[(3) - (6)].uival), int_vec_temp, idx_cfg_parse);
;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 204 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Input Ports are " << endl;
#endif
//TODO
;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 213 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Input Ports are " << endl;
#endif
//TODO
	parser_->setNameOfGlobalIn((yyvsp[(3) - (6)].uival), string_vec_temp, idx_cfg_parse);
;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 224 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Output Ports are "<< endl;
#endif
//TODO
;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 233 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Output Ports are "<< endl;
#endif
//TODO
		parser_->setNameOfGlobalOut((yyvsp[(3) - (6)].uival), string_vec_temp, idx_cfg_parse);
;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 246 "../../src/parser/parse.y"
    {
;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 252 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
#endif
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 259 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
#endif
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 266 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> row "<<(yyvsp[(2) - (7)].uival)<<" data source : num = "<<(yyvsp[(4) - (7)].uival)<< endl;
#endif
	parser_->setDataSource((yyvsp[(4) - (7)].uival), string_vec_temp, idx_cfg_parse);	
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 275 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> op_row"<<(yyvsp[(2) - (7)].uival)<<endl;
#endif
	parser_->setOpcode((yyvsp[(4) - (7)].uival), string_vec_temp, idx_cfg_parse);	
;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 284 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> row "<<(yyvsp[(2) - (7)].uival)<<" data des : "<< endl;
#endif
	parser_->setDataDes((yyvsp[(4) - (7)].uival), string_vec_temp, idx_cfg_parse);	
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 294 "../../src/parser/parse.y"
    {
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 299 "../../src/parser/parse.y"
    {
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 304 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr<<"yyparse >> jump modular "<<" source : num = "<<(yyvsp[(3) - (6)].uival)<<endl;
#endif
//TODO
	parser_->setDataSource((yyvsp[(3) - (6)].uival), string_vec_temp, idx_cfg_parse);	
;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 314 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr<<"yyparse >> jump modular "<<" op : num = "<<(yyvsp[(3) - (6)].uival)<<endl;
#endif
//TODO
	parser_->setOpcode((yyvsp[(3) - (6)].uival), string_vec_temp, idx_cfg_parse);	
;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 324 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr<<"yyparse >> jump modular "<<" des : num = "<<(yyvsp[(3) - (6)].uival)<<endl;
#endif
//TODO
	parser_->setDataDes((yyvsp[(3) - (6)].uival), string_vec_temp, idx_cfg_parse);	
;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 336 "../../src/parser/parse.y"
    {
#if DEBUG_YACC	
	cerr << "yyparse >> Data Context Parse End." << endl<<endl;
#endif
;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 344 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr <<endl;
	cerr << "yyparse >> Data Context Parse Start. "<< endl;
	cerr << "yyparse >> Num of Data Context is "<<(yyvsp[(3) - (3)].uival)<< endl;
#endif
	parser_->setDataCfgNum((yyvsp[(3) - (3)].uival),idx_cfg_parse);
;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 355 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
#endif
;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 360 "../../src/parser/parse.y"
    {
;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 366 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
#endif
    idx_jump_modular = 0;
;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 374 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> Data Config Head : Index of Data Config = " <<(yyvsp[(2) - (2)].uival)<< endl;
#endif
	idx_data_cfg_parse = (yyvsp[(2) - (2)].uival);;
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 383 "../../src/parser/parse.y"
    {
;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 387 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> Here is Read Vgrf Config in Data Context "<<idx_data_cfg_parse<<endl;
#endif
	parser_->setReadVgrfCfg(idx_data_cfg_parse, (yyvsp[(3) - (6)].uival), idx_cfg_parse, int_vec_temp);
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 395 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> Here is Write Vgrf Config in Data Context "<<idx_data_cfg_parse<<endl;
#endif
	parser_->setWriteVgrfCfg(idx_data_cfg_parse,  (yyvsp[(3) - (6)].uival), idx_cfg_parse, int_vec_temp);
;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 404 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
#endif
;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 411 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	cerr << "yyparse >> Read Data Addr in Row "<<(yyvsp[(2) - (7)].uival)<<endl;
#endif
	parser_->setDataAddrIn((yyvsp[(4) - (7)].uival),idx_data_cfg_parse,idx_cfg_parse,int_vec_temp);
;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 421 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
#endif
;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 428 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	 cerr << "yyparse >> Read Data Addr Out Row "<<(yyvsp[(2) - (7)].uival)<<endl;
#endif
//TODO
	parser_->setDataAddrOut((yyvsp[(4) - (7)].uival),idx_data_cfg_parse,idx_cfg_parse,int_vec_temp);
;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 438 "../../src/parser/parse.y"
    {
	idx_jump_modular++;
;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 442 "../../src/parser/parse.y"
    {
    idx_jump_modular++;
;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 448 "../../src/parser/parse.y"
    {
;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 453 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	 cerr << "yyparse >> Jump modular Config, Num of Addr in:"<<(yyvsp[(3) - (6)].uival)<< endl;
#endif
	parser_->setJumpDataIn((yyvsp[(3) - (6)].uival),idx_data_cfg_parse,idx_cfg_parse,int_vec_temp,idx_jump_modular);
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 462 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	 cerr << "yyparse >> Jump modular 2 Config, Num of Addr Out:"<<(yyvsp[(3) - (6)].uival)<< endl;
#endif
	parser_->setJumpDataOut((yyvsp[(3) - (6)].uival),idx_data_cfg_parse,idx_cfg_parse,int_vec_temp,idx_jump_modular);
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 471 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	 cerr << "yyparse >> Jump Module 2 Config, Num of Mode:"<<(yyvsp[(3) - (6)].uival)<< endl;
#endif
	parser_->setJumpMode((yyvsp[(3) - (6)].uival),idx_data_cfg_parse,idx_cfg_parse,int_vec_temp,idx_jump_modular);
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 494 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	//cerr << "yyparse >> read an integer array!!! " << endl;
#endif
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 503 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	//cerr << "yyparse >> read an string array!!! " << endl;
#endif
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 511 "../../src/parser/parse.y"
    { 
	int_vec_temp.clear();  int_vec_temp.push_back((yyvsp[(1) - (1)].uival));  
	//cerr <<"yyparse >> read a digit "<<endl;
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 516 "../../src/parser/parse.y"
    {    
	int_vec_temp.push_back((yyvsp[(3) - (3)].uival));  
#if DEBUG_YACC
	//cerr <<"yyparse >> read a digit "<<endl;
#endif
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 525 "../../src/parser/parse.y"
    {  
	string_vec_temp.clear();   
	string_vec_temp.push_back((yyvsp[(1) - (1)].char_ptr)); 
;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 530 "../../src/parser/parse.y"
    {  string_vec_temp.push_back((yyvsp[(3) - (3)].char_ptr));  ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 534 "../../src/parser/parse.y"
    {
#if DEBUG_YACC
	//cerr <<"yyparse >> read a string "<<endl;
#endif
	(yyval.char_ptr) = (yyvsp[(2) - (3)].char_ptr);
;}
    break;



/* Line 1455 of yacc.c  */
#line 2124 "../../src/parser/parse.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 542 "../../src/parser/parse.y"


void yyerror( char const *s )
{
	fprintf(stderr,"%s\n",s);
}

void config_parse( string name )
{
	yyin = fopen( name.c_str(), "r" ); 

	yyparse();

	return;
}



