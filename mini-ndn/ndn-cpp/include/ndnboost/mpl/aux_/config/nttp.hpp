
#ifndef NDNBOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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

// MSVC 6.5 ICE-s on the code as simple as this (see "aux_/nttp_decl.hpp"
// for a workaround):
//
//    namespace std {
//    template< typename Char > struct string;
//    }
//
//    void foo(std::string<char>);
//
//    namespace ndnboost { namespace mpl {
//    template< int > struct arg;
//    }}

#if    !defined(NDNBOOST_MPL_CFG_NTTP_BUG) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE) \
    && NDNBOOST_WORKAROUND(NDNBOOST_MSVC, < 1300)

#   define NDNBOOST_MPL_CFG_NTTP_BUG

#endif

#endif // NDNBOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
