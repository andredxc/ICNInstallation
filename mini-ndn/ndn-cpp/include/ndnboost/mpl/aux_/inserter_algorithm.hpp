
#ifndef NDNBOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED
#define NDNBOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/back_inserter.hpp>
#include <ndnboost/mpl/front_inserter.hpp>
#include <ndnboost/mpl/push_back.hpp>
#include <ndnboost/mpl/push_front.hpp>
#include <ndnboost/mpl/back_inserter.hpp>
#include <ndnboost/mpl/front_inserter.hpp>
#include <ndnboost/mpl/clear.hpp>
#include <ndnboost/mpl/eval_if.hpp>
#include <ndnboost/mpl/if.hpp>
#include <ndnboost/mpl/aux_/na.hpp>
#include <ndnboost/mpl/aux_/common_name_wknd.hpp>
#include <ndnboost/mpl/aux_/na_spec.hpp>
#include <ndnboost/mpl/aux_/preprocessor/params.hpp>
#include <ndnboost/mpl/aux_/preprocessor/default_params.hpp>
#include <ndnboost/mpl/aux_/config/ctps.hpp>

#include <ndnboost/preprocessor/arithmetic/dec.hpp>

#if !defined(NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define NDNBOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
NDNBOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      NDNBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
    : aux::name##_impl<NDNBOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), typename P) \
    > \
struct name< NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back< typename clear<P1>::type> \
        , aux::name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      NDNBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
    : aux::reverse_##name##_impl<NDNBOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), typename P) \
    > \
struct reverse_##name< NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
NDNBOOST_MPL_AUX_NA_SPEC(arity, name) \
NDNBOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#else

#   define NDNBOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
NDNBOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), typename P) \
    > \
struct def_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      NDNBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
{ \
    typedef typename eval_if< \
          is_na<NDNBOOST_PP_CAT(P, arity)> \
        , def_##name##_impl<NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P)> \
        , aux::name##_impl<NDNBOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
\
template< \
      NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), typename P) \
    > \
struct def_reverse_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
template< \
      NDNBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
{ \
    typedef typename eval_if< \
          is_na<NDNBOOST_PP_CAT(P, arity)> \
        , def_reverse_##name##_impl<NDNBOOST_MPL_PP_PARAMS(NDNBOOST_PP_DEC(arity), P)> \
        , aux::reverse_##name##_impl<NDNBOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
NDNBOOST_MPL_AUX_NA_SPEC(arity, name) \
NDNBOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#endif // NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // NDNBOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED
