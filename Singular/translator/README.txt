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