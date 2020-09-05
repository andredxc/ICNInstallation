
#ifndef NDNBOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

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
#   include <ndnboost/mpl/next_prior.hpp>
#   include <ndnboost/mpl/apply.hpp>
#   include <ndnboost/mpl/deref.hpp>
#   include <ndnboost/mpl/aux_/config/ctps.hpp>
#   if defined(NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <ndnboost/mpl/if.hpp>
#       include <ndnboost/type_traits/is_same.hpp>
#   endif
#endif

#include <ndnboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE)

#   define NDNBOOST_MPL_PREPROCESSED_HEADER fold_impl.hpp
#   include <ndnboost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX fold
#   include <ndnboost/mpl/aux_/fold_impl_body.hpp>

#endif // NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // NDNBOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
