
#ifndef NDNBOOST_MPL_PUSH_FRONT_HPP_INCLUDED
#define NDNBOOST_MPL_PUSH_FRONT_HPP_INCLUDED

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

#include <ndnboost/mpl/push_front_fwd.hpp>
#include <ndnboost/mpl/aux_/push_front_impl.hpp>
#include <ndnboost/mpl/sequence_tag.hpp>
#include <ndnboost/mpl/aux_/na_spec.hpp>
#include <ndnboost/mpl/aux_/lambda_support.hpp>

namespace ndnboost { namespace mpl {

template<
      typename NDNBOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename NDNBOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_front
    : push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_front,(Sequence,T))
};


template< 
      typename NDNBOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_front
    : has_push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_front,(Sequence))
};

NDNBOOST_MPL_AUX_NA_SPEC(2, push_front)
NDNBOOST_MPL_AUX_NA_SPEC(1, has_push_front)

}}

#endif // NDNBOOST_MPL_PUSH_FRONT_HPP_INCLUDED
