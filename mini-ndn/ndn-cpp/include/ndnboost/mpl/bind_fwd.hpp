
#if !defined(NDNBOOST_PP_IS_ITERATING)

///// header body

#ifndef NDNBOOST_MPL_BIND_FWD_HPP_INCLUDED
#define NDNBOOST_MPL_BIND_FWD_HPP_INCLUDED

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
#   include <ndnboost/mpl/aux_/na.hpp>
#endif

#include <ndnboost/mpl/aux_/config/bind.hpp>
#include <ndnboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE)

#   define NDNBOOST_MPL_PREPROCESSED_HEADER bind_fwd.hpp
#   include <ndnboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <ndnboost/mpl/limits/arity.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <ndnboost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>

#   include <ndnboost/preprocessor/comma_if.hpp>
#   include <ndnboost/preprocessor/iterate.hpp>
#   include <ndnboost/preprocessor/cat.hpp>

namespace ndnboost { namespace mpl {

// local macros, #undef-ined at the end of the header

#   if defined(NDNBOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)
#       define AUX778076_DMC_PARAM() , int dummy_ = 0
#   else
#       define AUX778076_DMC_PARAM()
#   endif

#   define AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    NDNBOOST_MPL_PP_DEFAULT_PARAMS( \
          NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    AUX778076_DMC_PARAM() \
    /**/

#   define AUX778076_BIND_N_PARAMS(n, param) \
    NDNBOOST_PP_COMMA_IF(n) NDNBOOST_MPL_PP_PARAMS(n, param) \
    AUX778076_DMC_PARAM() \
    /**/

#if !defined(NDNBOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, AUX778076_BIND_DEFAULT_PARAMS(typename T, na)
    >
struct bind;
#endif

#define NDNBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <ndnboost/mpl/bind_fwd.hpp>))
#include NDNBOOST_PP_ITERATE()

#   undef AUX778076_BIND_N_PARAMS
#   undef AUX778076_BIND_DEFAULT_PARAMS
#   undef AUX778076_DMC_PARAM
}}

#endif // NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // NDNBOOST_MPL_BIND_FWD_HPP_INCLUDED

///// iteration

#else
#define i_ NDNBOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct NDNBOOST_PP_CAT(bind,i_);

#undef i_
#endif // NDNBOOST_PP_IS_ITERATING
