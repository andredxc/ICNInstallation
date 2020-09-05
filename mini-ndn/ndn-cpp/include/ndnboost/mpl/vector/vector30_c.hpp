
#ifndef NDNBOOST_MPL_VECTOR_VECTOR30_C_HPP_INCLUDED
#define NDNBOOST_MPL_VECTOR_VECTOR30_C_HPP_INCLUDED

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

#if !defined(NDNBOOST_MPL_PREPROCESSING_MODE)
#   include <ndnboost/mpl/vector/vector20_c.hpp>
#   include <ndnboost/mpl/vector/vector30.hpp>
#endif

#include <ndnboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(NDNBOOST_MPL_PREPROCESSING_MODE)

#   define NDNBOOST_MPL_PREPROCESSED_HEADER vector30_c.hpp
#   include <ndnboost/mpl/vector/aux_/include_preprocessed.hpp>

#else

#   include <ndnboost/mpl/aux_/config/typeof.hpp>
#   include <ndnboost/mpl/aux_/config/ctps.hpp>
#   include <ndnboost/preprocessor/iterate.hpp>
#   include <ndnboost/config.hpp>

namespace ndnboost { namespace mpl {

#   define NDNBOOST_PP_ITERATION_PARAMS_1 \
    (3,(21, 30, <ndnboost/mpl/vector/aux_/numbered_c.hpp>))
#   include NDNBOOST_PP_ITERATE()

}}

#endif // NDNBOOST_MPL_CFG_USE_PREPROCESSED_HEADERS

#endif // NDNBOOST_MPL_VECTOR_VECTOR30_C_HPP_INCLUDED
