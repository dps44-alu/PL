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
#line 11 "plp5.y"


#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#include "comun.h"
#include "TablaSimbolos.h"
#include "TablaTipos.h"

extern int ncol, nlin, findefichero;
extern int yylex();
extern char *yytext;
extern FILE *yyin;
void yyerror(char *s);

const int MEM_TOTAL = 16384;
const int MEM_VAR   = 16000;

TablaSimbolos   ts  = new TablaSimbolos(NULL);
TablaTipos      tt  = TablaTipos();

int posMemoria = 0;
int numEtiqueta = 1;
int numbloque = 0;

using namespace std;


#line 104 "plp5.tab.c"

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

#include "plp5.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_fn = 3,                         /* fn  */
  YYSYMBOL_endfn = 4,                      /* endfn  */
  YYSYMBOL_numint = 5,                     /* numint  */
  YYSYMBOL_numreal = 6,                    /* numreal  */
  YYSYMBOL_id = 7,                         /* id  */
  YYSYMBOL__int = 8,                       /* _int  */
  YYSYMBOL_real = 9,                       /* real  */
  YYSYMBOL_array = 10,                     /* array  */
  YYSYMBOL_var = 11,                       /* var  */
  YYSYMBOL__if = 12,                       /* _if  */
  YYSYMBOL__else = 13,                     /* _else  */
  YYSYMBOL_elif = 14,                      /* elif  */
  YYSYMBOL_fi = 15,                        /* fi  */
  YYSYMBOL_range = 16,                     /* range  */
  YYSYMBOL__while = 17,                    /* _while  */
  YYSYMBOL_loop = 18,                      /* loop  */
  YYSYMBOL_endloop = 19,                   /* endloop  */
  YYSYMBOL_pari = 20,                      /* pari  */
  YYSYMBOL_pard = 21,                      /* pard  */
  YYSYMBOL_cori = 22,                      /* cori  */
  YYSYMBOL_cord = 23,                      /* cord  */
  YYSYMBOL_coma = 24,                      /* coma  */
  YYSYMBOL_let = 25,                       /* let  */
  YYSYMBOL_asig = 26,                      /* asig  */
  YYSYMBOL_pyc = 27,                       /* pyc  */
  YYSYMBOL_print = 28,                     /* print  */
  YYSYMBOL__read = 29,                     /* _read  */
  YYSYMBOL_opas = 30,                      /* opas  */
  YYSYMBOL_opmd = 31,                      /* opmd  */
  YYSYMBOL_dosp = 32,                      /* dosp  */
  YYSYMBOL_blq = 33,                       /* blq  */
  YYSYMBOL_fblq = 34,                      /* fblq  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_S = 36,                         /* S  */
  YYSYMBOL_Fun = 37,                       /* Fun  */
  YYSYMBOL_SType = 38,                     /* SType  */
  YYSYMBOL_Type = 39,                      /* Type  */
  YYSYMBOL_Dim = 40,                       /* Dim  */
  YYSYMBOL_Cod = 41,                       /* Cod  */
  YYSYMBOL_I = 42,                         /* I  */
  YYSYMBOL_43_1 = 43,                      /* $@1  */
  YYSYMBOL_44_2 = 44,                      /* $@2  */
  YYSYMBOL_Range = 45,                     /* Range  */
  YYSYMBOL_Blq = 46,                       /* Blq  */
  YYSYMBOL_Ip = 47,                        /* Ip  */
  YYSYMBOL_IT = 48,                        /* IT  */
  YYSYMBOL_E = 49,                         /* E  */
  YYSYMBOL_T = 50,                         /* T  */
  YYSYMBOL_F = 51,                         /* F  */
  YYSYMBOL_Ref = 52,                       /* Ref  */
  YYSYMBOL_LExpr = 53                      /* LExpr  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   85

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  43
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  86

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    46,    46,    53,    60,    64,    70,    74,    80,    84,
      90,    94,   100,   104,   149,   168,   205,   210,   209,   230,
     229,   261,   267,   272,   279,   283,   289,   293,   297,   303,
     309,   315,   396,   400,   410,   492,   501,   506,   511,   515,
     524,   549,   555,   559
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
  "\"end of file\"", "error", "\"invalid token\"", "fn", "endfn",
  "numint", "numreal", "id", "_int", "real", "array", "var", "_if",
  "_else", "elif", "fi", "range", "_while", "loop", "endloop", "pari",
  "pard", "cori", "cord", "coma", "let", "asig", "pyc", "print", "_read",
  "opas", "opmd", "dosp", "blq", "fblq", "$accept", "S", "Fun", "SType",
  "Type", "Dim", "Cod", "I", "$@1", "$@2", "Range", "Blq", "Ip", "IT", "E",
  "T", "F", "Ref", "LExpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-24)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,     2,    11,   -24,    -1,   -24,    -4,    43,    14,    -2,
     -24,   -24,    16,    -2,    16,    43,    -3,   -24,   -24,     3,
     -24,   -24,    21,    -2,    24,    34,    18,   -24,   -24,    -2,
      46,    39,    36,   -24,    -7,   -24,    43,    29,   -24,    -2,
     -15,    18,    24,    27,    24,    34,    53,    -2,   -24,   -24,
     -24,   -24,    49,   -24,   -24,    36,     9,   -24,    18,    43,
      -2,   -24,   -24,   -24,   -24,    65,    36,    68,   -24,    -2,
      59,    34,    45,    43,    51,   -24,    36,   -24,    27,    73,
      60,    68,   -24,   -24,   -24,   -24
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     0,     0,     0,
      17,    19,     0,     0,     0,    24,     0,    11,    12,    30,
      36,    37,    40,     0,     0,     0,    33,    35,    39,     0,
       0,     0,    15,    16,     0,     3,     0,     0,    14,     0,
       0,    32,     0,     0,     0,     0,     0,     0,    25,    10,
       4,     5,     0,     6,    29,    43,     0,    38,    31,     0,
       0,    28,    21,    34,    18,     0,    13,     0,    41,     0,
       0,     0,    23,     0,     9,     7,    42,    26,     0,     0,
       0,     0,    27,    22,    20,     8
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,   -24,    28,   -24,     1,    66,   -23,   -24,   -24,
     -24,   -24,     6,   -24,   -13,   -17,    41,     0,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,    53,    54,    75,    16,    17,    29,    30,
      73,    18,    62,    38,    25,    26,    27,    28,    56
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    35,    43,    20,    21,    22,    57,    41,     1,     4,
      40,     5,    31,    49,    33,    42,    45,     7,    23,     6,
      36,    19,    64,    22,    36,    58,    55,    48,    24,    20,
      21,    22,    68,    69,    66,    37,    70,    50,    51,    52,
      59,    60,    61,    39,    23,     8,     9,    71,    78,    44,
      80,    10,    11,    46,     8,     9,    76,    50,    51,    12,
      10,    11,    13,    14,    42,    47,    42,    15,    12,    65,
      72,    13,    14,    74,    77,    81,    15,    79,    83,    84,
      67,    34,    85,     0,    82,    63
};

static const yytype_int8 yycheck[] =
{
      13,     4,    25,     5,     6,     7,    21,    24,     3,     7,
      23,     0,    12,    36,    14,    30,    29,    21,    20,    20,
      27,     7,    45,     7,    27,    42,    39,    34,    30,     5,
       6,     7,    23,    24,    47,    32,    59,     8,     9,    10,
      13,    14,    15,    22,    20,    11,    12,    60,    71,    31,
      73,    17,    18,     7,    11,    12,    69,     8,     9,    25,
      17,    18,    28,    29,    30,    26,    30,    33,    25,    16,
       5,    28,    29,     5,    15,    24,    33,    32,     5,    19,
      52,    15,    81,    -1,    78,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    36,    37,     7,     0,    20,    21,    11,    12,
      17,    18,    25,    28,    29,    33,    41,    42,    46,     7,
       5,     6,     7,    20,    30,    49,    50,    51,    52,    43,
      44,    52,    49,    52,    41,     4,    27,    32,    48,    22,
      49,    50,    30,    42,    31,    49,     7,    26,    34,    42,
       8,     9,    10,    38,    39,    49,    53,    21,    50,    13,
      14,    15,    47,    51,    42,    16,    49,    38,    23,    24,
      42,    49,     5,    45,     5,    40,    49,    15,    42,    32,
      42,    24,    47,     5,    19,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    38,    38,    39,    39,    40,    40,
      41,    41,    42,    42,    42,    42,    42,    43,    42,    44,
      42,    42,    45,    45,    46,    46,    47,    47,    47,    48,
      48,    49,    49,    49,    50,    50,    51,    51,    51,    51,
      52,    52,    53,    53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     6,     1,     1,     1,     3,     3,     1,
       3,     1,     1,     4,     3,     2,     2,     0,     4,     0,
       7,     4,     3,     1,     1,     3,     3,     4,     1,     2,
       0,     3,     2,     1,     3,     1,     1,     1,     3,     1,
       1,     4,     3,     1
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
  case 2: /* S: Fun  */
#line 47 "plp5.y"
            {
                yyval.cod = yyvsp[0].cod;
                cout << yyval.cod;
            }
#line 1195 "plp5.tab.c"
    break;

  case 3: /* Fun: fn id pari pard Cod endfn  */
#line 54 "plp5.y"
            {
                yyval.cod = yyvsp[-1].cod;
                yyval.cod += "halt\n";    // Fin de programa
            }
#line 1204 "plp5.tab.c"
    break;

  case 4: /* SType: _int  */
#line 61 "plp5.y"
            {
                yyval.tipo = ENTERO;
            }
#line 1212 "plp5.tab.c"
    break;

  case 5: /* SType: real  */
#line 65 "plp5.y"
            {
                yyval.tipo = REAL;
            }
#line 1220 "plp5.tab.c"
    break;

  case 6: /* Type: SType  */
#line 71 "plp5.y"
            {
                yyval.tipo = yyvsp[0].tipo;
            }
#line 1228 "plp5.tab.c"
    break;

  case 7: /* Type: array SType Dim  */
#line 75 "plp5.y"
            {

            }
#line 1236 "plp5.tab.c"
    break;

  case 8: /* Dim: numint coma Dim  */
#line 81 "plp5.y"
            {

            }
#line 1244 "plp5.tab.c"
    break;

  case 9: /* Dim: numint  */
#line 85 "plp5.y"
            {

            }
#line 1252 "plp5.tab.c"
    break;

  case 10: /* Cod: Cod pyc I  */
#line 91 "plp5.y"
            {
                yyval.cod = yyvsp[-2].cod + yyvsp[0].cod;
            }
#line 1260 "plp5.tab.c"
    break;

  case 11: /* Cod: I  */
#line 95 "plp5.y"
            {
                yyval.cod = yyvsp[0].cod;
            }
#line 1268 "plp5.tab.c"
    break;

  case 12: /* I: Blq  */
#line 101 "plp5.y"
            {
                yyval.cod = yyvsp[0].cod;
            }
#line 1276 "plp5.tab.c"
    break;

  case 13: /* I: let Ref asig E  */
#line 105 "plp5.y"
            {
                if (yyvsp[-2].tipo != yyvsp[0].tipo)
                {
                    if (yyvsp[-2].tipo == REAL && yyvsp[0].tipo == ENTERO)
                    {
                        yyval.cod = string(yyvsp[-2].lexema) + " mov " + to_string(yyvsp[0].dir) + " A\n";   // mov E.dir A
                        yyval.cod += "itor\n";                             // itor
                        yyval.cod += "mov A " + to_string(yyvsp[-2].dir) + "\n";  // mov A Ref.dir
                    }
                    else if (yyvsp[-2].tipo == ENTERO && yyvsp[0].tipo == REAL)
                    {
                        yyval.cod = "mov " + to_string(yyvsp[0].dir) + " A\n";   // mov E.dir A
                        yyval.cod += "rtoi\n";                             // rtoi
                        yyval.cod += "mov A " + to_string(yyvsp[-2].dir) + "\n";  // mov A Ref.dir
                    }
                }
                else
                {
                    if (yyvsp[0].isVar)
                    {
                        if (yyvsp[0].isOp)
                        {
                            yyval.cod = yyvsp[0].cod;                                                        // E.cod
                            yyval.cod += "mov A " + to_string(yyvsp[-2].dir) + "\n";                          // mov E.id id
                        }
                        else
                        {
                            yyval.cod = "mov " + to_string(yyvsp[0].dir) + " " + to_string(yyvsp[-2].dir) + "\n";   // mov E.id id
                        }
                    }
                    else
                    {
                        if (yyvsp[0].isOp)
                        {
                            yyval.cod = yyvsp[0].cod;                                                        // E.cod
                            yyval.cod = "mov #" + yyvsp[0].cod + " " + to_string(yyvsp[-2].dir) + "\n";             // mov E.num id
                        }
                        else
                        {
                            yyval.cod = "mov #" + yyvsp[0].cod + " " + to_string(yyvsp[-2].dir) + "\n";             // mov E.num id
                        }
                    }
                }
            }
#line 1325 "plp5.tab.c"
    break;

  case 14: /* I: var id IT  */
#line 150 "plp5.y"
            {
                Simbolo newSymb;
                newSymb.nombre = yyvsp[-1].lexema;
                newSymb.tipo = yyvsp[0].tipo;
                newSymb.dir = posMemoria;
                newSymb.tam = 1;

                for (int i = 0; i < numbloque; i++)
                {
                    newSymb.nombre += "_b" + to_string(i);
                }

                ts.newSymb(newSymb);

                yyval.cod = "mov #0 " + to_string(posMemoria) + "\n";     // mov #0 id

                posMemoria += 1;
            }
#line 1348 "plp5.tab.c"
    break;

  case 15: /* I: print E  */
#line 169 "plp5.y"
            {
                if (yyvsp[0].isVar)
                {
                    yyval.cod = "mov " + to_string(yyvsp[0].dir) + " A\n";   // mov E.id A
                    yyval.cod += "hola\n";
                }
                else
                {
                    if (yyvsp[0].isOp)
                    {
                        yyval.cod = yyvsp[0].cod;                        // E.cod
                    }
                    else
                    {
                        if (yyvsp[0].tipo == ENTERO)
                        {
                            yyval.cod = "mov #" + yyvsp[0].cod + " A\n";   // mov E.id A
                        }
                        else if (yyvsp[0].tipo == REAL)
                        {
                            yyval.cod = "mov $" + yyvsp[0].cod + " A\n";   // mov E.id A
                        }
                    }
                }

                if (yyvsp[0].tipo == ENTERO)
                {
                    yyval.cod += "wri A\n";                        // wri A
                }
                else if (yyvsp[0].tipo == REAL)
                {
                    yyval.cod += "wrr A\n";                        // wrr B
                }

                yyval.cod += "wrl\n";                              // wrl
            }
#line 1389 "plp5.tab.c"
    break;

  case 16: /* I: _read Ref  */
#line 206 "plp5.y"
            {

            }
#line 1397 "plp5.tab.c"
    break;

  case 17: /* $@1: %empty  */
#line 210 "plp5.y"
            {
                numbloque++;
            }
#line 1405 "plp5.tab.c"
    break;

  case 18: /* I: _while $@1 E I  */
#line 214 "plp5.y"
            {
                numbloque--;

                string e1 = "E" + to_string(numEtiqueta);
                numEtiqueta++;
                string e2 = "E" + to_string(numEtiqueta);
                numEtiqueta++;

                yyval.cod = e1 + ":\n";            // e1;
                yyval.cod += yyvsp[-1].cod;               // E.cod
                yyval.cod += "jz " + e2 + "\n";    // jz e2
                yyval.cod += yyvsp[0].cod;               // I.cod
                yyval.cod += "jmp " + e1 + "\n";   // jmp e1
                yyval.cod += e2 + ":\n";           // e2:
            }
#line 1425 "plp5.tab.c"
    break;

  case 19: /* $@2: %empty  */
#line 230 "plp5.y"
            {
                numbloque++;
            }
#line 1433 "plp5.tab.c"
    break;

  case 20: /* I: loop $@2 id range Range I endloop  */
#line 234 "plp5.y"
            {
                numbloque--;

                Simbolo* s = ts.searchSymb(yyvsp[-4].lexema);
                if (s == NULL)
                {
                    // Error
                }

                string e1 = "E" + to_string(numEtiqueta);
                numEtiqueta++;
                string e2 = "E" + to_string(numEtiqueta);
                numEtiqueta++;

                yyval.cod = string("mov #") + yyvsp[-2].r1 + " " + to_string(s->dir) + "\n";  // mov Range.r1 id.dir
                yyval.cod += e1 + ":\n";                                               // e1:
                yyval.cod += "mov " + to_string(s->dir) + " A\n";                      // mov id.dir A
                yyval.cod += "muli #-1\n";                                             // muli #-1
                yyval.cod += string("addi #") + yyvsp[-2].r2 + "\n";                          // addi Range.r2
                yyval.cod += "jz " + e2 + "\n";                                        // jz e2
                yyval.cod += yyvsp[-1].cod;                                                   // I
                yyval.cod += "mov " + to_string(s->dir) + " A\n";                      // mov id.dir A
                yyval.cod += "addi #1\n";                                              // addi #1
                yyval.cod += "mov A " + to_string(s->dir) + "\n";                      // mov A id.dir
                yyval.cod += "jmp " + e1 + "\n";                                       // jmp e1
                yyval.cod += e2 + ":\n";                                               // e2:
            }
#line 1465 "plp5.tab.c"
    break;

  case 21: /* I: _if E I Ip  */
#line 262 "plp5.y"
            {

            }
#line 1473 "plp5.tab.c"
    break;

  case 22: /* Range: numint dosp numint  */
#line 268 "plp5.y"
            {
                yyval.r1 = yyvsp[-2].lexema;
                yyval.r2 = yyvsp[0].lexema;
            }
#line 1482 "plp5.tab.c"
    break;

  case 23: /* Range: numint  */
#line 273 "plp5.y"
            {
                yyval.r1 = "0";
                yyval.r2 = yyvsp[0].lexema;
            }
#line 1491 "plp5.tab.c"
    break;

  case 24: /* Blq: blq  */
#line 280 "plp5.y"
            {
                yyval.cod = "";
            }
#line 1499 "plp5.tab.c"
    break;

  case 25: /* Blq: blq Cod fblq  */
#line 284 "plp5.y"
            {
                yyval.cod = yyvsp[-1].cod;
            }
#line 1507 "plp5.tab.c"
    break;

  case 26: /* Ip: _else I fi  */
#line 290 "plp5.y"
            {

            }
#line 1515 "plp5.tab.c"
    break;

  case 27: /* Ip: elif E I Ip  */
#line 294 "plp5.y"
            {

            }
#line 1523 "plp5.tab.c"
    break;

  case 28: /* Ip: fi  */
#line 298 "plp5.y"
            {

            }
#line 1531 "plp5.tab.c"
    break;

  case 29: /* IT: dosp Type  */
#line 304 "plp5.y"
            {
                // var id : tipo;
                yyval.tipo = yyvsp[0].tipo;
            }
#line 1540 "plp5.tab.c"
    break;

  case 30: /* IT: %empty  */
#line 309 "plp5.y"
            {
                // var id;  -> ENTERO implícito
                yyval.tipo = ENTERO;
            }
#line 1549 "plp5.tab.c"
    break;

  case 31: /* E: E opas T  */
#line 316 "plp5.y"
            {
                yyval.isOp = true;

                if (yyvsp[-2].tipo == ENTERO && yyvsp[0].tipo == ENTERO)
                {
                    yyval.tipo = ENTERO;
                }
                else if (yyvsp[-2].tipo == REAL && yyvsp[0].tipo == REAL)
                {
                    yyval.tipo = REAL;
                }
                else if (yyvsp[-2].tipo == ENTERO && yyvsp[0].tipo == REAL)
                {
                    yyval.tipo = REAL;
                }
                else if (yyvsp[-2].tipo == REAL && yyvsp[0].tipo == ENTERO)
                {
                    yyval.tipo = REAL;
                }

                if (yyvsp[-2].isVar)
                {
                    yyval.cod = "mov " + to_string(yyvsp[-2].dir) + " A\n";    // mov E.dir A
                }
                else
                {
                    yyval.cod = "mov #" + yyvsp[-2].cod + " A\n";              // mov E.cod A
                }

                if (strcmp(yyvsp[-1].lexema, "+") == 0)
                {
                    if (yyval.tipo == ENTERO)
                    {
                        if (yyvsp[0].isVar)
                        {
                            yyval.cod += "addi " + to_string(yyvsp[0].dir) + "\n";   // addi T.dir
                        }
                        else
                        {
                            yyval.cod += "addi #" + yyvsp[0].cod + "\n";             // addi T.cod
                        }
                    }
                    else
                    {
                       if (yyvsp[0].isVar)
                       {
                           yyval.cod += "addr " + to_string(yyvsp[0].dir) + "\n";   // addr T.dir
                       }
                       else
                       {
                           yyval.cod += "addr #" + yyvsp[0].cod + "\n";             // addr T.cod
                       }
                    }
                }
                else
                {
                    if (yyval.tipo == ENTERO)
                    {
                        if (yyvsp[0].isVar)
                        {
                            yyval.cod += "subi " + to_string(yyvsp[0].dir) + "\n";   // subi T.dir
                        }
                        else
                        {
                            yyval.cod += "subi #" + yyvsp[0].cod + "\n";             // subi T.dir
                        }
                    }
                    else
                    {
                        if (yyvsp[0].isVar)
                        {
                            yyval.cod += "subr " + to_string(yyvsp[0].dir) + "\n";   // subr T.dir
                        }
                        else
                        {
                            yyval.cod += "subr #" + yyvsp[0].cod + "\n";             // subr T.dir
                        }
                    }
                }
            }
#line 1634 "plp5.tab.c"
    break;

  case 32: /* E: opas T  */
#line 397 "plp5.y"
            {

            }
#line 1642 "plp5.tab.c"
    break;

  case 33: /* E: T  */
#line 401 "plp5.y"
            {
                yyval.isOp = yyvsp[0].isOp;
                yyval.tipo = yyvsp[0].tipo;
                yyval.dir = yyvsp[0].dir;
                yyval.isVar = yyvsp[0].isVar;
                yyval.cod = yyvsp[0].cod;
            }
#line 1654 "plp5.tab.c"
    break;

  case 34: /* T: T opmd F  */
#line 411 "plp5.y"
            {
                yyval.isOp = true;
                yyvsp[-2].isVar = false;

                if (yyvsp[-2].tipo == ENTERO && yyvsp[0].tipo == ENTERO)
                {
                    yyval.tipo = ENTERO;
                }
                else if (yyvsp[-2].tipo == REAL && yyvsp[0].tipo == REAL)
                {
                    yyval.tipo = REAL;
                }
                else if (yyvsp[-2].tipo == ENTERO && yyvsp[0].tipo == REAL)
                {
                    yyval.tipo = REAL;
                }
                else if (yyvsp[-2].tipo == REAL && yyvsp[0].tipo == ENTERO)
                {
                    yyval.tipo = REAL;
                }

                if (yyvsp[-2].isVar)
                {
                    yyval.cod = "mov " + to_string(yyvsp[-2].dir) + " A\n";    // mov E.dir A
                }
                else
                {
                    yyval.cod = "mov #" + yyvsp[-2].cod + " A\n";              // mov E.cod A
                }

                if (strcmp(yyvsp[-1].lexema, "*") == 0)
                {
                    if (yyval.tipo == ENTERO)
                    {
                        if (yyvsp[0].isVar)
                        {
                            yyval.cod += "muli " + to_string(yyvsp[0].dir) + "\n";   // muli T.dir
                        }
                        else
                        {
                            yyval.cod += "muli #" + yyvsp[0].cod + "\n";             // muli T.cod
                        }
                    }
                    else
                    {
                        if (yyvsp[0].isVar)
                        {
                            yyval.cod += "mulr " + to_string(yyvsp[0].dir) + "\n";   // mulr T.dir
                        }
                        else
                        {
                            yyval.cod += "mulr #" + yyvsp[0].cod + "\n";             // mulr T.cod
                        }
                    }
                }
                else
                {
                    if (yyval.tipo == ENTERO)
                    {
                        if (yyvsp[0].isVar)
                        {
                            yyval.cod += "subi " + to_string(yyvsp[0].dir) + "\n";   // divi T.dir
                        }
                        else
                        {
                            yyval.cod += "subi #" + yyvsp[0].cod + "\n";             // divi T.cod
                        }
                    }
                    else
                    {
                        if (yyvsp[0].isVar)
                        {
                            yyval.cod += "divr " + to_string(yyvsp[0].dir) + "\n";   // divr T.dir
                        }
                        else
                        {
                            yyval.cod += "divr #" + yyvsp[0].cod + "\n";             // divr T.cod
                        }
                    }
                }
            }
#line 1740 "plp5.tab.c"
    break;

  case 35: /* T: F  */
#line 493 "plp5.y"
            {
                yyval.tipo = yyvsp[0].tipo;
                yyval.dir = yyvsp[0].dir;
                yyval.isVar = yyvsp[0].isVar;
                yyval.cod = yyvsp[0].cod;
            }
#line 1751 "plp5.tab.c"
    break;

  case 36: /* F: numint  */
#line 502 "plp5.y"
            {
                yyval.tipo = ENTERO;
                yyval.cod = yyvsp[0].lexema;
            }
#line 1760 "plp5.tab.c"
    break;

  case 37: /* F: numreal  */
#line 507 "plp5.y"
            {
                yyval.tipo = REAL;
                yyval.cod = yyvsp[0].lexema;
            }
#line 1769 "plp5.tab.c"
    break;

  case 38: /* F: pari E pard  */
#line 512 "plp5.y"
            {
                yyval.cod = yyvsp[-1].cod;  // E.cod
            }
#line 1777 "plp5.tab.c"
    break;

  case 39: /* F: Ref  */
#line 516 "plp5.y"
            {
                yyval.tipo = yyvsp[0].tipo;
                yyval.dir = yyvsp[0].dir;
                yyval.isVar = yyvsp[0].isVar;
                yyval.cod = yyvsp[0].cod;
            }
#line 1788 "plp5.tab.c"
    break;

  case 40: /* Ref: id  */
#line 525 "plp5.y"
            {
                Simbolo* s = NULL;

                // Buscar desde el nivel actual hacia arriba
                for (int nivel = numbloque; nivel >= 0 && s == NULL; nivel--) {
                    string nombreConPrefijo = yyvsp[0].lexema;
                    for (int i = 0; i < nivel; i++) {
                        nombreConPrefijo += "_b" + to_string(i);
                    }
                    s = ts.searchSymb(nombreConPrefijo);
                }

                if (s != NULL)
                {
                    yyval.tipo = s->tipo;
                    yyval.dir = s->dir;
                    yyval.isVar = true;
                    yyval.cod = s->dir;
                }
                else
                {
                    errorSemantico(ERR_NODECL, yyvsp[0].nlin, yyvsp[0].ncol, yyvsp[0].lexema);
                }
            }
#line 1817 "plp5.tab.c"
    break;

  case 41: /* Ref: id cori LExpr cord  */
#line 550 "plp5.y"
            {

            }
#line 1825 "plp5.tab.c"
    break;

  case 42: /* LExpr: LExpr coma E  */
#line 556 "plp5.y"
            {

            }
#line 1833 "plp5.tab.c"
    break;

  case 43: /* LExpr: E  */
#line 560 "plp5.y"
            {

            }
#line 1841 "plp5.tab.c"
    break;


#line 1845 "plp5.tab.c"

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

#line 565 "plp5.y"


int main (int argc, char *argv[])
{
    FILE *fent;

        if (argc == 2)
        {
            fent = fopen(argv[1], "rt");
            if (fent)
            {
                yyin = fent;
                yyparse();
                fclose(fent);
            }
            else
            {
                fprintf(stderr, "No puedo abrir el fichero\n");
            }
        }
        else
        {
            fprintf(stderr, "Uso: plp5 <nombre de fichero>\n");
        }

        return 0;
}

void yyerror (char *s)
{
	extern int findefichero;
	if (findefichero)
	{
	   msgError(ERREOF,-1,-1,"");
	}
	msgError(ERRSINT, nlin, ncol-strlen(yytext), yytext);
}

void errorSemantico (int nerror, int fila, int columna, const char *s)
{
    fprintf(stderr,"Error semantico (%d,%d): ",fila,columna);
    switch (nerror) {
        case ERR_YADECL: fprintf(stderr,"variable '%s' ya declarada\n",s);
               // fila,columna de la variable
               break;
        case ERR_NODECL: fprintf(stderr,"variable '%s' no declarada\n",s);
               // fila,columna de la variable
               break;
        case ERR_NOCABE:fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s);
               // fila,columna de la variable
               break;

        case ERR_IFWHILE:fprintf(stderr,"la expresion del '%s' debe ser de tipo entero",s);
               // fila,columna del 'if' o 'while'
               break;
        case ERR_LOOP:fprintf(stderr,"la variable del '%s' debe ser de tipo entero",s);
               // fila,columna del 'loop'
               break;

        case ERR_DIM: fprintf(stderr,"la dimension debe ser mayor que 0\n");
               // fila,columna de la dimension (numint)
               break;
        case ERR_FALTAN: fprintf(stderr,"faltan indices\n");
               // fila,columna del id (si no hay ningún índice) o del último ']'
               break;
        case ERR_SOBRAN: fprintf(stderr,"sobran indices\n");
               // fila,columna del '[' si no es array, o de la ',' que sobra
               break;
        case ERR_INDICE_ENTERO: fprintf(stderr,"el indice de un array debe ser de tipo entero\n");
               // fila,columna del '[' si es el primero, o de la ',' inmediatamente anterior
               break;

        case ERR_ASIG: fprintf(stderr,"tipos incompatibles en la asignacion\n");
               // fila,columna del '='
               break;
        case ERR_MAXTEMP:fprintf(stderr,"no hay espacio para variables temporales\n");
               // fila,columna da igual
               break;
    }
    exit(-1);
}

void msgError (int nerror, int nlin, int ncol, const char *s)
{
     switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT: fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF: fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
         case ERRLEXEOF: fprintf(stderr,"Error lexico: fin de fichero inesperado\n");
            break;
     }

     exit(1);
}
