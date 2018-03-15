using Nemo
using Cxx

###################################### THIS IS BECAUSE using Singular doesnt work for me
# const pkgdir = realpath(joinpath(dirname(@__FILE__), ".."))
const pkgdir = realpath("/home/remi/.julia/v0.6/Singular")
const libsingular = joinpath(pkgdir, "local", "lib", "libSingular")

prefix = joinpath(Pkg.dir("Singular"), "local");
nemoinc = joinpath(Pkg.dir("Nemo"), "local");

addHeaderDir(joinpath(prefix, "include"), kind = C_User)
addHeaderDir(joinpath(prefix, "include", "singular"), kind = C_User)
addHeaderDir(joinpath(prefix, "include", "resources"), kind = C_User)
addHeaderDir(joinpath(nemoinc, "include"), kind = C_User)

function __init__()
   Libdl.dlopen(libsingular, Libdl.RTLD_GLOBAL)

   # include Singular header files

   cxxinclude(joinpath("gmp.h"), isAngled = false)
   cxxinclude(joinpath("omalloc", "omalloc.h"), isAngled = false)
   cxxinclude(joinpath("misc", "intvec.h"), isAngled = false)
   cxxinclude(joinpath("misc", "auxiliary.h"), isAngled = false)
   cxxinclude(joinpath("reporter", "reporter.h"), isAngled = false)
   cxxinclude(joinpath("feFopen.h"), isAngled = false)
   cxxinclude(joinpath("coeffs", "coeffs.h"), isAngled = false)
   cxxinclude(joinpath("polys", "clapsing.h"), isAngled = false)
   cxxinclude(joinpath("coeffs", "bigintmat.h"), isAngled = false)
   cxxinclude(joinpath("coeffs", "rmodulon.h"), isAngled = false)
   cxxinclude(joinpath("polys", "monomials", "ring.h"), isAngled = false)
   cxxinclude(joinpath("polys", "monomials", "p_polys.h"), isAngled = false)
   cxxinclude(joinpath("polys", "simpleideals.h"), isAngled = false)
   cxxinclude(joinpath("kernel", "GBEngine", "kstd1.h"), isAngled = false) 
   cxxinclude(joinpath("kernel", "GBEngine", "syz.h"), isAngled = false)
   cxxinclude(joinpath("kernel", "ideals.h"), isAngled = false)
   cxxinclude(joinpath("kernel", "polys.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "grammar.h"), isAngled = false) 
   cxxinclude(joinpath("Singular", "libsingular.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "fevoices.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "ipshell.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "ipid.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "subexpr.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "lists.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "idrec.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "tok.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "links", "silink.h"), isAngled = false)
   cxxinclude(joinpath("Singular", "fehelp.h"), isAngled = false)

   # Initialise Singular
   
#    binSingular = joinpath(prefix, "bin", "Singular")
#    ENV["SINGULAR_EXECUTABLE"] = binSingular
# 
#    @cxx siInit(pointer(binSingular))
# 
#    # set up Singular parents (we cannot do this before Singular is initialised)
# 
#    ZZ.ptr = get_n_Z()
#    ZZ.refcount = 1
# 
#    QQ.ptr = get_n_Q()
#    QQ.refcount = 1
# 
#    # done in __init__ since headers must be included first
# 
#    global const n_Z_2_n_Q = libSingular.n_SetMap(ZZ.ptr, QQ.ptr)
#    global const n_Q_2_n_Z = libSingular.n_SetMap(QQ.ptr, ZZ.ptr)
# 
#    global const ringorder_no = @cxx ringorder_no
#    global const ringorder_lp = @cxx ringorder_lp
#    global const ringorder_rp = @cxx ringorder_rp
#    global const ringorder_dp = @cxx ringorder_dp
#    global const ringorder_Dp = @cxx ringorder_Dp
#    global const ringorder_ls = @cxx ringorder_ls
#    global const ringorder_rs = @cxx ringorder_rs
#    global const ringorder_ds = @cxx ringorder_ds
#    global const ringorder_Ds = @cxx ringorder_Ds
#    global const ringorder_c  = @cxx ringorder_c
#    global const ringorder_C  = @cxx ringorder_C
# 
#    global const sym2ringorder = Dict{Symbol, Cxx.CppEnum}(
#    	  :lex => ringorder_lp,
#       :revlex => ringorder_rp, 
#    	  :neglex => ringorder_ls,
#       :negrevlex => ringorder_rs, 
# 	  :degrevlex => ringorder_dp,
#       :deglex => ringorder_Dp,
# 	  :negdegrevlex => ringorder_ds,
#       :negdeglex => ringorder_Ds,
# 	  :comp1max => ringorder_c,
#       :comp1min => ringorder_C
#    )
end

###################################### THIS IS BECAUSE using Singular doesnt work for me

# include("/home/remi/.julia/v0.6/Singular/src/LibSingular.jl")
# include("/home/remi/.julia/v0.6/Singular/src/libsingular/LibSingularTypes.jl")

# using Cxx
# using Singular
include("/home/remi/.julia/v0.6/Singular/src/LibSingular.jl")
include("/home/remi/.julia/v0.6/Singular/src/libsingular/LibSingularTypes.jl")

type LongComplexInfo
    float_len::Cshort
    float_len2::Cshort
    par_name::Ptr{UInt8}
end

function p_mInit(rep::Ptr{UInt8}, r::ring)
    dummy::Cint =1;
    n = icxx"""p_mInit($rep, $dummy, $r);"""
    return n
end

__init__()

# _singular_actual_ring = libSingular.rDefault(libSingular.nInitChar( (Cxx.@cxx n_Q), Ptr{Void}(0) ),
#                                                      [pointer(Vector{UInt8}(string(str)*"\0")) for str in ["x"]],
#                                                      (@cxx ringorder_lp))
_singular_actual_ring = 0;

import Base: *, +, -, ^

function *(p::poly, q::poly )
    return libSingular.p_Mult_q(p, q, _singular_actual_ring)
end

function *(p::poly, q::Int )
    qpoly = p_mInit(pointer(Vector{UInt8}(string(q))), _singular_actual_ring)
    return *(p,qpoly)
end

function *(p::Int, q::poly )
    return *(q,p)
end

function +(p::poly, q::poly )
    return libSingular.p_Add_q(p, q, _singular_actual_ring)
end

function +(p::poly, q::Int )
    qpoly = p_mInit(pointer(Vector{UInt8}(string(q))), _singular_actual_ring)
    return +(p,qpoly)
end

function +(p::Int, q::poly )
    return +(q,p)
end

function -(p::poly)
    return libSingular.p_Neg(p, _singular_actual_ring)
end

function -(p::poly, q::poly )
    return libSingular.p_Sub(p, q, _singular_actual_ring)
end

function -(p::poly, q::Int )
    qpoly = p_mInit(pointer(Vector{UInt8}(string(q))), _singular_actual_ring)
    return -(p,qpoly)
end

function -(p::Int, q::poly )
    ppoly = p_mInit(pointer(Vector{UInt8}(string(p))), _singular_actual_ring)
    return -(ppoly,q)
end

function ^(x::poly, y::Int)
    y > typemax(Cint) || y < typemin(Cint) && throw(DomainError())
    return libSingular.p_Power(x, Cint(y), _singular_actual_ring)
end

function id_String(id::ideal, name::String, r::ring)
   for i=1:libSingular.ngens(id)
        print("$name[$i]=")
        print(STDOUT,unsafe_string(libSingular.p_String(libSingular.getindex(id, Cint(i-1)), r)))
        print("\n")
   end
end

function idealFromArray(ids::Array{poly, 1})
   n = length(ids)
   id = libSingular.idInit(Cint(n))
   for i = 1:n
        libSingular.setindex!(id, ids[i], Cint(i - 1))
   end
   return id
end

function m_id_Std(I:: ideal, R::ring; complete_reduction::Bool=false)
   if complete_reduction
      crbit = icxx"""Sy_bit(OPT_REDSB);"""
   else
      crbit = Cuint(0);
   end
   icxx"""ideal id = NULL;
          if (!idIs0($I))
          {
             intvec * n = NULL;
             tHomog h = testHomog;
             const ring origin = currRing;
             unsigned int save_opt = si_opt_1;
             si_opt_1 |= $crbit;
             rChangeCurrRing($R);
             id = kStd($I, $R->qideal, h, &n);
             si_opt_1 = save_opt;
             rChangeCurrRing(origin);
             if (n != NULL)
                delete n;
          } else
             id = idInit(0, $I->rank);
          idSkipZeroes (id);
          id;
       """
end