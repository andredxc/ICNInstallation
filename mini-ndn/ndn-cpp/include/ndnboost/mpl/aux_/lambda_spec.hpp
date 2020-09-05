
#ifndef NDNBOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2007
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/void.hpp>
#include <ndnboost/mpl/lambda_fwd.hpp>
#include <ndnboost/mpl/int_fwd.hpp>
#include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#include <ndnboost/mpl/aux_/lambda_arity_param.hpp>
#include <ndnboost/mpl/aux_/config/lambda.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define NDNBOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) \
template< \
      NDNBOOST_MPL_PP_PARAMS(i, typename T) \
    , typename Tag \
    > \
struct lambda< \
      name< NDNBOOST_MPL_PP_PARAMS(i, T) > \
    , Tag \
    NDNBOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<i>) \
    > \
{ \
    typedef false_ is_le; \
    typedef name< NDNBOOST_MPL_PP_PARAMS(i, T) > result_; \
    typedef result_ type; \
}; \
/**/

#else

#   define NDNBOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) /**/

#endif

#endif // NDNBOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED
