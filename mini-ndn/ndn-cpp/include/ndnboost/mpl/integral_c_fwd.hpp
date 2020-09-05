
#ifndef NDNBOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
#define NDNBOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2006
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
#include <ndnboost/mpl/aux_/adl_barrier.hpp>

NDNBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

#if NDNBOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
template< typename T, long N > struct integral_c;
#else
template< typename T, T N > struct integral_c;
#endif

NDNBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
NDNBOOST_MPL_AUX_ADL_BARRIER_DECL(integral_c)

#endif // NDNBOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
