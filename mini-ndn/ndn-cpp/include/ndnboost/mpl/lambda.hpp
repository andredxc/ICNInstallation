
#ifndef NDNBOOST_MPL_LAMBDA_HPP_INCLUDED
#define NDNBOOST_MPL_LAMBDA_HPP_INCLUDED

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

#include <ndnboost/mpl/lambda_fwd.hpp>
#include <ndnboost/mpl/bind.hpp>
#include <ndnboost/mpl/aux_/config/lambda.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   include <ndnboost/mpl/aux_/full_lambda.hpp>
#else
#   include <ndnboost/mpl/aux_/lambda_no_ctps.hpp>
#   include <ndnboost/mpl/aux_/lambda_support.hpp>
#   define NDNBOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#endif // NDNBOOST_MPL_LAMBDA_HPP_INCLUDED
