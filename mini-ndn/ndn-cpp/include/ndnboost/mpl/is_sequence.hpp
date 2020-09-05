
#ifndef NDNBOOST_MPL_IS_SEQUENCE_HPP_INCLUDED
#define NDNBOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/not.hpp>
#include <ndnboost/mpl/and.hpp>
#include <ndnboost/mpl/begin_end.hpp>
#include <ndnboost/mpl/if.hpp>
#include <ndnboost/mpl/bool.hpp>
#include <ndnboost/mpl/sequence_tag_fwd.hpp>
#include <ndnboost/mpl/identity.hpp>
#include <ndnboost/mpl/void.hpp>
#include <ndnboost/mpl/aux_/has_tag.hpp>
#include <ndnboost/mpl/aux_/has_begin.hpp>
#include <ndnboost/mpl/aux_/na_spec.hpp>
#include <ndnboost/mpl/aux_/lambda_support.hpp>
#include <ndnboost/mpl/aux_/config/eti.hpp>
#include <ndnboost/mpl/aux_/config/msvc.hpp>
#include <ndnboost/mpl/aux_/config/workaround.hpp>
#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, < 1300)
#   include <ndnboost/mpl/aux_/msvc_is_class.hpp>
#elif NDNBOOST_WORKAROUND(NDNBOOST_MSVC, == 1300)
#   include <ndnboost/type_traits/is_class.hpp>
#endif

#include <ndnboost/type_traits/is_same.hpp>

namespace ndnboost { namespace mpl {

#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, <= 1300)

namespace aux {

// agurt, 11/jun/03: 
// MSVC 6.5/7.0 fails if 'has_begin' is instantiated on a class type that has a
// 'begin' member that doesn't name a type; e.g. 'has_begin< std::vector<int> >'
// would fail; requiring 'T' to have _both_ 'tag' and 'begin' members workarounds
// the issue for most real-world cases
template< typename T > struct is_sequence_impl
    : and_<
          identity< aux::has_tag<T> >
        , identity< aux::has_begin<T> >
        >
{
};

} // namespace aux
        
template<
      typename NDNBOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : if_<
#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, < 1300)
          aux::msvc_is_class<T> 
#else
          ndnboost::is_class<T> 
#endif
        , aux::is_sequence_impl<T>
        , bool_<false>
        >::type
{
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#elif defined(NDNBOOST_MPL_CFG_NO_HAS_XXX)

template<
      typename NDNBOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : bool_<false>
{
};

#else

template<
      typename NDNBOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : not_< is_same< typename begin<T>::type, void_ > >
{
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#endif // NDNBOOST_MSVC

#if defined(NDNBOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct is_sequence<int>
    : bool_<false>
{
};
#endif

NDNBOOST_MPL_AUX_NA_SPEC_NO_ETI(1, is_sequence)

}}

#endif // NDNBOOST_MPL_IS_SEQUENCE_HPP_INCLUDED
