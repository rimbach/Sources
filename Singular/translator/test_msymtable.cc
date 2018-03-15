#include "msymtable.h"

int main(){
    char s1[10] = "test1";
    char s2[10] = "test2";
    char s3[10] = "test3";
    
    msymtable mtab = msymtable_init();
    mtab = msymtable_add_name(mtab, s1);
    
    printf("is s1 in mtab: %d \n", msymtable_is_name_in_msymtable(mtab, s1));
    printf("is s2 in mtab: %d \n", msymtable_is_name_in_msymtable(mtab, s2));
    
    mtab = msymtable_add_name(mtab, s2);
    printf("is s1 in mtab: %d \n", msymtable_is_name_in_msymtable(mtab, s1));
    printf("is s2 in mtab: %d \n", msymtable_is_name_in_msymtable(mtab, s2));
    
    msymtable_free(mtab);
}
