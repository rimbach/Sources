#ifndef MSTRING_H
#define MSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mchar {
    char          _char;
    struct mchar *_next;
};

struct list_mchar {
    struct mchar *_begin;
    struct mchar *_end;
    int           _size;
};

typedef struct list_mchar * mstring;

mstring mstring_init();

mstring mstring_free(mstring m);

mstring mstring_init_char( char c );

mstring mstring_concat( mstring ms1, mstring ms2 );

mstring mstring_init_string( const char * s );    

char * mstring_to_str(mstring ms);

// void mstring_print( mstring ms );

mstring mstring_concat_3( mstring ms1, mstring ms2, mstring ms3);

static __inline__ mstring ms_conc_ms_s_ms(mstring ms1, const char * ms2, mstring ms3){
    return mstring_concat_3( ms1, mstring_init_string(ms2), ms3);
}

static __inline__ mstring ms_conc_s_ms_s(const char * ms1, mstring ms2, const char * ms3){
    return mstring_concat_3( mstring_init_string(ms1), ms2, mstring_init_string(ms3));
}

static __inline__ mstring ms_conc_ms_ms_s(mstring ms1, mstring ms2, const char * ms3){
    return mstring_concat_3( ms1, ms2, mstring_init_string(ms3));
}

static __inline__ mstring ms_conc_s_ms_ms(const char * ms1, mstring ms2, mstring ms3){
    return mstring_concat_3( mstring_init_string(ms1), ms2, ms3);
}

static __inline__ mstring ms_conc_s_s_ms(const char * ms1, const char * ms2, mstring ms3){
    return mstring_concat_3( mstring_init_string(ms1), mstring_init_string(ms2), ms3);
}

mstring mstring_get_lofstr(mstring ms);

mstring mstring_init_mstring(mstring ms);

#define NB_SPACE_BY_INDENT 3
mstring mstring_indent(mstring ms, int depth);
mstring mstring_dedent(mstring ms, int depth);

// mstring exp_PLUS__expr ( mstring ms1, mstring ms2);
// mstring exp_MINUS_expr ( mstring ms1, mstring ms2);
// mstring exp_DIV___expr ( mstring ms1, mstring ms2);


#endif