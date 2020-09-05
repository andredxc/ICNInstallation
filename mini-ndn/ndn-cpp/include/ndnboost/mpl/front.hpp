
#ifndef NDNBOOST_MPL_FRONT_HPP_INCLUDED
#define NDNBOOST_MPL_FRONT_HPP_INCLUDED

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

#include <ndnboost/mpl/front_fwd.hpp>
#include <ndnboost/mpl/aux_/front_impl.hpp>
#include <ndnboost/mpl/sequence_tag.hpp>
#include <ndnboost/mpl/aux_/na_spec.hpp>
#include <ndnboost/mpl/aux_/lambda_support.hpp>

namespace ndnboost { namespace mpl {

template<
      typename NDNBOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct front
    : front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1,front,(Sequence))
};

NDNBOOST_MPL_AUX_NA_SPEC(1, front)

}}

#endif // NDNBOOST_MPL_FRONT_HPP_INCLUDED
