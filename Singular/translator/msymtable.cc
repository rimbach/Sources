#include "./msymtable.h"

msymtable msymtable_init(){
    msymtable m = (msymtable) malloc ( sizeof(struct list_mname) );
    m->_begin = m->_end = NULL;
    m->_size = 0;
    return m;
}

msymtable msymtable_free(msymtable m){
    struct mname * voyager = m->_begin;
    while (m->_begin!=m->_end) {
        voyager = m->_begin;
        m->_begin = m->_begin->_next;
        free(voyager->_name);
        free(voyager);
    }
    if (m->_begin!=NULL){
        free(m->_begin->_name);
        free(m->_begin);
    }
    free(m);
    return m;
}

msymtable msymtable_add_name(msymtable m, const char * name){
    struct mname * mn = (struct mname *) malloc (sizeof(struct mname));
    mn->_name = (char *) malloc (strlen(name) + 1);
//     sprintf(mn->_name, "%s", name);
    strcpy ( mn->_name, name);
    mn->_next = NULL;
    if (m->_size == 0) {
        m->_begin = m->_end = mn;
        m->_size = 1;
    }  
    else {
        m->_end->_next = mn;
        m->_end = m->_end->_next;
        m->_size += 1;
    }
    return m;
}

int msymtable_is_name_in_msymtable(msymtable m, const char * name){
    int res = 1;
    struct mname * voyager = m->_begin;
    while ((voyager!=NULL)&&(res!=0)) {
//         printf("voyager->_name: %s\n", voyager->_name);
//         printf("name:           %s\n", name);
        res = strcmp ( voyager->_name, name );
//         printf("res: %d\n", res);
        voyager = voyager->_next;
    }
    return !res;
}