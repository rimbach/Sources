Rémi Imbach, March 15, 2018
imbach@mathematik.uni-kl.de
or remi.imbach@laposte.net

This document is a short report on what I did for implementing 
a translator from the singular language to the julia language.

My work is in the (git) branch called "translator".

All the paths given in this document are relative paths 
given relatively to the singular source repository.

The translator takes the form of a Singular interpreter that translates
singular commands to julia commands.
The obtained julia commands can be interpreted by the julia
interpreter and the Singular.jl library + some add-ons
that are in the file Singular/translator/mySingular.jl.

0/ Installation / Compilation
==============================

git clone https://github.com/rimbach/Sources.git Singular
./autogen.sh
./configure

1/ Exemples
===========

a/ First exemple
-----------------
In Singular/ run ./Singular.
The prompt is now the question mark '?'.
Type:
? int a = 3;
The answer is:
JULIA COMMAND  STDIN (0) 0> a = Int32(3)
The first part, JULIA COMMAND  STDIN (0) 0>, can beignored.
The second part, a = Int32(3), is the julia command.
It can be directly copied/paste in a julia interpreter.

b/ Second exemple
-----------------

Type:


