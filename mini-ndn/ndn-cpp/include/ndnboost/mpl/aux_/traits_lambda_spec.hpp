
#ifndef NDNBOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/sequence_tag_fwd.hpp>
#include <ndnboost/mpl/void.hpp>
#include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#include <ndnboost/mpl/aux_/config/lambda.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define NDNBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) /**/

#elif !defined(NDNBOOST_MPL_CFG_MSVC_ETI_BUG)

#   define NDNBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< NDNBOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
/**/

#else

#   define NDNBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< NDNBOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
template<> struct trait<int> \
{ \
    template< NDNBOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
        typedef int type; \
    }; \
}; \
/**/

#endif // NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT


#define NDNBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(i, trait) \
    NDNBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
    template<> struct trait<non_sequence_tag> {}; \
/**/

#endif // NDNBOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
