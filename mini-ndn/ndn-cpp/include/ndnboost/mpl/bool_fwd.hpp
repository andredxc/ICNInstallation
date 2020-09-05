
#ifndef NDNBOOST_MPL_BOOL_FWD_HPP_INCLUDED
#define NDNBOOST_MPL_BOOL_FWD_HPP_INCLUDED

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

#include <ndnboost/mpl/aux_/adl_barrier.hpp>

NDNBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_;

// shorcuts
typedef bool_<true> true_;
typedef bool_<false> false_;

NDNBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

NDNBOOST_MPL_AUX_ADL_BARRIER_DECL(bool_)
NDNBOOST_MPL_AUX_ADL_BARRIER_DECL(true_)
NDNBOOST_MPL_AUX_ADL_BARRIER_DECL(false_)

#endif // NDNBOOST_MPL_BOOL_FWD_HPP_INCLUDED
