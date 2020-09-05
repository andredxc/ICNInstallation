
#ifndef NDNBOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED
#define NDNBOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

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

#include <ndnboost/mpl/long.hpp>
#include <ndnboost/mpl/void.hpp>
#include <ndnboost/mpl/aux_/na.hpp>
#include <ndnboost/mpl/aux_/type_wrapper.hpp>

#include <ndnboost/mpl/vector/aux_/iterator.hpp>
#include <ndnboost/mpl/vector/aux_/tag.hpp>
#include <ndnboost/mpl/aux_/config/typeof.hpp>

namespace ndnboost { namespace mpl {

template< typename Dummy = na > struct vector0;

template<> struct vector0<na>
{
#if defined(NDNBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef aux::vector_tag tag;
    typedef vector0         type;
    typedef long_<32768>    lower_bound_;
    typedef lower_bound_    upper_bound_;
    typedef long_<0>        size;

    static aux::type_wrapper<void_> item_(...);
#else
    typedef aux::vector_tag<0> tag;
    typedef vector0 type;
    typedef void_ item0;
    
    typedef v_iter<vector0<>,0> begin;
    typedef v_iter<vector0<>,0> end;
#endif
};

}}

#endif // NDNBOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED
