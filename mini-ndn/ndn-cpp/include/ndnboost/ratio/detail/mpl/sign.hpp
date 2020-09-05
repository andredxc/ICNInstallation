////////////////////////////////////////////////////////////////////
//
// Copyright Vicente J. Botet Escriba 2010
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.
//
////////////////////////////////////////////////////////////////////
#ifndef NDNBOOST_MPL_SIGN_HPP_INCLUDED
#define NDNBOOST_MPL_SIGN_HPP_INCLUDED

#include <ndnboost/mpl/integral_c.hpp>
#include <ndnboost/mpl/aux_/na_spec.hpp>
#include <ndnboost/mpl/aux_/lambda_support.hpp>
#include <ndnboost/mpl/aux_/config/integral.hpp>
#include <ndnboost/mpl/aux_/config/static_constant.hpp>

#if    !defined(NDNBOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE) \
    && !defined(__CUDACC__) \
    && ( defined(NDNBOOST_MSVC) \
        || NDNBOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
        )

#   define NDNBOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2

#endif

namespace ndnboost { namespace mpl {

template< typename Tag > struct sign_impl;

template< typename T > struct sign_tag
{
    typedef typename T::tag type;
};

template<
      typename NDNBOOST_MPL_AUX_NA_PARAM(N)
    >
struct sign
    : sign_impl<
          typename sign_tag<N>::type
        >::template apply<N>::type
{
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1, sign, (N))
};

NDNBOOST_MPL_AUX_NA_SPEC(1, sign)

template<
      typename T
    , T n1
    >
struct sign_c
    : sign<integral_c<T,n1> >
{
};

#if defined(NDNBOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2)
namespace aux {
template< typename T, T n > struct sign_wknd
{
    NDNBOOST_STATIC_CONSTANT(T, value = (n == 0 ? 0 : (n < 0 ? -1 : 1)));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct sign_impl<integral_c_tag>
{
#if defined(NDNBOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2)
    template< typename N > struct apply
        : aux::sign_wknd< typename N::value_type, N::value >
#else
    template< typename N > struct apply
        : integral_c< typename N::value_type, (N::value == 0 ? 0 : (N::value < 0 ? -1 : 1)) >
#endif
    {
    };
};

}}

#endif // NDNBOOST_MPL_SIGN_HPP_INCLUDED
