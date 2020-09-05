
#ifndef NDNBOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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
#include <ndnboost/mpl/aux_/config/workaround.hpp>

#if    !defined(NDNBOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE) \
    && ( NDNBOOST_WORKAROUND(__BORLANDC__, NDNBOOST_TESTED_AT(0x610)) \
        || NDNBOOST_WORKAROUND(NDNBOOST_MSVC, <= 1300) \
        )

#   define NDNBOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES

#endif

#endif // NDNBOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED
