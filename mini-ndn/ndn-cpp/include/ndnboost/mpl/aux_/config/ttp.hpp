
#ifndef NDNBOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

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

#include <ndnboost/mpl/aux_/config/msvc.hpp>
#include <ndnboost/mpl/aux_/config/gcc.hpp>
#include <ndnboost/mpl/aux_/config/workaround.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && ( defined(NDNBOOST_NO_TEMPLATE_TEMPLATES) \
      || NDNBOOST_WORKAROUND( __BORLANDC__, NDNBOOST_TESTED_AT( 0x590) ) \
       )

#   define NDNBOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif


#if    !defined(NDNBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE) \
    && (   NDNBOOST_WORKAROUND(NDNBOOST_MPL_CFG_GCC, NDNBOOST_TESTED_AT(0x0302)) \
        || NDNBOOST_WORKAROUND(__BORLANDC__, NDNBOOST_TESTED_AT(0x610)) \
        )

#   define NDNBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

#endif

#endif // NDNBOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
