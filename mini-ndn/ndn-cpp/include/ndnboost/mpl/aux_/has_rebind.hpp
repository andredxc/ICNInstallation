
#ifndef NDNBOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED

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

#include <ndnboost/mpl/aux_/config/msvc.hpp>
#include <ndnboost/mpl/aux_/config/intel.hpp>
#include <ndnboost/mpl/aux_/config/workaround.hpp>

#if NDNBOOST_WORKAROUND(__EDG_VERSION__, <= 244) && !defined(NDNBOOST_INTEL_CXX_VERSION)
#   include <ndnboost/mpl/has_xxx.hpp>
#elif NDNBOOST_WORKAROUND(NDNBOOST_MSVC, < 1300)
#   include <ndnboost/mpl/has_xxx.hpp>
#   include <ndnboost/mpl/if.hpp>
#   include <ndnboost/mpl/bool.hpp>
#   include <ndnboost/mpl/aux_/msvc_is_class.hpp>
#elif NDNBOOST_WORKAROUND(__BORLANDC__, NDNBOOST_TESTED_AT(0x610))
#   include <ndnboost/mpl/if.hpp>
#   include <ndnboost/mpl/bool.hpp>
#   include <ndnboost/mpl/aux_/yes_no.hpp>
#   include <ndnboost/mpl/aux_/config/static_constant.hpp>
#   include <ndnboost/type_traits/is_class.hpp>
#else
#   include <ndnboost/mpl/aux_/type_wrapper.hpp>
#   include <ndnboost/mpl/aux_/yes_no.hpp>
#   include <ndnboost/mpl/aux_/config/static_constant.hpp>
#endif

namespace ndnboost { namespace mpl { namespace aux {

#if NDNBOOST_WORKAROUND(__EDG_VERSION__, <= 244) && !defined(NDNBOOST_INTEL_CXX_VERSION)

NDNBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_rebind, rebind, false)

#elif NDNBOOST_WORKAROUND(NDNBOOST_MSVC, < 1300)

NDNBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_rebind_impl, rebind, false)

template< typename T >
struct has_rebind
    : if_< 
          msvc_is_class<T>
        , has_rebind_impl<T>
        , bool_<false>
        >::type
{
};

#else // the rest

template< typename T > struct has_rebind_tag {};
no_tag operator|(has_rebind_tag<int>, void const volatile*);

#   if !NDNBOOST_WORKAROUND(__BORLANDC__, NDNBOOST_TESTED_AT(0x610))
template< typename T >
struct has_rebind
{
    static has_rebind_tag<T>* get();
    NDNBOOST_STATIC_CONSTANT(bool, value = 
          sizeof(has_rebind_tag<int>() | get()) == sizeof(yes_tag)
        );
};
#   else // __BORLANDC__
template< typename T >
struct has_rebind_impl
{
    static T* get();
    NDNBOOST_STATIC_CONSTANT(bool, value = 
          sizeof(has_rebind_tag<int>() | get()) == sizeof(yes_tag)
        );
};

template< typename T >
struct has_rebind
    : if_< 
          is_class<T>
        , has_rebind_impl<T>
        , bool_<false>
        >::type
{
};
#   endif // __BORLANDC__

#endif

}}}

#endif // NDNBOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED
