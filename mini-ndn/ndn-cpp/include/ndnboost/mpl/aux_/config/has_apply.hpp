
#ifndef NDNBOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

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

#include <ndnboost/mpl/aux_/config/has_xxx.hpp>
#include <ndnboost/mpl/aux_/config/msvc.hpp>
#include <ndnboost/mpl/aux_/config/workaround.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_HAS_APPLY) \
    && (   defined(NDNBOOST_MPL_CFG_NO_HAS_XXX) \
        || NDNBOOST_WORKAROUND(__EDG_VERSION__, < 300) \
        || NDNBOOST_WORKAROUND(NDNBOOST_MSVC, <= 1300) \
        || NDNBOOST_WORKAROUND(__MWERKS__, NDNBOOST_TESTED_AT(0x3202)) \
        )

#   define NDNBOOST_MPL_CFG_NO_HAS_APPLY

#endif

#endif // NDNBOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED
