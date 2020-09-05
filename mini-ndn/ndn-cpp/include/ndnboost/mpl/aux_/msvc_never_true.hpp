
#ifndef NDNBOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

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
#include <ndnboost/mpl/aux_/config/workaround.hpp>

#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, <= 1300)

namespace ndnboost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // NDNBOOST_MSVC

#endif // NDNBOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
