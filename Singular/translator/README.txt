Rémi Imbach, March 15, 2018
imbach@mathematik.uni-kl.de
or remi.imbach@laposte.net

This document is a short report on what I did for implementing 
a translator from the singular language to the julia language.

My work is in the (git) branch called "translator".

All the paths given in this document are paths 
given relatively to the singular source repository.

The translator takes the form of a interpreter that translates
singular commands to julia commands.
The obtained julia commands can be interpreted by the julia
interpreter. 
The obtained julia commands use types and functions of
libSingular.jl, and some functions defined in
the file Singular/translator/mySingular.jl.

Below is a short overview of what has been done. 
a/ definition and arithmetic of int and bigint objects: PARTIALY DONE: &, NOTEQUAL (<>), DOTDOT (..), :, NOT (!) are not handled yet.
b/ definition and call of procedures:                   PARTIALY DONE: the rule proccmd: PROC_CMD extendedid BLOCKTOK is not handled
c/ flow controls 1: while and for loops:                DONE
d/ flow controls 2: if - else -end :                    PROBLEMATIC  
e/ rings declaration:                                   PARTIALY DONE: partial support of fields, variables and ordering
f/ number over fields and polynomials:                  DONE
g/ ideals and standard basis :                          DONE
h/ everything else:                                     TODO
Details are given in 3/ of this document

0/ Installation / Compilation / Exemples
========================================

a/ Installation / Compilation
-----------------------------
git clone https://github.com/rimbach/Sources.git Singular
git checkout translator
./autogen.sh
./configure
make 

b/ First exemple: basic definition
-----------------------------------
In Singular/ run ./Singular.
The prompt is now the question mark '?'.
Type:
? int a = 3;
The answer is:
JULIA COMMAND  STDIN (0) 0> a = Int32(3)
The first part, JULIA COMMAND  STDIN (0) 0>, can be ignored.
The second part, a = Int32(3), is the julia command.
It can be directly copied/pasted in a julia interpreter.

c/ Second exemple: procedure and flow-controls
----------------------------------------------
When defining the procedure:

proc times2totheN(int a, int N){
    int i=1;
    while (i<=N) {
        a = a + a;
        i++;
    }
    return(a)
}

one obtains:

JULIA COMMAND  FUNCT (0) 1> function times2totheN( 
JULIA COMMAND  FUNCT (0) 1>    a::Int, N::Int) 
JULIA COMMAND  FUNCT (0) 1>    i = Int32(1) 
JULIA COMMAND   LOOP (0) 2>    while 
JULIA COMMAND   LOOP (0) 2>       (i<=N) 
JULIA COMMAND   LOOP (0) 2>       a = Int32((a + a)) 
JULIA COMMAND   LOOP (0) 2>       i=(i + 1) 
JULIA COMMAND  FUNCT (0) 1>    end 
JULIA COMMAND  FUNCT (0) 1>    return a 
JULIA COMMAND  STDIN (0) 0> end

One can copy/paste the julia command in a julia 
interpreter to define the julia procedure.

a call to times2totheN:
? times2totheN(1,2);
gives the julia command:
JULIA COMMAND  STDIN (0) 0> times2totheN(1, 2)


d/ Third exemple: defining an ideal and computing its standard basis
---------------------------------------------------------------------

Type:
ring r = 0,(x,y), dp;
ideal i = x+y, xy;
ideal si = std(i);
si;

The answers are:

JULIA COMMAND  STDIN (0) 0> r=libSingular.rDefault(libSingular.nInitChar( (Cxx.@cxx n_Q), Ptr{Void}(0) ),
[pointer(Vector{UInt8}(string(str)*"\0")) for str in ["x","y"]],
(@cxx ringorder_dp))
 _singular_actual_ring = r 
JULIA COMMAND  STDIN (0) 0> i = idealFromArray([(p_mInit(pointer(Vector{UInt8}("x")), _singular_actual_ring) + p_mInit(pointer(Vector{UInt8}("y")), _singular_actual_ring)), p_mInit(pointer(Vector{UInt8}("xy")), _singular_actual_ring)]) 
JULIA COMMAND  STDIN (0) 0> si = m_id_Std(i, _singular_actual_ring) 
JULIA COMMAND  STDIN (0) 0> id_String(si,"si",_singular_actual_ring) 

In the Julia interpreter, include Singular/translator/mySingular.jl:
julia> include("mySingular.jl")

then copy/paste one by one the julia commands
and finally obtain:

julia> id_String(si,"si",_singular_actual_ring)
si[1]=x+y
si[2]=y^2

1/ Architecture of the singular-julia translator
================================================
The grammar of the singular langage is defined in Singular/grammar.y
The later file describes language rules and the interpretation of sentences
of the language.
With the classical singular interpreter, commands are evaluated,
whereas with the singular-julia translator, commands
are translated in julia commands, i.e. in strings.

The file describing how sentences of the singular language 
are translated into strings is Singular/grammartranslator.y
It introduces little changes in the grammar that were
required to handle procedure definitions and flow controls.
See a/ below.

Constructing the strings from singular commands requires
(1) a data structure dedicated to string management,
(2) to modify the type of terminal and non-terminal symbols (interpreted objects)
so that it carries the sub-strings corresponding to under-construction julia commands
(3) modifying the rules of the grammar to construct the strings
from terminal and non-terminal symbols.
(1) and (2) are described in b/ below.
(3) is described in 3/

a/ New grammar
---------------
The new grammar as defined in Singular/grammartranslator.y
introduces little changes in the grammar:

1 - four new terminal symbols have been added:
%token <i> JULIA_ENDELSE_CMD
%token <i> JULIA_ENDIF_CMD
%token <i> JULIA_ENDLOOP_CMD
%token <i> JULIA_ENDPROC_CMD
(notice these symbols have also been added to Singular/grammar.y
for the co-existence of the two grammars)

2 - four new rules for constructing a flowctrl from the new 
terminal symbols have been defined

These changes are required to handle procedure definition and flow controls.
The grammar defined in Singular/grammartranslator.y 
can then be seen as an extension of the one
defined in Singular/grammar.y.

b/ Constructing strings instead of evaluating commands
-------------------------------------------------------
Singular/translator/mstring.h and Singular/translator/mstring.cc
implement strings as linked lists of char, and define the type mstring as 
a pointer on a linked list of char.
It provides: -initialization of a mstring from a characted or a string (const char *),
             -construction of a string (char *) from a mstring (it allocated memory so 
              the returned object has to be freed by the caller)
             -concatenation of two mstring; this is a destructive concatenation,
              meaning that the concatenated strings are empty after the concatenation,
              and it is not necessary to de-allocate memory.
             -based on the previous function, concatenation of char * and strings.
See Singular/translator/mstring.h and Singular/translator/mstring.cc for details.

The class sleftv defined in Singular/subexpr.h
defines (list of) interpreted objects.
It has now a new public attribute of type mstring, called ms,
pointing on a string corresponding to the julia command
constructing the interpreted object.
Notice that at the creation of an object o of the class sleftv,
ms is an uninitialized pointer, and ms is false until a call to 
mstring_init_something(o.ms).

In Singular/grammartranslator.y (and also in Singular/grammar.y) 
the symbols having the type <lv> corresponds to the class sleftv
(see Singular/stype.h).

In Singular/grammartranslator.y, some non-terminal symbols
have now the type <lv> (instead of no type in Singular/grammar.y).
%type <lv> assign 
%type <lv> command 
%type <lv> exportcmd killcmd listcmd parametercmd ringcmd scriptcmd setringcmd typecmd
%type <lv> pprompt
%type <lv> flowctrl ifcmd whilecmd example_dummy forcmd proccmd filecmd helpcmd
%type <lv> returncmd
%type <lv> listparametercmd 
This allow to define rules constructing julia command (i.e. mstrings)
for these symbols.

2/ Practical things
===================
After a change to the grammar file Singular/grammartranslator.y,
the grammar has to be re-generated. This is done with 
make_grammar in Singular/
Then run 
make Singular in Singular/
to generate the main programm.

Understanding the symbol constructions from rules defined 
in Singular/grammartranslator.y is an hard task for a human.
When decommenting the preprocessor directive
#define JL_TRANSLATOR_GRAMMAR_DEBUG
in Singular/grammartranslator.y,
the programm will display how rules are called.
But this is very verbose.

3/ State of the implementation
===============================

a/ definition and arithmetic of int and bigint objects: PARTIALY DONE
-------------------------------------------------------
The types int and bigint of singular are 
mapped to types Int32 and BigInt of julia.
This is hard-coded in the rule 
assign: left_value exprlist

Julia commands corresponding to arithmetic expressions are constructed 
in the rules for constructing symbol expr_arithmetic.
The strings are constructed in functions of translator/toJulia.h
and translator/toJulia.cc

The arithmetic operations &, 
NOTEQUAL (<>)
DOTDOT (..)
:
NOT (!)
are not handled yet.

b/ definition and call of procedures: PARTIALY DONE
-------------------------------------
Translation of whole procedures is handled througth the 
buffer mechanism. Buffers are defined in 
Singular/fevoices.h and Singular/fevoices.cc

Consider the procedure 
proc myAdd(int a, int b){
    return(a+b)
}

When a procedure declaration is encountered
(see the rule proccmd: ... | PROC_DEF STRINGTOK BLOCKTOK)
two strings are created.
The first one is roughly the head of the corresponding julia function:
function myAdd(
that is the attribute ms of the constructed symbol (proccmd).
The other one is a singular sequence of commands that will
be interpreted in a new buffer:
(parameter int a; parameter int b; )
    return(a+b)
julia_endproc

The new buffer interprets the body of the function and
stops when "julia_endproc", corresponding to 
the terminal symbol JULIA_ENDPROC_CMD,
is encountered.
See the rule pprompt: ... | JULIA_ENDPROC_CMD for more details.

The typing of the parameters is hard-coded in the rule:
parametercmd: ... | PARAMETER declare_ip_variable ';'
and it could be extended for handling other types.

The translation of the call to a procedure 
for instance 
myAdd(1,2);
is done in the rule:
elemexpr: ... elemexpr '(' exprlist ')'

Notice that the rule 
proccmd: PROC_CMD extendedid BLOCKTOK
is not handled

c/ flow controls 1: while and for loops: DONE
----------------------------------------

The while loops are handled more or less in the same
way than the procedure definitions,
and the for loops are translated in while loops.
See the rules 
whilecmd: WHILE_CMD STRINGTOK BLOCKTOK
and
forcmd: FOR_CMD STRINGTOK STRINGTOK STRINGTOK BLOCKTOK
for details.

d/ flow controls 2: if - else -end : PROBLEMATIC
------------------------------------
This flow control is problematic because of the "end"
keyword that is required in julia but not in Singular:
in the Singular interpreter, an "if" statement is
interpreted regardless of the existence of a pending 
"else" statement.

For now, if one type:
? if (1==1) {1+1;} else { 1-1;}
the answer is:
JULIA COMMAND  FUNCT (0) 1> if ( (1 == 1) ) 
JULIA COMMAND  FUNCT (0) 1>    (1 + 1) 
JULIA COMMAND  FUNCT (0) 2>    else  
JULIA COMMAND  FUNCT (0) 2>       (1 - 1) 
JULIA COMMAND  FUNCT (0) 1>    end 
JULIA COMMAND  STDIN (0) 0> end
and it is fine.
But if one type:
? if (1==1) {1+1;};
the answer is
JULIA COMMAND  FUNCT (0) 1> if ( (1 == 1) ) 
JULIA COMMAND  FUNCT (0) 1>   
JULIA COMMAND  FUNCT (0) 1>    (1 + 1) 
JULIA COMMAND  STDIN (0) 0> end
and 
? else { 1-1;}
gives
JULIA COMMAND  FUNCT (0) 1> else  
JULIA COMMAND  FUNCT (0) 1>    (1 - 1) 
JULIA COMMAND  STDIN (0) 0> end

If the translator is used to translate a file,
one can make a pass on the obtained file 
to remove the "end" after the if statement...

e/ rings declaration: PARTIALY DONE
---------------------
Simple ring declaration commands like: 
ring r = field, vars, ordering
are handled by the translator.

It requires the ability of translating: 
- a field, this is done only for several fields in the function 
mstring_toJulia_coeffs in Singular/translator/toJulia.cc
- a list of variables, this is done in the function 
mstring_toJulia_vars in Singular/translator/toJulia.cc
- an ordering, this is done in the function 
mstring_toJulia_ordering in Singular/translator/toJulia.cc

The fields that are handled are real and complex floating points 
(i.e. real, (real, mantissa), complex, (complex, mantissa), (complex, mantissa, sqrtminus1))
and integers fields (i.e. Z/pZ, declared with an integer) and Q (declared with 0).

The list of variables that are handled are of the type (x,y,...):
indexed variables (e.g. (x(1..10))) are not supported. 

The ordering that are handled are
-simple orderings i.e. dp, lp, ...
- list of simple orderings i.e. (dp,lp)

Interpreting obtained julia commands require to include 
Singular/translator/mySingular.jl
that imports types from libSingular.jl of Singular.jl
It also uses a global variable _singular_actual_ring
that is set to the actual singular ring by the julia command.

f/ number over fields and polynomials: DONE
-------------------------------------
Polynomial definition is tricky because of the Singular syntax for monomials:
2x2 in singular means 2*x^2.
For handling this kind of syntax in the translator, I did the following.

For the declaration of a poly or a number, the translator 
enters in a special mode "ring_decl".
When the translator is in this mode, 
each non declared symbol 
(e.g x, or 2x2 or xy ...) 
is translated into the julia command:
p_mInit(pointer(Vector{UInt8}("2x2")), _singular_actual_ring)
The function p_mInit(...,...) calls a singular function
that constructs a monomial on a ring from a string.

The mode ring_decl is handled by the attribute ring_decl of the class Voice
defined in Singular/devoices.h.
Then it suffices to set currentVoice->ring_decl to 1 when one of the keywords
"poly" or "number" is encountered
(see the rule declare_ip_variable: ... | RING_DECL elemexpr)
and to set it to 0 at the assignment 
(see the rule assign: left_value exprlist).

Testing if a symbol has already been declared
is done by consulting a table of symbols that is 
independant from the one of the original interpreter.
This table of symbols is implemented in 
Singular/translator/msymtable.h and Singular/translator/msymtable.cc
as a linked list of strings.
The table of symbols is the attribute table_of_symbols of the class voice
and the table of symbols of the current scope can be accessed with
currentVoice->table_of_symbols.

The functions for adding a symbol to the table 
of symbols of the actual scope are
void add_symbol_in_table_of_symbol_string(const char * name)
and 
void add_symbol_in_table_of_symbol_mstring(mstring ms)

The function for checking in the table of symbols of all scopes
is
int is_symbol_in_table_of_symbol(const char * name)

These functions are defined in Singular/grammartranslator.y

g/ ideals and standard basis :
------------------------------
The definintion of an ideal boils down to the 
construction of a list of polynomials.
Then the function idealFromArray defined in mySingular.jl
does the work.

The translation of std (the singular command for the standard basis)
is done in the rule
elemexpr: ... | CMD_M '(' exprlist ')'.


h/ everything else: TODO
------------------------

ANNEXE A: co-existence of two grammar files
===========================================

++++ in Singular/grammartranslator.h:
- replace #include "Singular/grammar.h" 
with #include "Singular/grammartranslator.h"
- add %define api.prefix {jl} before the definition of the symbols.
the new grammar now uses now it uses JLSTYPE, JLLTYPE,jlparse, jllval
instead of YYSTYPE, YYLTYPE, yyparse, yylval

++++ in grammar.h (generated by make_grammar)
- add #ifndef YY_JL_GRAMMARTRANSLATOR_HH_INCLUDED
in the beginning end #endif at the end

++++ in grammartranslator.h (generated by make_grammar)
- add "#ifndef YY_YY_GRAMMAR_HH_INCLUDED"
in the beginning end #endif at the end

++++ in grammartranslator.cc (generated by make_grammar)
-comment or suppress 
#define yylex jllex
and
#define YYSTYPE JLSTYPE

The three latter modifications are made in make_grammar.

Finally jlparse() is used instead of yyparse() in 
Singular/tesths.cc

