
#ifndef NDNBOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define NDNBOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

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

#include <ndnboost/mpl/void_fwd.hpp>
#include <ndnboost/mpl/aux_/na.hpp>
#include <ndnboost/mpl/aux_/config/lambda.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   include <ndnboost/mpl/int.hpp>
#   include <ndnboost/mpl/aux_/lambda_arity_param.hpp>
#   include <ndnboost/mpl/aux_/template_arity_fwd.hpp>

namespace ndnboost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    NDNBOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = int_< aux::template_arity<T>::value >
        )
    >
struct lambda;

}}

#else // NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <ndnboost/mpl/bool.hpp>

namespace ndnboost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    , typename Protect = true_
    > 
struct lambda;

}}

#endif

#endif // NDNBOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
