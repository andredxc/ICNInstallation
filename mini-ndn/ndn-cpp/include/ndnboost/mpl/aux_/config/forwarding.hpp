
#ifndef NDNBOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED

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

#include <ndnboost/mpl/aux_/config/workaround.hpp>

#if    !defined(NDNBOOST_MPL_CFG_NO_NESTED_FORWARDING) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE) \
    && NDNBOOST_WORKAROUND(__BORLANDC__, NDNBOOST_TESTED_AT(0x610))

#   define NDNBOOST_MPL_CFG_NO_NESTED_FORWARDING

#endif

#endif // NDNBOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED
