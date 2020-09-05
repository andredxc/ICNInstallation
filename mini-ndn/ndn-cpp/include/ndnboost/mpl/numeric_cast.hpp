
#ifndef NDNBOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
#define NDNBOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

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

// agurt 21/sep/04: portability macro for the sake of MSVC 6.x-7.0;
// resolves conflicts with 'ndnboost::numeric_cast' function template.
// use it in your own code _only_ if you care about compatibility with
// these outdated compilers!
#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, <= 1300) || NDNBOOST_WORKAROUND(__BORLANDC__, NDNBOOST_TESTED_AT(0x570) )
#   define NDNBOOST_MPL_AUX_NUMERIC_CAST numeric_cast_
#else
#   define NDNBOOST_MPL_AUX_NUMERIC_CAST numeric_cast
#endif

namespace ndnboost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename SourceTag, typename TargetTag > struct NDNBOOST_MPL_AUX_NUMERIC_CAST
{
    template< typename N > struct apply;
};

}}

#endif // NDNBOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
