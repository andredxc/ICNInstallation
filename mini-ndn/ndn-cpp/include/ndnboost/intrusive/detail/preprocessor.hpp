//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef NDNBOOST_INTRUSIVE_DETAIL_PREPROCESSOR_HPP
#define NDNBOOST_INTRUSIVE_DETAIL_PREPROCESSOR_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

#include <ndnboost/intrusive/detail/config_begin.hpp>
#include <ndnboost/intrusive/detail/workaround.hpp>

#include <ndnboost/preprocessor/iteration/local.hpp>
#include <ndnboost/preprocessor/punctuation/paren_if.hpp>
#include <ndnboost/preprocessor/punctuation/comma_if.hpp>
#include <ndnboost/preprocessor/control/expr_if.hpp>
#include <ndnboost/preprocessor/cat.hpp>
#include <ndnboost/preprocessor/repetition/enum.hpp>
#include <ndnboost/preprocessor/repetition/enum_params.hpp>
#include <ndnboost/preprocessor/repetition/enum_trailing_params.hpp>
#include <ndnboost/preprocessor/repetition/enum_trailing.hpp>
#include <ndnboost/preprocessor/repetition/enum_shifted_params.hpp>
#include <ndnboost/preprocessor/repetition/enum_shifted.hpp>
#include <ndnboost/preprocessor/repetition/repeat.hpp>
#include <ndnboost/preprocessor/logical/not.hpp>
#include <ndnboost/preprocessor/arithmetic/sub.hpp>
#include <ndnboost/preprocessor/arithmetic/add.hpp>
#include <ndnboost/preprocessor/iteration/iterate.hpp>

#define NDNBOOST_INTRUSIVE_MAX_CONSTRUCTOR_PARAMETERS 10

#define NDNBOOST_INTRUSIVE_PP_IDENTITY(z, n, data) data

#define NDNBOOST_INTRUSIVE_PP_DECLVAL(z, n, data) \
ndnboost::move_detail::declval< NDNBOOST_PP_CAT(P, n) >() \
//!

#define NDNBOOST_INTRUSIVE_PP_TEMPLATE_PARAM_VOID_DEFAULT(z, n, data)   \
  NDNBOOST_PP_CAT(class P, n) = void                                      \
//!

#include <ndnboost/intrusive/detail/config_end.hpp>

#endif //#ifndef NDNBOOST_INTRUSIVE_DETAIL_PREPROCESSOR_HPP
