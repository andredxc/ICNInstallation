
#ifndef NDNBOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
#define NDNBOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

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

#include <ndnboost/mpl/aux_/config/typeof.hpp>

#if defined(NDNBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <ndnboost/mpl/begin_end_fwd.hpp>
#   include <ndnboost/mpl/vector/aux_/iterator.hpp>
#   include <ndnboost/mpl/vector/aux_/tag.hpp>

namespace ndnboost { namespace mpl {

template<>
struct begin_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,0> type;
    };
};

template<>
struct end_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,Vector::size::value> type;
    };
};

}}

#endif // NDNBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // NDNBOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
