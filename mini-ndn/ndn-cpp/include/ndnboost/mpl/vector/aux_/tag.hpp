
#ifndef NDNBOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define NDNBOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

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

#include <ndnboost/mpl/aux_/config/typeof.hpp>
#include <ndnboost/mpl/aux_/nttp_decl.hpp>

namespace ndnboost { namespace mpl { namespace aux {

struct v_iter_tag;

#if defined(NDNBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< NDNBOOST_MPL_AUX_NTTP_DECL(long, N) > struct vector_tag;
#endif

}}}

#endif // NDNBOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
