
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

// $Source$
// $Date$
// $Revision$

#include <ndnboost/type_traits/detail/template_arity_spec.hpp>
#include <ndnboost/type_traits/integral_constant.hpp>
#include <ndnboost/mpl/bool.hpp>
#include <ndnboost/mpl/aux_/lambda_support.hpp>
#include <ndnboost/config.hpp>

//
// Unfortunately some libraries have started using this header without
// cleaning up afterwards: so we'd better undef the macros just in case 
// they've been defined already....
//
#ifdef NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL
#undef NDNBOOST_TT_AUX_BOOL_C_BASE
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_DEF1
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_DEF2
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC1
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC2
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC2
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_2
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_1
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_IMPL_PARTIAL_SPEC2_1
#undef NDNBOOST_TT_AUX_BOOL_TRAIT_CV_SPEC1
#endif

#if defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x570)
#   define NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    typedef ::ndnboost::integral_constant<bool,C> type; \
    enum { value = type::value }; \
    /**/
#   define NDNBOOST_TT_AUX_BOOL_C_BASE(C)
#endif

#ifndef NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL
#   define NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) /**/
#endif

#ifndef NDNBOOST_TT_AUX_BOOL_C_BASE
#   define NDNBOOST_TT_AUX_BOOL_C_BASE(C) : public ::ndnboost::integral_constant<bool,C>
#endif 


#define NDNBOOST_TT_AUX_BOOL_TRAIT_DEF1(trait,T,C) \
template< typename T > struct trait \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1,trait,(T)) \
}; \
\
NDNBOOST_TT_AUX_TEMPLATE_ARITY_SPEC(1,trait) \
/**/


#define NDNBOOST_TT_AUX_BOOL_TRAIT_DEF2(trait,T1,T2,C) \
template< typename T1, typename T2 > struct trait \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(2,trait,(T1,T2)) \
}; \
\
NDNBOOST_TT_AUX_TEMPLATE_ARITY_SPEC(2,trait) \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_DEF3(trait,T1,T2,T3,C) \
template< typename T1, typename T2, typename T3 > struct trait \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(3,trait,(T1,T2,T3)) \
}; \
\
NDNBOOST_TT_AUX_TEMPLATE_ARITY_SPEC(3,trait) \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,C) \
template<> struct trait< sp > \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,trait,(sp)) \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC2(trait,sp1,sp2,C) \
template<> struct trait< sp1,sp2 > \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2,trait,(sp1,sp2)) \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC1(trait,sp,C) \
template<> struct trait##_impl< sp > \
{ \
public:\
    NDNBOOST_STATIC_CONSTANT(bool, value = (C)); \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_IMPL_SPEC2(trait,sp1,sp2,C) \
template<> struct trait##_impl< sp1,sp2 > \
{ \
public:\
    NDNBOOST_STATIC_CONSTANT(bool, value = (C)); \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1(param,trait,sp,C) \
template< param > struct trait< sp > \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_2(param1,param2,trait,sp,C) \
template< param1, param2 > struct trait< sp > \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_1(param,trait,sp1,sp2,C) \
template< param > struct trait< sp1,sp2 > \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2,trait,(sp1,sp2)) \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(param1,param2,trait,sp1,sp2,C) \
template< param1, param2 > struct trait< sp1,sp2 > \
    NDNBOOST_TT_AUX_BOOL_C_BASE(C) \
{ \
public:\
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
}; \
/**/

#define NDNBOOST_TT_AUX_BOOL_TRAIT_IMPL_PARTIAL_SPEC2_1(param,trait,sp1,sp2,C) \
template< param > struct trait##_impl< sp1,sp2 > \
{ \
public:\
    NDNBOOST_STATIC_CONSTANT(bool, value = (C)); \
}; \
/**/

#ifndef NDNBOOST_NO_CV_SPECIALIZATIONS
#   define NDNBOOST_TT_AUX_BOOL_TRAIT_CV_SPEC1(trait,sp,value) \
    NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,value) \
    NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp const,value) \
    NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp volatile,value) \
    NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp const volatile,value) \
    /**/
#else
#   define NDNBOOST_TT_AUX_BOOL_TRAIT_CV_SPEC1(trait,sp,value) \
    NDNBOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,value) \
    /**/
#endif
