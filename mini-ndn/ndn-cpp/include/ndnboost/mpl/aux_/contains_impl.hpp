
#ifndef NDNBOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/contains_fwd.hpp>
#include <ndnboost/mpl/begin_end.hpp>
#include <ndnboost/mpl/find.hpp>
#include <ndnboost/mpl/not.hpp>
#include <ndnboost/mpl/aux_/traits_lambda_spec.hpp>
#include <ndnboost/mpl/aux_/config/forwarding.hpp>
#include <ndnboost/mpl/aux_/config/static_constant.hpp>

#include <ndnboost/type_traits/is_same.hpp>

namespace ndnboost { namespace mpl {

template< typename Tag >
struct contains_impl
{
    template< typename Sequence, typename T > struct apply
#if !defined(NDNBOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > >
    {
#else
    {
        typedef not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > > type;

        NDNBOOST_STATIC_CONSTANT(bool, value = 
              (not_< is_same<
                  typename find<Sequence,T>::type
                , typename end<Sequence>::type
                > >::value)
            );
#endif
    };
};

NDNBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,contains_impl)

}}

#endif // NDNBOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
