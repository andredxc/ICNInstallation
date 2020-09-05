
#ifndef NDNBOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

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

#include <ndnboost/mpl/has_xxx.hpp>
#include <ndnboost/mpl/aux_/config/has_apply.hpp>

namespace ndnboost { namespace mpl { namespace aux {
#if !defined(NDNBOOST_MPL_CFG_NO_HAS_APPLY)
NDNBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_apply, apply, false)
#else
template< typename T, typename fallback_ = false_ >
struct has_apply
    : fallback_
{
};
#endif
}}}

#endif // NDNBOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED
