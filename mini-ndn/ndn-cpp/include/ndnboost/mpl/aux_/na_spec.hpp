
#ifndef NDNBOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(NDNBOOST_MPL_PREPROCESSING_MODE)
#   include <ndnboost/mpl/lambda_fwd.hpp>
#   include <ndnboost/mpl/int.hpp>
#   include <ndnboost/mpl/bool.hpp>
#   include <ndnboost/mpl/aux_/na.hpp>
#   include <ndnboost/mpl/aux_/arity.hpp>
#   include <ndnboost/mpl/aux_/template_arity_fwd.hpp>
#endif

#include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#include <ndnboost/mpl/aux_/preprocessor/enum.hpp>
#include <ndnboost/mpl/aux_/preprocessor/def_params_tail.hpp>
#include <ndnboost/mpl/aux_/lambda_arity_param.hpp>
#include <ndnboost/mpl/aux_/config/dtp.hpp>
#include <ndnboost/mpl/aux_/config/eti.hpp>
#include <ndnboost/mpl/aux_/nttp_decl.hpp>
#include <ndnboost/mpl/aux_/config/ttp.hpp>
#include <ndnboost/mpl/aux_/config/lambda.hpp>
#include <ndnboost/mpl/aux_/config/overload_resolution.hpp>


#define NDNBOOST_MPL_AUX_NA_PARAMS(i) \
    NDNBOOST_MPL_PP_ENUM(i, na) \
/**/

#if defined(NDNBOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define NDNBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
namespace aux { \
template< NDNBOOST_MPL_AUX_NTTP_DECL(int, N) > \
struct arity< \
          name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > \
        , N \
        > \
    : int_< NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY > \
{ \
}; \
} \
/**/
#else
#   define NDNBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) /**/
#endif

#define NDNBOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
template<> \
struct name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > \
{ \
    template< \
          NDNBOOST_MPL_PP_PARAMS(i, typename T) \
        NDNBOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, typename T, na) \
        > \
    struct apply \
        : name< NDNBOOST_MPL_PP_PARAMS(i, T) > \
    { \
    }; \
}; \
/**/

#if defined(NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   define NDNBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template<> \
struct lambda< \
      name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > \
    , void_ \
    , true_ \
    > \
{ \
    typedef false_ is_le; \
    typedef name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
template<> \
struct lambda< \
      name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > \
    , void_ \
    , false_ \
    > \
{ \
    typedef false_ is_le; \
    typedef name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#else
#   define NDNBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template< typename Tag > \
struct lambda< \
      name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > \
    , Tag \
    NDNBOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<-1>) \
    > \
{ \
    typedef false_ is_le; \
    typedef name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > result_; \
    typedef name< NDNBOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#endif

#if defined(NDNBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    || defined(NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
        && defined(NDNBOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION)
#   define NDNBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
namespace aux { \
template< NDNBOOST_MPL_PP_PARAMS(j, typename T) > \
struct template_arity< \
          name< NDNBOOST_MPL_PP_PARAMS(j, T) > \
        > \
    : int_<j> \
{ \
}; \
\
template<> \
struct template_arity< \
          name< NDNBOOST_MPL_PP_ENUM(i, na) > \
        > \
    : int_<-1> \
{ \
}; \
} \
/**/
#else
#   define NDNBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) /**/
#endif

#if defined(NDNBOOST_MPL_CFG_MSVC_ETI_BUG)
#   define NDNBOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
template<> \
struct name< NDNBOOST_MPL_PP_ENUM(i, int) > \
{ \
    typedef int type; \
    enum { value = 0 }; \
}; \
/**/
#else
#   define NDNBOOST_MPL_AUX_NA_SPEC_ETI(i, name) /**/
#endif

#define NDNBOOST_MPL_AUX_NA_PARAM(param) param = na

#define NDNBOOST_MPL_AUX_NA_SPEC_NO_ETI(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, i, name) \
/**/

#define NDNBOOST_MPL_AUX_NA_SPEC(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_NO_ETI(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
/**/

#define NDNBOOST_MPL_AUX_NA_SPEC2(i, j, name) \
NDNBOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
NDNBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
/**/


#endif // NDNBOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED
