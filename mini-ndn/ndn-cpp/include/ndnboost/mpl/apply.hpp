
#if !defined(NDNBOOST_PP_IS_ITERATING)

///// header body

#ifndef NDNBOOST_MPL_APPLY_HPP_INCLUDED
#define NDNBOOST_MPL_APPLY_HPP_INCLUDED

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
#   include <ndnboost/mpl/apply_fwd.hpp>
#   include <ndnboost/mpl/apply_wrap.hpp>
#   include <ndnboost/mpl/placeholders.hpp>
#   include <ndnboost/mpl/lambda.hpp>
#   include <ndnboost/mpl/aux_/na.hpp>
#   include <ndnboost/mpl/aux_/lambda_support.hpp>
#endif

#include <ndnboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE)

#   define NDNBOOST_MPL_PREPROCESSED_HEADER apply.hpp
#   include <ndnboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <ndnboost/mpl/limits/arity.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <ndnboost/mpl/aux_/preprocessor/enum.hpp>
#   include <ndnboost/mpl/aux_/config/lambda.hpp>
#   include <ndnboost/mpl/aux_/config/dtp.hpp>
#   include <ndnboost/mpl/aux_/nttp_decl.hpp>
#   include <ndnboost/mpl/aux_/config/eti.hpp>
#   include <ndnboost/mpl/aux_/config/msvc.hpp>
#   include <ndnboost/mpl/aux_/config/workaround.hpp>

#   include <ndnboost/preprocessor/comma_if.hpp>
#   include <ndnboost/preprocessor/inc.hpp>
#   include <ndnboost/preprocessor/iterate.hpp>
#   include <ndnboost/preprocessor/cat.hpp>

namespace ndnboost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY_PARAMS(param) \
    NDNBOOST_MPL_PP_PARAMS( \
          NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_APPLY_DEF_PARAMS(param, value) \
    NDNBOOST_MPL_PP_DEFAULT_PARAMS( \
          NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_APPLY_N_PARAMS(n, param) \
    NDNBOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_N_COMMA_PARAMS(n, param) \
    NDNBOOST_PP_COMMA_IF(n) \
    NDNBOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(n, param, def) \
    NDNBOOST_PP_COMMA_IF(n) \
    NDNBOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
    /**/
    
#   define AUX778076_APPLY_N_SPEC_PARAMS(n, param) \
    NDNBOOST_MPL_PP_ENUM(NDNBOOST_PP_INC(n), param) \
    /**/


#define NDNBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <ndnboost/mpl/apply.hpp>))
#include NDNBOOST_PP_ITERATE()

#   if !defined(NDNBOOST_MPL_CFG_NO_APPLY_TEMPLATE)
// real C++ version is already taken care of
#   if defined(NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// apply_count_args
#define AUX778076_COUNT_ARGS_PREFIX apply
#define AUX778076_COUNT_ARGS_DEFAULT na
#define AUX778076_COUNT_ARGS_ARITY NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY
#include <ndnboost/mpl/aux_/count_args.hpp>
}


template<
      typename F, AUX778076_APPLY_DEF_PARAMS(typename T, na)
    >
struct apply
    : aux::apply_chooser< 
          aux::apply_count_args< AUX778076_APPLY_PARAMS(T) >::value
        >::template result_< F, AUX778076_APPLY_PARAMS(T) >::type
{
};

#   endif // NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // NDNBOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef AUX778076_APPLY_N_SPEC_PARAMS
#   undef AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS
#   undef AUX778076_APPLY_N_COMMA_PARAMS
#   undef AUX778076_APPLY_N_PARAMS
#   undef AUX778076_APPLY_DEF_PARAMS
#   undef AUX778076_APPLY_PARAMS

}}

#endif // NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // NDNBOOST_MPL_APPLY_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// NDNBOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // NDNBOOST_PP_IS_ITERATING
#if NDNBOOST_PP_ITERATION_DEPTH() == 1

#   define i_ NDNBOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct NDNBOOST_PP_CAT(apply,i_)
#if !NDNBOOST_WORKAROUND(NDNBOOST_MSVC, < 1300)
    : NDNBOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >
{
#else
{
    typedef typename NDNBOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >::type type;
#endif
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(
          NDNBOOST_PP_INC(i_)
        , NDNBOOST_PP_CAT(apply,i_)
        , (F AUX778076_APPLY_N_COMMA_PARAMS(i_,T))
        )
};


#if defined(NDNBOOST_MPL_CFG_MSVC_ETI_BUG)
/// workaround for ETI bug
template<>
struct NDNBOOST_PP_CAT(apply,i_)<AUX778076_APPLY_N_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   if !defined(NDNBOOST_MPL_CFG_NO_APPLY_TEMPLATE)
#   if !defined(NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == NDNBOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template (not a specialization!)
template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply
    : NDNBOOST_PP_CAT(apply,i_)< F AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#else
template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply< F AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(i_, T, na) >
    : NDNBOOST_PP_CAT(apply,i_)< F AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#endif

#   else // NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined(NDNBOOST_MPL_CFG_NO_APPLY_TEMPLATE)
namespace aux {

template<>
struct apply_chooser<i_>
{
    template<
          typename F, AUX778076_APPLY_PARAMS(typename T)
        >
    struct result_
    {
        typedef NDNBOOST_PP_CAT(apply,i_)<
              F AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
            > type;
    };
};

} // namespace aux
#endif

#   endif // NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // NDNBOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef i_

#endif // NDNBOOST_PP_ITERATION_DEPTH()
#endif // NDNBOOST_PP_IS_ITERATING
