#ifndef TOJULIA_H
#define TOJULIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./mstring.h"

#include "Singular/subexpr.h"
#include "coeffs/coeffs.h"

/*prefixed notation*/
// #define TOJULIA_PREFIX

/*coeffs construction */
mstring mstring_toJulia_coeffs ( leftv coeffs );
/*list of vars construction*/
mstring mstring_toJulia_vars(leftv vars);
/*ordering construction*/
mstring mstring_toJulia_ordering(leftv vars);
mstring mstring_toJulia_one_ordering(leftv vars);

/* aritmetic operations*/
mstring mstring_toJulia_ipp( mstring ms1 );
mstring mstring_toJulia_imm( mstring ms1 );
mstring mstring_toJulia_uminus( mstring ms1 );
mstring mstring_toJulia_add( mstring ms1, mstring ms2 );
mstring mstring_toJulia_sub( mstring ms1, mstring ms2 );
mstring mstring_toJulia_div( mstring ms1, mstring ms2 );
mstring mstring_toJulia_mul( mstring ms1, mstring ms2 );
mstring mstring_toJulia_pow( mstring ms1, mstring ms2 );
/* comparisons */
mstring mstring_toJulia_cmp1(int ope, mstring ms1, mstring ms2 );
mstring mstring_toJulia_eqeq(mstring ms1, mstring ms2 );
#endif