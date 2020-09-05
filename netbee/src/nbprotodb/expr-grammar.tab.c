/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         pdl_parse
#define yylex           pdl_lex
#define yyerror         pdl_error
#define yydebug         pdl_debug
#define yynerrs         pdl_nerrs


/* Copy the first part of user declarations.  */
#line 1 "expr-grammar.y" /* yacc.c:339  */

/*****************************************************************************/
/*                                                                           */
/* Copyright notice: please read file license.txt in the NetBee root folder. */
/*                                                                           */
/*****************************************************************************/



#include <stdio.h>
#include "expressions.h"
#include <nbprotodb_exports.h>
#include "../nbee/globals/utils.h"
#include "../nbee/globals/debug.h"

#define YYSTYPE void*

int yylex(YYSTYPE *lvalp);
//int yyerror(char **ParsedExpression, char *Message);
int yyerror(void **ParsedExpression, void *Message);

char *ParserErrorBuffer;
int ParserErrorBufferSize;

// This variable (which is the buffer to be parsed, managed by LEX) is needed for debug purposes
extern char *source_buffer_string;


#line 101 "expr-grammar.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "expr-grammar.tab.h".  */
#ifndef YY_PDL_EXPR_GRAMMAR_TAB_H_INCLUDED
# define YY_PDL_EXPR_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int pdl_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OPERAND_NUMBER = 258,
    OPERAND_STRING = 259,
    OPERAND_BOOLEAN = 260,
    OPERAND_VARIABLE_NUMBER = 261,
    OPERAND_VARIABLE_STRING = 262,
    OPERAND_VARIABLE_LOOKUPTABLE = 263,
    FUNCTION_HASSTRING = 264,
    FUNCTION_EXTRACTSTRING = 265,
    FUNCTION_DEBUG = 266,
    FUNCTION_BUFFER2INT = 267,
    FUNCTION_INT2BUFFER = 268,
    FUNCTION_ISPRESENT = 269,
    FUNCTION_ISASN1TYPE = 270,
    FUNCTION_CHANGEBYTEORDER = 271,
    FUNCTION_ASCII2INT = 272,
    FUNCTION_CHECKLOOKUPTABLE = 273,
    FUNCTION_UPDATELOOKUPTABLE = 274,
    OPERAND_PROTOFIELD = 275,
    AND = 276,
    OR = 277,
    GE = 278,
    GT = 279,
    LE = 280,
    LT = 281,
    EQ = 282,
    NEQ = 283,
    BWAND = 284,
    BWOR = 285,
    ADD = 286,
    SUB = 287,
    MUL = 288,
    DIV = 289,
    MOD = 290,
    NOT = 291,
    BWNOT = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int pdl_parse (void **ParsedExpression);

#endif /* !YY_PDL_EXPR_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 189 "expr-grammar.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   301

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    43,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    57,    57,    69,    81,    96,   105,   106,   107,   108,
     113,   114,   118,   119,   120,   121,   122,   123,   124,   130,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   161,   162,   163,   167,   168,   173,   174,   175,
     176,   177,   182
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OPERAND_NUMBER", "OPERAND_STRING",
  "OPERAND_BOOLEAN", "OPERAND_VARIABLE_NUMBER", "OPERAND_VARIABLE_STRING",
  "OPERAND_VARIABLE_LOOKUPTABLE", "FUNCTION_HASSTRING",
  "FUNCTION_EXTRACTSTRING", "FUNCTION_DEBUG", "FUNCTION_BUFFER2INT",
  "FUNCTION_INT2BUFFER", "FUNCTION_ISPRESENT", "FUNCTION_ISASN1TYPE",
  "FUNCTION_CHANGEBYTEORDER", "FUNCTION_ASCII2INT",
  "FUNCTION_CHECKLOOKUPTABLE", "FUNCTION_UPDATELOOKUPTABLE",
  "OPERAND_PROTOFIELD", "AND", "OR", "GE", "GT", "LE", "LT", "EQ", "NEQ",
  "BWAND", "BWOR", "ADD", "SUB", "MUL", "DIV", "MOD", "NOT", "BWNOT",
  "'('", "')'", "','", "'['", "':'", "']'", "$accept", "program",
  "parameter_list", "mathoperand", "mathexpr", "stringoperand",
  "stringexpr", "boolexp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    40,    41,
      44,    91,    58,    93
};
# endif

#define YYPACT_NINF -40

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-40)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      64,   -40,   -40,   -40,   -40,   -39,   -27,   -13,     1,    19,
      20,    21,    22,    27,    34,    47,    48,   -14,   119,   119,
     119,    32,   -40,   266,   -40,    -9,   -40,   119,    83,    83,
      64,    83,   119,    68,    83,    83,    83,    81,    87,   119,
     -40,    -9,   -40,   247,   -23,   -40,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,    83,    83,    83,    83,   183,    83,    51,    52,    58,
      59,   227,    65,    69,    71,    88,    80,   113,   205,   -40,
     -40,   117,   117,    84,    84,    84,    84,    84,    84,   -25,
     -25,   -11,   -11,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     119,   115,   104,   169,   -40,   -40,   171,   -40,   172,   -40,
     -40,   119,   119,   119,   137,   136,   138,   140,   156,    -2,
     266,    -9,    16,   160,   -40,   174,   194,   -40,   195,   -40,
     119,   -40,   -40,   161,   159,   162,   266,    -9,   -40,   199,
     -40,   180,   -40
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,    42,    52,    11,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
       0,     0,    12,     2,    45,     3,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    36,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      51,    34,    35,    31,    30,    33,    32,    28,    29,    27,
      26,    21,    22,    23,    24,    25,    38,    39,    40,    41,
       0,     0,     0,     0,     5,    14,     0,    17,     0,    48,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     0,     0,    49,     0,     0,    47,     0,    18,
       0,    19,    50,     0,     0,     0,     8,     9,    16,     0,
      13,     0,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -40,   190,   109,   -40,    -6,   -40,     0,   -40
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    21,   119,    22,    23,    24,    41,    26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    61,    27,    62,    63,    64,    56,    57,    58,    59,
      60,    28,    40,    42,    43,    61,    80,    62,    63,    64,
      44,    65,    58,    59,    60,    29,    71,    39,    67,    68,
      25,    70,    45,    78,    73,    74,    75,   129,   130,    30,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,   131,   130,    31,    32,    33,
      34,    96,    97,    98,    99,    35,   101,     1,     2,     3,
       4,     5,    36,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    37,    38,     2,    72,    76,
       5,   102,   103,     7,   114,    77,    10,   104,   105,    13,
      18,    19,    20,    17,   107,   120,   120,   123,   115,   108,
     109,   121,   121,    54,    55,    56,    57,    58,    59,    60,
     111,    66,     1,     2,   136,     4,     5,   110,     6,     7,
     137,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,   112,    80,    18,    19,    20,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,   116,   117,   118,   125,   133,   126,   127,
     124,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   128,   134,   135,   139,
     138,   140,   141,   132,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   142,
      69,   122,     0,     0,     0,   100,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,     0,     0,     0,   113,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,   106,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,    79,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60
};

static const yytype_int16 yycheck[] =
{
       0,    24,    41,    26,    27,    28,    31,    32,    33,    34,
      35,    38,    18,    19,    20,    24,    39,    26,    27,    28,
      20,    27,    33,    34,    35,    38,    32,    41,    28,    29,
      30,    31,     0,    39,    34,    35,    36,    39,    40,    38,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    39,    40,    38,    38,    38,
      38,    61,    62,    63,    64,    38,    66,     3,     4,     5,
       6,     7,    38,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    38,    38,     4,    20,     8,
       7,    40,    40,    10,   100,     8,    13,    39,    39,    16,
      36,    37,    38,    20,    39,   111,   112,   113,     4,    40,
      39,   111,   112,    29,    30,    31,    32,    33,    34,    35,
      40,    38,     3,     4,   130,     6,     7,    39,     9,    10,
     130,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    40,    39,    36,    37,    38,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     4,     3,     3,    40,     3,    40,    39,
      43,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    40,     3,     3,    40,
      39,    39,     3,    43,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    39,
      30,   112,    -1,    -1,    -1,    42,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    42,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    39,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    36,    37,
      38,    45,    47,    48,    49,    50,    51,    41,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    41,
      48,    50,    48,    48,    50,     0,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    24,    26,    27,    28,    48,    38,    50,    50,    45,
      50,    48,    20,    50,    50,    50,     8,     8,    48,    39,
      39,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    50,    50,    50,    50,
      42,    50,    40,    40,    39,    39,    40,    39,    40,    39,
      39,    40,    40,    42,    48,     4,     4,     3,     3,    46,
      48,    50,    46,    48,    43,    40,    40,    39,    40,    39,
      40,    39,    43,     3,     3,     3,    48,    50,    39,    40,
      39,     3,    39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    45,    46,    46,    46,    46,
      47,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    49,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    51
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     4,     1,     1,     3,     3,
       1,     1,     1,     8,     4,     4,     8,     4,     6,     6,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     3,
       3,     3,     1,     1,     1,     1,    10,     6,     4,     6,
       6,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (ParsedExpression, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, ParsedExpression); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void **ParsedExpression)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (ParsedExpression);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void **ParsedExpression)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, ParsedExpression);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void **ParsedExpression)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , ParsedExpression);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, ParsedExpression); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void **ParsedExpression)
{
  YYUSE (yyvaluep);
  YYUSE (ParsedExpression);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void **ParsedExpression)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 58 "expr-grammar.y" /* yacc.c:1646  */
    {
				if (yynerrs > 0)
				{
					ParsedExpression= NULL;
					YYABORT;
				}
				else
				{
					*ParsedExpression= (yyvsp[0]);
				}
			}
#line 1405 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 70 "expr-grammar.y" /* yacc.c:1646  */
    {
				if (yynerrs > 0)
				{
					ParsedExpression= NULL;
					YYABORT;
				}
				else
				{
					*ParsedExpression= (yyvsp[0]);
				}
			}
#line 1421 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 82 "expr-grammar.y" /* yacc.c:1646  */
    {
				//[icerrato]
				if (yynerrs > 0)
				{
					ParsedExpression= NULL;
					YYABORT;
				}
				else
				{
					*ParsedExpression= (yyvsp[0]);
				}
			
			}
#line 1439 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 97 "expr-grammar.y" /* yacc.c:1646  */
    {
			((struct _nbNetPDLExprBase *) *ParsedExpression)->PrintDebug= 1;
		}
#line 1447 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 105 "expr-grammar.y" /* yacc.c:1646  */
    {(yyval) = (void *) CreateParameterList(NULL, (struct _nbNetPDLExprBase *) (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1453 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 106 "expr-grammar.y" /* yacc.c:1646  */
    {(yyval) = (void *) CreateParameterList(NULL, (struct _nbNetPDLExprBase *) (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1459 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 107 "expr-grammar.y" /* yacc.c:1646  */
    {(yyval) = (void *) CreateParameterList((struct _nbParamsLinkedList *) (yyvsp[-2]), (struct _nbNetPDLExprBase *) (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1465 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 108 "expr-grammar.y" /* yacc.c:1646  */
    {(yyval) = (void *) CreateParameterList((struct _nbParamsLinkedList *) (yyvsp[-2]), (struct _nbNetPDLExprBase *) (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1471 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 119 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateFunctionIsASN1Type((struct _nbNetPDLExprString *) (yyvsp[-5]), (struct _nbNetPDLExprNumber *) (yyvsp[-3]), (struct _nbNetPDLExprNumber *) (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1477 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 120 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateFunctionBuffer2IntItem((struct _nbNetPDLExprBase *) (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1483 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 121 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateFunctionAscii2IntItem((struct _nbNetPDLExprBase *) (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1489 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 122 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateFunctionHasStringItem((struct _nbNetPDLExprBase *) (yyvsp[-5]), (const char *) (yyvsp[-3]), (struct _nbNetPDLExprNumber *) (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1495 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 123 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateFunctionIsPresentItem((struct _nbNetPDLExprFieldRef *) (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1501 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 124 "expr-grammar.y" /* yacc.c:1646  */
    {
																									(yyval) = (void *) CreateFunctionCheckUpdateLookupTableItem((struct _nbNetPDLExprVariable *) (yyvsp[-3]), (struct _nbParamsLinkedList *) (yyvsp[-1]));
																									if ((yyval) == NULL) YYABORT;
																									else ((struct _nbNetPDLExprFunctionCheckUpdateLookupTable *)(yyval))->Type= nbNETPDL_ID_EXPR_OPERAND_FUNCTION_CHECKLOOKUPTABLE;
																								}
#line 1511 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 130 "expr-grammar.y" /* yacc.c:1646  */
    {
																									(yyval) = (void *) CreateFunctionCheckUpdateLookupTableItem((struct _nbNetPDLExprVariable *) (yyvsp[-3]), (struct _nbParamsLinkedList *) (yyvsp[-1]));
																									if ((yyval) == NULL) YYABORT;
																									else ((struct _nbNetPDLExprFunctionCheckUpdateLookupTable *)(yyval))->Type= nbNETPDL_ID_EXPR_OPERAND_FUNCTION_UPDATELOOKUPTABLE;
																								}
#line 1521 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 135 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1527 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 136 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1533 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 137 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1539 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 138 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1545 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 139 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1551 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 140 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1557 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 141 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1563 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 142 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1569 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 143 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1575 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 144 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1581 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 145 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1587 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 146 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1593 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 147 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1599 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 148 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1605 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 149 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1611 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 150 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1617 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 151 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem(NULL, (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1623 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 152 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem(NULL, (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1629 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 153 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1635 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 154 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1641 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 155 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1647 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 156 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateExpressionItem((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); if ((yyval) == NULL) YYABORT; }
#line 1653 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 161 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateStringItem((const char *) (yyvsp[0])); }
#line 1659 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 169 "expr-grammar.y" /* yacc.c:1646  */
    { 
								(yyval) = (void *) CreateFunctionExtractStringItem((struct _nbNetPDLExprBase *) (yyvsp[-7]), (const char *) (yyvsp[-5]), (struct _nbNetPDLExprNumber *) (yyvsp[-3]), (struct _nbNetPDLExprNumber *) (yyvsp[-1]));
								if ((yyval) == NULL) YYABORT;
							}
#line 1668 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 173 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateFunctionInt2BufferItem((struct _nbNetPDLExprBase *) (yyvsp[-3]), (struct _nbNetPDLExprNumber *) (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1674 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 174 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) CreateFunctionChangeByteOrderItem((struct _nbNetPDLExprBase *) (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1680 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 175 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) UpdateVariableItem((yyvsp[-5]), (yyvsp[-3]), (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1686 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 176 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (void *) UpdateProtoFieldItem((yyvsp[-5]), (yyvsp[-3]), (yyvsp[-1])); if ((yyval) == NULL) YYABORT; }
#line 1692 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 182 "expr-grammar.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]);}
#line 1698 "expr-grammar.tab.c" /* yacc.c:1646  */
    break;


#line 1702 "expr-grammar.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (ParsedExpression, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (ParsedExpression, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
                      yytoken, &yylval, ParsedExpression);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp, ParsedExpression);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (ParsedExpression, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, ParsedExpression);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, ParsedExpression);
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
  return yyresult;
}
#line 185 "expr-grammar.y" /* yacc.c:1906  */




//int yyerror(char **ParsedExpression, char *Message)
int yyerror(void **ParsedExpression, void *Message)
{
	// Do not overwrite an existing error message
	if ((ParserErrorBufferSize > 0) && (ParserErrorBuffer[0] == 0))
	{
		// I don't know why, but it seems that '*ParsedExpression' is always NULL
		errorsnprintf(__FILE__, __FUNCTION__, __LINE__, ParserErrorBuffer, ParserErrorBufferSize, 
							"Error compiling NetPDL expression '%s': %s", source_buffer_string, (char*) Message);
	};

	return 1;
}
