
#if !defined(NDNBOOST_PP_IS_ITERATING)

///// header body

#ifndef NDNBOOST_MPL_ARG_HPP_INCLUDED
#define NDNBOOST_MPL_ARG_HPP_INCLUDED

// Copyright Peter Dimov 2001-2002
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

#if !defined(NDNBOOST_MPL_PREPROCESSING_MODE)
#   include <ndnboost/mpl/arg_fwd.hpp>
#   include <ndnboost/mpl/aux_/na.hpp>
#   include <ndnboost/mpl/aux_/na_assert.hpp>
#   include <ndnboost/mpl/aux_/arity_spec.hpp>
#   include <ndnboost/mpl/aux_/arg_typedef.hpp>
#endif

#include <ndnboost/mpl/aux_/config/static_constant.hpp>
#include <ndnboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE)

#   define NDNBOOST_MPL_PREPROCESSED_HEADER arg.hpp
#   include <ndnboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <ndnboost/mpl/limits/arity.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#   include <ndnboost/mpl/aux_/config/lambda.hpp>
#   include <ndnboost/mpl/aux_/config/dtp.hpp>
#   include <ndnboost/mpl/aux_/nttp_decl.hpp>

#   include <ndnboost/preprocessor/iterate.hpp>
#   include <ndnboost/preprocessor/inc.hpp>
#   include <ndnboost/preprocessor/cat.hpp>

NDNBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

// local macro, #undef-ined at the end of the header
#if !defined(NDNBOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    NDNBOOST_MPL_PP_DEFAULT_PARAMS( \
          NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/
#else
#   define AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    NDNBOOST_MPL_PP_PARAMS( \
          NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/
#endif

#define NDNBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <ndnboost/mpl/arg.hpp>))
#include NDNBOOST_PP_ITERATE()


#   undef AUX778076_ARG_N_DEFAULT_PARAMS

NDNBOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int,arg)

NDNBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // NDNBOOST_MPL_ARG_HPP_INCLUDED

///// iteration

#else
#define i_ NDNBOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

template<> struct arg<i_>
{
    NDNBOOST_STATIC_CONSTANT(int, value = i_);
    typedef arg<NDNBOOST_PP_INC(i_)> next;
    NDNBOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    NDNBOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef NDNBOOST_PP_CAT(U,i_) type;
        NDNBOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#else

template<> struct arg<-1>
{
    NDNBOOST_STATIC_CONSTANT(int, value = -1);
    NDNBOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    NDNBOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef U1 type;
        NDNBOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#endif // i_ > 0

#undef i_
#endif // NDNBOOST_PP_IS_ITERATING
