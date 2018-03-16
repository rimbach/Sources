/****************************************
*  Computer Algebra System SINGULAR     *
****************************************/
/*
* ABSTRACT: SINGULAR shell grammatik
*/
%{

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

%}

/* (now it uses JLSTYPE, JLLTYPE,jlparse, jllval
/* instead of YYSTYPE, YYLTYPE, yyparse, yylval) */
%define api.prefix {jl}

/* %expect 22 */
/* %pure_parser */
%pure-parser

/* special symbols */
%token DOTDOT
%token EQUAL_EQUAL
%token GE
%token LE
%token MINUSMINUS
%token NOT
%token NOTEQUAL
%token PLUSPLUS
%token COLONCOLON
%token ARROW

/* types, part 1 (ring indep.)*/
%token <i> GRING_CMD
%token <i> BIGINTMAT_CMD
%token <i> INTMAT_CMD
%token <i> PROC_CMD
%token <i> RING_CMD

/* valid when ring defined ! */
%token <i> BEGIN_RING
/* types, part 2 */
%token <i> IDEAL_CMD
%token <i> MAP_CMD
%token <i> MATRIX_CMD
%token <i> MODUL_CMD
%token <i> NUMBER_CMD
%token <i> POLY_CMD
%token <i> RESOLUTION_CMD
%token <i> VECTOR_CMD
/* end types */

/* ring dependent cmd, with argumnts indep. of a ring*/
%token <i> BETTI_CMD
%token <i> E_CMD
%token <i> FETCH_CMD
%token <i> FREEMODULE_CMD
%token <i> KEEPRING_CMD
%token <i> IMAP_CMD
%token <i> KOSZUL_CMD
%token <i> MAXID_CMD
%token <i> MONOM_CMD
%token <i> PAR_CMD
%token <i> PREIMAGE_CMD
%token <i> VAR_CMD

/*system variables in ring block*/
%token <i> VALTVARS
%token <i> VMAXDEG
%token <i> VMAXMULT
%token <i> VNOETHER
%token <i> VMINPOLY

%token <i> END_RING
/* end of ring definitions */

%token <i> CMD_1
%token <i> CMD_2
%token <i> CMD_3
%token <i> CMD_12
%token <i> CMD_13
%token <i> CMD_23
%token <i> CMD_123
%token <i> CMD_M
%token <i> ROOT_DECL
        /* put variables of this type into the idroot list */
%token <i> ROOT_DECL_LIST
        /* put variables of this type into the idroot list */
%token <i> RING_DECL
        /* put variables of this type into the currRing list */
%token <i> RING_DECL_LIST
        /* put variables of this type into the currRing list */
%token <i> EXAMPLE_CMD
%token <i> EXPORT_CMD
%token <i> HELP_CMD
%token <i> KILL_CMD
%token <i> LIB_CMD
%token <i> LISTVAR_CMD
%token <i> SETRING_CMD
%token <i> TYPE_CMD

%token <name> STRINGTOK BLOCKTOK INT_CONST
%token <name> UNKNOWN_IDENT RINGVAR PROC_DEF

/* control */
%token <i> APPLY
%token <i> ASSUME_CMD
%token <i> BREAK_CMD
%token <i> CONTINUE_CMD
%token <i> ELSE_CMD
%token <i> EVAL
%token <i> QUOTE
%token <i> FOR_CMD
%token <i> IF_CMD
%token <i> SYS_BREAK
%token <i> WHILE_CMD
%token <i> RETURN
%token <i> PARAMETER

/* system variables */
%token <i> SYSVAR

%type <name> extendedid
%type <lv>   rlist ordering OrderingList orderelem
%type <name> stringexpr
%type <lv>   expr elemexpr exprlist expr_arithmetic
%type <lv>   declare_ip_variable left_value
%type <i>    error
%type <i>    ordername
%type <i>    cmdeq
%type <i>    setrings
%type <i>    ringcmd1
%type <i>    mat_cmd

%type <i>    '=' '<' '>' '+' '-' COLONCOLON
%type <i>    '/' '[' ']' '^' ',' ';'

/*#ifdef JL_TRANSLATOR_GRAMMAR*/
%type <lv> assign 
%type <lv> command 
%type <lv> exportcmd killcmd listcmd parametercmd ringcmd scriptcmd setringcmd typecmd
%type <lv> pprompt
%type <lv> flowctrl ifcmd whilecmd example_dummy forcmd proccmd filecmd helpcmd
%type <lv> returncmd
%type <lv> listparametercmd
/*#endif*/

/*%nonassoc '=' PLUSEQUAL DOTDOT*/
/*%nonassoc '=' DOTDOT COLONCOLON*/
%nonassoc '='
%left ','
%left '&'
%left EQUAL_EQUAL NOTEQUAL
%left '<'
%nonassoc DOTDOT
%left '+' '-' ':'
%left '/'
%left UMINUS NOT
%left  '^'
%left '[' ']'
%left '(' ')'
%left PLUSPLUS MINUSMINUS
%left COLONCOLON
%left '.'
%left ARROW

/* #ifdef JL_TRANSLATOR_GRAMMAR */
%token <i> JULIA_ENDELSE_CMD
%token <i> JULIA_ENDIF_CMD
%token <i> JULIA_ENDLOOP_CMD
%token <i> JULIA_ENDPROC_CMD
/* #endif */

%%
lines:
        /**/
        | lines pprompt
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
            if ($2.ms) $2.ms = mstring_indent($2.ms, depth);
            /*{
                for (int i = 0; i<depth*3; i++)
                    $2.ms = mstring_concat( mstring_init_string(" "), $2.ms );
                disp = mstring_to_str( $2.ms );
            }*/
            if ($2.ms) disp = mstring_to_str( $2.ms );
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
            if ($2.ms) mstring_free($2.ms);
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
        ;
        
pprompt:
        flowctrl {                      /* if, while, for, proc */
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "flowctrl");
            printf("\n");
#endif
#endif        
        }
        | command ';'                  /* commands returning no value */
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ($1.ms) $$.ms = $1.ms;
            else $$.ms = mstring_init_string(uninitialized);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "pprompt", "command \';\'", $$.ms);
#endif
#endif
            currentVoice->ifsw=0;
           }
        | declare_ip_variable ';' {     /* default initialization */
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ($1.ms) $$.ms = mstring_concat($1.ms, mstring_init_string(";"));
            else $$.ms = mstring_init_string(uninitialized);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "pprompt", "declare_ip_variable \';\'", $$.ms);
#endif
#endif            
          $1.CleanUp(); currentVoice->ifsw=0;   
          }
        | returncmd
          {
/*             YYACCEPT; */
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            $$.ms = $1.ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "returncmd");
            printf("\n");
#endif
#endif
          }
        | SYS_BREAK
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
        | ';' {                    /* ignore empty statements */
          currentVoice->ifsw=0;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", ";");
            printf("\n");
#endif
#endif          
          }
        | error ';'
          {
            #ifdef SIQ
            siq=0;
            #endif
            yyInRingConstruction = FALSE;
            currentVoice->ifsw=0;
            if (inerror)
            {
/*  bison failed here*/
              if ((inerror!=3) && ($1<UMINUS) && ($1>' '))
              {
                // 1: yyerror called
                // 2: scanner put actual string
                // 3: error rule put token+\n
                inerror=3;
                Print(" error at token `%s`\n",iiTwoOps($1));
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
          | JULIA_ENDELSE_CMD {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            $$.ms = mstring_init_string("end");
/*             mstring_dedent($$.ms, 1); */
            exitBuffer(BT_else);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDELSE_CMD");
            printf("\n");
#endif
#endif
          }
          | JULIA_ENDIF_CMD {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            $$.ms = mstring_init_string("end");
/*             mstring_dedent($$.ms, 1); */
            exitBuffer(BT_if);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDIF_CMD");
            printf("\n");
#endif
#endif
          }
          | JULIA_ENDLOOP_CMD {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            $$.ms = mstring_init_string("end");
            exitBuffer(BT_break);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDLOOP_CMD");
            printf("\n");
#endif
#endif
          }
          | JULIA_ENDPROC_CMD {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            $$.ms = mstring_init_string("end");
            exitBuffer(BT_proc);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "JULIA_ENDPROC_CMD");
            printf("\n");
#endif
#endif
          }
          | '(' listparametercmd ')' {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
/*             $$.ms = ms_conc_s_ms_s("(", $2.ms, ")"); */
            $$.ms = mstring_concat($2.ms, mstring_init_string(")"));
/*             exitBuffer(BT_proc); */
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "pprompt", "listparametercmd");
            printf("\n");
#endif
#endif
          }
          
        ;

flowctrl: ifcmd { 
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "ifcmd");
            printf("\n");
#endif
#endif
          }
          | whilecmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "whilecmd");
            printf("\n");
#endif
#endif
          }
          | example_dummy
          | forcmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "forcmd");
            printf("\n");
#endif
#endif
          }
          | proccmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "flowctrl", "proccmd");
            printf("\n");
#endif
#endif
          }
          | filecmd
          | helpcmd
          | examplecmd
            {if (currentVoice!=NULL) currentVoice->ifsw=0;}
        ;

example_dummy : EXAMPLE_CMD BLOCKTOK { omFree((ADDRESS)$2); }
        ;

command: assign { 
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = $1.ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "command", "assign", $$.ms);
#endif
#endif
            }
         | exportcmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "exportcmd");
            printf("\n");
#endif
#endif
         }
         | killcmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "killcmd");
            printf("\n");
#endif
#endif
         }
         | listcmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "listcmd");
            printf("\n");
#endif
#endif
         }
         | ringcmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "ringcmd");
            printf("\n");
#endif
#endif
         }
         | scriptcmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "scriptcmd");
            printf("\n");
#endif
#endif
         }
         | setringcmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "command", "setringcmd");
            printf("\n");
#endif
#endif
         }
         | typecmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring temp;
            switch ($1.Typ()){
                case INT_CMD:
                    $$.ms = $1.ms;
                    break;
                case BIGINT_CMD:
                    $$.ms = $1.ms;
                    break;
                case NUMBER_CMD:
                    $$.ms = ms_conc_s_ms_s( "print(STDOUT,unsafe_string(libSingular.p_String(", $1.ms, ",_singular_actual_ring)))" );
                    break;
                case POLY_CMD:
                    $$.ms = ms_conc_s_ms_s( "print(STDOUT,unsafe_string(libSingular.p_String(", $1.ms, ",_singular_actual_ring)))" );
                    break;
                case IDEAL_CMD:
/*                     $$.ms = ms_conc_s_ms_s( "print(STDOUT,unsafe_string(libSingular.id_Show(", $1.ms, ",_singular_actual_ring)))" ); */
                    temp = mstring_init_mstring($1.ms);
                    $$.ms = ms_conc_s_ms_s( "id_String(", $1.ms, ",\"" );
                    $$.ms = ms_conc_ms_ms_s( $$.ms, temp, "\",_singular_actual_ring)"  );
                    break;
                default:
                    $$.ms = $1.ms;
            }
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "command", "typecmd", $$.ms);
#endif
#endif
         }
         ;

assign: left_value exprlist
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "assign", "left_value exprlist");
#endif
            leftv voyager;
            switch ($1.Typ()){
                case INT_CMD:
                    $$.ms = ms_conc_s_ms_s( "Int32(", $2.ms, ")" );
                    break;
                case BIGINT_CMD:
                    $$.ms = ms_conc_s_ms_s( "BigInt(", $2.ms, ")" );
                    break;
                case NUMBER_CMD:
                    $$.ms = $2.ms;
/*                     $$.ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", $2.ms, "\")), _singular_actual_ring)" ); */
                    currentVoice->ring_decl = 0;
                    break;
                case POLY_CMD:
                    $$.ms = $2.ms;
/*                     $$.ms = ms_conc_s_ms_s( "polyTODO(", $2.ms, ")" ); */
                    currentVoice->ring_decl = 0;
                    break;
                case IDEAL_CMD:
                    if ($2.Typ() == POLY_CMD) {
                        $$.ms = $2.ms;
                        voyager = &$2;
                        while (voyager->next!=NULL){
                            $$.ms = ms_conc_ms_s_ms( $$.ms, ", ", voyager->next->ms);
                            voyager = voyager->next;
                        }
                        $$.ms = ms_conc_s_ms_s("[", $$.ms, "]");
                        $$.ms = ms_conc_s_ms_s( "idealFromArray(", $$.ms, ")" );
                        
                    }
                    else {
                        $$.ms = $2.ms;
                    }
                    currentVoice->ring_decl = 0;
                    break;
                default:
                    $$.ms = $2.ms;
            }
            $$.ms = mstring_concat($1.ms, $$.ms);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
/*             printfrule_ms(translator_NbRuleTraversed, "assign", "left_value exprlist", $$.ms); */
            char * disp;
            if ($$.ms) disp = mstring_to_str( $$.ms ); //TODO: not sure it is safe
            else disp = setUninitialized();
            printf("rtyp: %d, ms: %s\n", $1.Typ(), disp);
            free(disp);
#endif
/*             iiAssign(&$1,&$2); */
#else
            if(iiAssign(&$1,&$2)) YYERROR;
#endif
          }
        ;

elemexpr:
        RINGVAR
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_string($1);
#endif
            if (currRing==NULL) MYYERROR("no ring active");
            syMake(&$$,omStrDup($1));
#ifdef JL_TRANSLATOR_GRAMMAR
/*             $$.ms = ms; */
            $$.ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", ms, "\")), _singular_actual_ring)" );
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "RINGVAR", $$.ms);
#endif
#endif
          }
        | extendedid
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_string($1);
#endif
            syMake(&$$,$1);
#ifdef JL_TRANSLATOR_GRAMMAR
            char * disp = mstring_to_str( ms );

            if ( ( ((int) currentVoice->ring_decl)==1)
               &&( ((int) is_symbol_in_table_of_symbol(disp))==0 ))
                $$.ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", ms, "\")), _singular_actual_ring)" );
            else
                $$.ms = ms;
                
            free(disp);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "extendedid", $$.ms);
#endif
// #else
/*             syMake(&$$,$1); */
#endif

          }
        | elemexpr COLONCOLON elemexpr
          {
            if(iiExprArith2(&$$, &$1, COLONCOLON, &$3)) YYERROR;
          }
        | expr '.' elemexpr
          {
            if(iiExprArith2(&$$, &$1, '.', &$3)) YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR    
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "expr \'.\' elemexpr");
            printf("\n");
#endif
#endif
          }
        | elemexpr '('  ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR    
            translator_NbRuleTraversed++;
            $$.ms = mstring_concat($1.ms, mstring_init_string("()"));
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "elemexpr \'(\' \')\'", $$.ms);
#endif
#else
            if(iiExprArith1(&$$,&$1,'(')) YYERROR;
#endif
          }
        | elemexpr '(' exprlist ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR    
            translator_NbRuleTraversed++;
            if ($1.next==NULL) {
            
                $$.ms = $3.ms;
                leftv voyager = &$3;
                while (voyager->next!=NULL){
                    $$.ms = ms_conc_ms_s_ms( $$.ms, ", ", voyager->next->ms);
                    voyager = voyager->next;
                }
                $$.ms = ms_conc_s_ms_s("(", $$.ms, ")");
                $$.ms = mstring_concat($1.ms, $$.ms);
            }
            else if ($1.rtyp==UNKNOWN) {
                $$.ms = mstring_init_string("!!!sorry but not implemented!!!");
            }
            else
                $$.ms = mstring_init_string("!!!sorry but not implemented!!!");
/*             omFree((ADDRESS)$1); */
/*             omFree((ADDRESS)$3); */
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "elemexpr \'(\' exprlist \')\'", $$.ms);
#endif
#else           
            if ($1.next==NULL)
            {
              $1.next=(leftv)omAllocBin(sleftv_bin);
              memcpy($1.next,&$3,sizeof(sleftv));
              if(iiExprArithM(&$$,&$1,'(')) YYERROR;
            }
            else if ($1.rtyp==UNKNOWN)
            { // for x(i)(j)
              if(iiExprArith2(&$$,&$1,'(',&$3)) YYERROR;
            }
            else YYERROR;
#endif
          }
        | '[' exprlist ']'
          {
            if (currRingHdl==NULL) MYYERROR("no ring active");
            int j = 0;
            memset(&$$,0,sizeof(sleftv));
            $$.rtyp=VECTOR_CMD;
            leftv v = &$2;
            while (v!=NULL)
            {
              int i,t;
              sleftv tmp;
              memset(&tmp,0,sizeof(tmp));
              i=iiTestConvert((t=v->Typ()),POLY_CMD);
              if((i==0) || (iiConvert(t /*v->Typ()*/,POLY_CMD,i,v,&tmp)))
              {
                pDelete((poly *)&$$.data);
                $2.CleanUp();
                MYYERROR("expected '[poly,...'");
              }
              poly p = (poly)tmp.CopyD(POLY_CMD);
              pSetCompP(p,++j);
              $$.data = (void *)pAdd((poly)$$.data,p);
              v->next=tmp.next;tmp.next=NULL;
              tmp.CleanUp();
              v=v->next;
            }
            $2.CleanUp();
          }
        | INT_CONST
          {
            memset(&$$,0,sizeof($$));
            int i = atoi($1);
            /*remember not to omFree($1)
            *because it is a part of the scanner buffer*/
            $$.rtyp  = INT_CMD;
            $$.data = (void *)(long)i;

            /* check: out of range input */
            int l = strlen($1)+2;
            number n;
            if (l >= MAX_INT_LEN)
            {
              char tmp[MAX_INT_LEN+5];
              sprintf(tmp,"%d",i);
              if (strcmp(tmp,$1)!=0)
              {
                n_Read($1,&n,coeffs_BIGINT);
                $$.rtyp=BIGINT_CMD;
                $$.data = n;
              }
            }
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = mstring_init_string($1);
            
//             if ( ((int) currentVoice->ring_decl)==1)
//                 $$.ms = ms_conc_s_ms_s( "p_mInit(pointer(Vector{UInt8}(\"", $$.ms, "\")), _singular_actual_ring)" );
                
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "INT_CONST", $$.ms);
#endif
#endif
          }
        | SYSVAR
          {
            memset(&$$,0,sizeof($$));
            $$.rtyp = $1;
            $$.data = $$.Data();
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "SYSVAR");
            printf("\n");
#endif
#endif
          }
        | stringexpr
          {
            memset(&$$,0,sizeof($$));
            $$.rtyp  = STRING_CMD;
            $$.data = $1;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "stringexpr");
            printf("\n");
#endif
#endif
          }
        | PROC_CMD '(' expr ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "PROC_CMD \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | ROOT_DECL '(' expr ')'
          {
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | ROOT_DECL_LIST '(' exprlist ')'
          {
            if(iiExprArithM(&$$,&$3,$1)) YYERROR;
          }
        | ROOT_DECL_LIST '(' ')'
          {
            if(iiExprArithM(&$$,NULL,$1)) YYERROR;
          }
        | RING_DECL '(' expr ')'
          {
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | RING_DECL_LIST '(' exprlist ')'
          {
            if(iiExprArithM(&$$,&$3,$1)) YYERROR;
          }
        | RING_DECL_LIST '(' ')'
          {
            if(iiExprArithM(&$$,NULL,$1)) YYERROR;
          }
        | CMD_1 '(' expr ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_1 \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | CMD_12 '(' expr ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_12 \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | CMD_13 '(' expr ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_13 \'(\' expr \')\'");
            printf("\n");
#endif
#endif
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | CMD_123 '(' expr ')'
          {
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | CMD_2 '(' expr ',' expr ')'
          {
            if(iiExprArith2(&$$,&$3,$1,&$5,TRUE)) YYERROR;
          }
        | CMD_12 '(' expr ',' expr ')'
          {
            if(iiExprArith2(&$$,&$3,$1,&$5,TRUE)) YYERROR;
          }
        | CMD_23 '(' expr ',' expr ')'
          {
            if(iiExprArith2(&$$,&$3,$1,&$5,TRUE)) YYERROR;
          }
        | CMD_123 '(' expr ',' expr ')'
          {
            if(iiExprArith2(&$$,&$3,$1,&$5,TRUE)) YYERROR;
          }
        | CMD_3 '(' expr ',' expr ',' expr ')'
          {
            if(iiExprArith3(&$$,$1,&$3,&$5,&$7)) YYERROR;
          }
        | CMD_13 '(' expr ',' expr ',' expr ')'
          {
            if(iiExprArith3(&$$,$1,&$3,&$5,&$7)) YYERROR;
          }
        | CMD_23 '(' expr ',' expr ',' expr ')'
          {
            if(iiExprArith3(&$$,$1,&$3,&$5,&$7)) YYERROR;
          }
        | CMD_123 '(' expr ',' expr ',' expr ')'
          {
            if(iiExprArith3(&$$,$1,&$3,&$5,&$7)) YYERROR;
          }
        | CMD_M '(' ')'
          {
            if(iiExprArithM(&$$,NULL,$1)) YYERROR;
          }
        | CMD_M '(' exprlist ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            int b;
            leftv voyager;
            switch($1){
                case STD_CMD:
/*                     printf("POLY_CMD: %d, IDEAL_CMD: %d, $3.Typ(): %d\n", POLY_CMD, IDEAL_CMD, $3.Typ()); */
                    if ($3.Typ() == IDEAL_CMD)
                        $$.ms = ms_conc_s_ms_s("m_id_Std(", $3.ms, ", _singular_actual_ring)");
                    else if ($3.Typ() == POLY_CMD) {
                        /*construct an ideal from the list of polys...*/
                        
                        $$.ms = $3.ms;
                        voyager = &$3;
                        while (voyager->next!=NULL){
                            $$.ms = ms_conc_ms_s_ms( $$.ms, ", ", voyager->next->ms);
                            voyager = voyager->next;
                        }
                        $$.ms = ms_conc_s_ms_s("[", $$.ms, "]");
                        $$.ms = ms_conc_s_ms_s( "idealFromArray(", $$.ms, ")" );
                        $$.ms = ms_conc_s_ms_s("m_id_Std(", $$.ms, ", _singular_actual_ring)");
                        
                    }
                    break;
                default:
/*                     $$.ms = ms_conc_s_ms_s("TODO(", $3.ms, ")"); */
                    b=iiExprArithM(&$$,&$3,$1); // handle branchTo
                    if (b==TRUE) YYERROR;
                    if (b==2) YYACCEPT;
            }
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "elemexpr", "CMD_M \'(\' exprlist \')\'", $$.ms);
/*             printf("CMD_M: %d\n", (int) $1); */
/*             printfrule(translator_NbRuleTraversed, "elemexpr", "CMD_M \'(\' exprlist \')\'"); */
            printf("\n");
               
#endif
// #endif
#else
            int b=iiExprArithM(&$$,&$3,$1); // handle branchTo
            if (b==TRUE) YYERROR;
            if (b==2) YYACCEPT;
#endif
          }
        | mat_cmd '(' expr ',' expr ',' expr ')'
          {
            if(iiExprArith3(&$$,$1,&$3,&$5,&$7)) YYERROR;
          }
        | mat_cmd '(' expr ')'
          {
            if(iiExprArith1(&$$,&$3,$1)) YYERROR;
          }
        | RING_CMD '(' rlist ',' rlist ',' ordering ')'
          {
            if(iiExprArith3(&$$,RING_CMD,&$3,&$5,&$7)) YYERROR;
          }
        | RING_CMD '(' expr ')'
          {
            if(iiExprArith1(&$$,&$3,RING_CMD)) YYERROR;
          }
        | extendedid  ARROW BLOCKTOK
          {
            if (iiARROW(&$$,$1,$3)) YYERROR;
          }
        | '(' exprlist ')'    { 
            $$ = $2; 
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "\'(\' exprlist \')\'");
            printf("\n");
#endif
#endif
            }
        ;

exprlist:
        exprlist ',' expr
          {
// #ifdef JL_TRANSLATOR_GRAMMAR 
//             mstring ms;
//             if (($1.ms)&&($3.ms))
//                 ms = ms_conc_ms_s_ms( $1.ms, ", ", $3.ms);
// #endif
            leftv v = &$1;
            while (v->next!=NULL)
            {
              v=v->next;
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&($3),sizeof(sleftv));
            $$ = $1;
#ifdef JL_TRANSLATOR_GRAMMAR 
/*             $$.ms = ms; */
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_listofms(translator_NbRuleTraversed, "exprlist", "exprlist \',\' expr", &$$);
#endif
#endif
          }
        | expr
          {
            $$ = $1;
#ifdef JL_TRANSLATOR_GRAMMAR            
            $$.ms = $1.ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "exprlist", "expr", $$.ms);
#endif
#endif
          }
        ;

expr:   expr_arithmetic
          {
            /*if ($1.typ == eunknown) YYERROR;*/
            $$ = $1;
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = $1.ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr", "expr_arithmetic", $$.ms);
#endif
#endif
          }
        | elemexpr       { 
            $$ = $1; 
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = $1.ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule_ms(translator_NbRuleTraversed, "expr", "elemexpr",$$.ms);
#endif
#endif
            }
        | expr '[' expr ',' expr ']'
          {
            if(iiExprArith3(&$$,'[',&$1,&$3,&$5)) YYERROR;
          }
        | expr '[' expr ']'
          {
            if(iiExprArith2(&$$,&$1,'[',&$3)) YYERROR;
          }
        | APPLY '('  expr ',' CMD_1 ')'
          {
            if (iiApply(&$$, &$3, $5, NULL)) YYERROR;
          }
        | APPLY '('  expr ',' CMD_12 ')'
          {
            if (iiApply(&$$, &$3, $5, NULL)) YYERROR;
          }
        | APPLY '('  expr ',' CMD_13 ')'
          {
            if (iiApply(&$$, &$3, $5, NULL)) YYERROR;
          }
        | APPLY '('  expr ',' CMD_123 ')'
          {
            if (iiApply(&$$, &$3, $5, NULL)) YYERROR;
          }
        | APPLY '('  expr ',' CMD_M ')'
          {
            if (iiApply(&$$, &$3, $5, NULL)) YYERROR;
          }
        | APPLY '('  expr ',' expr ')'
          {
            if (iiApply(&$$, &$3, 0, &$5)) YYERROR;
          }
        | quote_start expr quote_end
          {
            $$=$2;
          }
        | quote_start expr '=' expr quote_end
          {
            #ifdef SIQ
            siq++;
            if (siq>0)
            { if (iiExprArith2(&$$,&$2,'=',&$4)) YYERROR; }
            else
            #endif
            {
              memset(&$$,0,sizeof($$));
              $$.rtyp=NONE;
              if (iiAssign(&$2,&$4)) YYERROR;
            }
            #ifdef SIQ
            siq--;
            #endif
          }
        | assume_start expr ',' expr quote_end
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule(translator_NbRuleTraversed, "expr", "assume_start expr \',\' expr quote_end");
            printf("\n");
#endif
#endif
            iiTestAssume(&$2,&$4);
            memset(&$$,0,sizeof($$));
            $$.rtyp=NONE;
          }
        | EVAL  '('
          {
            #ifdef SIQ
            siq--;
            #endif
          }
          expr ')'
          {
            #ifdef SIQ
            if (siq<=0) $4.Eval();
            #endif
            $$=$4;
            #ifdef SIQ
            siq++;
            #endif
          }
          ;

quote_start:    QUOTE  '('
          {
            #ifdef SIQ
            siq++;
            #endif
          }
          ;

assume_start:    ASSUME_CMD '('
          {
            #ifdef SIQ
            siq++;
            #endif
          }
          ;

quote_end: ')'
          {
            #ifdef SIQ
            siq--;
            #endif
          }
          ;

expr_arithmetic:
          expr PLUSPLUS     %prec PLUSPLUS
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_ipp( $1.ms );
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr PLUSPLUS     %%prec PLUSPLUS", $$.ms);
#endif
#else
            if(iiExprArith1(&$$,&$1,PLUSPLUS)) YYERROR;
#endif
          }
        | expr MINUSMINUS   %prec MINUSMINUS
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_imm( $1.ms );
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr MINUSMINUS     %%prec MINUSMINUS", $$.ms);
#endif
#else
            if(iiExprArith1(&$$,&$1,MINUSMINUS)) YYERROR;
#endif
          }
        | expr '+' expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_add( $1.ms, $3.ms );
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'+\' expr", $$.ms);
#endif
#else
            if(iiExprArith2(&$$,&$1,'+',&$3)) YYERROR;
#endif
          }
        | expr '-' expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_sub( $1.ms, $3.ms );
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'-\' expr", $$.ms);
#endif
#else
            if(iiExprArith2(&$$,&$1,'-',&$3)) YYERROR;
#endif
          }
        | expr '/' expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms;
            switch($2){
                case '/':
                    ms = mstring_toJulia_div( $1.ms, $3.ms );
                    break;
                case '*':
                    ms = mstring_toJulia_mul( $1.ms, $3.ms );
                    break;
                default:
                    ms = mstring_init_char( $2 );
                    ms = ms_conc_ms_s_ms(ms, "(", $1.ms);
                    ms = ms_conc_ms_s_ms(ms, ",", $3.ms);
                    ms = mstring_concat( ms, mstring_init_char( ')' ));
            }
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'/\' expr", $$.ms);
#endif
#else
            if(iiExprArith2(&$$,&$1,$<i>2,&$3)) YYERROR;
#endif
          }
        | expr '^' expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_pow( $1.ms, $3.ms );
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'^\' expr", $$.ms);
#endif
#else
            if(iiExprArith2(&$$,&$1,'^',&$3)) YYERROR;
#endif
          }
        | expr '<' expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_cmp1($2, $1.ms, $3.ms );
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr \'<\' expr", $$.ms);
#endif
#else
            if(iiExprArith2(&$$,&$1,$<i>2,&$3)) YYERROR;
#endif
          }
        | expr '&' expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr \'&\' expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&$$,&$1,$<i>2,&$3)) YYERROR;
          }
        | expr NOTEQUAL expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr NOTEQUAL expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&$$,&$1,NOTEQUAL,&$3)) YYERROR;
          }
        | expr EQUAL_EQUAL expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_eqeq($1.ms, $3.ms );
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "expr_arithmetic", "expr EQUAL_EQUAL expr", $$.ms);
#endif
#else
            if(iiExprArith2(&$$,&$1,EQUAL_EQUAL,&$3)) YYERROR;
#endif
          }
        | expr DOTDOT expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr DOTDOT expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&$$,&$1,DOTDOT,&$3)) YYERROR;
          }
        | expr ':' expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "expr \':\' expr");
            printf("\n");
#endif
#endif
            if(iiExprArith2(&$$,&$1,':',&$3)) YYERROR;
          }
        | NOT expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "NOT expr");
            printf("\n");
#endif
#endif
            if (siq>0)
            { if (iiExprArith1(&$$,&$2,NOT)) YYERROR; }
            else
            {
              memset(&$$,0,sizeof($$));
              int i; TESTSETINT($2,i);
              $$.rtyp  = INT_CMD;
              $$.data = (void *)(long)(i == 0 ? 1 : 0);
            }
          }
        | '-' expr %prec UMINUS
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            mstring ms = mstring_toJulia_uminus($2.ms);
            $$.ms = ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "expr_arithmetic", "\'-\' expr %%prec UMINUS");
            printf("\n");
#endif
#else
            if(iiExprArith1(&$$,&$2,'-')) YYERROR;
#endif
          }
        ;

left_value:
        declare_ip_variable cmdeq  {
            $$ = $1; 
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = $1.ms;
            $$.ms = mstring_concat($$.ms, mstring_init_string(" = "));
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "left_value", "declare_ip_variable cmdeq", $$.ms);
#endif
#endif
        }
        | exprlist '='
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = $1.ms;
            $$.ms = mstring_concat($$.ms, mstring_init_string(" = "));
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "left_value", "exprlist \'=\'", $$.ms);
#endif
#else
            if ($1.rtyp==0)
            {
              Werror("`%s` is undefined",$1.Fullname());
              YYERROR;
            }
            else if (($1.rtyp==MODUL_CMD)
            // matrix m; m[2]=...
            && ($1.e!=NULL) && ($1.e->next==NULL))
            {
              MYYERROR("matrix must have 2 indices");
            }
            $$ = $1;
#endif
          }
        ;


extendedid:
        UNKNOWN_IDENT {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "extendedid", "UNKNOWN_IDENT");
            printf("name: %s, ring_decl? %d, is defined? %d \n", $1, ((int) currentVoice->ring_decl), (int) is_symbol_in_table_of_symbol($1));
            
/*             printf("already defined: \n"); */
#endif
#endif
        }
        | '`' expr '`'
          {
            if ($2.Typ()!=STRING_CMD)
            {
              MYYERROR("string expression expected");
            }
            $$ = (char *)$2.CopyD(STRING_CMD);
            $2.CleanUp();
          }
        ;

declare_ip_variable:
        ROOT_DECL elemexpr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_mstring($2.ms);
            iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot));
/*             $$.ms = $2.ms; */
/*             $$.ms = mstring_init_mstring($2.ms); */
            $$.ms = ms;
            add_symbol_in_table_of_symbol_mstring($$.ms);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "declare_ip_variable", "ROOT_DECL elemexpr", $$.ms);
#endif
#else
// #endif
            if (iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot)))
              YYERROR;
#endif
          }
        | ROOT_DECL_LIST elemexpr
          {
            if (iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot)))
              YYERROR;
          }
        | RING_DECL elemexpr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_mstring($2.ms);
            iiDeclCommand(&$$,&$2,myynest,$1,&(currRing->idroot), TRUE);
/*             mstring ms = $2.ms; */
/*             $$.ms = $2.ms; */
            $$.ms = ms;
            add_symbol_in_table_of_symbol_mstring($$.ms);
            currentVoice->ring_decl = 1;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "declare_ip_variable", "RING_DECL elemexpr", $$.ms);
#endif
#else
            if (iiDeclCommand(&$$,&$2,myynest,$1,&(currRing->idroot), TRUE)) YYERROR;
#endif
          }
        | RING_DECL_LIST elemexpr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            mstring ms = mstring_init_mstring($2.ms);
            iiDeclCommand(&$$,&$2,myynest,$1,&(currRing->idroot), TRUE);
            $$.ms = ms;
            add_symbol_in_table_of_symbol_mstring($$.ms);
            currentVoice->ring_decl = 1;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "declare_ip_variable", "RING_DECL_LIST elemexpr", $$.ms);
#endif
#else
            if (iiDeclCommand(&$$,&$2,myynest,$1,&(currRing->idroot), TRUE)) YYERROR;
#endif
          }
        | mat_cmd elemexpr '[' expr ']' '[' expr ']'
          {
            int r; TESTSETINT($4,r);
            int c; TESTSETINT($7,c);
            leftv v;
            idhdl h;
            if ($1 == MATRIX_CMD)
            {
              if (iiDeclCommand(&$$,&$2,myynest,$1,&(currRing->idroot), TRUE)) YYERROR;
              v=&$$;
              h=(idhdl)v->data;
              idDelete(&IDIDEAL(h));
              IDMATRIX(h) = mpNew(r,c);
              if (IDMATRIX(h)==NULL) YYERROR;
            }
            else if ($1 == INTMAT_CMD)
            {
              if (iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot)))
                YYERROR;
              v=&$$;
              h=(idhdl)v->data;
              delete IDINTVEC(h);
              IDINTVEC(h) = new intvec(r,c,0);
              if (IDINTVEC(h)==NULL) YYERROR;
            }
            else /* BIGINTMAT_CMD */
            {
              if (iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot)))
                YYERROR;
              v=&$$;
              h=(idhdl)v->data;
              delete IDBIMAT(h);
              IDBIMAT(h) = new bigintmat(r, c, coeffs_BIGINT);
              if (IDBIMAT(h)==NULL) YYERROR;
            }
          }
        | mat_cmd elemexpr
          {
            if ($1 == MATRIX_CMD)
            {
              if (iiDeclCommand(&$$,&$2,myynest,$1,&(currRing->idroot), TRUE)) YYERROR;
            }
            else if ($1 == INTMAT_CMD)
            {
              if (iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot)))
                YYERROR;
              leftv v=&$$;
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
              if (iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot)))
                YYERROR;
            }
          }
        | declare_ip_variable ',' elemexpr
          {
            int t=$1.Typ();
            sleftv r;
            memset(&r,0,sizeof(sleftv));
            if ((BEGIN_RING<t) && (t<END_RING))
            {
              if (iiDeclCommand(&r,&$3,myynest,t,&(currRing->idroot), TRUE))
                YYERROR;
            }
            else
            {
              if (iiDeclCommand(&r,&$3,myynest,t,&($3.req_packhdl->idroot)))
                YYERROR;
            }
            leftv v=&$1;
            while (v->next!=NULL) v=v->next;
            v->next=(leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&r,sizeof(sleftv));
            $$=$1;
          }
        | PROC_CMD elemexpr
          {
            if (iiDeclCommand(&$$,&$2,myynest,$1,&($2.req_packhdl->idroot)))
              YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR            
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "elemexpr", "PROC_CMD elemexpr");
            printf("\n");
#endif
#endif
          }
        ;

stringexpr:
        STRINGTOK {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "stringexpr", "STRINGTOK");
            printf("\n");
#endif
#endif        
}
        ;

rlist:
        expr {
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = $1.ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "rlist", "expr", $$.ms);
#endif
#endif
        }
        | '(' expr ',' exprlist ')'
          {
// #ifdef JL_TRANSLATOR_GRAMMAR 
//             mstring ms;
//             if (($2.ms)&&($4.ms))
//                 ms = ms_conc_ms_s_ms( $2.ms, ", ", $4.ms);
// #endif
            leftv v = &$2;
            while (v->next!=NULL)
            {
/*               v=v->next; */
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&($4),sizeof(sleftv));
            $$ = $2;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_listofms(translator_NbRuleTraversed, "rlist", "\'(\' expr \',\' exprlist \')\'", &$$);
#endif
#endif
          }
        ;

ordername:
        UNKNOWN_IDENT
        {
          // let rInit take care of any errors
          $$=rOrderName($1);
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ordername", "UNKNOWN_IDENT");
            printf("\n");
#endif
#endif
        }
        ;

orderelem:
        ordername
          {
            memset(&$$,0,sizeof($$));
            intvec *iv = new intvec(2);
            (*iv)[0] = 1;
            (*iv)[1] = $1;
            $$.rtyp = INTVEC_CMD;
            $$.data = (void *)iv;
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = mstring_init_string( rSimpleOrdStr( $1 ) );
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "orderelem", "ordername", $$.ms);
#endif
#endif
          }
        | ordername '(' exprlist ')'
          {
            memset(&$$,0,sizeof($$));
            leftv sl = &$3;
            int slLength;
            {
              slLength =  exprlist_length(sl);
              int l = 2 +  slLength;
              intvec *iv = new intvec(l);
              (*iv)[0] = slLength;
              (*iv)[1] = $1;

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
                  $3.CleanUp();
                  MYYERROR("wrong type in ordering");
                }
                sl = sl->next;
              }
              $$.rtyp = INTVEC_CMD;
              $$.data = (void *)iv;
            }
            $3.CleanUp();
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "orderelem", "ordername \'(\' exprlist \')\'");
            printf("\n");
#endif
#endif
          }
        ;

OrderingList:
        orderelem {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "OrderingList", "orderelem");
            printf("\n");
#endif
#endif
        }
        |  orderelem ',' OrderingList
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "OrderingList", "orderelem \',\' OrderingList");
            printf("\n");
#endif
#endif
            $$ = $1;
            $$.next = (sleftv *)omAllocBin(sleftv_bin);
            memcpy($$.next,&$3,sizeof(sleftv));
          }
        ;

ordering:
        orderelem {
#ifdef JL_TRANSLATOR_GRAMMAR
            $$.ms = $1.ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "ordering", "orderelem", $$.ms);
#endif
#endif
        }
        | '(' OrderingList ')'
          {
            $$ = $2;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_listofms(translator_NbRuleTraversed, "ordering", "\'(\' OrderingList \')\'", &$$);
#endif
#endif
          }
        ;

cmdeq:  '='
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
        ;


mat_cmd: MATRIX_CMD
            { $$ = $1; }
        | INTMAT_CMD
            { $$ = $1; }
        | BIGINTMAT_CMD
            { $$ = $1; }
          ;

/* --------------------------------------------------------------------*/
/* section of pure commands                                            */
/* --------------------------------------------------------------------*/

filecmd:
/*        '<' stringexpr
          { if ($<i>1 != '<') YYERROR;
            if((feFilePending=feFopen($2,"r",NULL,TRUE))==NULL) YYERROR; }
        ';'
          { newFile($2,feFilePending); }
        ;*/
        '<' stringexpr
          { newFile($2); omFree($2); }
        ;

helpcmd:
        HELP_CMD STRINGTOK ';'
          {
            feHelp($2);
            omFree((ADDRESS)$2);
          }
        | HELP_CMD ';'
          {
            feHelp(NULL);
          }
        ;

examplecmd:
        EXAMPLE_CMD STRINGTOK ';'
          {
            singular_example($2);
            omFree((ADDRESS)$2);
          }
       ;

exportcmd:
        EXPORT_CMD exprlist
        {
          if (basePack!=$2.req_packhdl)
          {
            if(iiExport(&$2,0,currPack)) YYERROR;
          }
          else
            if (iiExport(&$2,0)) YYERROR;
        }
        ;

killcmd:
        KILL_CMD elemexpr
        {
          leftv v=&$2;
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
        | killcmd ',' elemexpr
        {
          leftv v=&$3;
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
        ;

listcmd:
        LISTVAR_CMD '(' ROOT_DECL ')'
          {
            list_cmd($3,NULL,"// ",TRUE);
          }
        | LISTVAR_CMD '(' ROOT_DECL_LIST ')'
          {
            list_cmd($3,NULL,"// ",TRUE);
          }
        | LISTVAR_CMD '(' RING_DECL ')'
          {
            if ($3==QRING_CMD) $3=RING_CMD;
            list_cmd($3,NULL,"// ",TRUE);
          }
        | LISTVAR_CMD '(' RING_DECL_LIST ')'
          {
            list_cmd($3,NULL,"// ",TRUE);
          }
        | LISTVAR_CMD '(' RING_CMD ')'
          {
            list_cmd(RING_CMD,NULL,"// ",TRUE);
          }
        | LISTVAR_CMD '(' mat_cmd ')'
          {
            list_cmd($3,NULL,"// ",TRUE);
           }
        | LISTVAR_CMD '(' PROC_CMD ')'
          {
            list_cmd(PROC_CMD,NULL,"// ",TRUE);
          }
        | LISTVAR_CMD '(' elemexpr ')'
          {
            list_cmd(0,$3.Fullname(),"// ",TRUE);
            $3.CleanUp();
          }
        | LISTVAR_CMD '(' elemexpr ',' ROOT_DECL ')'
          {
            if($3.Typ() == PACKAGE_CMD)
              list_cmd($5,NULL,"// ",TRUE);
            $3.CleanUp();
          }
        | LISTVAR_CMD '(' elemexpr ',' ROOT_DECL_LIST ')'
          {
            if($3.Typ() == PACKAGE_CMD)
              list_cmd($5,NULL,"// ",TRUE);
            $3.CleanUp();
          }
        | LISTVAR_CMD '(' elemexpr ',' RING_DECL ')'
          {
            if($3.Typ() == PACKAGE_CMD)
              list_cmd($5,NULL,"// ",TRUE);
            $3.CleanUp();
          }
        | LISTVAR_CMD '(' elemexpr ',' RING_DECL_LIST ')'
          {
            if($3.Typ() == PACKAGE_CMD)
              list_cmd($5,NULL,"// ",TRUE);
            $3.CleanUp();
          }
        | LISTVAR_CMD '(' elemexpr ',' RING_CMD ')'
          {
            if($3.Typ() == PACKAGE_CMD)
              list_cmd($5,NULL,"// ",TRUE);
            $3.CleanUp();
          }
        | LISTVAR_CMD '(' elemexpr ',' mat_cmd ')'
          {
            if($3.Typ() == PACKAGE_CMD)
              list_cmd($5,NULL,"// ",TRUE);
            $3.CleanUp();
          }
        | LISTVAR_CMD '(' elemexpr ',' PROC_CMD ')'
          {
            if($3.Typ() == PACKAGE_CMD)
              list_cmd($5,NULL,"// ",TRUE);
            $3.CleanUp();
          }
        //| LISTVAR_CMD '(' elemexpr ',' elemexpr ')'
        //  {
        //    //if($3.Typ() == PACKAGE_CMD)
        //    //  list_cmd($5,NULL,"// ",TRUE);
        //    $3.CleanUp();
        //  }
        | LISTVAR_CMD '(' ')'
          {
            list_cmd(-1,NULL,"// ",TRUE);
          }
        ;

ringcmd1:
       RING_CMD { 
       yyInRingConstruction = TRUE; 
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd1", "RING_CMD");
            printf("\n");
#endif
#endif
       }
       ;

ringcmd:
        ringcmd1
          elemexpr cmdeq
          rlist     ','      /* description of coeffs */
          rlist     ','      /* var names */
          ordering           /* list of (multiplier ordering (weight(s))) */
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            /*construct strings before args are cleaned*/
            add_symbol_in_table_of_symbol_mstring($2.ms);
            mstring r_name  = $2.ms;
            mstring r_name2 = mstring_init_mstring(r_name);
            mstring r_field = mstring_toJulia_coeffs(&$4);
            /* add vars in symbol table */
            /*add_symbol_in_table_of_symbol_mstring($6.ms);
            leftv voyager = &$6;
            while (voyager->next!=NULL){
                add_symbol_in_table_of_symbol_mstring(voyager->next->ms);
                voyager = voyager->next;
            }*/
            /* end add vars in symbol table */
            mstring r_vars  = mstring_toJulia_vars(&$6);
            mstring r_ord   = mstring_toJulia_ordering(&$8);
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
            $$.ms = ms_conc_ms_s_ms(r_field, ",\n", r_vars);
            $$.ms = ms_conc_ms_s_ms($$.ms, ",\n", r_ord);
            if ((&$8)->listLength() == 1)
                $$.ms = ms_conc_s_ms_s ("libSingular.rDefault(", $$.ms, ")");
            else 
                $$.ms = ms_conc_s_ms_s ("libSingular.rDefault(", $$.ms, ", [Int32(1)], [Int32(1)])");
            $$.ms = ms_conc_ms_s_ms (r_name, "=", $$.ms);
            $$.ms = ms_conc_ms_s_ms ($$.ms, "\n _singular_actual_ring = ", r_name2);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr cmdeq rlist \',\' rlist \',\' ordering", $$.ms);
#endif
#endif
            const char *ring_name = $2.name;
            ring b=
            rInit(&$4,            /* characteristik and list of parameters*/
                  &$6,            /* names of ringvariables */
                  &$8);            /* ordering */
            idhdl newRingHdl=NULL;

            if (b!=NULL)
            {
              newRingHdl=enterid(ring_name, myynest, RING_CMD,
                                   &($2.req_packhdl->idroot),FALSE);
              $2.CleanUp();
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
        | ringcmd1 elemexpr
          {
            const char *ring_name = $2.name;
            if (!inerror) rDefault(ring_name);
            yyInRingConstruction = FALSE;
            $2.CleanUp();
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr");
            printf("\n");
#endif
#endif
          }
        | ringcmd1 elemexpr cmdeq elemexpr
          {
            yyInRingConstruction = FALSE;
            if (iiAssignCR(&$2,&$4)) YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr cmdeq elemexpr");
            printf("\n");
#endif
#endif
          }
        | ringcmd1 elemexpr cmdeq elemexpr '[' exprlist ']'
        {
          yyInRingConstruction = FALSE;
          sleftv tmp;
          $4.next=(leftv)omAlloc(sizeof(sleftv));
          memcpy($4.next,&$6,sizeof(sleftv));
          memset(&$6,0,sizeof(sleftv));
          if (iiExprArithM(&tmp,&$4,'[')) YYERROR;
          if (iiAssignCR(&$2,&tmp)) YYERROR;
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "ringcmd", "ringcmd1 elemexpr cmdeq elemexpr \'[\' exprlist \']\'");
            printf("\n");
#endif
#endif
        }
        ;

scriptcmd:
         SYSVAR stringexpr
          {
            if (($1!=LIB_CMD)||(jjLOAD($2,TRUE))) YYERROR;
          }
        ;

setrings:  SETRING_CMD | KEEPRING_CMD ;

setringcmd:
        setrings expr
          {
            if (($1==KEEPRING_CMD) && (myynest==0))
               MYYERROR("only inside a proc allowed");
            const char * n=$2.Name();
            if (($2.Typ()==RING_CMD)
            && ($2.rtyp==IDHDL))
            {
              idhdl h=(idhdl)$2.data;
              if ($2.e!=NULL) h=rFindHdl((ring)$2.Data(),NULL);
              //Print("setring %s lev %d (ptr:%x)\n",IDID(h),IDLEV(h),IDRING(h));
              if ($1==KEEPRING_CMD)
              {
                if (h!=NULL)
                {
                  if (IDLEV(h)!=0)
                  {
                    if (iiExport(&$2,myynest-1)) YYERROR;
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
                  $2.CleanUp();
                  YYERROR;
                }
              }
              if (h!=NULL) rSetHdl(h);
              else
              {
                Werror("cannot find the name of the basering %s",n);
                $2.CleanUp();
                YYERROR;
              }
              $2.CleanUp();
            }
            else
            {
              Werror("%s is no name of a ring/qring",n);
              $2.CleanUp();
              YYERROR;
            }
          }
        ;

typecmd:
        TYPE_CMD expr
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "typecmd", "TYPE_CMD expr");
            printf("\n");
#endif
#else
            type_cmd(&($2));
#endif
          }
        | exprlist
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
            if ($1.rtyp!=COMMAND)
            {
            #endif
              if ($1.Typ()==UNKNOWN)
              {
                if ($1.name!=NULL)
                {
                  Werror("`%s` is undefined",$1.name);
                  omFree((ADDRESS)$1.name);
                }
                YYERROR;
              }
            #ifdef SIQ
            }
            #endif
            $1.Print(&sLastPrinted);
            $1.CleanUp(currRing);
            if (errorreported) YYERROR;
#endif
          }
        ;

/* --------------------------------------------------------------------*/
/* section of flow control                                             */
/* --------------------------------------------------------------------*/

ifcmd: IF_CMD '(' expr ')' BLOCKTOK
          {
#ifdef JL_TRANSLATOR_GRAMMAR
/*             printf("waitingForEnd: %d\n", currentVoice->waitingForEnd); */
            char * iftrueblock  = (char *) omAlloc (strlen($5)+50);
            sprintf(iftrueblock, "%s\njulia_endproc\n", $5);
/*             sprintf(iftrueblock, "%s\n", $5); */
            omFree((ADDRESS)$5);
#else
            int i; TESTSETINT($3,i);
            if (i!=0)
            {
              newBuffer( $5, BT_if);
            }
            else
            {
              omFree((ADDRESS)$5);
              currentVoice->ifsw=1;
            }
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if (!($3.ms)) $3.ms = mstring_init_char(' ');
            $$.ms = ms_conc_s_ms_s( "if ( ", $3.ms, " )" );
            $$.ms = mstring_dedent($$.ms, 1);
/*             currentVoice->waitingForEnd=1; */
/*             printf("waitingForEnd: %d\n", currentVoice->waitingForEnd); */
            newBuffer( iftrueblock, BT_proc );
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "ifcmd", "IF_CMD \'(\' expr \')\' BLOCKTOK", $$.ms);
#endif
#endif
          }
        | IF_CMD '(' expr ')' BLOCKTOK ELSE_CMD BLOCKTOK
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            char * iftrueblock  = (char *) omAlloc (strlen($5)+strlen($7)+50);
            sprintf(iftrueblock, "%s\n else {\n%s} \njulia_endproc\n", $5, $7 );
/*             printf("%s\n", iftrueblock); */
            omFree((ADDRESS)$5);
            omFree((ADDRESS)$7);
#else
            int i; TESTSETINT($3,i);
            if (i!=0)
            {
              newBuffer( $5, BT_if);
            }
            else
            {
              omFree((ADDRESS)$5);
              currentVoice->ifsw=1;
            }
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
          translator_NbRuleTraversed++;
            if (!($3.ms)) $3.ms = mstring_init_char(' ');
            $$.ms = ms_conc_s_ms_s( "if ( ", $3.ms, " )" );
            $$.ms = mstring_dedent($$.ms, 1);
          newBuffer( iftrueblock, BT_proc );
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
          printfrule_ms(translator_NbRuleTraversed, "ifcmd", "IF_CMD \'(\' expr \')\' BLOCKTOK ELSE_CMD BLOCKTOK", $$.ms);
#endif
#endif
          }
        | ELSE_CMD BLOCKTOK
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            char * elseblock  = (char *) omAlloc (strlen($2)+50);
            sprintf(elseblock, "%s\njulia_endproc\n", $2);
/*             sprintf(elseblock, "%s", $2); */
            omFree((ADDRESS)$2);
#else
            if (currentVoice->ifsw==1)
            {
              currentVoice->ifsw=0;
              newBuffer( $2, BT_else);
            }
            else
            {
              if (currentVoice->ifsw!=2)
              {
                Warn("`else` without `if` in level %d",myynest);
              }
              omFree((ADDRESS)$2);
            }
            currentVoice->ifsw=0;
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
          translator_NbRuleTraversed++;
          $$.ms = mstring_init_string( "else " );
          $$.ms = mstring_dedent($$.ms, 1);
          newBuffer( elseblock, BT_proc );
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
          printfrule_ms(translator_NbRuleTraversed, "ifcmd", "ELSE_CMD BLOCKTOK", $$.ms);
#endif
#endif
          }
        | IF_CMD '(' expr ')' BREAK_CMD
          {
            int i; TESTSETINT($3,i);
            if (i)
            {
              if (exitBuffer(BT_break)) YYERROR;
            }
            currentVoice->ifsw=0;
          }
        | BREAK_CMD
          {
            if (exitBuffer(BT_break)) YYERROR;
            currentVoice->ifsw=0;
          }
        | CONTINUE_CMD
          {
            if (contBuffer(BT_break)) YYERROR;
            currentVoice->ifsw=0;
          }
      ;

whilecmd:
        WHILE_CMD STRINGTOK BLOCKTOK
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            
            char * whilehead  = (char *) omAlloc (10);
            sprintf(whilehead, "while");
            char * whilebody  = (char *) omAlloc (strlen($2)+strlen($3)+50);
            sprintf(whilebody, "%s;\n%s\njulia_endloop\n", $2, $3);
#else
            /* -> if(!$2) break; $3; continue;*/
            char * s = (char *)omAlloc( strlen($2) + strlen($3) + 36);
            sprintf(s,"whileif (!(%s)) break;\n%scontinue;\n " ,$2,$3);
            newBuffer(s,BT_break);
#endif
            omFree((ADDRESS)$2);
            omFree((ADDRESS)$3);
#ifdef JL_TRANSLATOR_GRAMMAR
            newBuffer( whilebody, BT_break );
            $$.ms = mstring_init_string( whilehead );
            $$.ms = mstring_dedent($$.ms, 1);
            omFree(whilehead);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "whilecmd", "WHILE_CMD STRINGTOK BLOCKTOK", $$.ms);
#endif
#endif            
          }
        ;

forcmd:
        FOR_CMD STRINGTOK STRINGTOK STRINGTOK BLOCKTOK
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            /* rewrite it as a while loop */
            char * prelimina  = (char *) omAlloc (strlen($2)+50);
            sprintf(prelimina, "%s;", $2);
            char * whilehead  = (char *) omAlloc (strlen($3)+50);
            sprintf(whilehead, "while (%s)", $3);
            char * whilebody  = (char *) omAlloc (strlen($4)+strlen($5)+50);
            sprintf(whilebody, "{%s%s;}", $5, $4);
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
            char * s = (char *)omAlloc( strlen($3)+strlen($4)+strlen($5)+36);
            sprintf(s,"forif (!(%s)) break;\n%s%s;\ncontinue;\n "
                   ,$3,$5,$4);
            newBuffer(s,BT_break);
            s = (char *)omAlloc( strlen($2) + 3);
            sprintf(s,"%s;\n",$2);
            newBuffer(s,BT_if);
#endif            
            omFree((ADDRESS)$2);
            omFree((ADDRESS)$3);
            omFree((ADDRESS)$4);
            omFree((ADDRESS)$5);
#ifdef JL_TRANSLATOR_GRAMMAR
            newBuffer( whileloop, BT_break );
            $$.ms = mstring_init_string( " " );
/*             $$.ms = mstring_dedent($$.ms, 1); */
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "forcmd", "FOR_CMD STRINGTOK STRINGTOK STRINGTOK BLOCKTOK");
            printf("\n");
#endif
#endif            
          }
        ;

proccmd:
        PROC_CMD extendedid BLOCKTOK
          {
            idhdl h = enterid($2,myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL) {omFree((ADDRESS)$2);omFree((ADDRESS)$3); YYERROR;}
            iiInitSingularProcinfo(IDPROC(h),"", $2, 0, 0);
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen($3)+31);;
            sprintf(IDPROC(h)->data.s.body,"parameter list #;\n%s;return();\n\n",$3);
            omFree((ADDRESS)$3);
            omFree((ADDRESS)$2);
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "proccmd", "PROC_CMD extendedid BLOCKTOK");
            printf("\n");
#endif
#endif
          }
        | PROC_DEF STRINGTOK BLOCKTOK
          {
#ifdef JL_TRANSLATOR_GRAMMAR
/*             printf(" $1: %s, $2: %s, $3: %s \n", $1, $2, $3); */
/*             printf("\n"); */
/*             printf(" $2: %s, len: %d\n", $2, strlen($2)); */
            add_symbol_in_table_of_symbol_string($1);
            char * funcname  = (char *) omAlloc (strlen($1)+15);
            char * funcargt  = iiProcArgs($2,FALSE);
            char * funcargs  = (char *) omAlloc (strlen(funcargt)+2);
            if (strlen(funcargt)>0){
                sprintf(funcname, "function %s(", $1);
                sprintf(funcargs, "(%s)", funcargt);
            }
            else {
                sprintf(funcname, "function %s()", $1);
                sprintf(funcargs, "%s", funcargt);
            }
            char * funcbody  = (char *) omAlloc (strlen(funcargs)+strlen($3)+14);
            sprintf(funcbody, "%s\n%s\njulia_endproc\n", funcargs, $3);
/*             printf(" functionargt: %s, len: %d\n", funcargt, strlen(funcargt)); */
/*             printf(" functionargs: %s, len: %d\n", funcargs, strlen(funcargs)); */
/*             printf(" functionbody: %s, len: %d\n", funcbody, strlen(funcbody)); */
            omFree(funcargt);
            omFree(funcargs);
#endif
            idhdl h = enterid($1,myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL)
            {
              omFree((ADDRESS)$1);
              omFree((ADDRESS)$2);
              omFree((ADDRESS)$3);
              YYERROR;
            }
            char *args=iiProcArgs($2,FALSE);
            omFree((ADDRESS)$2);
            iiInitSingularProcinfo(IDPROC(h),"", $1, 0, 0);
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen($3)+strlen(args)+14);;
            sprintf(IDPROC(h)->data.s.body,"%s\n%s;return();\n\n",args,$3);
            omFree((ADDRESS)args);
            omFree((ADDRESS)$3);
            omFree((ADDRESS)$1);
#ifdef JL_TRANSLATOR_GRAMMAR
            newBuffer( funcbody, BT_proc );
            $$.ms = mstring_init_string( funcname );
            $$.ms = mstring_dedent($$.ms, 1);
            omFree(funcname);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "proccmd", "PROC_DEF STRINGTOK BLOCKTOK", $$.ms);
#endif
#endif
          }
        | PROC_DEF STRINGTOK STRINGTOK BLOCKTOK
          {
            omFree((ADDRESS)$3);
            idhdl h = enterid($1,myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL)
            {
              omFree((ADDRESS)$1);
              omFree((ADDRESS)$2);
              omFree((ADDRESS)$4);
              YYERROR;
            }
            char *args=iiProcArgs($2,FALSE);
            omFree((ADDRESS)$2);
            iiInitSingularProcinfo(IDPROC(h),"", $1, 0, 0);
            omFree((ADDRESS)$1);
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen($4)+strlen(args)+14);;
            sprintf(IDPROC(h)->data.s.body,"%s\n%s;return();\n\n",args,$4);
            omFree((ADDRESS)args);
            omFree((ADDRESS)$4);
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "proccmd", "PROC_DEF STRINGTOK STRINGTOK BLOCKTOK");
            printf("\n");
#endif
#endif
          }
        ;

parametercmd:
        PARAMETER declare_ip_variable
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ($2.Typ() == INT_CMD){
                $2.ms = mstring_concat( $2.ms, mstring_init_string("::Int32") );
            }
            else if ($2.Typ() == BIGINT_CMD) {
                $2.ms = mstring_concat( $2.ms, mstring_init_string("::BigInt") );
            }
//             else {
//                 $$.ms = $2.ms;
//             }
            $$.ms = $2.ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "parametercmd", "PARAMETER declare_ip_variable", $$.ms);
#endif
#else
            // decl. of type proc p(int i)
            if ($1==PARAMETER)  { if (iiParameter(&$2)) YYERROR; }
            else                { if (iiAlias(&$2)) YYERROR; }
#endif
          }
        | PARAMETER declare_ip_variable ';'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            if ($2.Typ() == INT_CMD){
                $2.ms = mstring_concat( $2.ms, mstring_init_string("::Int") );
            }
            else if ($2.Typ() == BIGINT_CMD) {
                $2.ms = mstring_concat( $2.ms, mstring_init_string("::BigInt") );
            }
//             else {
//                 $$.ms = $2.ms;
//             }
            $$.ms = $2.ms;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "parametercmd", "PARAMETER declare_ip_variable \';\'", $$.ms);
#endif
#endif
          }
        | PARAMETER expr
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
            if ($1==ALIAS_CMD) MYYERROR("alias requires a type");
            if ((iiDeclCommand(&tmp_expr,&$2,myynest,DEF_CMD,&IDROOT))
            || (iiParameter(&tmp_expr)))
              YYERROR;
          }
        ;

returncmd:
        RETURN '(' exprlist ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
            char * expr_str;
            if ($3.ms) expr_str = mstring_to_str( $3.ms ); //TODO: not sure it is safe
            else expr_str = setUninitialized();
            $$.ms = mstring_concat( mstring_init_string("return "), mstring_init_string(expr_str) );
            free(expr_str);
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule_ms(translator_NbRuleTraversed, "returncmd", "RETURN \'(\' exprlist \')\'", $$.ms);
#endif
#endif

#ifdef JL_TRANSLATOR_GRAMMAR
//             iiRETURNEXPR.Copy(&$3);
//             $3.CleanUp();
//             if (exitBuffer(BT_proc)) YYERROR;
#endif
          }
        | RETURN '(' ')'
          {
#ifdef JL_TRANSLATOR_GRAMMAR
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG
            printfrule(translator_NbRuleTraversed, "returncmd", "RETURN \'(\' \')\'");
            printf("\n");
#endif
#endif
#ifdef JL_TRANSLATOR_GRAMMAR
            if ($1==RETURN)
            {
              iiRETURNEXPR.Init();
              iiRETURNEXPR.rtyp=NONE;
              if (exitBuffer(BT_proc)) YYERROR;
            }
#endif
          }
        ;

listparametercmd: 
            parametercmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            $$ = $1;
            $$.ms = $1.ms;
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule_ms(translator_NbRuleTraversed, "listparametercmd", "parametercmd", $$.ms);
#endif
#endif
        }
            | listparametercmd parametercmd {
#ifdef JL_TRANSLATOR_GRAMMAR
            /*leftv v = &$1;
            while (v->next!=NULL)
            {
              v=v->next;
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&($3),sizeof(sleftv));*/
            $$ = $1;
/*             $$.ms = $1.ms; */
            $$.ms = ms_conc_ms_s_ms( $1.ms, ", ", $2.ms);
            translator_NbRuleTraversed++;
#ifdef JL_TRANSLATOR_GRAMMAR_DEBUG    
            printfrule_ms(translator_NbRuleTraversed, "listparametercmd", "listparametercmd parametercmd",$$.ms);
#endif
#endif
            }
            ;
            
