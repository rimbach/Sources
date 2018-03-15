#include "./mstring.h"

mstring mstring_init(){
    mstring m = (mstring) malloc ( sizeof(struct list_mchar) );
    m->_begin = m->_end = NULL;
    m->_size = 0;
    return m;
}

mstring mstring_free(mstring m){
    struct mchar * voyager = m->_begin;
    while (m->_begin!=m->_end) {
        voyager = m->_begin;
        m->_begin = m->_begin->_next;
        free(voyager);
    }
    if (m->_begin!=NULL)
        free(m->_begin);
    free(m);
    return m;
}

mstring mstring_init_char( char c ){
    struct mchar * mc = (struct mchar *) malloc (sizeof(struct mchar));
    mc->_char = c;
    mc->_next = NULL;
    mstring m = mstring_init();
    m->_begin = m->_end = mc;
    m->_size = 1;
    return m;
}

mstring mstring_concat( mstring ms1, mstring ms2 ){
    if (ms1->_size == 0 ) {
        free(ms1);
        return ms2;
    }
    if (ms2->_size == 0 ){
        free(ms2);
        return ms1;
    }
    
    mstring res = mstring_init();
    res->_begin = ms1->_begin;
    res->_end   = ms2->_end;
    ms1->_end->_next = ms2->_begin;
    res->_size = ms1->_size + ms2->_size;
    free(ms1); free(ms2);
    return res;
}

mstring mstring_init_string( const char * s ){
    int pos_in_string = 0;
    mstring m = mstring_init();
    
    while(s[pos_in_string]!= '\0' ) {
        m = mstring_concat( m, mstring_init_char(s[pos_in_string]));
        pos_in_string += 1;
    }
    
    return m;
}  

mstring mstring_init_mstring(mstring m){
    mstring res = mstring_init();
    struct mchar * voyager = m->_begin;
    while (voyager!=NULL) {
        res = mstring_concat( res, mstring_init_char( voyager->_char ));
        voyager = voyager->_next;
    }
    return res;
}


char * mstring_to_str(mstring ms){
    char * res = (char *) malloc ( ms->_size + 1 );
    int pos_in_string = 0;
    struct mchar * voyager = ms->_begin;
    while (voyager!=ms->_end){
        res[pos_in_string] = voyager->_char;
        voyager = voyager->_next;
        pos_in_string += 1;
    }
    if (voyager)
        res[pos_in_string] = voyager->_char;
    res[ms->_size] = '\0';
    return res;
}


// void mstring_print( mstring ms );

mstring mstring_concat_3( mstring ms1, mstring ms2, mstring ms3){
    mstring res = mstring_init();
    res = mstring_concat( ms1, ms2 );
    res = mstring_concat( res, ms3 );
    return res;
}

mstring mstring_indent(mstring ms, int depth){
    for(int i=0; i<depth*NB_SPACE_BY_INDENT; i++) 
        ms = mstring_concat( mstring_init_string( " " ), ms);
    return ms;
}

mstring mstring_dedent(mstring ms, int depth){
    for(int i=0; i<depth*NB_SPACE_BY_INDENT; i++) 
        ms = mstring_concat( mstring_init_string( "\u0008" ), ms);
    return ms;
}


mstring mstring_get_lofstr(mstring ms){
    
    struct mchar * voyager, * mc;
    
    voyager = ms->_begin;
    
//     mc = (struct mchar *) malloc (sizeof(struct mchar));
//     mc->_char = '\"';
//     mc->_next = ms->_begin;
//     ms->_begin = mc;
    ms = mstring_concat( mstring_init_char('\"'), ms );
    
//     mc = (struct mchar *) malloc (sizeof(struct mchar));
//     mc->_char = '\"';
//     mc->_next = NULL;
//     ms->_end->_next = mc;
//     ms->_end = mc;
    ms = mstring_concat( ms, mstring_init_char('\"') );
    
    while (voyager->_next !=NULL) {
        if (voyager->_next->_char == ',') {
            mc = (struct mchar *) malloc (sizeof(struct mchar));
            mc->_char = '\"';
            mc->_next = voyager->_next;
            voyager->_next = mc;
            ms->_size +=1;
            voyager = mc->_next;
        }
        if (voyager->_char == ',') {
            mc = (struct mchar *) malloc (sizeof(struct mchar));
            mc->_char = '\"';
            mc->_next = voyager->_next;
            voyager->_next = mc;
            ms->_size +=1;
//             voyager = voyager->_next;
        }
        voyager = voyager->_next;
    }
    return ms;
}