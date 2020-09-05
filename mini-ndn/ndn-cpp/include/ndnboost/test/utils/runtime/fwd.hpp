//  (C) Copyright Gennadiy Rozental 2005-2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : global framework level forward declaration
// ***************************************************************************

#ifndef NDNBOOST_RT_FWD_HPP_062604GER
#define NDNBOOST_RT_FWD_HPP_062604GER

// Boost.Runtime.Parameter
#include <ndnboost/test/utils/runtime/config.hpp>

// Boost
#include <ndnboost/shared_ptr.hpp>

namespace ndnboost {

namespace NDNBOOST_RT_PARAM_NAMESPACE {

class parameter;

class argument;
typedef shared_ptr<argument> argument_ptr;
typedef shared_ptr<argument const> const_argument_ptr;

template<typename T> class value_interpreter;
template<typename T> class typed_argument;

} // namespace NDNBOOST_RT_PARAM_NAMESPACE

} // namespace ndnboost

#endif // NDNBOOST_RT_FWD_HPP_062604GER
