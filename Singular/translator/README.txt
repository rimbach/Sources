Rémi Imbach, March 15, 2018
imbach@mathematik.uni-kl.de
or remi.imbach@laposte.net

This document is a short report on what I did for implementing 
a translator from the singular language to the julia language.

My work is in the (git) branch called "translator".

All the paths given in this document are paths 
given relatively to the singular source repository.

The translator takes the form of a Singular interpreter that translates
singular commands to julia commands.
The obtained julia commands can be interpreted by the julia
interpreter and the Singular.jl library + some add-ons
that are in the file Singular/translator/mySingular.jl.

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
The first part, JULIA COMMAND  STDIN (0) 0>, can beignored.
The second part, a = Int32(3), is the julia command.
It can be directly copied/paste in a julia interpreter.

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
? times2totheN(1,2)
gives the julia command:
JULIA COMMAND  STDIN (0) 0> times2totheN(1, 2)


d/ Second exemple: defining an ideal and computing its standard basis
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

copy/paste one by one the julia commands
at the end and obtain:

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
corresponding to the interpreted object.
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

d/ flow controls 2: if - then - else -end : TODO
-------------------------------------------

e/ rings and numbers over fields and polynomials:
-------------------------------------------------

f/ ideals:
----------

g/ everything else: TODO
------------------------

ANNEXE A: co-existence of two grammar files
===========================================

