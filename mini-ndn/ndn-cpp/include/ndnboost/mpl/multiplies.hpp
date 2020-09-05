
#ifndef NDNBOOST_MPL_MULTIPLIES_HPP_INCLUDED
#define NDNBOOST_MPL_MULTIPLIES_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/times.hpp>
#include <ndnboost/mpl/aux_/na_spec.hpp>
#include <ndnboost/mpl/aux_/lambda_support.hpp>
#include <ndnboost/mpl/aux_/preprocessor/default_params.hpp>
#include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#include <ndnboost/mpl/aux_/config/ctps.hpp>

// backward compatibility header, deprecated

namespace ndnboost { namespace mpl {

#if !defined(NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define AUX778076_OP_ARITY NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY
#else
#   define AUX778076_OP_ARITY 2
#endif

template<
      NDNBOOST_MPL_PP_DEFAULT_PARAMS(AUX778076_OP_ARITY, typename N, na)
    >
struct multiplies
    : times< NDNBOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) >
{
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , multiplies
        , ( NDNBOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

NDNBOOST_MPL_AUX_NA_SPEC(AUX778076_OP_ARITY, multiplies)

#undef AUX778076_OP_ARITY

}}

#endif // NDNBOOST_MPL_MULTIPLIES_HPP_INCLUDED
