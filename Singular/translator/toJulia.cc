#include "./toJulia.h"
#include "misc/prime.h"

/*coeffs construction */
#define DEBUG
mstring mstring_toJulia_coeffs ( leftv coeffs ) {
    mstring res;
//     res = mstring_init_string("<here the command for creating the coeffs in Julia>");
    const int P = coeffs->listLength();
    int float_len=0;
    int float_len2=0;
    
    if (coeffs->Typ()==CRING_CMD){
        res = mstring_init_string("Typ: CRING_CMD. Sorry but not yet implemented");
    }
    else if (coeffs->Typ()==INT_CMD){
        res = mstring_init_string("Typ: INT_CMD. Sorry but not yet implemented");
        
        int ch = (int)(long)coeffs->Data();
        leftv pnn=coeffs;
        pnn = pnn->next;
        if (pnn == NULL){
            if (ch!=0){
                int ch2=IsPrime(ch);
                if ((ch<2)||(ch!=ch2)) {
//                     Warn("%d is invalid as characteristic of the ground field. 32003 is used.", ch);
                    ch=32003;
                }
                char ch_str[50];
                mstring ch_ms;
                sprintf(ch_str, "%d", ch);    
//                 ch_ms  = ms_conc_s_ms_s( "$(Ptr{Void}(Clong(", mstring_init_string( ch_str ), "))) ");
                ch_ms  = ms_conc_s_ms_s( "Ptr{Void}(Clong(", mstring_init_string( ch_str ), ")) ");
//                 res = ms_conc_s_ms_s("field = icxx\"\"\"nInitChar( $(Cxx.@cxx n_Zp), ", ch_ms, ");\"\"\"");
                res = ms_conc_s_ms_s("libSingular.nInitChar( (Cxx.@cxx n_Zp), ", ch_ms, ")");
            }
            else {
//                 res = mstring_init_string("field = icxx\"\"\"nInitChar( $(Cxx.@cxx n_Q), $(Ptr{Void}(0)) );\"\"\"");
                res = mstring_init_string("libSingular.nInitChar( (Cxx.@cxx n_Q), Ptr{Void}(0) )");
            }
                
        }
        else {
            res = mstring_init_string("Typ: INT_CMD with param, should create GF something. Sorry but not yet implemented");
        }
    }
    else if ((coeffs->name != NULL)
    && ((strcmp(coeffs->name,"real")==0) || (strcmp(coeffs->name,"complex")==0))){
        
//         res = mstring_init_string("name: real or complex. Sorry but not yet implemented");
        
        leftv pnn=coeffs->next;
        bool complex_flag=(strcmp(coeffs->name,"complex")==0);
        if ((pnn!=NULL) && (pnn->Typ()==INT_CMD)){
            float_len=(int)(long)pnn->Data();
            float_len2=float_len;
            pnn=pnn->next;
            if ((pnn!=NULL) && (pnn->Typ()==INT_CMD)){
                float_len2=(int)(long)pnn->Data();
                pnn=pnn->next;
            }
        }
        if (!complex_flag) complex_flag= (pnn!=NULL) && (pnn->name!=NULL);
        if( !complex_flag && (float_len2 <= (short)SHORT_REAL_LENGTH)) {
//             res = mstring_init_string("name: real, simple precision floating point. Sorry but not yet implemented");
//             res = mstring_init_string("field = icxx\"\"\"nInitChar( $(Cxx.@cxx n_R), $(Ptr{Void}(0)) );\"\"\"");
            res = mstring_init_string("libSingular.nInitChar( (Cxx.@cxx n_R), Ptr{Void}(0) )");
        }
        else {
            
            LongComplexInfo param;
            param.par_name=(const char*)"\0";
            
            param.float_len = si_min (float_len, 32767);
            param.float_len2 = si_min (float_len2, 32767);

            // set the parameter name
            if (complex_flag){
                if (param.float_len < SHORT_REAL_LENGTH)
                {
                param.float_len= SHORT_REAL_LENGTH;
                param.float_len2= SHORT_REAL_LENGTH;
                }
                if ((pnn == NULL) || (pnn->name == NULL))
                param.par_name=(const char*)"i"; //default to i
                else
                param.par_name = (const char*)pnn->name;
            }
// should define somewhere in Julia:
//type LongComplexInfo
//    float_len::Cshort
//    float_len2::Cshort
//    par_name::Ptr{UInt8}
//end
            mstring param_ms, float_len_ms, float_len2_ms, par_name_ms;
            char float_len_str[50];
            char float_len2_str[50];
            sprintf(float_len_str, "%hd", param.float_len);
            sprintf(float_len2_str, "%hd", param.float_len2);
            float_len_ms  = ms_conc_s_ms_s( "Cshort(", mstring_init_string( float_len_str ), "), ");
            float_len2_ms = ms_conc_s_ms_s( "Cshort(", mstring_init_string( float_len2_str ), "), ");
            par_name_ms   = ms_conc_s_ms_s( "pointer(Vector{UInt8}(string(\"", mstring_init_string( param.par_name ), "\")))");
            param_ms = mstring_concat_3( float_len_ms, float_len2_ms, par_name_ms );
//             param_ms = ms_conc_s_ms_s("$(pointer_from_objref(LongComplexInfo(", param_ms, ")))");
            param_ms = ms_conc_s_ms_s("pointer_from_objref(LongComplexInfo(", param_ms, "))");
            if (complex_flag) {
//                 res = ms_conc_s_ms_s("field = icxx\"\"\"nInitChar( $(Cxx.@cxx n_long_C), ", param_ms, ");\"\"\"");
                res = ms_conc_s_ms_s("libSingular.nInitChar( (Cxx.@cxx n_long_C), ", param_ms, ")");
            }
            else {
//                 res = ms_conc_s_ms_s("field = icxx\"\"\"nInitChar( $(Cxx.@cxx n_long_R), ", param_ms, ");\"\"\"");
                res = ms_conc_s_ms_s("libSingular.nInitChar( (Cxx.@cxx n_long_R), ", param_ms, ")");
//                 res = mstring_init_string("name: complex or fixed precision real. Sorry but not yet implemented");
            }
        }
            
    }
    else if ((coeffs->name != NULL) && (strcmp(coeffs->name, "integer") == 0)){
        res = mstring_init_string("name: integer. Sorry but not yet implemented");
    }
    else if ((coeffs->Typ()==RING_CMD) && (P == 1)){
        res = mstring_init_string("Typ: RING_CMD. Sorry but not yet implemented");
    }
    else {
        res = mstring_init_string("Wrong or unknown ground field specification");
    }
    /*clean mstrings*/
    leftv voyager = coeffs;
    while (voyager!=NULL) {
        if (voyager->ms) mstring_free(voyager->ms);
        voyager = voyager->next; 
    }
    return res;
}

mstring mstring_toJulia_vars(leftv vars){
    mstring res = mstring_init_string("[pointer(Vector{UInt8}(string(str)*\"\\0\")) for str in [\"");
    res = mstring_concat(res, vars->ms);
    while (vars->next!=NULL) {
        res = ms_conc_ms_s_ms( res, "\",\"", vars->next->ms );
        vars = vars->next;
    }
    res = mstring_concat(res, mstring_init_string("\"]]"));
    return res;
}

mstring mstring_toJulia_ordering(leftv vars){
//     printf("REMI SAYS: ORDERING NOT YET IMPLEMENTED\n");
//     mstring res = mstring_init_string("(@cxx ringorder_lp)");
//     return res;
//     return mstring_toJulia_one_ordering(vars);
    if (vars->listLength() == 1)
        return mstring_toJulia_one_ordering(vars);
    
    mstring res = mstring_init_string("[");
    res = mstring_concat(res, mstring_toJulia_one_ordering(vars));
    while (vars->next!=NULL) {
        res = ms_conc_ms_s_ms( res, ", ", mstring_toJulia_one_ordering(vars->next) );
        vars = vars->next;
    }
    res = mstring_concat(res, mstring_init_string("]"));
    return res;
}

mstring mstring_toJulia_one_ordering(leftv vars){
    
    char * disp = mstring_to_str(vars->ms);
    if (strcmp(disp,rSimpleOrdStr(ringorder_no))==0) {
        mstring_free(vars->ms);
        return mstring_init_string("(@cxx ringorder_no)");
    }
    if (strcmp(disp,rSimpleOrdStr(ringorder_a64))==0){
        mstring_free(vars->ms);
        return mstring_init_string("(@cxx ringorder_a64)");
    }
    if (strcmp(disp,rSimpleOrdStr(ringorder_unspec))==0) {
        mstring_free(vars->ms);
        return mstring_init_string("(@cxx ringorder_unspec)");
    }
    free(disp);
    return ms_conc_s_ms_s("(@cxx ringorder_", vars->ms, ")");
}

/* aritmetic operations*/
mstring mstring_toJulia_ipp( mstring ms1 ){
    char * save = mstring_to_str(ms1);
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("+(", ms1, ", 1)");
#else
    res = ms_conc_s_ms_s("(", ms1, " + 1)");
#endif
    res = ms_conc_s_s_ms(save, "=", res);
    free(save);
    return res;
}

mstring mstring_toJulia_imm( mstring ms1 ){
    char * save = mstring_to_str(ms1);
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("-(", ms1, ", 1)");
#else
    res = ms_conc_s_ms_s("(", ms1, " - 1)");
#endif
    res = ms_conc_s_s_ms(save, "=", res);
    free(save);
    return res;
}

mstring mstring_toJulia_uminus( mstring ms1 ){
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("(-", ms1, ")");
#else
    res = ms_conc_s_ms_s("(-", ms1, ")");
#endif
    return res;
}

mstring mstring_toJulia_add( mstring ms1, mstring ms2 ){
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("+(", ms1, ", ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#else
    res = ms_conc_s_ms_s("(", ms1, " + ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#endif
    return res;
}

mstring mstring_toJulia_sub( mstring ms1, mstring ms2 ){
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("-(", ms1, ", ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#else
    res = ms_conc_s_ms_s("(", ms1, " - ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#endif
    return res;
}

mstring mstring_toJulia_div( mstring ms1, mstring ms2 ){
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("/(", ms1, ", ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#else
    res = ms_conc_s_ms_s("(", ms1, " / ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#endif
    return res;
}

mstring mstring_toJulia_mul( mstring ms1, mstring ms2 ){
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("*(", ms1, ", ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#else
    res = ms_conc_s_ms_s("(", ms1, " * ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#endif
    return res;
}

mstring mstring_toJulia_pow( mstring ms1, mstring ms2 ){
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("^(", ms1, ", ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#else
    res = ms_conc_s_ms_s("(", ms1, " ^ ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#endif
    return res;
}

/* comparisons */
mstring mstring_toJulia_cmp1(int ope, mstring ms1, mstring ms2 ){
    mstring res;
    char *op = (char *) malloc (3);
    switch (ope){
        case LE:
            sprintf(op, "<=");
            break;
        case GE:
            sprintf(op, ">=");
            break;
//         case EQUAL_EQUAL:
//             sprintf(op, "==");
//             break;
        case int('<'):
            sprintf(op, "<");
            break;
        case int('>'):
            sprintf(op, ">");
            break;
        default:
            sprintf(op, "%c", char(ope));
    }
    
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_s_ms( op, "(", ms1);
    res = ms_conc_ms_s_ms( res, ", ", ms2);
    res = mstring_concat( res, mstring_init_string(")"));
#else
    res = ms_conc_s_ms_s("(", ms1, op);
    res = ms_conc_ms_ms_s( res, ms2, ")");
#endif
    free(op);
    return res;
}

mstring mstring_toJulia_eqeq(mstring ms1, mstring ms2 ){
    mstring res;
#ifdef TOJULIA_PREFIX
    res = ms_conc_s_ms_s("==(", ms1, ", ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#else
    res = ms_conc_s_ms_s("(", ms1, " == ");
    res = ms_conc_ms_ms_s( res, ms2, ")");
#endif
    return res;
}