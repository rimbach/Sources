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

/* Substitute the type names.  */
/* Substitute the variable and function names.  */
#define yyparse         jlparse
#define yyerror         jlerror
#define yydebug         jldebug
#define yynerrs         jlnerrs


/* Copy the first part of user declarations.  */
#line 7 "grammartranslator.y" /* yacc.c:339  */


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "kernel/mod2.h"
// #include "Singular/grammar.h"
#include "Singular/grammartranslator.h"

#include "misc/mylimits.h"
#include "omalloc/omalloc.h"
#include "Singular/tok.h"
#include "misc/options.h"
#include "Singular/stype.h"
#include "Singular/fehelp.h"
#include "Singular/ipid.h"
#include "misc/intvec.h"
#include "kernel/oswrapper/feread.h"
#include "Singular/fevoices.h"
#include "polys/matpol.h"
#include "polys/monomials/ring.h"
#include "kernel/GBEngine/kstd1.h"
#include "Singular/subexpr.h"
#include "Singular/ipshell.h"
#include "Singular/ipconv.h"
#include "Singular/sdb.h"
#include "kernel/ideals.h"
#include "coeffs/numbers.h"
#include "kernel/polys.h"
#include "kernel/combinatorics/stairc.h"
#include "kernel/oswrapper/timer.h"
#include "Singular/cntrlc.h"
#include "polys/monomials/maps.h"
#include "kernel/GBEngine/syz.h"
#include "Singular/lists.h"
#include "Singular/libparse.h"
#include "coeffs/bigintmat.h"

#define JL_TRANSLATOR_GRAMMAR
// #define JL_TRANSLATOR_GRAMMAR_DEBUG

#include "Singular/translator/mstring.h"
#include "Singular/translator/toJulia.h"
#include "Singular/translator/msymtable.h"


#if 0
void debug_list(leftv v)
{
  idhdl r=basePackHdl;
  idhdl h;
  BOOLEAN found=FALSE;
  const char *nn=v->name;
  h=IDROOT->get(nn,myynest);
  if (h!=NULL)
  {
     Print("Curr::%s, (%s)\n",nn,Tok2Cmdname((int)IDTYP(h)));
     found=TRUE;
  }
  else         Print("`%s` not found in IDROOT\n",nn);
  while (r!=NULL)
  {
    if ((IDTYP(r)==PACKAGE_CMD)
    || (IDTYP(r)==RING_CMD))
    {
      h=IDPACKAGE(r)->idroot->get(nn,myynest);
      if (h!=NULL)
      {
        Print("%s::%s, (%s)\n",r->id,nn,Tok2Cmdname((int)IDTYP(h)));
        found=TRUE;
      }
      else         Print("%s::%s not found\n",r->id,nn);
    }
    if (r==basePackHdl) r=IDPACKAGE(r)->idroot;
    r=r->next;
   if (r==basePackHdl) break;
  }
  if (!found)
  {
    listall(TRUE);
  }
}
#endif

/* From the bison docu:

     By defining the macro `YYMAXDEPTH', you can control how deep the
parser stack can become before a stack overflow occurs.  Define the
macro with a value that is an integer.  This value is the maximum number
of tokens that can be shifted (and not reduced) before overflow.  It
must be a constant expression whose value is known at compile time.

   The stack space allowed is not necessarily allocated.  If you
specify a large value for `YYMAXDEPTH', the parser actually allocates a
small stack at first, and then makes it bigger by stages as needed.
This increasing allocation happens automatically and silently.
Therefore, you do not need to make `YYMAXDEPTH' painfully small merely
to save space for ordinary inputs that do not need much stack.

   The default value of `YYMAXDEPTH', if you do not define it, is 10000.
*/
#define YYMAXDEPTH MAX_INT_VAL

extern int   yylineno;
extern FILE* yyin;

/*
const  char *  currid;
BOOLEAN    yyInRingConstruction=FALSE;
BOOLEAN    expected_parms;
int        cmdtok;
int        inerror = 0;
 */
 
extern const  char *  currid;
extern BOOLEAN    yyInRingConstruction;
extern BOOLEAN    expected_parms;
extern int        cmdtok;
extern int        inerror;


#ifdef JL_TRANSLATOR_GRAMMAR
int translator_NbRuleTraversed = 0;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
const char * uninitialized = "(NULL)";
#else
const char * uninitialized = " ";
#endif
char * setUninitialized() {
    char * dest = (char *) malloc (sizeof(uninitialized));
    memcpy( dest, uninitialized, sizeof(uninitialized) );
    return dest;
}
void printfrule( int nbtraversed, const char * target, const char * symbs){
    printf("%5d, (RULE %-20s : %-55s) ", nbtraversed, target, symbs);
}
void printfms  (mstring ms) { 
    char * disp;
    if (ms) disp = mstring_to_str( ms );
    else disp = setUninitialized();
    printf("ms: %s", disp);
    free(disp);
}
void printflistofms(leftv list) {
    printf("list of %d ms: ", list->listLength());
    leftv voyager = list;
    while (voyager!=NULL) {
        if (voyager->ms) printf("%s", mstring_to_str( voyager->ms ));
        if ( (voyager->next != NULL)&&(voyager->next->ms) ) printf(", ");
        voyager = voyager->next;
    }
}
void printfrule_ms( int nbtraversed, const char * target, const char * symbs, mstring ms){
    printfrule(nbtraversed, target, symbs);
    printfms(ms);
    printf("\n");
}
void printfrule_listofms( int nbtraversed, const char * target, const char * symbs, leftv list){
    printfrule(nbtraversed, target, symbs);
    printflistofms(list);
    printf("\n");
}

int is_symbol_in_table_of_symbol(const char * name) {
    Voice * voyager = currentVoice;
    int res = 0;                  
    while ((voyager !=NULL)&&(res==0)) {
        if (voyager->table_of_symbols!=NULL)
            res = msymtable_is_name_in_msymtable(voyager->table_of_symbols, name);
        voyager = voyager->prev;
    }
    return res;
}

void add_symbol_in_table_of_symbol_string(const char * name) {
    if (currentVoice->table_of_symbols==NULL) {
        currentVoice->table_of_symbols = msymtable_init();
    }
    currentVoice->table_of_symbols = msymtable_add_name(currentVoice->table_of_symbols, name);
}

void add_symbol_in_table_of_symbol_mstring(mstring ms) {
    if (currentVoice->table_of_symbols==NULL) {
        currentVoice->table_of_symbols = msymtable_init();
    }
    if (ms) {
        char * disp;
        disp = mstring_to_str( ms );
        currentVoice->table_of_symbols = msymtable_add_name(currentVoice->table_of_symbols, disp);
        free(disp);
    }
}
#endif //JL_TRANSLATOR_GRAMMAR

#define TESTSETINT(a,i)                                \
   if ((a).Typ() != INT_CMD)                           \
   {                                                   \
     WerrorS("no int expression");                     \
     YYERROR;                                          \
   }                                                   \
   (i) = (int)((long)(a).Data());(a).CleanUp()

#define MYYERROR(a) { WerrorS(a); YYERROR; }

void yyerror(const char * fmt)
{

  BOOLEAN old_errorreported=errorreported;
  errorreported = TRUE;
  if (currid!=NULL)
  {
    killid(currid,&IDROOT);
    currid = NULL;
  }
  if(inerror==0)
  {
    {
      if ((strlen(fmt)>1)
      && (strncmp(fmt,"parse",5)!=0)
      && (strncmp(fmt,"syntax",6)!=0))
        WerrorS(fmt);
      Werror( "error occurred in or before %s line %d: `%s`"
             ,VoiceName(), yylineno, my_yylinebuf);
    }
    if (cmdtok!=0)
    {
      const char *s=Tok2Cmdname(cmdtok);
      if (expected_parms)
      {
        Werror("expected %s-expression. type \'help %s;\'",s,s);
      }
      else
      {
        Werror("wrong type declaration. type \'help %s;\'",s);
      }
    }
    if (!old_errorreported && (lastreserved!=NULL))
    {
      Werror("last reserved name was `%s`",lastreserved);
    }
    inerror=1;
  }
  if ((currentVoice!=NULL)
  && (currentVoice->prev!=NULL)
  && (myynest>0)
#ifdef HAVE_SDB
  && ((sdb_flags &1)==0)
#endif
  )
  {
    Werror("leaving %s",VoiceName());
  }
}


#line 332 "grammartranslator.cc" /* yacc.c:339  */

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
   by #include "grammartranslator.hh".  */
#ifndef YY_JL_GRAMMARTRANSLATOR_HH_INCLUDED
# define YY_JL_GRAMMARTRANSLATOR_HH_INCLUDED
/* Debug traces.  */
#ifndef JLDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define JLDEBUG 1
#  else
#   define JLDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define JLDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined JLDEBUG */
#if JLDEBUG
extern int jldebug;
#endif

/* Token type.  */
#ifndef JLTOKENTYPE
# define JLTOKENTYPE
  enum jltokentype
  {
    DOTDOT = 258,
    EQUAL_EQUAL = 259,
    GE = 260,
    LE = 261,
    MINUSMINUS = 262,
    NOT = 263,
    NOTEQUAL = 264,
    PLUSPLUS = 265,
    COLONCOLON = 266,
    ARROW = 267,
    GRING_CMD = 268,
    BIGINTMAT_CMD = 269,
    INTMAT_CMD = 270,
    PROC_CMD = 271,
    RING_CMD = 272,
    BEGIN_RING = 273,
    IDEAL_CMD = 274,
    MAP_CMD = 275,
    MATRIX_CMD = 276,
    MODUL_CMD = 277,
    NUMBER_CMD = 278,
    POLY_CMD = 279,
    RESOLUTION_CMD = 280,
    VECTOR_CMD = 281,
    BETTI_CMD = 282,
    E_CMD = 283,
    FETCH_CMD = 284,
    FREEMODULE_CMD = 285,
    KEEPRING_CMD = 286,
    IMAP_CMD = 287,
    KOSZUL_CMD = 288,
    MAXID_CMD = 289,
    MONOM_CMD = 290,
    PAR_CMD = 291,
    PREIMAGE_CMD = 292,
    VAR_CMD = 293,
    VALTVARS = 294,
    VMAXDEG = 295,
    VMAXMULT = 296,
    VNOETHER = 297,
    VMINPOLY = 298,
    END_RING = 299,
    CMD_1 = 300,
    CMD_2 = 301,
    CMD_3 = 302,
    CMD_12 = 303,
    CMD_13 = 304,
    CMD_23 = 305,
    CMD_123 = 306,
    CMD_M = 307,
    ROOT_DECL = 308,
    ROOT_DECL_LIST = 309,
    RING_DECL = 310,
    RING_DECL_LIST = 311,
    EXAMPLE_CMD = 312,
    EXPORT_CMD = 313,
    HELP_CMD = 314,
    KILL_CMD = 315,
    LIB_CMD = 316,
    LISTVAR_CMD = 317,
    SETRING_CMD = 318,
    TYPE_CMD = 319,
    STRINGTOK = 320,
    BLOCKTOK = 321,
    INT_CONST = 322,
    UNKNOWN_IDENT = 323,
    RINGVAR = 324,
    PROC_DEF = 325,
    APPLY = 326,
    ASSUME_CMD = 327,
    BREAK_CMD = 328,
    CONTINUE_CMD = 329,
    ELSE_CMD = 330,
    EVAL = 331,
    QUOTE = 332,
    FOR_CMD = 333,
    IF_CMD = 334,
    SYS_BREAK = 335,
    WHILE_CMD = 336,
    RETURN = 337,
    PARAMETER = 338,
    SYSVAR = 339,
    UMINUS = 340,
    JULIA_ENDELSE_CMD = 341,
    JULIA_ENDIF_CMD = 342,
    JULIA_ENDLOOP_CMD = 343,
    JULIA_ENDPROC_CMD = 344
  };
#endif

/* Value type.  */



int jlparse (void);

#endif /* !YY_JL_GRAMMARTRANSLATOR_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 475 "grammartranslator.cc" /* yacc.c:358  */

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
         || (defined JLSTYPE_IS_TRIVIAL && JLSTYPE_IS_TRIVIAL)))

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2605

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  408

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   344

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    96,     2,
      99,   100,     2,    88,    94,    89,   101,    90,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,    95,
      86,    85,    87,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    91,     2,    92,    93,     2,   106,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      98,   102,   103,   104,   105
};

#if JLDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   428,   428,   430,   517,   526,   538,   549,   561,   573,
     583,   632,   644,   656,   667,   678,   693,   702,   711,   712,
     721,   730,   731,   732,   736,   739,   748,   757,   766,   775,
     784,   793,   802,   835,   897,   913,   938,   942,   953,   965,
    1004,  1032,  1067,  1080,  1093,  1104,  1108,  1112,  1116,  1120,
    1124,  1128,  1139,  1150,  1161,  1165,  1169,  1173,  1177,  1181,
    1185,  1189,  1193,  1197,  1201,  1230,  1234,  1238,  1242,  1246,
    1250,  1263,  1286,  1299,  1311,  1321,  1325,  1329,  1333,  1337,
    1341,  1345,  1349,  1353,  1357,  1374,  1388,  1387,  1405,  1413,
    1421,  1430,  1443,  1456,  1469,  1482,  1508,  1521,  1534,  1545,
    1556,  1569,  1580,  1591,  1610,  1627,  1638,  1666,  1677,  1689,
    1708,  1713,  1731,  1747,  1783,  1809,  1830,  1845,  1857,  1866,
    1891,  1906,  1922,  1974,  1983,  1999,  2008,  2020,  2034,  2036,
    2038,  2053,  2058,  2063,  2070,  2078,  2090,  2107,  2127,  2131,
    2135,  2140,  2144,  2148,  2152,  2156,  2161,  2167,  2173,  2179,
    2185,  2191,  2197,  2209,  2216,  2229,  2307,  2321,  2333,  2353,
    2359,  2359,  2362,  2430,  2442,  2479,  2512,  2543,  2576,  2585,
    2590,  2598,  2628,  2674,  2691,  2744,  2774,  2797,  2816,  2835,
    2855,  2876,  2886
};
#endif

#if JLDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DOTDOT", "EQUAL_EQUAL", "GE", "LE",
  "MINUSMINUS", "NOT", "NOTEQUAL", "PLUSPLUS", "COLONCOLON", "ARROW",
  "GRING_CMD", "BIGINTMAT_CMD", "INTMAT_CMD", "PROC_CMD", "RING_CMD",
  "BEGIN_RING", "IDEAL_CMD", "MAP_CMD", "MATRIX_CMD", "MODUL_CMD",
  "NUMBER_CMD", "POLY_CMD", "RESOLUTION_CMD", "VECTOR_CMD", "BETTI_CMD",
  "E_CMD", "FETCH_CMD", "FREEMODULE_CMD", "KEEPRING_CMD", "IMAP_CMD",
  "KOSZUL_CMD", "MAXID_CMD", "MONOM_CMD", "PAR_CMD", "PREIMAGE_CMD",
  "VAR_CMD", "VALTVARS", "VMAXDEG", "VMAXMULT", "VNOETHER", "VMINPOLY",
  "END_RING", "CMD_1", "CMD_2", "CMD_3", "CMD_12", "CMD_13", "CMD_23",
  "CMD_123", "CMD_M", "ROOT_DECL", "ROOT_DECL_LIST", "RING_DECL",
  "RING_DECL_LIST", "EXAMPLE_CMD", "EXPORT_CMD", "HELP_CMD", "KILL_CMD",
  "LIB_CMD", "LISTVAR_CMD", "SETRING_CMD", "TYPE_CMD", "STRINGTOK",
  "BLOCKTOK", "INT_CONST", "UNKNOWN_IDENT", "RINGVAR", "PROC_DEF", "APPLY",
  "ASSUME_CMD", "BREAK_CMD", "CONTINUE_CMD", "ELSE_CMD", "EVAL", "QUOTE",
  "FOR_CMD", "IF_CMD", "SYS_BREAK", "WHILE_CMD", "RETURN", "PARAMETER",
  "SYSVAR", "'='", "'<'", "'>'", "'+'", "'-'", "'/'", "'['", "']'", "'^'",
  "','", "';'", "'&'", "':'", "UMINUS", "'('", "')'", "'.'",
  "JULIA_ENDELSE_CMD", "JULIA_ENDIF_CMD", "JULIA_ENDLOOP_CMD",
  "JULIA_ENDPROC_CMD", "'`'", "$accept", "lines", "pprompt", "flowctrl",
  "example_dummy", "command", "assign", "elemexpr", "exprlist", "expr",
  "$@1", "quote_start", "assume_start", "quote_end", "expr_arithmetic",
  "left_value", "extendedid", "declare_ip_variable", "stringexpr", "rlist",
  "ordername", "orderelem", "OrderingList", "ordering", "cmdeq", "mat_cmd",
  "filecmd", "helpcmd", "examplecmd", "exportcmd", "killcmd", "listcmd",
  "ringcmd1", "ringcmd", "scriptcmd", "setrings", "setringcmd", "typecmd",
  "ifcmd", "whilecmd", "forcmd", "proccmd", "parametercmd", "returncmd",
  "listparametercmd", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,    61,    60,    62,    43,    45,
      47,    91,    93,    94,    44,    59,    38,    58,   340,    40,
      41,    46,   341,   342,   343,   344,    96
};
# endif

#define YYPACT_NINF -372

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-372)))

#define YYTABLE_NINF -158

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-158)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -372,   396,  -372,   -80,   944,  -372,  -372,  1009,   -69,  -372,
    -372,   -49,   -24,   -20,   -15,    25,    38,    45,    48,  1074,
    1139,  1204,  1269,     1,   944,   -58,   944,    50,  -372,   944,
    -372,  -372,  -372,  -372,   -12,    67,    74,  -372,  -372,    55,
      81,    83,   121,   110,  -372,   131,   112,   160,   160,   944,
     944,  -372,   489,  -372,  -372,  -372,  -372,   944,  -372,  -372,
    -372,   135,  -372,    -5,   -60,  2440,   944,   944,  -372,   944,
     220,   -76,  -372,  1334,  -372,  -372,  -372,  -372,   139,  -372,
     944,  -372,  -372,   944,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,  -372,   137,   -69,   141,   142,   144,   145,  -372,   944,
      37,   146,   944,   324,  2440,    -8,  1399,   944,   944,   944,
     944,   944,   944,   944,   554,   944,   498,   619,   556,   944,
     563,   684,   621,   143,  -372,   152,   154,  -372,    32,   749,
    2440,    22,   944,  -372,  -372,  -372,  -372,   182,   944,   186,
     814,  -372,  -372,    37,   -59,  1464,   -52,  -372,   -71,   165,
    -372,   944,   879,  -372,   944,   944,   944,  -372,   944,  -372,
     944,   944,   944,   944,   944,   944,   944,   944,   944,   279,
    1715,   152,   191,  -372,   944,  -372,  -372,   944,   239,   944,
      51,  2440,   944,   944,   619,   944,   684,   944,     7,  -372,
     944,  1745,   166,  1761,  1790,  1810,   425,  1555,  1856,  1583,
    -372,   -48,  1885,  -372,   -43,  1905,  -372,   -40,  -372,  -372,
      34,    41,    43,    56,    77,    79,  -372,    -9,    89,   193,
    -372,  1921,   944,   198,  1951,  -372,  -372,   -39,  -372,  1009,
    2440,    97,  -372,  -372,  -372,  -372,  -372,  -372,   -30,  2440,
     293,   262,   262,  2504,    21,    21,    37,  1600,    14,  2469,
      21,  -372,   944,  -372,  -372,   944,  -372,   686,  1620,   944,
      58,  1399,     7,  1885,   -18,  1905,   -17,  1620,  -372,  1980,
    -372,  1399,  -372,   944,   944,   944,  -372,   944,  -372,   944,
     944,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,  2073,  -372,  -372,  -372,  1529,  2016,   201,
     -46,  -372,  -372,  -372,  -372,   944,  2046,  2046,   944,  -372,
    2075,    11,  2440,   170,  -372,  -372,   944,   174,  2089,  2111,
    2141,  2184,  1650,  1695,   173,   175,   176,   177,   178,   179,
     184,    95,   100,   102,   105,   122,  2206,  -372,  -372,   195,
    -372,  2236,  -372,  -372,  2250,   194,   944,  1399,   -14,   -63,
    -372,   944,  -372,   944,   944,  -372,   944,  -372,  -372,  -372,
    -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,   221,  -372,   944,   944,   -29,   196,  -372,  -372,   223,
     199,  -372,   192,  2279,  2301,  2345,  2374,  -372,  2396,  2412,
    -372,   -63,   200,   197,   944,  -372,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,   223,  -372,    23,  -372,  -372
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,   130,   129,     0,   154,   128,
     161,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160,     0,
     117,    41,   107,    34,     0,     0,     0,   169,   170,     0,
       0,     0,     0,     0,     8,     0,     0,    42,     0,     0,
       0,     9,     0,    11,    12,    13,    14,     0,     3,     4,
      18,     0,    25,    74,   164,    72,     0,     0,    73,     0,
      35,     0,    43,     0,    21,    22,    23,    26,    27,    28,
       0,    29,    30,     0,    31,    32,    16,    17,    19,    20,
       7,    10,     0,     0,     0,     0,     0,     0,    42,     0,
     103,     0,     0,    74,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    74,     0,    74,     0,
      74,     0,    74,     0,    24,   135,     0,   133,    74,     0,
     163,     0,     0,    89,   167,    86,    88,     0,     0,     0,
       0,   159,   131,   104,     0,     0,     0,   181,     0,     0,
       5,     0,     0,   106,     0,     0,     0,    92,     0,    91,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     0,   127,     0,     6,   105,     0,    74,     0,
      74,   162,     0,     0,     0,     0,     0,     0,    72,   173,
       0,   118,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     0,    72,    47,     0,    72,    50,     0,   134,   132,
       0,     0,     0,     0,     0,     0,   153,    74,     0,     0,
     174,     0,     0,     0,     0,   171,   180,     0,    40,     0,
     178,   176,    70,    15,   182,   108,    36,    38,     0,    71,
     101,   100,    99,    97,    93,    94,    95,     0,    96,    98,
     102,    37,     0,    90,    83,     0,    69,    74,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,    44,    72,
      68,     0,    51,     0,     0,     0,    52,     0,    53,     0,
       0,    54,    64,    45,    46,    48,    49,   144,   142,   138,
     139,   140,   141,     0,   145,   143,   175,     0,     0,     0,
       0,   179,   177,    39,    76,     0,     0,     0,     0,    66,
       0,    74,   118,     0,    46,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    87,   172,   165,
     168,     0,    84,    85,     0,     0,     0,     0,     0,     0,
      55,     0,    56,     0,     0,    57,     0,    58,   152,   150,
     146,   147,   148,   149,   151,    77,    78,    79,    80,    81,
      82,     0,    75,     0,     0,     0,     0,   119,   120,     0,
     121,   125,     0,     0,     0,     0,     0,   166,     0,     0,
     158,     0,   123,     0,     0,    67,    59,    60,    61,    62,
      65,   113,   155,     0,   126,     0,   124,   122
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -372,  -372,  -372,  -372,  -372,  -372,  -372,    19,    -1,    52,
    -372,  -372,  -372,   -83,  -372,  -372,   288,   156,   180,  -258,
    -372,  -371,  -104,   -89,   125,     0,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,  -372,   158,  -372,  -372
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    58,    59,    60,    61,    62,    63,   146,    65,
     222,    66,    67,   254,    68,    69,    70,    71,    72,   192,
     380,   381,   393,   382,   176,   101,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,   147,    90,   148
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    73,   151,   313,   172,   378,   151,   126,   392,   173,
     155,   156,   145,   317,   157,    91,   158,   159,   174,   175,
     339,   157,   151,   125,   159,   153,   103,   340,   157,   233,
     106,   159,   392,   228,   154,   154,   379,   127,   116,   118,
     120,   122,   154,   151,   157,   128,   154,   159,   232,   144,
     107,   154,   282,   131,   154,   154,   100,   284,   189,   104,
     286,   301,   151,   390,   154,   154,   123,   124,   171,   151,
     303,   104,   104,   104,   104,   108,   154,   154,   104,   109,
     154,   130,   314,   315,   110,   293,   377,   219,   220,   376,
     152,   294,   178,   160,   152,   161,   162,   163,   164,   180,
     165,   143,   346,   166,   167,   164,  -157,   268,   168,   149,
     152,   163,   164,   201,   165,   168,   204,   154,   169,   170,
     207,   134,   168,   407,   111,   104,  -136,  -136,   164,   218,
     165,   152,   104,   182,   287,   181,   173,   112,   168,   227,
     106,   288,   183,   289,   113,    73,  -156,   114,   217,   129,
     152,   238,  -137,  -137,   188,   184,   290,   152,   191,   193,
     194,   195,   196,   197,   198,   199,   132,   202,   155,   156,
     236,   205,   157,   133,   158,   159,   185,   291,   186,   292,
     135,   104,   136,   264,   221,   266,   137,   251,   187,   295,
     224,   174,   302,   257,   107,   365,   139,   230,   260,   110,
     366,   111,   367,   104,   113,   368,   239,   240,   241,   138,
     242,   140,   243,   244,   245,   246,   247,   248,   249,   250,
     104,   114,   369,   342,   343,    30,   104,   141,   142,   258,
     150,   104,   172,   179,   262,   263,   182,   265,   208,   267,
     183,   184,   269,   185,   186,   187,   154,   223,   103,   209,
     151,   160,   225,   161,   162,   163,   164,   256,   165,   296,
     271,   166,   167,   299,   347,   155,   168,   338,   349,   157,
     371,   235,   159,   358,   298,   359,   360,   361,   362,   363,
     311,   104,   155,   156,   364,   374,   157,   387,   158,   159,
     391,   378,   395,   330,   403,   105,  -158,   404,   394,   406,
     157,   231,   402,   159,   306,   261,   234,   307,     0,     0,
       0,   310,     0,   312,     0,   348,     0,     0,     0,     0,
       0,     0,  -114,   312,  -114,   318,   319,   320,     0,   321,
     259,   322,   323,  -114,  -114,   151,     0,     0,   152,  -114,
       0,     0,     0,     0,     0,   375,     0,     0,   160,   336,
     161,   162,   163,   164,     0,   165,     0,   341,     0,   167,
     344,     0,     0,   168,   252,   160,     0,   161,   162,   163,
     164,     0,   165,     0,     0,   166,   167,     0,     0,   253,
     168,   161,   162,   163,   164,     0,   165,     0,     0,     0,
     167,     0,     0,   405,   168,     0,     2,     3,     0,   312,
       0,     0,     0,   383,     4,   384,   385,  -116,   386,  -116,
       5,     6,     7,     8,     0,     0,     0,     9,  -116,  -116,
       0,     0,     0,   152,  -116,   388,   389,    10,   155,   156,
       0,     0,   157,     0,   158,   159,     0,     0,     0,     0,
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,    27,    28,
      29,    30,     0,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,     0,
      47,     0,    48,     0,     0,    49,     0,    50,     0,     0,
       0,    51,     0,     0,     0,    52,     0,     4,    53,    54,
      55,    56,    57,     5,     6,    92,    93,     0,     0,   151,
       9,   160,     0,   161,   162,   163,   164,     0,   165,   275,
       0,   166,   167,     0,     0,   276,   168,     0,     0,     0,
       0,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,   151,     5,     6,
      92,    93,   145,    98,   151,     9,     0,     0,    49,     0,
      50,  -109,     0,  -109,     0,     0,     0,     0,    99,     0,
       0,     0,  -109,  -109,     0,    57,     0,   152,  -109,    11,
      12,    13,    14,    15,    16,    17,    18,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,   151,     5,     6,    92,    93,     0,    98,  -110,
       9,  -110,     0,    49,     0,    50,  -111,     0,  -111,     0,
    -110,  -110,     0,    99,   200,   152,  -110,  -111,  -111,     0,
      57,     0,   152,  -111,    11,    12,    13,    14,    15,    16,
      17,    18,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,   151,     5,     6,
      92,    93,     0,    98,  -112,     9,  -112,     0,    49,     0,
      50,     0,     0,     0,     0,  -112,  -112,     0,    99,   203,
     152,  -112,     0,     0,     0,    57,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,     0,     5,     6,   210,   211,     0,    98,  -115,
       9,  -115,     0,    49,     0,    50,     0,     0,     0,     0,
    -115,  -115,     0,    99,   206,   152,  -115,     0,     0,     0,
      57,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,   212,   213,   214,   215,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,     0,     5,     6,
      92,    93,     0,    98,     0,     9,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,     0,    99,   216,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,     0,     5,     6,    92,    93,     0,    98,     0,
       9,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,     0,     0,    99,   226,     0,     0,     0,     0,     0,
      57,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,     0,     5,     6,
      92,    93,     0,    98,     0,     9,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,     0,    99,   237,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,     0,     5,     6,    92,    93,     0,    98,     0,
       9,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,     0,     0,
      57,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,     0,     5,     6,
      92,    93,     0,    98,     0,     9,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,     0,   102,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,     0,     5,     6,    92,    93,     0,    98,     0,
       9,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,     0,     0,   115,     0,     0,     0,     0,     0,     0,
      57,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,     0,     5,     6,
      92,    93,     0,    98,     0,     9,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,     0,     5,     6,    92,    93,     0,    98,     0,
       9,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,     0,     0,   119,     0,     0,     0,     0,     0,     0,
      57,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,     0,     5,     6,
      92,    93,     0,    98,     0,     9,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,     0,   121,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,     0,     5,     6,    92,    93,     0,    98,     0,
       9,     0,     0,    49,     0,    50,     0,     0,     0,     0,
       0,     0,     0,   177,     0,     0,     0,     0,     0,     0,
      57,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,     0,
      35,    36,     4,     0,     0,    40,    41,     0,     5,     6,
     229,    93,     0,    98,     0,     9,     0,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,     0,   190,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,    33,     0,    35,    36,     4,     0,     0,
      40,    41,     0,     5,     6,    92,    93,     0,    98,     0,
       9,     0,     0,    49,     0,    50,     0,     0,   155,   156,
       0,     0,   157,    99,   158,   159,     0,     0,     0,     0,
      57,     0,     0,     0,   331,    12,    13,   332,   333,    16,
     334,   335,    94,    95,    96,    97,   155,   156,     0,     0,
     157,     0,   158,   159,    30,     0,    31,    32,    33,     0,
      35,    36,     0,   155,   156,    40,    41,   157,     0,   158,
     159,     0,     0,    98,     0,     0,     0,     0,    49,     0,
      50,     0,     0,   155,   156,     0,     0,   157,    99,   158,
     159,     0,     0,     0,     0,    57,     0,     0,     0,     0,
       0,   160,     0,   161,   162,   163,   164,     0,   165,   277,
       0,   166,   167,   155,   156,   278,   168,   157,     0,   158,
     159,     0,     0,     0,     0,     0,     0,     0,     0,   160,
       0,   161,   162,   163,   164,     0,   165,   280,     0,   166,
     167,     0,     0,   281,   168,     0,   160,     0,   161,   162,
     163,   164,   304,   165,   305,     0,   166,   167,   155,   156,
       0,   168,   157,     0,   158,   159,   160,     0,   161,   162,
     163,   164,     0,   165,   308,     0,   166,   167,   155,   156,
     309,   168,   157,     0,   158,   159,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   160,     0,   161,   162,
     163,   164,     0,   165,   354,     0,   166,   167,   155,   156,
     355,   168,   157,     0,   158,   159,     0,     0,     0,     0,
       0,     0,     0,     0,   155,   156,     0,     0,   157,     0,
     158,   159,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   160,     0,   161,   162,   163,   164,     0,   165,   356,
       0,   166,   167,   155,   156,   357,   168,   157,     0,   158,
     159,   160,     0,   161,   162,   163,   164,     0,   165,   255,
       0,   166,   167,   155,   156,     0,   168,   157,     0,   158,
     159,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   160,     0,   161,   162,   163,   164,     0,   165,     0,
       0,   166,   167,     0,     0,   270,   168,   160,     0,   161,
     162,   163,   164,     0,   165,     0,     0,   166,   167,   155,
     156,   272,   168,   157,     0,   158,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   160,     0,   161,   162,
     163,   164,     0,   165,   273,     0,   166,   167,   155,   156,
       0,   168,   157,     0,   158,   159,   160,     0,   161,   162,
     163,   164,     0,   165,   274,     0,   166,   167,   155,   156,
       0,   168,   157,     0,   158,   159,     0,     0,     0,     0,
       0,     0,     0,     0,   155,   156,     0,     0,   157,     0,
     158,   159,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   160,     0,   161,   162,   163,   164,     0,   165,
     279,     0,   166,   167,   155,   156,     0,   168,   157,     0,
     158,   159,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   160,     0,   161,   162,   163,   164,     0,   165,     0,
       0,   166,   167,   155,   156,   283,   168,   157,     0,   158,
     159,   160,     0,   161,   162,   163,   164,     0,   165,     0,
       0,   166,   167,     0,     0,   285,   168,   160,     0,   161,
     162,   163,   164,     0,   165,   297,     0,   166,   167,   155,
     156,     0,   168,   157,     0,   158,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   160,     0,   161,
     162,   163,   164,     0,   165,     0,     0,   166,   167,   155,
     156,   300,   168,   157,     0,   158,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   160,     0,   161,   162,
     163,   164,     0,   165,   316,     0,   166,   167,   155,   156,
       0,   168,   157,     0,   158,   159,     0,     5,     6,   324,
     325,     0,   155,   156,     9,     0,   157,     0,   158,   159,
       0,     0,   160,     0,   161,   162,   163,   164,     0,   165,
       0,     0,   166,   167,   155,   156,   337,   168,   157,     0,
     158,   159,     0,     0,     0,     0,   326,   327,   328,   329,
       0,     0,   160,     0,   161,   162,   163,   164,     0,   165,
       0,     0,   166,   167,   155,   156,   253,   168,   157,     0,
     158,   159,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   160,     0,   161,   162,   163,   164,   345,   165,     0,
       0,   166,   167,     0,     0,   160,   168,   161,   162,   163,
     164,     0,   165,     0,     0,   166,   167,   155,   156,   350,
     168,   157,     0,   158,   159,     0,     0,   160,     0,   161,
     162,   163,   164,     0,   165,   351,     0,   166,   167,   155,
     156,     0,   168,   157,     0,   158,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   160,     0,   161,
     162,   163,   164,     0,   165,     0,     0,   166,   167,   155,
     156,   352,   168,   157,     0,   158,   159,     0,     0,     0,
       0,     0,     0,   155,   156,     0,     0,   157,     0,   158,
     159,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     160,     0,   161,   162,   163,   164,     0,   165,   353,     0,
     166,   167,   155,   156,     0,   168,   157,     0,   158,   159,
       0,     0,   160,     0,   161,   162,   163,   164,     0,   165,
       0,     0,   166,   167,   155,   156,   370,   168,   157,     0,
     158,   159,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   160,     0,   161,   162,   163,   164,   372,   165,
       0,     0,   166,   167,     0,     0,   160,   168,   161,   162,
     163,   164,     0,   165,   373,     0,   166,   167,   155,   156,
       0,   168,   157,     0,   158,   159,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   160,     0,   161,   162,   163,
     164,     0,   165,     0,     0,   166,   167,   155,   156,   396,
     168,   157,     0,   158,   159,     0,     0,   160,     0,   161,
     162,   163,   164,     0,   165,     0,     0,   166,   167,   155,
     156,   397,   168,   157,     0,   158,   159,     0,     0,     0,
       0,     0,     0,     0,     0,   155,   156,     0,     0,   157,
       0,   158,   159,     0,     0,     0,     0,     0,     0,     0,
       0,   160,     0,   161,   162,   163,   164,     0,   165,     0,
       0,   166,   167,   155,   156,   398,   168,   157,     0,   158,
     159,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     160,     0,   161,   162,   163,   164,     0,   165,     0,     0,
     166,   167,   155,   156,   399,   168,   157,     0,   158,   159,
       0,     0,   160,     0,   161,   162,   163,   164,     0,   165,
       0,     0,   166,   167,     0,     0,   400,   168,   160,     0,
     161,   162,   163,   164,   401,   165,     0,   155,   166,   167,
       0,   157,     0,   168,   159,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   160,     0,   161,   162,
     163,   164,     0,   165,     0,     0,   166,   167,     0,     0,
       0,   168,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   160,     0,   161,   162,   163,
     164,     0,   165,     0,     0,     0,   167,     0,     0,     0,
     168,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   161,   162,   163,   164,     0,   165,     0,     0,
       0,   167,     0,     0,     0,   168
};

static const yytype_int16 yycheck[] =
{
       1,     1,    11,   261,    12,    68,    11,    65,   379,    85,
       3,     4,    83,   271,     7,    95,     9,    10,    94,    95,
      66,     7,    11,    24,    10,    85,     7,    73,     7,   100,
      99,    10,   403,    92,    94,    94,    99,    95,    19,    20,
      21,    22,    94,    11,     7,    26,    94,    10,   100,    50,
      99,    94,   100,    65,    94,    94,     4,   100,    66,     7,
     100,   100,    11,    92,    94,    94,    65,    66,    69,    11,
     100,    19,    20,    21,    22,    99,    94,    94,    26,    99,
      94,    29,   100,   100,    99,    94,   100,    65,    66,   347,
      99,   100,    73,    86,    99,    88,    89,    90,    91,    80,
      93,    49,    91,    96,    97,    91,    95,   100,   101,    57,
      99,    90,    91,   114,    93,   101,   117,    94,    66,    67,
     121,    66,   101,   100,    99,    73,    94,    95,    91,   129,
      93,    99,    80,    99,   100,    83,    85,    99,   101,   140,
      99,   100,    99,   100,    99,   145,    95,    99,   129,    99,
      99,   152,    94,    95,   102,    99,   100,    99,   106,   107,
     108,   109,   110,   111,   112,   113,    99,   115,     3,     4,
     151,   119,     7,    99,     9,    10,    99,   100,    99,   100,
      99,   129,    99,   184,   132,   186,    65,   168,    99,   100,
     138,    94,    95,   174,    99,   100,    65,   145,   179,    99,
     100,    99,   100,   151,    99,   100,   154,   155,   156,    99,
     158,    99,   160,   161,   162,   163,   164,   165,   166,   167,
     168,    99,   100,   306,   307,    65,   174,    47,    48,   177,
      95,   179,    12,    94,   182,   183,    99,   185,    95,   187,
      99,    99,   190,    99,    99,    99,    94,    65,   229,    95,
      11,    86,    66,    88,    89,    90,    91,    66,    93,    66,
      94,    96,    97,    65,    94,     3,   101,    66,    94,     7,
      75,   106,    10,   100,   222,   100,   100,   100,   100,   100,
     261,   229,     3,     4,   100,    91,     7,    66,     9,    10,
      94,    68,   100,   293,    94,     7,     3,   100,    99,   403,
       7,   145,   391,    10,   252,   180,   148,   255,    -1,    -1,
      -1,   259,    -1,   261,    -1,   316,    -1,    -1,    -1,    -1,
      -1,    -1,    83,   271,    85,   273,   274,   275,    -1,   277,
      91,   279,   280,    94,    95,    11,    -1,    -1,    99,   100,
      -1,    -1,    -1,    -1,    -1,   346,    -1,    -1,    86,   297,
      88,    89,    90,    91,    -1,    93,    -1,   305,    -1,    97,
     308,    -1,    -1,   101,    85,    86,    -1,    88,    89,    90,
      91,    -1,    93,    -1,    -1,    96,    97,    -1,    -1,   100,
     101,    88,    89,    90,    91,    -1,    93,    -1,    -1,    -1,
      97,    -1,    -1,   394,   101,    -1,     0,     1,    -1,   347,
      -1,    -1,    -1,   351,     8,   353,   354,    83,   356,    85,
      14,    15,    16,    17,    -1,    -1,    -1,    21,    94,    95,
      -1,    -1,    -1,    99,   100,   373,   374,    31,     3,     4,
      -1,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      84,    -1,    86,    -1,    -1,    89,    -1,    91,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,     8,   102,   103,
     104,   105,   106,    14,    15,    16,    17,    -1,    -1,    11,
      21,    86,    -1,    88,    89,    90,    91,    -1,    93,    94,
      -1,    96,    97,    -1,    -1,   100,   101,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    11,    14,    15,
      16,    17,    83,    84,    11,    21,    -1,    -1,    89,    -1,
      91,    83,    -1,    85,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    94,    95,    -1,   106,    -1,    99,   100,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    11,    14,    15,    16,    17,    -1,    84,    83,
      21,    85,    -1,    89,    -1,    91,    83,    -1,    85,    -1,
      94,    95,    -1,    99,   100,    99,   100,    94,    95,    -1,
     106,    -1,    99,   100,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    11,    14,    15,
      16,    17,    -1,    84,    83,    21,    85,    -1,    89,    -1,
      91,    -1,    -1,    -1,    -1,    94,    95,    -1,    99,   100,
      99,   100,    -1,    -1,    -1,   106,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    -1,    14,    15,    16,    17,    -1,    84,    83,
      21,    85,    -1,    89,    -1,    91,    -1,    -1,    -1,    -1,
      94,    95,    -1,    99,   100,    99,   100,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    -1,    14,    15,
      16,    17,    -1,    84,    -1,    21,    -1,    -1,    89,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    -1,    14,    15,    16,    17,    -1,    84,    -1,
      21,    -1,    -1,    89,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    -1,    14,    15,
      16,    17,    -1,    84,    -1,    21,    -1,    -1,    89,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    -1,    14,    15,    16,    17,    -1,    84,    -1,
      21,    -1,    -1,    89,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    -1,    14,    15,
      16,    17,    -1,    84,    -1,    21,    -1,    -1,    89,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    -1,    14,    15,    16,    17,    -1,    84,    -1,
      21,    -1,    -1,    89,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    -1,    14,    15,
      16,    17,    -1,    84,    -1,    21,    -1,    -1,    89,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    -1,    14,    15,    16,    17,    -1,    84,    -1,
      21,    -1,    -1,    89,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    -1,    14,    15,
      16,    17,    -1,    84,    -1,    21,    -1,    -1,    89,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    -1,    14,    15,    16,    17,    -1,    84,    -1,
      21,    -1,    -1,    89,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      71,    72,     8,    -1,    -1,    76,    77,    -1,    14,    15,
      16,    17,    -1,    84,    -1,    21,    -1,    -1,    89,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    71,    72,     8,    -1,    -1,
      76,    77,    -1,    14,    15,    16,    17,    -1,    84,    -1,
      21,    -1,    -1,    89,    -1,    91,    -1,    -1,     3,     4,
      -1,    -1,     7,    99,     9,    10,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     3,     4,    -1,    -1,
       7,    -1,     9,    10,    65,    -1,    67,    68,    69,    -1,
      71,    72,    -1,     3,     4,    76,    77,     7,    -1,     9,
      10,    -1,    -1,    84,    -1,    -1,    -1,    -1,    89,    -1,
      91,    -1,    -1,     3,     4,    -1,    -1,     7,    99,     9,
      10,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    -1,    93,    94,
      -1,    96,    97,     3,     4,   100,   101,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    88,    89,    90,    91,    -1,    93,    94,    -1,    96,
      97,    -1,    -1,   100,   101,    -1,    86,    -1,    88,    89,
      90,    91,    92,    93,    94,    -1,    96,    97,     3,     4,
      -1,   101,     7,    -1,     9,    10,    86,    -1,    88,    89,
      90,    91,    -1,    93,    94,    -1,    96,    97,     3,     4,
     100,   101,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    89,
      90,    91,    -1,    93,    94,    -1,    96,    97,     3,     4,
     100,   101,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    -1,    93,    94,
      -1,    96,    97,     3,     4,   100,   101,     7,    -1,     9,
      10,    86,    -1,    88,    89,    90,    91,    -1,    93,    94,
      -1,    96,    97,     3,     4,    -1,   101,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    -1,    93,    -1,
      -1,    96,    97,    -1,    -1,   100,   101,    86,    -1,    88,
      89,    90,    91,    -1,    93,    -1,    -1,    96,    97,     3,
       4,   100,   101,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    89,
      90,    91,    -1,    93,    94,    -1,    96,    97,     3,     4,
      -1,   101,     7,    -1,     9,    10,    86,    -1,    88,    89,
      90,    91,    -1,    93,    94,    -1,    96,    97,     3,     4,
      -1,   101,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    88,    89,    90,    91,    -1,    93,
      94,    -1,    96,    97,     3,     4,    -1,   101,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    -1,    93,    -1,
      -1,    96,    97,     3,     4,   100,   101,     7,    -1,     9,
      10,    86,    -1,    88,    89,    90,    91,    -1,    93,    -1,
      -1,    96,    97,    -1,    -1,   100,   101,    86,    -1,    88,
      89,    90,    91,    -1,    93,    94,    -1,    96,    97,     3,
       4,    -1,   101,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,
      89,    90,    91,    -1,    93,    -1,    -1,    96,    97,     3,
       4,   100,   101,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    89,
      90,    91,    -1,    93,    94,    -1,    96,    97,     3,     4,
      -1,   101,     7,    -1,     9,    10,    -1,    14,    15,    16,
      17,    -1,     3,     4,    21,    -1,     7,    -1,     9,    10,
      -1,    -1,    86,    -1,    88,    89,    90,    91,    -1,    93,
      -1,    -1,    96,    97,     3,     4,   100,   101,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      -1,    -1,    86,    -1,    88,    89,    90,    91,    -1,    93,
      -1,    -1,    96,    97,     3,     4,   100,   101,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    92,    93,    -1,
      -1,    96,    97,    -1,    -1,    86,   101,    88,    89,    90,
      91,    -1,    93,    -1,    -1,    96,    97,     3,     4,   100,
     101,     7,    -1,     9,    10,    -1,    -1,    86,    -1,    88,
      89,    90,    91,    -1,    93,    94,    -1,    96,    97,     3,
       4,    -1,   101,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,
      89,    90,    91,    -1,    93,    -1,    -1,    96,    97,     3,
       4,   100,   101,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    88,    89,    90,    91,    -1,    93,    94,    -1,
      96,    97,     3,     4,    -1,   101,     7,    -1,     9,    10,
      -1,    -1,    86,    -1,    88,    89,    90,    91,    -1,    93,
      -1,    -1,    96,    97,     3,     4,   100,   101,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    88,    89,    90,    91,    92,    93,
      -1,    -1,    96,    97,    -1,    -1,    86,   101,    88,    89,
      90,    91,    -1,    93,    94,    -1,    96,    97,     3,     4,
      -1,   101,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    89,    90,
      91,    -1,    93,    -1,    -1,    96,    97,     3,     4,   100,
     101,     7,    -1,     9,    10,    -1,    -1,    86,    -1,    88,
      89,    90,    91,    -1,    93,    -1,    -1,    96,    97,     3,
       4,   100,   101,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    -1,    93,    -1,
      -1,    96,    97,     3,     4,   100,   101,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    88,    89,    90,    91,    -1,    93,    -1,    -1,
      96,    97,     3,     4,   100,   101,     7,    -1,     9,    10,
      -1,    -1,    86,    -1,    88,    89,    90,    91,    -1,    93,
      -1,    -1,    96,    97,    -1,    -1,   100,   101,    86,    -1,
      88,    89,    90,    91,    92,    93,    -1,     3,    96,    97,
      -1,     7,    -1,   101,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    89,
      90,    91,    -1,    93,    -1,    -1,    96,    97,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    89,    90,
      91,    -1,    93,    -1,    -1,    -1,    97,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    -1,    93,    -1,    -1,
      -1,    97,    -1,    -1,    -1,   101
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   108,     0,     1,     8,    14,    15,    16,    17,    21,
      31,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    62,    63,    64,
      65,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    84,    86,    89,
      91,    95,    99,   102,   103,   104,   105,   106,   109,   110,
     111,   112,   113,   114,   115,   116,   118,   119,   121,   122,
     123,   124,   125,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     150,    95,    16,    17,    53,    54,    55,    56,    84,    99,
     116,   132,    99,   114,   116,   123,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,   114,    99,   114,    99,
     114,    99,   114,    65,    66,   115,    65,    95,   114,    99,
     116,    65,    99,    99,    66,    99,    99,    65,    99,    65,
      99,   125,   125,   116,   115,    83,   115,   149,   151,   116,
      95,    11,    99,    85,    94,     3,     4,     7,     9,    10,
      86,    88,    89,    90,    91,    93,    96,    97,   101,   116,
     116,   115,    12,    85,    94,    95,   131,    99,   114,    94,
     114,   116,    99,    99,    99,    99,    99,    99,   116,    66,
      99,   116,   126,   116,   116,   116,   116,   116,   116,   116,
     100,   115,   116,   100,   115,   116,   100,   115,    95,    95,
      16,    17,    53,    54,    55,    56,   100,   114,   132,    65,
      66,   116,   117,    65,   116,    66,   100,   115,    92,    16,
     116,   124,   100,   100,   149,   106,   114,   100,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   114,    85,   100,   120,    94,    66,   114,   116,    91,
     114,   131,   116,   116,   115,   116,   115,   116,   100,   116,
     100,    94,   100,    94,    94,    94,   100,    94,   100,    94,
      94,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,    94,   100,   100,    66,    94,   116,    65,
     100,   100,    95,   100,    92,    94,   116,   116,    94,   100,
     116,   114,   116,   126,   100,   100,    94,   126,   116,   116,
     116,   116,   116,   116,    16,    17,    53,    54,    55,    56,
     132,    45,    48,    49,    51,    52,   116,   100,    66,    66,
      73,   116,   120,   120,   116,    92,    91,    94,   115,    94,
     100,    94,   100,    94,    94,   100,    94,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,    75,    92,    94,    91,   115,   126,   100,    68,    99,
     127,   128,   130,   116,   116,   116,   116,    66,   116,   116,
      92,    94,   128,   129,    99,   100,   100,   100,   100,   100,
     100,    92,   130,    94,   100,   115,   129,   100
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   111,   112,   112,   112,   112,   112,
     112,   112,   112,   113,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   115,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   116,   118,   119,
     120,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   122,   122,   123,   123,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   126,   126,
     127,   128,   128,   129,   129,   130,   130,   131,   132,   132,
     132,   133,   134,   134,   135,   136,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   140,   140,   140,   140,   141,
     142,   142,   143,   144,   144,   145,   145,   145,   145,   145,
     145,   146,   147,   148,   148,   148,   149,   149,   149,   150,
     150,   151,   151
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     2,     1,     1,     1,
       2,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     3,     3,     3,     4,
       3,     1,     1,     1,     4,     4,     4,     3,     4,     4,
       3,     4,     4,     4,     4,     6,     6,     6,     6,     8,
       8,     8,     8,     3,     4,     8,     4,     8,     4,     3,
       3,     3,     1,     1,     1,     6,     4,     6,     6,     6,
       6,     6,     6,     3,     5,     5,     0,     5,     2,     2,
       1,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     1,     3,     2,
       2,     2,     2,     8,     2,     3,     2,     1,     1,     5,
       1,     1,     4,     1,     3,     1,     3,     1,     1,     1,
       1,     2,     3,     2,     3,     2,     2,     3,     4,     4,
       4,     4,     4,     4,     4,     4,     6,     6,     6,     6,
       6,     6,     6,     3,     1,     8,     2,     4,     7,     2,
       1,     1,     2,     2,     1,     5,     7,     2,     5,     1,
       1,     3,     5,     3,     3,     4,     2,     3,     2,     4,
       3,     1,     2
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if JLDEBUG

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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
#else /* !JLDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !JLDEBUG */


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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
yyparse (void)
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
        case 3:
#line 431 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            
            translator_NbRuleTraversed++;

            int depth = 0;
            Voice * voyager = currentVoice;
            while ((voyager !=NULL)&&(voyager->prev !=NULL)) {
                voyager = voyager->prev;
                depth++;
            }
            
            char * disp;
            if ((yyvsp[0].lv).ms) (yyvsp[0].lv).ms = mstring_indent((yyvsp[0].lv).ms, depth);
            /*{
                for (int i = 0; i<depth*3; i++)
                    $2.ms = mstring_concat( mstring_init_string(" "), $2.ms );
                disp = mstring_to_str( $2.ms );
            }*/
            if ((yyvsp[0].lv).ms) disp = mstring_to_str( (yyvsp[0].lv).ms );
            else disp = setUninitialized();
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "lines", "lines pprompt");
            printf("ms: %s\n", disp);
#endif            
            char waitingForEnd;
            if (currentVoice == NULL)
                waitingForEnd = 0;
            else
                waitingForEnd = currentVoice->waitingForEnd;
                
            if (currentVoice == NULL)
                printf("JULIA COMMAND   NULL (%d) %d> %s !!currentVoice is NULL!!\n", waitingForEnd, depth, disp);
            else if (currentVoice->sw == BI_stdin)
                printf("JULIA COMMAND  STDIN (%d) %d> %s \n", waitingForEnd, depth, disp);
            else if ((currentVoice->sw == BI_buffer)&&(currentVoice->typ == BT_proc))
                printf("JULIA COMMAND  FUNCT (%d) %d> %s \n", waitingForEnd, depth, disp);
            else if ((currentVoice->sw == BI_buffer)&&(currentVoice->typ == BT_break))
                printf("JULIA COMMAND   LOOP (%d) %d> %s \n", waitingForEnd, depth, disp);
            else if ((currentVoice->sw == BI_buffer)&&(currentVoice->typ == BT_if))
                printf("JULIA COMMAND     IF (%d) %d> %s \n", waitingForEnd, depth, disp);
            else if ((currentVoice->sw == BI_buffer)&&(currentVoice->typ == BT_else))
                printf("JULIA COMMAND   ELSE (%d) %d> %s \n", waitingForEnd, depth, disp);
            else 
                printf("JULIA COMMAND  OTHER (%d) %d> %s \n", waitingForEnd, depth, disp);
                
            free(disp);
            if ((yyvsp[0].lv).ms) mstring_free((yyvsp[0].lv).ms);
            translator_NbRuleTraversed = 0;
#endif
            if (timerv)
            {
              writeTime("used time:");
              startTimer();
            }
            if (rtimerv)
            {
              writeRTime("used real time:");
              startRTimer();
            }
            prompt_char = '>';
#ifdef JL_TRANSLATOR_GRAMMAR
            prompt_char = '?';
#endif

#ifdef HAVE_SDB
            if (sdb_flags & 2) { sdb_flags=1; YYERROR; }
#endif
            if(siCntrlc)
            {
              WerrorS("abort...");
              while((currentVoice!=NULL) && (currentVoice->prev!=NULL)) exitVoice();
              if (currentVoice!=NULL) currentVoice->ifsw=0;
            }
            if (errorreported) /* also catches abort... */
            {
              yyerror("");
            }
            if (inerror==2) PrintLn();
            errorreported = inerror = cmdtok = 0;
            lastreserved = currid = NULL;
            expected_parms = siCntrlc = FALSE;
          }
#line 2372 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 517 "grammartranslator.y" /* yacc.c:1646  */
    {                      /* if, while, for, proc */
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "flowctrl");
            printf("\n");
#endif
#endif        
        }
#line 2386 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 527 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ((yyvsp[-1].lv).ms) (yyval.lv).ms = (yyvsp[-1].lv).ms;
            else (yyval.lv).ms = mstring_init_string(uninitialized);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "pprompt", "command \';\'", (yyval.lv).ms);
#endif
#endif
            currentVoice->ifsw=0;
           }
#line 2402 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 538 "grammartranslator.y" /* yacc.c:1646  */
    {     /* default initialization */
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ((yyvsp[-1].lv).ms) (yyval.lv).ms = mstring_concat((yyvsp[-1].lv).ms, mstring_init_string(";"));
            else (yyval.lv).ms = mstring_init_string(uninitialized);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "pprompt", "declare_ip_variable \';\'", (yyval.lv).ms);
#endif
#endif            
          (yyvsp[-1].lv).CleanUp(); currentVoice->ifsw=0;   
          }
#line 2418 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 550 "grammartranslator.y" /* yacc.c:1646  */
    {
/*             YYACCEPT; */
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            (yyval.lv).ms = (yyvsp[0].lv).ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "returncmd");
            printf("\n");
#endif
#endif
          }
#line 2434 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 562 "grammartranslator.y" /* yacc.c:1646  */
    {
            currentVoice->ifsw=0;
            iiDebug();
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "SYS_BREAK");
            printf("\n");
#endif
#endif
          }
#line 2450 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 573 "grammartranslator.y" /* yacc.c:1646  */
    {                    /* ignore empty statements */
          currentVoice->ifsw=0;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", ";");
            printf("\n");
#endif
#endif          
          }
#line 2465 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 584 "grammartranslator.y" /* yacc.c:1646  */
    {
            #ifdef SIQ
            siq=0;
            #endif
            yyInRingConstruction = FALSE;
            currentVoice->ifsw=0;
            if (inerror)
            {
/*  bison failed here*/
              if ((inerror!=3) && ((yyvsp[-1].i)<UMINUS) && ((yyvsp[-1].i)>' '))
              {
                // 1: yyerror called
                // 2: scanner put actual string
                // 3: error rule put token+\n
                inerror=3;
                Print(" error at token `%s`\n",iiTwoOps((yyvsp[-1].i)));
              }
/**/

            }
            if (!errorreported) WerrorS("...parse error");
            yyerror("");
            yyerrok;
#ifdef HAVE_SDB
            if ((sdb_flags & 1) && currentVoice->pi!=NULL)
            {
              currentVoice->pi->trace_flag |=1;
            }
            else
#endif
            if (myynest>0)
            {
              feBufferTypes t=currentVoice->Typ();
              //PrintS("leaving yyparse\n");
              exitBuffer(BT_proc);
              if (t==BT_example)
                YYACCEPT;
              else
                YYABORT;
            }
            else if (currentVoice->prev!=NULL)
            {
              exitVoice();
            }
#ifdef HAVE_SDB
            if (sdb_flags &2) sdb_flags=1;
#endif
          }
#line 2518 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 632 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            (yyval.lv).ms = mstring_init_string("end");
/*             mstring_dedent($$.ms, 1); */
            exitBuffer(BT_else);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDELSE_CMD");
            printf("\n");
#endif
#endif
          }
#line 2535 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 644 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            (yyval.lv).ms = mstring_init_string("end");
/*             mstring_dedent($$.ms, 1); */
            exitBuffer(BT_if);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDIF_CMD");
            printf("\n");
#endif
#endif
          }
#line 2552 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 656 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            (yyval.lv).ms = mstring_init_string("end");
            exitBuffer(BT_break);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDLOOP_CMD");
            printf("\n");
#endif
#endif
          }
#line 2568 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 667 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            (yyval.lv).ms = mstring_init_string("end");
            exitBuffer(BT_proc);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDPROC_CMD");
            printf("\n");
#endif
#endif
          }
#line 2584 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 678 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
/*             $$.ms = ms_conc_s_ms_s("(", $2.ms, ")"); */
            (yyval.lv).ms = mstring_concat((yyvsp[-1].lv).ms, mstring_init_string(")"));
/*             exitBuffer(BT_proc); */
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "listparametercmd");
            printf("\n");
#endif
#endif
          }
#line 2601 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 693 "grammartranslator.y" /* yacc.c:1646  */
    { 
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "ifcmd");
            printf("\n");
#endif
#endif
          }
#line 2615 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 702 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "whilecmd");
            printf("\n");
#endif
#endif
          }
#line 2629 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 712 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "forcmd");
            printf("\n");
#endif
#endif
          }
#line 2643 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 721 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "proccmd");
            printf("\n");
#endif
#endif
          }
#line 2657 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 733 "grammartranslator.y" /* yacc.c:1646  */
    {if (currentVoice!=NULL) currentVoice->ifsw=0;}
#line 2663 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 736 "grammartranslator.y" /* yacc.c:1646  */
    { omFree((ADDRESS)(yyvsp[0].name)); }
#line 2669 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 739 "grammartranslator.y" /* yacc.c:1646  */
    { 
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = (yyvsp[0].lv).ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "command", "assign", (yyval.lv).ms);
#endif
#endif
            }
#line 2683 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 748 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "exportcmd");
            printf("\n");
#endif
#endif
         }
#line 2697 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 757 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "killcmd");
            printf("\n");
#endif
#endif
         }
#line 2711 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 766 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "listcmd");
            printf("\n");
#endif
#endif
         }
#line 2725 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 775 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "ringcmd");
            printf("\n");
#endif
#endif
         }
#line 2739 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 784 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "scriptcmd");
            printf("\n");
#endif
#endif
         }
#line 2753 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 793 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "setringcmd");
            printf("\n");
#endif
#endif
         }
#line 2767 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 802 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring temp;
            switch ((yyvsp[0].lv).Typ()){
                case INT_CMD:
                    (yyval.lv).ms = (yyvsp[0].lv).ms;
                    break;
                case BIGINT_CMD:
                    (yyval.lv).ms = (yyvsp[0].lv).ms;
                    break;
                case NUMBER_CMD:
                    (yyval.lv).ms = ms_conc_s_ms_s( "print(STDOUT,unsafe_string(libSingular.p_String(", (yyvsp[0].lv).ms, ",_singular_actual_ring)))" );
                    break;
                case POLY_CMD:
                    (yyval.lv).ms = ms_conc_s_ms_s( "print(STDOUT,unsafe_string(libSingular.p_String(", (yyvsp[0].lv).ms, ",_singular_actual_ring)))" );
                    break;
                case IDEAL_CMD:
/*                     $$.ms = ms_conc_s_ms_s( "print(STDOUT,unsafe_string(libSingular.id_Show(", $1.ms, ",_singular_actual_ring)))" ); */
                    temp = mstring_init_mstring((yyvsp[0].lv).ms);
                    (yyval.lv).ms = ms_conc_s_ms_s( "id_String(", (yyvsp[0].lv).ms, ",\"" );
                    (yyval.lv).ms = ms_conc_ms_ms_s( (yyval.lv).ms, temp, "\",_singular_actual_ring)"  );
                    break;
                default:
                    (yyval.lv).ms = (yyvsp[0].lv).ms;
            }
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "command", "typecmd", (yyval.lv).ms);
#endif
#endif
         }
#line 2803 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 836 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "assign", "left_value exprlist");
#endif
            leftv voyager;
            switch ((yyvsp[-1].lv).Typ()){
                case INT_CMD:
                    (yyval.lv).ms = ms_conc_s_ms_s( "Int32(", (yyvsp[0].lv).ms, ")" );
                    break;
                case BIGINT_CMD:
                    (yyval.lv).ms = ms_conc_s_ms_s( "BigInt(", (yyvsp[0].lv).ms, ")" );
                    break;
                case NUMBER_CMD:
                    (yyval.lv).ms = (yyvsp[0].lv).ms;
/*                     $$.ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", $2.ms, "\")), _singular_actual_ring)" ); */
                    currentVoice->ring_decl = 0;
                    break;
                case POLY_CMD:
                    (yyval.lv).ms = (yyvsp[0].lv).ms;
/*                     $$.ms = ms_conc_s_ms_s( "polyTODO(", $2.ms, ")" ); */
                    currentVoice->ring_decl = 0;
                    break;
                case IDEAL_CMD:
                    if ((yyvsp[0].lv).Typ() == POLY_CMD) {
                        (yyval.lv).ms = (yyvsp[0].lv).ms;
                        voyager = &(yyvsp[0].lv);
                        while (voyager->next!=NULL){
                            (yyval.lv).ms = ms_conc_ms_s_ms( (yyval.lv).ms, ", ", voyager->next->ms);
                            voyager = voyager->next;
                        }
                        (yyval.lv).ms = ms_conc_s_ms_s("[", (yyval.lv).ms, "]");
                        (yyval.lv).ms = ms_conc_s_ms_s( "idealFromArray(", (yyval.lv).ms, ")" );
                        
                    }
                    else {
                        (yyval.lv).ms = (yyvsp[0].lv).ms;
                    }
                    currentVoice->ring_decl = 0;
                    break;
                default:
                    (yyval.lv).ms = (yyvsp[0].lv).ms;
            }
            (yyval.lv).ms = mstring_concat((yyvsp[-1].lv).ms, (yyval.lv).ms);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
/*             printfrule_ms(translator_NbRuleTraversed, "assign", "left_value exprlist", $$.ms); */
            char * disp;
            if ((yyval.lv).ms) disp = mstring_to_str( (yyval.lv).ms ); //TODO: not sure it is safe
            else disp = setUninitialized();
            printf("rtyp: %d, ms: %s\n", (yyvsp[-1].lv).Typ(), disp);
            free(disp);
#endif
/*             iiAssign(&$1,&$2); */
#else
            if(iiAssign(&(yyvsp[-1].lv),&(yyvsp[0].lv))) YYERROR;
#endif
          }
#line 2866 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 898 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_string((yyvsp[0].name));
#endif
            if (currRing==NULL) MYYERROR("no ring active");
            syMake(&(yyval.lv),omStrDup((yyvsp[0].name)));
#ifdef JL_TRANSLATOR_GRAMMAR
/*             $$.ms = ms; */
            (yyval.lv).ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", ms, "\")), _singular_actual_ring)" );
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "RINGVAR", (yyval.lv).ms);
#endif
#endif
          }
#line 2886 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 914 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_string((yyvsp[0].name));
#endif
            syMake(&(yyval.lv),(yyvsp[0].name));
#ifdef JL_TRANSLATOR_GRAMMAR
            char * disp = mstring_to_str( ms );

            if ( ( ((int) currentVoice->ring_decl)==1)
               &&( ((int) is_symbol_in_table_of_symbol(disp))==0 ))
                (yyval.lv).ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", ms, "\")), _singular_actual_ring)" );
            else
                (yyval.lv).ms = ms;
                
            free(disp);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "extendedid", (yyval.lv).ms);
#endif
// #else
/*             syMake(&$$,$1); */
#endif

          }
#line 2915 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 939 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith2(&(yyval.lv), &(yyvsp[-2].lv), COLONCOLON, &(yyvsp[0].lv))) YYERROR;
          }
#line 2923 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 943 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith2(&(yyval.lv), &(yyvsp[-2].lv), '.', &(yyvsp[0].lv))) YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR    
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "expr \'.\' elemexpr");
            printf("\n");
#endif
#endif
          }
#line 2938 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 954 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR    
            translator_NbRuleTraversed++;
            (yyval.lv).ms = mstring_concat((yyvsp[-2].lv).ms, mstring_init_string("()"));
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "elemexpr \'(\' \')\'", (yyval.lv).ms);
#endif
#else
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-2].lv),'(')) YYERROR;
#endif
          }
#line 2954 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 966 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR    
            translator_NbRuleTraversed++;
            if ((yyvsp[-3].lv).next==NULL) {
            
                (yyval.lv).ms = (yyvsp[-1].lv).ms;
                leftv voyager = &(yyvsp[-1].lv);
                while (voyager->next!=NULL){
                    (yyval.lv).ms = ms_conc_ms_s_ms( (yyval.lv).ms, ", ", voyager->next->ms);
                    voyager = voyager->next;
                }
                (yyval.lv).ms = ms_conc_s_ms_s("(", (yyval.lv).ms, ")");
                (yyval.lv).ms = mstring_concat((yyvsp[-3].lv).ms, (yyval.lv).ms);
            }
            else if ((yyvsp[-3].lv).rtyp==UNKNOWN) {
                (yyval.lv).ms = mstring_init_string("!!!sorry but not implemented!!!");
            }
            else
                (yyval.lv).ms = mstring_init_string("!!!sorry but not implemented!!!");
/*             omFree((ADDRESS)$1); */
/*             omFree((ADDRESS)$3); */
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "elemexpr \'(\' exprlist \')\'", (yyval.lv).ms);
#endif
#else           
            if ((yyvsp[-3].lv).next==NULL)
            {
              (yyvsp[-3].lv).next=(leftv)omAllocBin(sleftv_bin);
              memcpy((yyvsp[-3].lv).next,&(yyvsp[-1].lv),sizeof(sleftv));
              if(iiExprArithM(&(yyval.lv),&(yyvsp[-3].lv),'(')) YYERROR;
            }
            else if ((yyvsp[-3].lv).rtyp==UNKNOWN)
            { // for x(i)(j)
              if(iiExprArith2(&(yyval.lv),&(yyvsp[-3].lv),'(',&(yyvsp[-1].lv))) YYERROR;
            }
            else YYERROR;
#endif
          }
#line 2997 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 1005 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (currRingHdl==NULL) MYYERROR("no ring active");
            int j = 0;
            memset(&(yyval.lv),0,sizeof(sleftv));
            (yyval.lv).rtyp=VECTOR_CMD;
            leftv v = &(yyvsp[-1].lv);
            while (v!=NULL)
            {
              int i,t;
              sleftv tmp;
              memset(&tmp,0,sizeof(tmp));
              i=iiTestConvert((t=v->Typ()),POLY_CMD);
              if((i==0) || (iiConvert(t /*v->Typ()*/,POLY_CMD,i,v,&tmp)))
              {
                pDelete((poly *)&(yyval.lv).data);
                (yyvsp[-1].lv).CleanUp();
                MYYERROR("expected '[poly,...'");
              }
              poly p = (poly)tmp.CopyD(POLY_CMD);
              pSetCompP(p,++j);
              (yyval.lv).data = (void *)pAdd((poly)(yyval.lv).data,p);
              v->next=tmp.next;tmp.next=NULL;
              tmp.CleanUp();
              v=v->next;
            }
            (yyvsp[-1].lv).CleanUp();
          }
#line 3029 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 1033 "grammartranslator.y" /* yacc.c:1646  */
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            int i = atoi((yyvsp[0].name));
            /*remember not to omFree($1)
            *because it is a part of the scanner buffer*/
            (yyval.lv).rtyp  = INT_CMD;
            (yyval.lv).data = (void *)(long)i;

            /* check: out of range input */
            int l = strlen((yyvsp[0].name))+2;
            number n;
            if (l >= MAX_INT_LEN)
            {
              char tmp[MAX_INT_LEN+5];
              sprintf(tmp,"%d",i);
              if (strcmp(tmp,(yyvsp[0].name))!=0)
              {
                n_Read((yyvsp[0].name),&n,coeffs_BIGINT);
                (yyval.lv).rtyp=BIGINT_CMD;
                (yyval.lv).data = n;
              }
            }
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = mstring_init_string((yyvsp[0].name));
            
//             if ( ((int) currentVoice->ring_decl)==1)
//                 $$.ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", $$.ms, "\")), _singular_actual_ring)" );
                
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "INT_CONST", (yyval.lv).ms);
#endif
#endif
          }
#line 3068 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 1068 "grammartranslator.y" /* yacc.c:1646  */
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            (yyval.lv).rtyp = (yyvsp[0].i);
            (yyval.lv).data = (yyval.lv).Data();
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "SYSVAR");
            printf("\n");
#endif
#endif
          }
#line 3085 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 1081 "grammartranslator.y" /* yacc.c:1646  */
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            (yyval.lv).rtyp  = STRING_CMD;
            (yyval.lv).data = (yyvsp[0].name);
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "stringexpr");
            printf("\n");
#endif
#endif
          }
#line 3102 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 1094 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "PROC_CMD \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3117 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 1105 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3125 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 1109 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArithM(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3133 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 1113 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArithM(&(yyval.lv),NULL,(yyvsp[-2].i))) YYERROR;
          }
#line 3141 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 1117 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3149 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 1121 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArithM(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3157 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 1125 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArithM(&(yyval.lv),NULL,(yyvsp[-2].i))) YYERROR;
          }
#line 3165 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 1129 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_1 \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3180 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 1140 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_12 \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3195 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 1151 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_13 \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3210 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 1162 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3218 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 1166 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-3].lv),(yyvsp[-5].i),&(yyvsp[-1].lv),TRUE)) YYERROR;
          }
#line 3226 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 1170 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-3].lv),(yyvsp[-5].i),&(yyvsp[-1].lv),TRUE)) YYERROR;
          }
#line 3234 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 1174 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-3].lv),(yyvsp[-5].i),&(yyvsp[-1].lv),TRUE)) YYERROR;
          }
#line 3242 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 1178 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-3].lv),(yyvsp[-5].i),&(yyvsp[-1].lv),TRUE)) YYERROR;
          }
#line 3250 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 1182 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[-7].i),&(yyvsp[-5].lv),&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
          }
#line 3258 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 1186 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[-7].i),&(yyvsp[-5].lv),&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
          }
#line 3266 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 1190 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[-7].i),&(yyvsp[-5].lv),&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
          }
#line 3274 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 1194 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[-7].i),&(yyvsp[-5].lv),&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
          }
#line 3282 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 1198 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArithM(&(yyval.lv),NULL,(yyvsp[-2].i))) YYERROR;
          }
#line 3290 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 1202 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            int b;
            switch((yyvsp[-3].i)){
                case STD_CMD:
                    (yyval.lv).ms = ms_conc_s_ms_s("m_id_Std(", (yyvsp[-1].lv).ms, ", _singular_actual_ring)");
                    break;
                default:
/*                     $$.ms = ms_conc_s_ms_s("TODO(", $3.ms, ")"); */
                    b=iiExprArithM(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i)); // handle branchTo
                    if (b==TRUE) YYERROR;
                    if (b==2) YYACCEPT;
            }
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "CMD_M \'(\' exprlist \')\'", (yyval.lv).ms);
/*             printf("CMD_M: %d\n", (int) $1); */
/*             printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_M \'(\' exprlist \')\'"); */
            printf("\n");
               
#endif
// #endif
#else
            int b=iiExprArithM(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i)); // handle branchTo
            if (b==TRUE) YYERROR;
            if (b==2) YYACCEPT;
#endif
          }
#line 3323 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 1231 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[-7].i),&(yyvsp[-5].lv),&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
          }
#line 3331 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 1235 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),(yyvsp[-3].i))) YYERROR;
          }
#line 3339 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 1239 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith3(&(yyval.lv),RING_CMD,&(yyvsp[-5].lv),&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
          }
#line 3347 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 1243 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),RING_CMD)) YYERROR;
          }
#line 3355 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 1247 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiARROW(&(yyval.lv),(yyvsp[-2].name),(yyvsp[0].name))) YYERROR;
          }
#line 3363 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 1250 "grammartranslator.y" /* yacc.c:1646  */
    { 
            (yyval.lv) = (yyvsp[-1].lv); 
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "\'(\' exprlist \')\'");
            printf("\n");
#endif
#endif
            }
#line 3378 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 1264 "grammartranslator.y" /* yacc.c:1646  */
    {
// #ifdef JL_TRANSLATOR_GRAMMAR 
//             mstring ms;
//             if (($1.ms)&&($3.ms))
//                 ms = ms_conc_ms_s_ms( $1.ms, ", ", $3.ms);
// #endif
            leftv v = &(yyvsp[-2].lv);
            while (v->next!=NULL)
            {
              v=v->next;
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&((yyvsp[0].lv)),sizeof(sleftv));
            (yyval.lv) = (yyvsp[-2].lv);
#ifdef JL_TRANSLATOR_GRAMMAR 
/*             $$.ms = ms; */
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_listofms(translator_NbRuleTraversed, "exprlist", "exprlist \',\' expr", &(yyval.lv));
#endif
#endif
          }
#line 3405 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 1287 "grammartranslator.y" /* yacc.c:1646  */
    {
            (yyval.lv) = (yyvsp[0].lv);
#ifdef JL_TRANSLATOR_GRAMMAR            
            (yyval.lv).ms = (yyvsp[0].lv).ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "exprlist", "expr", (yyval.lv).ms);
#endif
#endif
          }
#line 3420 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 1300 "grammartranslator.y" /* yacc.c:1646  */
    {
            /*if ($1.typ == eunknown) YYERROR;*/
            (yyval.lv) = (yyvsp[0].lv);
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = (yyvsp[0].lv).ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr", "expr_arithmetic", (yyval.lv).ms);
#endif
#endif
          }
#line 3436 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 1311 "grammartranslator.y" /* yacc.c:1646  */
    { 
            (yyval.lv) = (yyvsp[0].lv); 
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = (yyvsp[0].lv).ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule_ms(translator_NbRuleTraversed, "expr", "elemexpr",(yyval.lv).ms);
#endif
#endif
            }
#line 3451 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 1322 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith3(&(yyval.lv),'[',&(yyvsp[-5].lv),&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
          }
#line 3459 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 1326 "grammartranslator.y" /* yacc.c:1646  */
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-3].lv),'[',&(yyvsp[-1].lv))) YYERROR;
          }
#line 3467 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 1330 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiApply(&(yyval.lv), &(yyvsp[-3].lv), (yyvsp[-1].i), NULL)) YYERROR;
          }
#line 3475 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 1334 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiApply(&(yyval.lv), &(yyvsp[-3].lv), (yyvsp[-1].i), NULL)) YYERROR;
          }
#line 3483 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 1338 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiApply(&(yyval.lv), &(yyvsp[-3].lv), (yyvsp[-1].i), NULL)) YYERROR;
          }
#line 3491 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 1342 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiApply(&(yyval.lv), &(yyvsp[-3].lv), (yyvsp[-1].i), NULL)) YYERROR;
          }
#line 3499 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 1346 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiApply(&(yyval.lv), &(yyvsp[-3].lv), (yyvsp[-1].i), NULL)) YYERROR;
          }
#line 3507 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 1350 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiApply(&(yyval.lv), &(yyvsp[-3].lv), 0, &(yyvsp[-1].lv))) YYERROR;
          }
#line 3515 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 1354 "grammartranslator.y" /* yacc.c:1646  */
    {
            (yyval.lv)=(yyvsp[-1].lv);
          }
#line 3523 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 1358 "grammartranslator.y" /* yacc.c:1646  */
    {
            #ifdef SIQ
            siq++;
            if (siq>0)
            { if (iiExprArith2(&(yyval.lv),&(yyvsp[-3].lv),'=',&(yyvsp[-1].lv))) YYERROR; }
            else
            #endif
            {
              memset(&(yyval.lv),0,sizeof((yyval.lv)));
              (yyval.lv).rtyp=NONE;
              if (iiAssign(&(yyvsp[-3].lv),&(yyvsp[-1].lv))) YYERROR;
            }
            #ifdef SIQ
            siq--;
            #endif
          }
#line 3544 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 1375 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule(translator_NbRuleTraversed, "expr", "assume_start expr \',\' expr quote_end");
            printf("\n");
#endif
#endif
            iiTestAssume(&(yyvsp[-3].lv),&(yyvsp[-1].lv));
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            (yyval.lv).rtyp=NONE;
          }
#line 3561 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 1388 "grammartranslator.y" /* yacc.c:1646  */
    {
            #ifdef SIQ
            siq--;
            #endif
          }
#line 3571 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 1394 "grammartranslator.y" /* yacc.c:1646  */
    {
            #ifdef SIQ
            if (siq<=0) (yyvsp[-1].lv).Eval();
            #endif
            (yyval.lv)=(yyvsp[-1].lv);
            #ifdef SIQ
            siq++;
            #endif
          }
#line 3585 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 1406 "grammartranslator.y" /* yacc.c:1646  */
    {
            #ifdef SIQ
            siq++;
            #endif
          }
#line 3595 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 1414 "grammartranslator.y" /* yacc.c:1646  */
    {
            #ifdef SIQ
            siq++;
            #endif
          }
#line 3605 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 1422 "grammartranslator.y" /* yacc.c:1646  */
    {
            #ifdef SIQ
            siq--;
            #endif
          }
#line 3615 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 1431 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_ipp( (yyvsp[-1].lv).ms );
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr PLUSPLUS     %%prec PLUSPLUS", (yyval.lv).ms);
#endif
#else
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),PLUSPLUS)) YYERROR;
#endif
          }
#line 3632 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 1444 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_imm( (yyvsp[-1].lv).ms );
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr MINUSMINUS     %%prec MINUSMINUS", (yyval.lv).ms);
#endif
#else
            if(iiExprArith1(&(yyval.lv),&(yyvsp[-1].lv),MINUSMINUS)) YYERROR;
#endif
          }
#line 3649 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 1457 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_add( (yyvsp[-2].lv).ms, (yyvsp[0].lv).ms );
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'+\' expr", (yyval.lv).ms);
#endif
#else
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),'+',&(yyvsp[0].lv))) YYERROR;
#endif
          }
#line 3666 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 1470 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_sub( (yyvsp[-2].lv).ms, (yyvsp[0].lv).ms );
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'-\' expr", (yyval.lv).ms);
#endif
#else
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),'-',&(yyvsp[0].lv))) YYERROR;
#endif
          }
#line 3683 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 1483 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms;
            switch((yyvsp[-1].i)){
                case '/':
                    ms = mstring_toJulia_div( (yyvsp[-2].lv).ms, (yyvsp[0].lv).ms );
                    break;
                case '*':
                    ms = mstring_toJulia_mul( (yyvsp[-2].lv).ms, (yyvsp[0].lv).ms );
                    break;
                default:
                    ms = mstring_init_char( (yyvsp[-1].i) );
                    ms = ms_conc_ms_s_ms(ms, "(", (yyvsp[-2].lv).ms);
                    ms = ms_conc_ms_s_ms(ms, ",", (yyvsp[0].lv).ms);
                    ms = mstring_concat( ms, mstring_init_char( ')' ));
            }
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'/\' expr", (yyval.lv).ms);
#endif
#else
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),(yyvsp[-1].i),&(yyvsp[0].lv))) YYERROR;
#endif
          }
#line 3713 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 1509 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_pow( (yyvsp[-2].lv).ms, (yyvsp[0].lv).ms );
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'^\' expr", (yyval.lv).ms);
#endif
#else
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),'^',&(yyvsp[0].lv))) YYERROR;
#endif
          }
#line 3730 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 1522 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_cmp1((yyvsp[-1].i), (yyvsp[-2].lv).ms, (yyvsp[0].lv).ms );
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'<\' expr", (yyval.lv).ms);
#endif
#else
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),(yyvsp[-1].i),&(yyvsp[0].lv))) YYERROR;
#endif
          }
#line 3747 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 1535 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr \'&\' expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),(yyvsp[-1].i),&(yyvsp[0].lv))) YYERROR;
          }
#line 3762 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 1546 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr NOTEQUAL expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),NOTEQUAL,&(yyvsp[0].lv))) YYERROR;
          }
#line 3777 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 1557 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_eqeq((yyvsp[-2].lv).ms, (yyvsp[0].lv).ms );
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr EQUAL_EQUAL expr", (yyval.lv).ms);
#endif
#else
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),EQUAL_EQUAL,&(yyvsp[0].lv))) YYERROR;
#endif
          }
#line 3794 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 1570 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr DOTDOT expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),DOTDOT,&(yyvsp[0].lv))) YYERROR;
          }
#line 3809 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 1581 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr \':\' expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&(yyval.lv),&(yyvsp[-2].lv),':',&(yyvsp[0].lv))) YYERROR;
          }
#line 3824 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 1592 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "NOT expr");
            printf("\n");
#endif
#endif
            if (siq>0)
            { if (iiExprArith1(&(yyval.lv),&(yyvsp[0].lv),NOT)) YYERROR; }
            else
            {
              memset(&(yyval.lv),0,sizeof((yyval.lv)));
              int i; TESTSETINT((yyvsp[0].lv),i);
              (yyval.lv).rtyp  = INT_CMD;
              (yyval.lv).data = (void *)(long)(i == 0 ? 1 : 0);
            }
          }
#line 3847 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 1611 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_uminus((yyvsp[0].lv).ms);
            (yyval.lv).ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "\'-\' expr %%prec UMINUS");
            printf("\n");
#endif
#else
            if(iiExprArith1(&(yyval.lv),&(yyvsp[0].lv),'-')) YYERROR;
#endif
          }
#line 3865 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 1627 "grammartranslator.y" /* yacc.c:1646  */
    {
            (yyval.lv) = (yyvsp[-1].lv); 
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = (yyvsp[-1].lv).ms;
            (yyval.lv).ms = mstring_concat((yyval.lv).ms, mstring_init_string(" = "));
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "left_value", "declare_ip_variable cmdeq", (yyval.lv).ms);
#endif
#endif
        }
#line 3881 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 1639 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = (yyvsp[-1].lv).ms;
            (yyval.lv).ms = mstring_concat((yyval.lv).ms, mstring_init_string(" = "));
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "left_value", "exprlist \'=\'", (yyval.lv).ms);
#endif
#else
            if ((yyvsp[-1].lv).rtyp==0)
            {
              Werror("`%s` is undefined",(yyvsp[-1].lv).Fullname());
              YYERROR;
            }
            else if (((yyvsp[-1].lv).rtyp==MODUL_CMD)
            // matrix m; m[2]=...
            && ((yyvsp[-1].lv).e!=NULL) && ((yyvsp[-1].lv).e->next==NULL))
            {
              MYYERROR("matrix must have 2 indices");
            }
            (yyval.lv) = (yyvsp[-1].lv);
#endif
          }
#line 3909 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 1666 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "extendedid", "UNKNOWN_IDENT");
            printf("name: %s, ring_decl? %d, is defined? %d \n", (yyvsp[0].name), ((int) currentVoice->ring_decl), (int) is_symbol_in_table_of_symbol((yyvsp[0].name)));
            
/*             printf("already defined: \n"); */
#endif
#endif
        }
#line 3925 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 1678 "grammartranslator.y" /* yacc.c:1646  */
    {
            if ((yyvsp[-1].lv).Typ()!=STRING_CMD)
            {
              MYYERROR("string expression expected");
            }
            (yyval.name) = (char *)(yyvsp[-1].lv).CopyD(STRING_CMD);
            (yyvsp[-1].lv).CleanUp();
          }
#line 3938 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 1690 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_mstring((yyvsp[0].lv).ms);
            iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&((yyvsp[0].lv).req_packhdl->idroot));
/*             $$.ms = $2.ms; */
/*             $$.ms = mstring_init_mstring($2.ms); */
            (yyval.lv).ms = ms;
            add_symbol_in_table_of_symbol_mstring((yyval.lv).ms);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "declare_ip_variable", "ROOT_DECL elemexpr", (yyval.lv).ms);
#endif
#else
// #endif
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&((yyvsp[0].lv).req_packhdl->idroot)))
              YYERROR;
#endif
          }
#line 3961 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 1709 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&((yyvsp[0].lv).req_packhdl->idroot)))
              YYERROR;
          }
#line 3970 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 1714 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_mstring((yyvsp[0].lv).ms);
            iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&(currRing->idroot), TRUE);
/*             mstring ms = $2.ms; */
/*             $$.ms = $2.ms; */
            (yyval.lv).ms = ms;
            add_symbol_in_table_of_symbol_mstring((yyval.lv).ms);
            currentVoice->ring_decl = 1;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "declare_ip_variable", "RING_DECL elemexpr", (yyval.lv).ms);
#endif
#else
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&(currRing->idroot), TRUE)) YYERROR;
#endif
          }
#line 3992 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 1732 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_mstring((yyvsp[0].lv).ms);
            iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&(currRing->idroot), TRUE);
            (yyval.lv).ms = ms;
            add_symbol_in_table_of_symbol_mstring((yyval.lv).ms);
            currentVoice->ring_decl = 1;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "declare_ip_variable", "RING_DECL_LIST elemexpr", (yyval.lv).ms);
#endif
#else
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&(currRing->idroot), TRUE)) YYERROR;
#endif
          }
#line 4012 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 1748 "grammartranslator.y" /* yacc.c:1646  */
    {
            int r; TESTSETINT((yyvsp[-4].lv),r);
            int c; TESTSETINT((yyvsp[-1].lv),c);
            leftv v;
            idhdl h;
            if ((yyvsp[-7].i) == MATRIX_CMD)
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[-6].lv),myynest,(yyvsp[-7].i),&(currRing->idroot), TRUE)) YYERROR;
              v=&(yyval.lv);
              h=(idhdl)v->data;
              idDelete(&IDIDEAL(h));
              IDMATRIX(h) = mpNew(r,c);
              if (IDMATRIX(h)==NULL) YYERROR;
            }
            else if ((yyvsp[-7].i) == INTMAT_CMD)
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[-6].lv),myynest,(yyvsp[-7].i),&((yyvsp[-6].lv).req_packhdl->idroot)))
                YYERROR;
              v=&(yyval.lv);
              h=(idhdl)v->data;
              delete IDINTVEC(h);
              IDINTVEC(h) = new intvec(r,c,0);
              if (IDINTVEC(h)==NULL) YYERROR;
            }
            else /* BIGINTMAT_CMD */
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[-6].lv),myynest,(yyvsp[-7].i),&((yyvsp[-6].lv).req_packhdl->idroot)))
                YYERROR;
              v=&(yyval.lv);
              h=(idhdl)v->data;
              delete IDBIMAT(h);
              IDBIMAT(h) = new bigintmat(r, c, coeffs_BIGINT);
              if (IDBIMAT(h)==NULL) YYERROR;
            }
          }
#line 4052 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 1784 "grammartranslator.y" /* yacc.c:1646  */
    {
            if ((yyvsp[-1].i) == MATRIX_CMD)
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&(currRing->idroot), TRUE)) YYERROR;
            }
            else if ((yyvsp[-1].i) == INTMAT_CMD)
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&((yyvsp[0].lv).req_packhdl->idroot)))
                YYERROR;
              leftv v=&(yyval.lv);
              idhdl h;
              do
              {
                 h=(idhdl)v->data;
                 delete IDINTVEC(h);
                 IDINTVEC(h) = new intvec(1,1,0);
                 v=v->next;
              } while (v!=NULL);
            }
            else /* BIGINTMAT_CMD */
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&((yyvsp[0].lv).req_packhdl->idroot)))
                YYERROR;
            }
          }
#line 4082 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 1810 "grammartranslator.y" /* yacc.c:1646  */
    {
            int t=(yyvsp[-2].lv).Typ();
            sleftv r;
            memset(&r,0,sizeof(sleftv));
            if ((BEGIN_RING<t) && (t<END_RING))
            {
              if (iiDeclCommand(&r,&(yyvsp[0].lv),myynest,t,&(currRing->idroot), TRUE))
                YYERROR;
            }
            else
            {
              if (iiDeclCommand(&r,&(yyvsp[0].lv),myynest,t,&((yyvsp[0].lv).req_packhdl->idroot)))
                YYERROR;
            }
            leftv v=&(yyvsp[-2].lv);
            while (v->next!=NULL) v=v->next;
            v->next=(leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&r,sizeof(sleftv));
            (yyval.lv)=(yyvsp[-2].lv);
          }
#line 4107 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 1831 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[0].lv),myynest,(yyvsp[-1].i),&((yyvsp[0].lv).req_packhdl->idroot)))
              YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR            
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "PROC_CMD elemexpr");
            printf("\n");
#endif
#endif
          }
#line 4123 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 1845 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "stringexpr", "STRINGTOK");
            printf("\n");
#endif
#endif        
}
#line 4137 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 1857 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = (yyvsp[0].lv).ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "rlist", "expr", (yyval.lv).ms);
#endif
#endif
        }
#line 4151 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 1867 "grammartranslator.y" /* yacc.c:1646  */
    {
// #ifdef JL_TRANSLATOR_GRAMMAR 
//             mstring ms;
//             if (($2.ms)&&($4.ms))
//                 ms = ms_conc_ms_s_ms( $2.ms, ", ", $4.ms);
// #endif
            leftv v = &(yyvsp[-3].lv);
            while (v->next!=NULL)
            {
/*               v=v->next; */
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&((yyvsp[-1].lv)),sizeof(sleftv));
            (yyval.lv) = (yyvsp[-3].lv);
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_listofms(translator_NbRuleTraversed, "rlist", "\'(\' expr \',\' exprlist \')\'", &(yyval.lv));
#endif
#endif
          }
#line 4177 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 1892 "grammartranslator.y" /* yacc.c:1646  */
    {
          // let rInit take care of any errors
          (yyval.i)=rOrderName((yyvsp[0].name));
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ordername", "UNKNOWN_IDENT");
            printf("\n");
#endif
#endif
        }
#line 4193 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 1907 "grammartranslator.y" /* yacc.c:1646  */
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            intvec *iv = new intvec(2);
            (*iv)[0] = 1;
            (*iv)[1] = (yyvsp[0].i);
            (yyval.lv).rtyp = INTVEC_CMD;
            (yyval.lv).data = (void *)iv;
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = mstring_init_string( rSimpleOrdStr( (yyvsp[0].i) ) );
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "orderelem", "ordername", (yyval.lv).ms);
#endif
#endif
          }
#line 4213 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 1923 "grammartranslator.y" /* yacc.c:1646  */
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            leftv sl = &(yyvsp[-1].lv);
            int slLength;
            {
              slLength =  exprlist_length(sl);
              int l = 2 +  slLength;
              intvec *iv = new intvec(l);
              (*iv)[0] = slLength;
              (*iv)[1] = (yyvsp[-3].i);

              int i = 2;
              while ((i<l) && (sl!=NULL))
              {
                if (sl->Typ() == INT_CMD)
                {
                  (*iv)[i++] = (int)((long)(sl->Data()));
                }
                else if ((sl->Typ() == INTVEC_CMD)
                ||(sl->Typ() == INTMAT_CMD))
                {
                  intvec *ivv = (intvec *)(sl->Data());
                  int ll = 0,l = ivv->length();
                  for (; l>0; l--)
                  {
                    (*iv)[i++] = (*ivv)[ll++];
                  }
                }
                else
                {
                  delete iv;
                  (yyvsp[-1].lv).CleanUp();
                  MYYERROR("wrong type in ordering");
                }
                sl = sl->next;
              }
              (yyval.lv).rtyp = INTVEC_CMD;
              (yyval.lv).data = (void *)iv;
            }
            (yyvsp[-1].lv).CleanUp();
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "orderelem", "ordername \'(\' exprlist \')\'");
            printf("\n");
#endif
#endif
          }
#line 4266 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 1974 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "OrderingList", "orderelem");
            printf("\n");
#endif
#endif
        }
#line 4280 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 1984 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "OrderingList", "orderelem \',\' OrderingList");
            printf("\n");
#endif
#endif
            (yyval.lv) = (yyvsp[-2].lv);
            (yyval.lv).next = (sleftv *)omAllocBin(sleftv_bin);
            memcpy((yyval.lv).next,&(yyvsp[0].lv),sizeof(sleftv));
          }
#line 4297 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 1999 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv).ms = (yyvsp[0].lv).ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "ordering", "orderelem", (yyval.lv).ms);
#endif
#endif
        }
#line 4311 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 2009 "grammartranslator.y" /* yacc.c:1646  */
    {
            (yyval.lv) = (yyvsp[-1].lv);
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_listofms(translator_NbRuleTraversed, "ordering", "\'(\' OrderingList \')\'", &(yyval.lv));
#endif
#endif
          }
#line 4325 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 2021 "grammartranslator.y" /* yacc.c:1646  */
    {
            expected_parms = TRUE;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "cmdeq", "\'=\'");
            printf("\n");
#endif
#endif
          }
#line 4340 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 2035 "grammartranslator.y" /* yacc.c:1646  */
    { (yyval.i) = (yyvsp[0].i); }
#line 4346 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 2037 "grammartranslator.y" /* yacc.c:1646  */
    { (yyval.i) = (yyvsp[0].i); }
#line 4352 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 2039 "grammartranslator.y" /* yacc.c:1646  */
    { (yyval.i) = (yyvsp[0].i); }
#line 4358 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 2054 "grammartranslator.y" /* yacc.c:1646  */
    { newFile((yyvsp[0].name)); omFree((yyvsp[0].name)); }
#line 4364 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 2059 "grammartranslator.y" /* yacc.c:1646  */
    {
            feHelp((yyvsp[-1].name));
            omFree((ADDRESS)(yyvsp[-1].name));
          }
#line 4373 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 2064 "grammartranslator.y" /* yacc.c:1646  */
    {
            feHelp(NULL);
          }
#line 4381 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 2071 "grammartranslator.y" /* yacc.c:1646  */
    {
            singular_example((yyvsp[-1].name));
            omFree((ADDRESS)(yyvsp[-1].name));
          }
#line 4390 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 2079 "grammartranslator.y" /* yacc.c:1646  */
    {
          if (basePack!=(yyvsp[0].lv).req_packhdl)
          {
            if(iiExport(&(yyvsp[0].lv),0,currPack)) YYERROR;
          }
          else
            if (iiExport(&(yyvsp[0].lv),0)) YYERROR;
        }
#line 4403 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 2091 "grammartranslator.y" /* yacc.c:1646  */
    {
          leftv v=&(yyvsp[0].lv);
          if (v->rtyp!=IDHDL)
          {
            if (v->name!=NULL)
            {
               Werror("`%s` is undefined in kill",v->name);
	       omFree((ADDRESS)v->name); v->name=NULL;
            }
            else               WerrorS("kill what ?");
          }
          else
          {
            killhdl((idhdl)v->data,v->req_packhdl);
          }
        }
#line 4424 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 2108 "grammartranslator.y" /* yacc.c:1646  */
    {
          leftv v=&(yyvsp[0].lv);
          if (v->rtyp!=IDHDL)
          {
            if (v->name!=NULL)
            {
               Werror("`%s` is undefined in kill",v->name);
	       omFree((ADDRESS)v->name); v->name=NULL;
            }
            else               WerrorS("kill what ?");
          }
          else
          {
            killhdl((idhdl)v->data,v->req_packhdl);
          }
        }
#line 4445 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 2128 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
          }
#line 4453 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 2132 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
          }
#line 4461 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 2136 "grammartranslator.y" /* yacc.c:1646  */
    {
            if ((yyvsp[-1].i)==QRING_CMD) (yyvsp[-1].i)=RING_CMD;
            list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
          }
#line 4470 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 2141 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
          }
#line 4478 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 2145 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd(RING_CMD,NULL,"// ",TRUE);
          }
#line 4486 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 2149 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
           }
#line 4494 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 2153 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd(PROC_CMD,NULL,"// ",TRUE);
          }
#line 4502 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 2157 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd(0,(yyvsp[-1].lv).Fullname(),"// ",TRUE);
            (yyvsp[-1].lv).CleanUp();
          }
#line 4511 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 2162 "grammartranslator.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
            (yyvsp[-3].lv).CleanUp();
          }
#line 4521 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 2168 "grammartranslator.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
            (yyvsp[-3].lv).CleanUp();
          }
#line 4531 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 2174 "grammartranslator.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
            (yyvsp[-3].lv).CleanUp();
          }
#line 4541 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 2180 "grammartranslator.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
            (yyvsp[-3].lv).CleanUp();
          }
#line 4551 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 2186 "grammartranslator.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
            (yyvsp[-3].lv).CleanUp();
          }
#line 4561 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 2192 "grammartranslator.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
            (yyvsp[-3].lv).CleanUp();
          }
#line 4571 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 2198 "grammartranslator.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[-1].i),NULL,"// ",TRUE);
            (yyvsp[-3].lv).CleanUp();
          }
#line 4581 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 2210 "grammartranslator.y" /* yacc.c:1646  */
    {
            list_cmd(-1,NULL,"// ",TRUE);
          }
#line 4589 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 2216 "grammartranslator.y" /* yacc.c:1646  */
    { 
       yyInRingConstruction = TRUE; 
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd1", "RING_CMD");
            printf("\n");
#endif
#endif
       }
#line 4604 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 2234 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            /*construct strings before args are cleaned*/
            add_symbol_in_table_of_symbol_mstring((yyvsp[-6].lv).ms);
            mstring r_name  = (yyvsp[-6].lv).ms;
            mstring r_name2 = mstring_init_mstring(r_name);
            mstring r_field = mstring_toJulia_coeffs(&(yyvsp[-4].lv));
            /* add vars in symbol table */
            /*add_symbol_in_table_of_symbol_mstring($6.ms);
            leftv voyager = &$6;
            while (voyager->next!=NULL){
                add_symbol_in_table_of_symbol_mstring(voyager->next->ms);
                voyager = voyager->next;
            }*/
            /* end add vars in symbol table */
            mstring r_vars  = mstring_toJulia_vars(&(yyvsp[-2].lv));
            mstring r_ord   = mstring_toJulia_ordering(&(yyvsp[0].lv));
/*             $$.ms = mstring_init_string("Sorry, not implemented"); */
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            char * field = mstring_to_str( r_field );
            printf("field: %s\n", field);
            free(field);
            char * vars = mstring_to_str( r_vars );
            printf("vars: %s\n", vars);
            free(vars);
            char * orde = mstring_to_str( r_ord );
            printf("orde: %s\n", orde);
            free(orde);
#endif            
            (yyval.lv).ms = ms_conc_ms_s_ms(r_field, ",\n", r_vars);
            (yyval.lv).ms = ms_conc_ms_s_ms((yyval.lv).ms, ",\n", r_ord);
            if ((&(yyvsp[0].lv))->listLength() == 1)
                (yyval.lv).ms = ms_conc_s_ms_s ("libSingular.rDefault(", (yyval.lv).ms, ")");
            else 
                (yyval.lv).ms = ms_conc_s_ms_s ("libSingular.rDefault(", (yyval.lv).ms, ", [Int32(1)], [Int32(1)])");
            (yyval.lv).ms = ms_conc_ms_s_ms (r_name, "=", (yyval.lv).ms);
            (yyval.lv).ms = ms_conc_ms_s_ms ((yyval.lv).ms, "\n _singular_actual_ring = ", r_name2);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr cmdeq rlist \',\' rlist \',\' ordering", (yyval.lv).ms);
#endif
#endif
            const char *ring_name = (yyvsp[-6].lv).name;
            ring b=
            rInit(&(yyvsp[-4].lv),            /* characteristik and list of parameters*/
                  &(yyvsp[-2].lv),            /* names of ringvariables */
                  &(yyvsp[0].lv));            /* ordering */
            idhdl newRingHdl=NULL;

            if (b!=NULL)
            {
              newRingHdl=enterid(ring_name, myynest, RING_CMD,
                                   &((yyvsp[-6].lv).req_packhdl->idroot),FALSE);
              (yyvsp[-6].lv).CleanUp();
              if (newRingHdl!=NULL)
              {
                IDRING(newRingHdl)=b;
              }
              else
              {
                rKill(b);
              }
            }
            yyInRingConstruction = FALSE;
            if (newRingHdl==NULL)
            {
              MYYERROR("cannot make ring");
            }
            else
            {
              rSetHdl(newRingHdl);
            }
          }
#line 4682 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 2308 "grammartranslator.y" /* yacc.c:1646  */
    {
            const char *ring_name = (yyvsp[0].lv).name;
            if (!inerror) rDefault(ring_name);
            yyInRingConstruction = FALSE;
            (yyvsp[0].lv).CleanUp();
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr");
            printf("\n");
#endif
#endif
          }
#line 4700 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 2322 "grammartranslator.y" /* yacc.c:1646  */
    {
            yyInRingConstruction = FALSE;
            if (iiAssignCR(&(yyvsp[-2].lv),&(yyvsp[0].lv))) YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr cmdeq elemexpr");
            printf("\n");
#endif
#endif
          }
#line 4716 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 2334 "grammartranslator.y" /* yacc.c:1646  */
    {
          yyInRingConstruction = FALSE;
          sleftv tmp;
          (yyvsp[-3].lv).next=(leftv)omAlloc(sizeof(sleftv));
          memcpy((yyvsp[-3].lv).next,&(yyvsp[-1].lv),sizeof(sleftv));
          memset(&(yyvsp[-1].lv),0,sizeof(sleftv));
          if (iiExprArithM(&tmp,&(yyvsp[-3].lv),'[')) YYERROR;
          if (iiAssignCR(&(yyvsp[-5].lv),&tmp)) YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr cmdeq elemexpr \'[\' exprlist \']\'");
            printf("\n");
#endif
#endif
        }
#line 4737 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 2354 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (((yyvsp[-1].i)!=LIB_CMD)||(jjLOAD((yyvsp[0].name),TRUE))) YYERROR;
          }
#line 4745 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 2363 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (((yyvsp[-1].i)==KEEPRING_CMD) && (myynest==0))
               MYYERROR("only inside a proc allowed");
            const char * n=(yyvsp[0].lv).Name();
            if (((yyvsp[0].lv).Typ()==RING_CMD)
            && ((yyvsp[0].lv).rtyp==IDHDL))
            {
              idhdl h=(idhdl)(yyvsp[0].lv).data;
              if ((yyvsp[0].lv).e!=NULL) h=rFindHdl((ring)(yyvsp[0].lv).Data(),NULL);
              //Print("setring %s lev %d (ptr:%x)\n",IDID(h),IDLEV(h),IDRING(h));
              if ((yyvsp[-1].i)==KEEPRING_CMD)
              {
                if (h!=NULL)
                {
                  if (IDLEV(h)!=0)
                  {
                    if (iiExport(&(yyvsp[0].lv),myynest-1)) YYERROR;
#if 1
                    idhdl p=IDRING(h)->idroot;
                    idhdl root=p;
                    int prevlev=myynest-1;
                    while (p!=NULL)
                    {
                      if (IDLEV(p)==myynest)
                      {
                        idhdl old=root->get(IDID(p),prevlev);
                        if (old!=NULL)
                        {
                          if (BVERBOSE(V_REDEFINE))
                            Warn("redefining %s",IDID(p));
                          killhdl2(old,&root,IDRING(h));
                          IDRING(h)->idroot=root;
                        }
                        IDLEV(p)=prevlev;
                      }
                      p=IDNEXT(p);
                    }
#endif
                  }
                  iiLocalRing[myynest-1]=IDRING(h);
                }
                else
                {
                  Werror("%s is no identifier",n);
                  (yyvsp[0].lv).CleanUp();
                  YYERROR;
                }
              }
              if (h!=NULL) rSetHdl(h);
              else
              {
                Werror("cannot find the name of the basering %s",n);
                (yyvsp[0].lv).CleanUp();
                YYERROR;
              }
              (yyvsp[0].lv).CleanUp();
            }
            else
            {
              Werror("%s is no name of a ring/qring",n);
              (yyvsp[0].lv).CleanUp();
              YYERROR;
            }
          }
#line 4814 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 2431 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "typecmd", "TYPE_CMD expr");
            printf("\n");
#endif
#else
            type_cmd(&((yyvsp[0].lv)));
#endif
          }
#line 4830 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 2443 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "typecmd", "exprlist");
            printf("\n");
#endif
#else
            //Print("typ is %d, rtyp:%d\n",$1.Typ(),$1.rtyp);
            #ifdef SIQ
            if ((yyvsp[0].lv).rtyp!=COMMAND)
            {
            #endif
              if ((yyvsp[0].lv).Typ()==UNKNOWN)
              {
                if ((yyvsp[0].lv).name!=NULL)
                {
                  Werror("`%s` is undefined",(yyvsp[0].lv).name);
                  omFree((ADDRESS)(yyvsp[0].lv).name);
                }
                YYERROR;
              }
            #ifdef SIQ
            }
            #endif
            (yyvsp[0].lv).Print(&sLastPrinted);
            (yyvsp[0].lv).CleanUp(currRing);
            if (errorreported) YYERROR;
#endif
          }
#line 4865 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 2480 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
/*             printf("waitingForEnd: %d\n", currentVoice->waitingForEnd); */
            char * iftrueblock  = (char *) omAlloc (strlen((yyvsp[0].name))+50);
            sprintf(iftrueblock, "%s\njulia_endproc\n", (yyvsp[0].name));
/*             sprintf(iftrueblock, "%s\n", $5); */
            omFree((ADDRESS)(yyvsp[0].name));
#else
            int i; TESTSETINT((yyvsp[-2].lv),i);
            if (i!=0)
            {
              newBuffer( (yyvsp[0].name), BT_if);
            }
            else
            {
              omFree((ADDRESS)(yyvsp[0].name));
              currentVoice->ifsw=1;
            }
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if (!((yyvsp[-2].lv).ms)) (yyvsp[-2].lv).ms = mstring_init_char(' ');
            (yyval.lv).ms = ms_conc_s_ms_s( "if ( ", (yyvsp[-2].lv).ms, " )" );
            (yyval.lv).ms = mstring_dedent((yyval.lv).ms, 1);
/*             currentVoice->waitingForEnd=1; */
/*             printf("waitingForEnd: %d\n", currentVoice->waitingForEnd); */
            newBuffer( iftrueblock, BT_proc );
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "ifcmd", "IF_CMD \'(\' expr \')\' BLOCKTOK", (yyval.lv).ms);
#endif
#endif
          }
#line 4902 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 2513 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            char * iftrueblock  = (char *) omAlloc (strlen((yyvsp[-2].name))+strlen((yyvsp[0].name))+50);
            sprintf(iftrueblock, "%s\n else {\n%s} \njulia_endproc\n", (yyvsp[-2].name), (yyvsp[0].name) );
            printf("%s\n", iftrueblock);
            omFree((ADDRESS)(yyvsp[-2].name));
            omFree((ADDRESS)(yyvsp[0].name));
#else
            int i; TESTSETINT((yyvsp[-4].lv),i);
            if (i!=0)
            {
              newBuffer( (yyvsp[-2].name), BT_if);
            }
            else
            {
              omFree((ADDRESS)(yyvsp[-2].name));
              currentVoice->ifsw=1;
            }
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
          translator_NbRuleTraversed++;
            if (!((yyvsp[-4].lv).ms)) (yyvsp[-4].lv).ms = mstring_init_char(' ');
            (yyval.lv).ms = ms_conc_s_ms_s( "if ( ", (yyvsp[-4].lv).ms, " )" );
            (yyval.lv).ms = mstring_dedent((yyval.lv).ms, 1);
          newBuffer( iftrueblock, BT_proc );
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
          printfrule_ms(translator_NbRuleTraversed, "ifcmd", "IF_CMD \'(\' expr \')\' BLOCKTOK ELSE_CMD BLOCKTOK", (yyval.lv).ms);
#endif
#endif
          }
#line 4937 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 2544 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            char * elseblock  = (char *) omAlloc (strlen((yyvsp[0].name))+50);
/*             sprintf(elseblock, "%s\njulia_endproc\n", $2); */
            sprintf(elseblock, "%s", (yyvsp[0].name));
            omFree((ADDRESS)(yyvsp[0].name));
#else
            if (currentVoice->ifsw==1)
            {
              currentVoice->ifsw=0;
              newBuffer( (yyvsp[0].name), BT_else);
            }
            else
            {
              if (currentVoice->ifsw!=2)
              {
                Warn("`else` without `if` in level %d",myynest);
              }
              omFree((ADDRESS)(yyvsp[0].name));
            }
            currentVoice->ifsw=0;
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
          translator_NbRuleTraversed++;
          (yyval.lv).ms = mstring_init_string( "else " );
          (yyval.lv).ms = mstring_dedent((yyval.lv).ms, 1);
          newBuffer( elseblock, BT_proc );
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
          printfrule_ms(translator_NbRuleTraversed, "ifcmd", "ELSE_CMD BLOCKTOK", (yyval.lv).ms);
#endif
#endif
          }
#line 4974 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 2577 "grammartranslator.y" /* yacc.c:1646  */
    {
            int i; TESTSETINT((yyvsp[-2].lv),i);
            if (i)
            {
              if (exitBuffer(BT_break)) YYERROR;
            }
            currentVoice->ifsw=0;
          }
#line 4987 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 2586 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (exitBuffer(BT_break)) YYERROR;
            currentVoice->ifsw=0;
          }
#line 4996 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 2591 "grammartranslator.y" /* yacc.c:1646  */
    {
            if (contBuffer(BT_break)) YYERROR;
            currentVoice->ifsw=0;
          }
#line 5005 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 2599 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            
            char * whilehead  = (char *) omAlloc (10);
            sprintf(whilehead, "while");
            char * whilebody  = (char *) omAlloc (strlen((yyvsp[-1].name))+strlen((yyvsp[0].name))+50);
            sprintf(whilebody, "%s;\n%s\njulia_endloop\n", (yyvsp[-1].name), (yyvsp[0].name));
#else
            /* -> if(!$2) break; $3; continue;*/
            char * s = (char *)omAlloc( strlen((yyvsp[-1].name)) + strlen((yyvsp[0].name)) + 36);
            sprintf(s,"whileif (!(%s)) break;\n%scontinue;\n " ,(yyvsp[-1].name),(yyvsp[0].name));
            newBuffer(s,BT_break);
#endif
            omFree((ADDRESS)(yyvsp[-1].name));
            omFree((ADDRESS)(yyvsp[0].name));
#ifdef JL_TRANSLATOR_GRAMMAR
            newBuffer( whilebody, BT_break );
            (yyval.lv).ms = mstring_init_string( whilehead );
            (yyval.lv).ms = mstring_dedent((yyval.lv).ms, 1);
            omFree(whilehead);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "whilecmd", "WHILE_CMD STRINGTOK BLOCKTOK", (yyval.lv).ms);
#endif
#endif            
          }
#line 5036 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 2629 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            /* rewrite it as a while loop */
            char * prelimina  = (char *) omAlloc (strlen((yyvsp[-3].name))+50);
            sprintf(prelimina, "%s;", (yyvsp[-3].name));
            char * whilehead  = (char *) omAlloc (strlen((yyvsp[-2].name))+50);
            sprintf(whilehead, "while (%s)", (yyvsp[-2].name));
            char * whilebody  = (char *) omAlloc (strlen((yyvsp[-1].name))+strlen((yyvsp[0].name))+50);
            sprintf(whilebody, "{%s%s;}", (yyvsp[0].name), (yyvsp[-1].name));
            char * whileloop  = (char *) omAlloc (strlen(prelimina) + strlen(whilehead) + strlen(whilebody) + 50);
            sprintf(whileloop, "%s %s %s", prelimina, whilehead, whilebody);
/*             printf("prelimina:  %s\n", prelimina); */
/*             printf("whilehead:  %s\n", whilehead); */
/*             printf("whilebody:  %s\n", whilebody); */
/*             printf("whileloop:  %s\n", whileloop); */
            omFree(prelimina); omFree(whilehead); omFree(whilebody);
#else
            /* $2 */
            /* if (!$3) break; $5; $4; continue; */
            char * s = (char *)omAlloc( strlen((yyvsp[-2].name))+strlen((yyvsp[-1].name))+strlen((yyvsp[0].name))+36);
            sprintf(s,"forif (!(%s)) break;\n%s%s;\ncontinue;\n "
                   ,(yyvsp[-2].name),(yyvsp[0].name),(yyvsp[-1].name));
            newBuffer(s,BT_break);
            s = (char *)omAlloc( strlen((yyvsp[-3].name)) + 3);
            sprintf(s,"%s;\n",(yyvsp[-3].name));
            newBuffer(s,BT_if);
#endif            
            omFree((ADDRESS)(yyvsp[-3].name));
            omFree((ADDRESS)(yyvsp[-2].name));
            omFree((ADDRESS)(yyvsp[-1].name));
            omFree((ADDRESS)(yyvsp[0].name));
#ifdef JL_TRANSLATOR_GRAMMAR
            newBuffer( whileloop, BT_break );
            (yyval.lv).ms = mstring_init_string( " " );
/*             $$.ms = mstring_dedent($$.ms, 1); */
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "forcmd", "FOR_CMD STRINGTOK STRINGTOK STRINGTOK BLOCKTOK");
            printf("\n");
#endif
#endif            
          }
#line 5083 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 2675 "grammartranslator.y" /* yacc.c:1646  */
    {
            idhdl h = enterid((yyvsp[-1].name),myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL) {omFree((ADDRESS)(yyvsp[-1].name));omFree((ADDRESS)(yyvsp[0].name)); YYERROR;}
            iiInitSingularProcinfo(IDPROC(h),"", (yyvsp[-1].name), 0, 0);
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen((yyvsp[0].name))+31);;
            sprintf(IDPROC(h)->data.s.body,"parameter list #;\n%s;return();\n\n",(yyvsp[0].name));
            omFree((ADDRESS)(yyvsp[0].name));
            omFree((ADDRESS)(yyvsp[-1].name));
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "proccmd", "PROC_CMD extendedid BLOCKTOK");
            printf("\n");
#endif
#endif
          }
#line 5104 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 2692 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
/*             printf(" $1: %s, $2: %s, $3: %s \n", $1, $2, $3); */
/*             printf("\n"); */
/*             printf(" $2: %s, len: %d\n", $2, strlen($2)); */
            add_symbol_in_table_of_symbol_string((yyvsp[-2].name));
            char * funcname  = (char *) omAlloc (strlen((yyvsp[-2].name))+15);
            char * funcargt  = iiProcArgs((yyvsp[-1].name),FALSE);
            char * funcargs  = (char *) omAlloc (strlen(funcargt)+2);
            if (strlen(funcargt)>0){
                sprintf(funcname, "function %s(", (yyvsp[-2].name));
                sprintf(funcargs, "(%s)", funcargt);
            }
            else {
                sprintf(funcname, "function %s()", (yyvsp[-2].name));
                sprintf(funcargs, "%s", funcargt);
            }
            char * funcbody  = (char *) omAlloc (strlen(funcargs)+strlen((yyvsp[0].name))+14);
            sprintf(funcbody, "%s\n%s\njulia_endproc\n", funcargs, (yyvsp[0].name));
/*             printf(" functionargt: %s, len: %d\n", funcargt, strlen(funcargt)); */
/*             printf(" functionargs: %s, len: %d\n", funcargs, strlen(funcargs)); */
/*             printf(" functionbody: %s, len: %d\n", funcbody, strlen(funcbody)); */
            omFree(funcargt);
            omFree(funcargs);
#endif
            idhdl h = enterid((yyvsp[-2].name),myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL)
            {
              omFree((ADDRESS)(yyvsp[-2].name));
              omFree((ADDRESS)(yyvsp[-1].name));
              omFree((ADDRESS)(yyvsp[0].name));
              YYERROR;
            }
            char *args=iiProcArgs((yyvsp[-1].name),FALSE);
            omFree((ADDRESS)(yyvsp[-1].name));
            iiInitSingularProcinfo(IDPROC(h),"", (yyvsp[-2].name), 0, 0);
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen((yyvsp[0].name))+strlen(args)+14);;
            sprintf(IDPROC(h)->data.s.body,"%s\n%s;return();\n\n",args,(yyvsp[0].name));
            omFree((ADDRESS)args);
            omFree((ADDRESS)(yyvsp[0].name));
            omFree((ADDRESS)(yyvsp[-2].name));
#ifdef JL_TRANSLATOR_GRAMMAR
            newBuffer( funcbody, BT_proc );
            (yyval.lv).ms = mstring_init_string( funcname );
            (yyval.lv).ms = mstring_dedent((yyval.lv).ms, 1);
            omFree(funcname);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "proccmd", "PROC_DEF STRINGTOK BLOCKTOK", (yyval.lv).ms);
#endif
#endif
          }
#line 5161 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 2745 "grammartranslator.y" /* yacc.c:1646  */
    {
            omFree((ADDRESS)(yyvsp[-1].name));
            idhdl h = enterid((yyvsp[-3].name),myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL)
            {
              omFree((ADDRESS)(yyvsp[-3].name));
              omFree((ADDRESS)(yyvsp[-2].name));
              omFree((ADDRESS)(yyvsp[0].name));
              YYERROR;
            }
            char *args=iiProcArgs((yyvsp[-2].name),FALSE);
            omFree((ADDRESS)(yyvsp[-2].name));
            iiInitSingularProcinfo(IDPROC(h),"", (yyvsp[-3].name), 0, 0);
            omFree((ADDRESS)(yyvsp[-3].name));
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen((yyvsp[0].name))+strlen(args)+14);;
            sprintf(IDPROC(h)->data.s.body,"%s\n%s;return();\n\n",args,(yyvsp[0].name));
            omFree((ADDRESS)args);
            omFree((ADDRESS)(yyvsp[0].name));
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "proccmd", "PROC_DEF STRINGTOK STRINGTOK BLOCKTOK");
            printf("\n");
#endif
#endif
          }
#line 5192 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 2775 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ((yyvsp[0].lv).Typ() == INT_CMD){
                (yyvsp[0].lv).ms = mstring_concat( (yyvsp[0].lv).ms, mstring_init_string("::Int32") );
            }
            else if ((yyvsp[0].lv).Typ() == BIGINT_CMD) {
                (yyvsp[0].lv).ms = mstring_concat( (yyvsp[0].lv).ms, mstring_init_string("::BigInt") );
            }
//             else {
//                 $$.ms = $2.ms;
//             }
            (yyval.lv).ms = (yyvsp[0].lv).ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "parametercmd", "PARAMETER declare_ip_variable", (yyval.lv).ms);
#endif
#else
            // decl. of type proc p(int i)
            if ((yyvsp[-1].i)==PARAMETER)  { if (iiParameter(&(yyvsp[0].lv))) YYERROR; }
            else                { if (iiAlias(&(yyvsp[0].lv))) YYERROR; }
#endif
          }
#line 5219 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 2798 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ((yyvsp[-1].lv).Typ() == INT_CMD){
                (yyvsp[-1].lv).ms = mstring_concat( (yyvsp[-1].lv).ms, mstring_init_string("::Int") );
            }
            else if ((yyvsp[-1].lv).Typ() == BIGINT_CMD) {
                (yyvsp[-1].lv).ms = mstring_concat( (yyvsp[-1].lv).ms, mstring_init_string("::BigInt") );
            }
//             else {
//                 $$.ms = $2.ms;
//             }
            (yyval.lv).ms = (yyvsp[-1].lv).ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "parametercmd", "PARAMETER declare_ip_variable \';\'", (yyval.lv).ms);
#endif
#endif
          }
#line 5242 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 2817 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "parametercmd", "PARAMETER expr");
            printf("\n");
#endif
#endif
            // decl. of type proc p(i)
            sleftv tmp_expr;
            if ((yyvsp[-1].i)==ALIAS_CMD) MYYERROR("alias requires a type");
            if ((iiDeclCommand(&tmp_expr,&(yyvsp[0].lv),myynest,DEF_CMD,&IDROOT))
            || (iiParameter(&tmp_expr)))
              YYERROR;
          }
#line 5262 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 2836 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            char * expr_str;
            if ((yyvsp[-1].lv).ms) expr_str = mstring_to_str( (yyvsp[-1].lv).ms ); //TODO: not sure it is safe
            else expr_str = setUninitialized();
            (yyval.lv).ms = mstring_concat( mstring_init_string("return "), mstring_init_string(expr_str) );
            free(expr_str);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "returncmd", "RETURN \'(\' exprlist \')\'", (yyval.lv).ms);
#endif
#endif

#ifdef JL_TRANSLATOR_GRAMMAR
//             iiRETURNEXPR.Copy(&$3);
//             $3.CleanUp();
//             if (exitBuffer(BT_proc)) YYERROR;
#endif
          }
#line 5286 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 2856 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "returncmd", "RETURN \'(\' \')\'");
            printf("\n");
#endif
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
            if ((yyvsp[-2].i)==RETURN)
            {
              iiRETURNEXPR.Init();
              iiRETURNEXPR.rtyp=NONE;
              if (exitBuffer(BT_proc)) YYERROR;
            }
#endif
          }
#line 5308 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 2876 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            (yyval.lv) = (yyvsp[0].lv);
            (yyval.lv).ms = (yyvsp[0].lv).ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule_ms(translator_NbRuleTraversed, "listparametercmd", "parametercmd", (yyval.lv).ms);
#endif
#endif
        }
#line 5323 "grammartranslator.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 2886 "grammartranslator.y" /* yacc.c:1646  */
    {
#ifdef JL_TRANSLATOR_GRAMMAR
            /*leftv v = &$1;
            while (v->next!=NULL)
            {
              v=v->next;
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&($3),sizeof(sleftv));*/
            (yyval.lv) = (yyvsp[-1].lv);
/*             $$.ms = $1.ms; */
            (yyval.lv).ms = ms_conc_ms_s_ms( (yyvsp[-1].lv).ms, ", ", (yyvsp[0].lv).ms);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule_ms(translator_NbRuleTraversed, "listparametercmd", "listparametercmd parametercmd",(yyval.lv).ms);
#endif
#endif
            }
#line 5346 "grammartranslator.cc" /* yacc.c:1646  */
    break;


#line 5350 "grammartranslator.cc" /* yacc.c:1646  */
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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
