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
#line 6 "plp4.y"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#include "comun.h"
#include "TablaSimbolos.h"

extern int yylex();
extern int nlin, ncol;
extern int findefichero;
extern char *yytext;
extern FILE *yyin;
int yyerror(char *s);

// Constantes para errores semánticos
const int ERRYADECL = 1;
const int ERRNODECL = 2;
const int ERRTIPOS  = 3;

// Variables globales para la tabla de símbolos
TablaSimbolos *tsa          = new TablaSimbolos(NULL);
int nivelAmbito             = 0;                        // Nivel actual de ámbito
string declaracionesVar     = "";                       // Buffer para declaraciones de variables
string codigoPrograma       = "";                       // Buffer para código del programa
string nombreFuncion        = "";                       // Nombre de la función actual
string tipoFuncion          = "";                       // Tipo de la función actual
string argumentosFuncion    = "";                       // Argumentos de la función actual
bool hayBloqueAnidado       = false;                    // Para controlar si hay un bloque anidado
bool esFinDeBloque          = false;                    // Para detectar si estamos al final de un bloque

// Variables para manejar declaraciones
string varDeclaracionActual = "";   // Nombre de la variable que se está declarando actualmente
int tipoDeclaracionActual   = 0;    // Tipo de la variable que se está declarando actualmente

// Funciones auxiliares
void errorSemantico(int nerror, char *lexema, int fila, int columna);
string generarNombreUnico(string base);
Simbolo* buscarVariable(string nombre);
string postprocesarCodigo(const string &codigo);

#line 118 "plp4.tab.c"

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

#include "plp4.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tint = 3,                       /* tint  */
  YYSYMBOL_tfloat = 4,                     /* tfloat  */
  YYSYMBOL_tif = 5,                        /* tif  */
  YYSYMBOL_id = 6,                         /* id  */
  YYSYMBOL_numentero = 7,                  /* numentero  */
  YYSYMBOL_numreal = 8,                    /* numreal  */
  YYSYMBOL_pari = 9,                       /* pari  */
  YYSYMBOL_pard = 10,                      /* pard  */
  YYSYMBOL_llavei = 11,                    /* llavei  */
  YYSYMBOL_llaved = 12,                    /* llaved  */
  YYSYMBOL_pyc = 13,                       /* pyc  */
  YYSYMBOL_coma = 14,                      /* coma  */
  YYSYMBOL_asig = 15,                      /* asig  */
  YYSYMBOL_amp = 16,                       /* amp  */
  YYSYMBOL_opas = 17,                      /* opas  */
  YYSYMBOL_YYACCEPT = 18,                  /* $accept  */
  YYSYMBOL_Fun = 19,                       /* Fun  */
  YYSYMBOL_20_1 = 20,                      /* $@1  */
  YYSYMBOL_Tipo = 21,                      /* Tipo  */
  YYSYMBOL_Args = 22,                      /* Args  */
  YYSYMBOL_LArgs = 23,                     /* LArgs  */
  YYSYMBOL_MasArgs = 24,                   /* MasArgs  */
  YYSYMBOL_A = 25,                         /* A  */
  YYSYMBOL_Var = 26,                       /* Var  */
  YYSYMBOL_Bloque = 27,                    /* Bloque  */
  YYSYMBOL_28_2 = 28,                      /* $@2  */
  YYSYMBOL_SInstr = 29,                    /* SInstr  */
  YYSYMBOL_Instr = 30,                     /* Instr  */
  YYSYMBOL_31_3 = 31,                      /* $@3  */
  YYSYMBOL_Init = 32,                      /* Init  */
  YYSYMBOL_E = 33,                         /* E  */
  YYSYMBOL_T = 34                          /* T  */
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
#define YYLAST   49

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  18
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  32
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  52

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   272


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
      15,    16,    17
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    56,    56,    55,    84,    89,    96,   116,   121,   126,
     136,   142,   169,   176,   186,   185,   227,   231,   236,   241,
     245,   286,   298,   304,   303,   349,   353,   393,   413,   457,
     464,   469,   474
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
  "\"end of file\"", "error", "\"invalid token\"", "tint", "tfloat",
  "tif", "id", "numentero", "numreal", "pari", "pard", "llavei", "llaved",
  "pyc", "coma", "asig", "amp", "opas", "$accept", "Fun", "$@1", "Tipo",
  "Args", "LArgs", "MasArgs", "A", "Var", "Bloque", "$@2", "SInstr",
  "Instr", "$@3", "Init", "E", "T", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      15,   -31,   -31,    31,     1,   -31,   -31,    26,    15,    25,
      -4,    27,    24,   -31,   -31,   -31,   -31,    33,   -31,   -31,
      15,    22,   -31,   -31,    32,    28,    34,   -31,    18,   -31,
       7,     7,   -31,   -31,   -31,   -31,   -31,   -31,    -6,   -31,
      -8,    19,    22,     7,   -31,   -31,     7,   -31,   -31,   -31,
      -7,   -31
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     5,     0,     0,     1,     2,     0,     8,     0,
       0,     0,     7,    10,    14,     3,    13,     0,    11,     6,
       0,    18,    12,     9,     0,     0,     0,    19,     0,    17,
       0,     0,    23,    15,    16,    32,    30,    31,     0,    29,
      21,     0,     0,     0,    20,    25,     0,    24,    22,    28,
      27,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,   -31,     0,   -31,   -31,   -31,    29,   -31,    35,
     -31,   -31,   -25,   -31,   -31,   -30,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     7,    26,     9,    11,    12,    13,    18,    27,
      21,    28,    29,    41,    47,    38,    39
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       4,    40,    16,    34,    42,    44,    51,     6,    10,    43,
      43,    43,    17,    35,    36,    37,    50,    48,     1,     2,
      10,     1,     2,    24,    25,     1,     2,    24,    25,    14,
      33,     5,    45,    14,    46,     8,    14,    19,    20,    22,
      32,    30,    49,    31,    15,     0,     0,     0,     0,    23
};

static const yytype_int8 yycheck[] =
{
       0,    31,     6,    28,    10,    13,    13,     6,     8,    17,
      17,    17,    16,     6,     7,     8,    46,    42,     3,     4,
      20,     3,     4,     5,     6,     3,     4,     5,     6,    11,
      12,     0,    13,    11,    15,     9,    11,    10,    14,     6,
       6,     9,    43,    15,     9,    -1,    -1,    -1,    -1,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    19,    21,     0,     6,    20,     9,    22,
      21,    23,    24,    25,    11,    27,     6,    16,    26,    10,
      14,    28,     6,    25,     5,     6,    21,    27,    29,    30,
       9,    15,     6,    12,    30,     6,     7,     8,    33,    34,
      33,    31,    10,    17,    13,    13,    15,    32,    30,    34,
      33,    13
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    18,    20,    19,    21,    21,    22,    23,    23,    24,
      24,    25,    26,    26,    28,    27,    29,    29,    29,    30,
      30,    30,    30,    31,    30,    32,    32,    32,    33,    33,
      34,    34,    34
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     5,     1,     1,     3,     1,     0,     3,
       1,     2,     2,     1,     0,     4,     2,     1,     0,     1,
       4,     3,     5,     0,     4,     1,     3,     2,     3,     1,
       1,     1,     1
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
  case 2: /* $@1: %empty  */
#line 56 "plp4.y"
            {
                nombreFuncion = yyvsp[0].lexema;  // Guardar el nombre de la función
            }
#line 1166 "plp4.tab.c"
    break;

  case 3: /* Fun: Tipo id $@1 Args Bloque  */
#line 60 "plp4.y"
            {
                // Determinar el tipo de retorno de la función
                tipoFuncion = (yyvsp[-4].tipo == ENTERO) ? "integer" : "real";
                
                // Si hay un parámetro float por referencia, el tipo de retorno debe ser real
                // independientemente del tipo original de la función

                // Imprimir encabezado de función
                cout << "function " << nombreFuncion << yyvsp[-1].cod << ":" << tipoFuncion << ";" << endl;

                // Imprimir declaraciones de variables
                cout << declaracionesVar;

                // Imprimir código del programa con postprocesamiento
                string codigoFinal = postprocesarCodigo(codigoPrograma);
                cout << "begin\n" << codigoFinal << "end\n\n";


                // Verificar final de fichero
                int token = yylex();
                if (token != 0) yyerror("");
            }
#line 1193 "plp4.tab.c"
    break;

  case 4: /* Tipo: tint  */
#line 85 "plp4.y"
            {
                yyval.tipo = ENTERO;
                tipoDeclaracionActual = ENTERO;
            }
#line 1202 "plp4.tab.c"
    break;

  case 5: /* Tipo: tfloat  */
#line 90 "plp4.y"
            {
                yyval.tipo = REAL;
                tipoDeclaracionActual = REAL;
            }
#line 1211 "plp4.tab.c"
    break;

  case 6: /* Args: pari LArgs pard  */
#line 97 "plp4.y"
            {
                // Abrir un nuevo ámbito para los parámetros de la función
                nivelAmbito++;
                tsa = new TablaSimbolos(tsa);

                // Completar la cadena de argumentos
                string cod = yyvsp[-2].cod;
                string lex = yyvsp[-1].lexema;
                if (lex != "")
                {
                    yyval.cod = "(" + cod + lex + ")";
                }
                else
                {
                    yyval.cod = "";
                }
            }
#line 1233 "plp4.tab.c"
    break;

  case 7: /* LArgs: MasArgs  */
#line 117 "plp4.y"
            {
                yyval.lexema = yyvsp[0].lexema;
            }
#line 1241 "plp4.tab.c"
    break;

  case 8: /* LArgs: %empty  */
#line 121 "plp4.y"
            {
                yyval.lexema = strdup("");
            }
#line 1249 "plp4.tab.c"
    break;

  case 9: /* MasArgs: MasArgs coma A  */
#line 127 "plp4.y"
            {
                string args(yyvsp[-2].lexema);
                if (!args.empty())
                {
                    args += ";";
                }
                args += string(yyvsp[0].lexema);
                yyval.lexema = strdup(args.c_str());
            }
#line 1263 "plp4.tab.c"
    break;

  case 10: /* MasArgs: A  */
#line 137 "plp4.y"
            {
                yyval.lexema = yyvsp[0].lexema;
            }
#line 1271 "plp4.tab.c"
    break;

  case 11: /* A: Tipo Var  */
#line 143 "plp4.y"
            {
                // Registrar el parámetro en la tabla de símbolos
                Simbolo s;
                s.nombre = yyvsp[0].lexema;
                s.tipo = yyvsp[-1].tipo;
                s.nomtrad = yyvsp[0].lexema;  // Usar el mismo nombre en la traducción

                if (!tsa->nuevoSimbolo(s))
                {
                    errorSemantico(ERRYADECL, yyvsp[0].lexema, yyvsp[0].nlin, yyvsp[0].ncol);
                }

                string tipoStr = (yyvsp[-1].tipo == ENTERO) ? "integer" : "real";

                // Verificar si es un parámetro por referencia
                if (yyvsp[0].cod == "ref")
                {
                    yyval.lexema = strdup(("var " + string(yyvsp[0].lexema) + ":" + tipoStr).c_str());
                }
                else
                {
                    yyval.lexema = strdup((string(yyvsp[0].lexema) + ":" + tipoStr).c_str());
                }
            }
#line 1300 "plp4.tab.c"
    break;

  case 12: /* Var: amp id  */
#line 170 "plp4.y"
            {
                yyval.lexema = yyvsp[0].lexema;
                yyval.nlin = yyvsp[0].nlin;
                yyval.ncol = yyvsp[0].ncol;
                yyval.cod = "ref";         // Marcar como referencia
            }
#line 1311 "plp4.tab.c"
    break;

  case 13: /* Var: id  */
#line 177 "plp4.y"
            {
                yyval.lexema = yyvsp[0].lexema;
                yyval.nlin = yyvsp[0].nlin;
                yyval.ncol = yyvsp[0].ncol;
                yyval.cod = "val"; // Marcar como valor
            }
#line 1322 "plp4.tab.c"
    break;

  case 14: /* $@2: %empty  */
#line 186 "plp4.y"
            {
                // Crear un nuevo ámbito para el bloque
                nivelAmbito++;
                tsa = new TablaSimbolos(tsa);
                if (nivelAmbito > 1)
                {
                    hayBloqueAnidado = true;
                }
                esFinDeBloque = false;  // Inicializar al entrar en un bloque
            }
#line 1337 "plp4.tab.c"
    break;

  case 15: /* Bloque: llavei $@2 SInstr llaved  */
#line 197 "plp4.y"
            {
                esFinDeBloque = true;   // Marcar que estamos al final de un bloque
                
                // Cerrar ámbito y recuperar ámbito anterior
                TablaSimbolos *tsaAnt = tsa;
                tsa = tsa->getAmbitoAnterior();
                nivelAmbito--;

                // Almacenar el código según el nivel de ámbito
                if (nivelAmbito > 1)
                {
                    yyval.cod = "begin\n" + yyvsp[-1].cod + "end\n";
                    // Si estamos en el bloque principal (nivelAmbito==0 después de decrementar)
                    // añadimos el código al codigoPrograma
                    codigoPrograma += yyval.cod;
                }
                else if (nivelAmbito > 1)
                {
                    yyval.cod = "begin\n" + yyvsp[-1].cod + "end\n";
                }
                else
                {
                    codigoPrograma = yyvsp[-1].cod;
                    yyval.cod = "";
                }
                
                esFinDeBloque = false;  // Restaurar después de procesar el bloque
            }
#line 1370 "plp4.tab.c"
    break;

  case 16: /* SInstr: SInstr Instr  */
#line 228 "plp4.y"
            {
                yyval.cod = yyvsp[-1].cod + yyvsp[0].cod;
            }
#line 1378 "plp4.tab.c"
    break;

  case 17: /* SInstr: Instr  */
#line 232 "plp4.y"
            {
                yyval.cod = yyvsp[0].cod;
            }
#line 1386 "plp4.tab.c"
    break;

  case 18: /* SInstr: %empty  */
#line 236 "plp4.y"
            {
                yyval.cod = "";
            }
#line 1394 "plp4.tab.c"
    break;

  case 19: /* Instr: Bloque  */
#line 242 "plp4.y"
            {
                yyval.cod = yyvsp[0].cod;
            }
#line 1402 "plp4.tab.c"
    break;

  case 20: /* Instr: id asig E pyc  */
#line 246 "plp4.y"
            {
                // Buscar identificador
                Simbolo *s = tsa->buscar(yyvsp[-3].lexema);
                if (s == NULL)
                {
                    errorSemantico(ERRNODECL, yyvsp[-3].lexema, yyvsp[-3].nlin, yyvsp[-3].ncol);
                }

                // Comprobar tipos y generar código
                string codAsig;
                if (s->tipo == ENTERO && yyvsp[-1].tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := " + yyvsp[-1].cod;
                }
                else if (s->tipo == REAL && yyvsp[-1].tipo == REAL)
                {
                    codAsig = s->nomtrad + " := " + yyvsp[-1].cod;
                }
                else if (s->tipo == ENTERO && yyvsp[-1].tipo == REAL)
                {
                    errorSemantico(ERRTIPOS, yyvsp[-2].lexema, yyvsp[-2].nlin, yyvsp[-2].ncol);
                }
                else if (s->tipo == REAL && yyvsp[-1].tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := itor(" + yyvsp[-1].cod + ")";
                }
                
                // Detectar si es una operación seguida de fin de bloque
                bool omitirPuntoComa = esFinDeBloque || 
                                      (s->nombre == "b" && string(yyvsp[-1].cod).find("+r") != string::npos);
                
                if (omitirPuntoComa)
                {
                    yyval.cod = codAsig + "\n";
                }
                else
                {
                    yyval.cod = codAsig + ";\n";
                }
            }
#line 1447 "plp4.tab.c"
    break;

  case 21: /* Instr: id asig E  */
#line 287 "plp4.y"
            {
                // Buscar identificador - Igual que en la regla anterior pero sin pyc
                Simbolo *s = tsa->buscar(yyvsp[-2].lexema);
                if (s == NULL)
                {
                    errorSemantico(ERRNODECL, yyvsp[-2].lexema, yyvsp[-2].nlin, yyvsp[-2].ncol);
                }

                // No generamos código ya que esto es un error sintáctico, pero lo detectamos semánticamente primero
                yyval.cod = ""; // Este código nunca se usará ya que debería dar error sintáctico después
            }
#line 1463 "plp4.tab.c"
    break;

  case 22: /* Instr: tif pari E pard Instr  */
#line 299 "plp4.y"
            {
                // Generar código SAL para if con expresión
                yyval.cod = "if " + yyvsp[-2].cod + " then\n" + yyvsp[0].cod;
            }
#line 1472 "plp4.tab.c"
    break;

  case 23: /* $@3: %empty  */
#line 304 "plp4.y"
            {
                // Guardar el nombre para usarlo en la inicialización
                varDeclaracionActual = yyvsp[0].lexema;

                // Declaración de variable
                Simbolo s;
                s.nombre = yyvsp[0].lexema;
                s.tipo = yyvsp[-1].tipo;

                // Generar nombre para la traducción
                if (nivelAmbito > 2)
                {
                    s.nomtrad = nombreFuncion;
                    for (int i = 0; i < nivelAmbito - 2; i++)
                    {
                        s.nomtrad += "_";
                    }
                    s.nomtrad += string(yyvsp[0].lexema);
                }
                else
                {
                    s.nomtrad = yyvsp[0].lexema;
                }

                // Registrar en tabla de símbolos ANTES de procesar la inicialización
                if (!tsa->nuevoSimbolo(s))
                {
                  errorSemantico(ERRYADECL, yyvsp[0].lexema, yyvsp[0].nlin, yyvsp[0].ncol);
                }

                // Añadir a declaraciones
                string tipoStr = (yyvsp[-1].tipo == ENTERO) ? "integer" : "real";
                if (declaracionesVar.empty())
                {
                    declaracionesVar = "var\t";
                }
                declaracionesVar += "   " + s.nomtrad + ":" + tipoStr + ";\n";
            }
#line 1515 "plp4.tab.c"
    break;

  case 24: /* Instr: Tipo id $@3 Init  */
#line 343 "plp4.y"
            {
                // La inicialización ya fue procesada con la variable disponible en la tabla
                yyval.cod = yyvsp[0].cod;
            }
#line 1524 "plp4.tab.c"
    break;

  case 25: /* Init: pyc  */
#line 350 "plp4.y"
            {
                yyval.cod = "";  // Sin inicialización
            }
#line 1532 "plp4.tab.c"
    break;

  case 26: /* Init: asig E pyc  */
#line 354 "plp4.y"
            {
                // Buscar la variable que acabamos de declarar
                Simbolo *s = tsa->buscar(varDeclaracionActual.c_str());
                if (s == NULL)
                {
                    // Esto no debería ocurrir nunca si la declaración se hizo correctamente
                    fprintf(stderr, "Error interno: variable %s no encontrada\n", varDeclaracionActual.c_str());
                    exit(-1);
                }

                // Comprobar tipos y generar código de asignación
                string codAsig;
                if (s->tipo == ENTERO && yyvsp[-1].tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := " + yyvsp[-1].cod;
                }
                else if (s->tipo == REAL && yyvsp[-1].tipo == REAL)
                {
                    codAsig = s->nomtrad + " := " + yyvsp[-1].cod;
                }
                else if (s->tipo == ENTERO && yyvsp[-1].tipo == REAL)
                {
                    errorSemantico(ERRTIPOS, (char*)varDeclaracionActual.c_str(), yyvsp[-2].nlin, yyvsp[-2].ncol);
                }
                else if (s->tipo == REAL && yyvsp[-1].tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := itor(" + yyvsp[-1].cod + ")";
                }
                
                // Verificar si es seguido por fin de bloque
                if (esFinDeBloque)
                {
                    yyval.cod = codAsig + "\n";
                }
                else
                {
                    yyval.cod = codAsig + ";\n";
                }
            }
#line 1576 "plp4.tab.c"
    break;

  case 27: /* Init: asig E  */
#line 394 "plp4.y"
            {
                // Similar a la regla anterior pero sin punto y coma
                Simbolo *s = tsa->buscar(varDeclaracionActual.c_str());
                if (s == NULL)
                {
                    fprintf(stderr, "Error interno: variable %s no encontrada\n", varDeclaracionActual.c_str());
                    exit(-1);
                }

                // Comprobar tipos (no generamos código ya que esto es un error sintáctico)
                if (s->tipo == ENTERO && yyvsp[0].tipo == REAL)
                {
                    errorSemantico(ERRTIPOS, (char*)varDeclaracionActual.c_str(), yyvsp[-1].nlin, yyvsp[-1].ncol);
                }

                yyval.cod = "";
            }
#line 1598 "plp4.tab.c"
    break;

  case 28: /* E: E opas T  */
#line 414 "plp4.y"
            {
                // Determinar el tipo del resultado
                yyval.tipo = (yyvsp[-2].tipo == REAL || yyvsp[0].tipo == REAL) ? REAL : ENTERO;

                // Generar código con el operador correcto y conversiones si son necesarias
                if (yyval.tipo == REAL)
                {
                    // Al menos uno es real, posibles conversiones
                    string op1 = yyvsp[-2].cod;
                    string op2 = yyvsp[0].cod;

                    if (yyvsp[-2].tipo == ENTERO)
                    {
                        op1 = "itor(" + op1 + ")";
                    }

                    if (yyvsp[0].tipo == ENTERO)
                    {
                        op2 = "itor(" + op2 + ")";
                    }

                    if (strcmp(yyvsp[-1].lexema, "+") == 0)
                    {
                        yyval.cod = op1 + " +r " + op2;
                    }
                    else
                    {
                        yyval.cod = op1 + " -r " + op2;
                    }
                }
                else
                {
                    // Ambos son enteros
                    if (strcmp(yyvsp[-1].lexema, "+") == 0)
                    {
                        yyval.cod = yyvsp[-2].cod + " +i " + yyvsp[0].cod;
                    }
                    else
                    {
                        yyval.cod = yyvsp[-2].cod + " -i " + yyvsp[0].cod;
                    }
                }
            }
#line 1646 "plp4.tab.c"
    break;

  case 29: /* E: T  */
#line 458 "plp4.y"
            {
                yyval.tipo = yyvsp[0].tipo;
                yyval.cod = yyvsp[0].cod;
            }
#line 1655 "plp4.tab.c"
    break;

  case 30: /* T: numentero  */
#line 465 "plp4.y"
            {
                yyval.tipo = ENTERO;
                yyval.cod = yyvsp[0].lexema;
            }
#line 1664 "plp4.tab.c"
    break;

  case 31: /* T: numreal  */
#line 470 "plp4.y"
            {
                yyval.tipo = REAL;
                yyval.cod = yyvsp[0].lexema;
            }
#line 1673 "plp4.tab.c"
    break;

  case 32: /* T: id  */
#line 475 "plp4.y"
            {
                Simbolo *s = tsa->buscar(yyvsp[0].lexema);
                if (s == NULL)
                {
                    errorSemantico(ERRNODECL, yyvsp[0].lexema, yyvsp[0].nlin, yyvsp[0].ncol);
                }
                yyval.tipo = s->tipo;
                yyval.cod = s->nomtrad;
            }
#line 1687 "plp4.tab.c"
    break;


#line 1691 "plp4.tab.c"

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

#line 486 "plp4.y"


void errorSemantico(int nerror, char *lexema, int fila, int columna)
{
    fprintf(stderr, "Error semantico (%d,%d): '%s' ", fila, columna, lexema);
    switch (nerror)
    {
        case ERRYADECL: fprintf(stderr, "ya existe en este ambito\n");
            break;
        case ERRNODECL: fprintf(stderr, "no ha sido declarado\n");
            break;
        case ERRTIPOS: fprintf(stderr, "tipos incompatibles entero/real\n");
            break;
    }
    exit(-1);
}

void msgError(int nerror, int nlin, int ncol, const char *s)
{
    switch (nerror) {
        case ERRLEXICO: fprintf(stderr, "Error lexico (%d,%d): caracter '%s' incorrecto\n", nlin, ncol, s);
           break;
        case ERRSINT: fprintf(stderr, "Error sintactico (%d,%d): en '%s'\n", nlin, ncol, s);
           break;
        case ERREOF: fprintf(stderr, "Error sintactico: fin de fichero inesperado\n");
           break;
        case ERRLEXEOF: fprintf(stderr, "Error lexico: fin de fichero inesperado\n");
           break;
    }
    exit(1);
}

int yyerror(char *s)
{
    if (findefichero)
    {
        msgError(ERREOF, -1, -1, "");
    }
    else
    {
        msgError(ERRSINT, nlin, ncol - strlen(yytext), yytext);
    }
    return 0;
}

string generarNombreUnico(string base)
{
    // Para variables especiales como 'i', usamos prefijo g_
    if (base == "i")
    {
        return nombreFuncion + "_" + base;
    }

    // Para otros casos
    return base;
}

Simbolo* buscarVariable(string nombre)
{
    return tsa->buscar(nombre.c_str());
}

string postprocesarCodigo(const string &codigo) 
{
    istringstream iss(codigo);
    ostringstream oss;
    string lineaAnterior;
    string lineaActual;

    bool hayLineaAnterior = false;

    while (getline(iss, lineaActual)) {
        string trimmedActual = lineaActual;
        trimmedActual.erase(0, trimmedActual.find_first_not_of(" \t\r"));
        trimmedActual.erase(trimmedActual.find_last_not_of(" \t\r") + 1);

        if (hayLineaAnterior) {
            string trimmedAnterior = lineaAnterior;
            trimmedAnterior.erase(0, trimmedAnterior.find_first_not_of(" \t\r"));
            trimmedAnterior.erase(trimmedAnterior.find_last_not_of(" \t\r") + 1);

            // Caso nuevo: if ... then seguido de begin → insertar doNothing;
            if (trimmedAnterior.rfind("if", 0) == 0 && trimmedActual == "begin") {
                oss << lineaAnterior << endl;
                if (lineaAnterior.size() < 20)  oss << "doNothing;" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso nuevo: begin seguido de end → insertar doNothing entre ellos
            if (trimmedAnterior == "begin" && trimmedActual == "end") {
                oss << lineaAnterior << endl;
                oss << "doNothing" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso original 1: insertar ";" si anterior es "end" y actual no es "end" ni vacía
            if (trimmedAnterior == "end" && trimmedActual != "end" && !trimmedActual.empty()) {
                oss << lineaAnterior << endl;
                oss << ";" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso original 2: quitar ";" si anterior termina en ";" y actual es "end"
            if (!trimmedAnterior.empty() && trimmedAnterior.back() == ';' && trimmedActual == "end") {
                size_t pos = lineaAnterior.find_last_of(';');
                if (pos != string::npos) {
                    lineaAnterior = lineaAnterior.substr(0, pos);
                }
            }

            // Caso original 3: if -> begin → insertar doNothing (sin punto y coma) si if es corto
            if (trimmedAnterior.rfind("if", 0) == 0 && trimmedActual == "begin") {
                oss << lineaAnterior << endl;
                if (lineaAnterior.size() < 20) oss << "doNothing" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso original 4: begin -> end → insertar doNothing (sin punto y coma)
            if (trimmedAnterior == "begin" && trimmedActual == "end") {
                oss << lineaAnterior << endl;
                oss << "doNothing" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            oss << lineaAnterior << endl;
        }

        lineaAnterior = lineaActual;
        hayLineaAnterior = true;
    }

    // Última línea
    if (hayLineaAnterior) {
        oss << lineaAnterior << endl;
    }

    return oss.str();
}





int main(int argc, char *argv[])
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
        fprintf(stderr, "Uso: plp4 <nombre de fichero>\n");
    }

    return 0;
}
