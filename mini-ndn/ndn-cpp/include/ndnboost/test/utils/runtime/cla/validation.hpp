//  (C) Copyright Gennadiy Rozental 2005-2008.
//  Use, modification, and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : input validation helpers definition
// ***************************************************************************

#ifndef NDNBOOST_RT_CLA_VALIDATION_HPP_062604GER
#define NDNBOOST_RT_CLA_VALIDATION_HPP_062604GER

// Boost.Runtime.Parameter
#include <ndnboost/test/utils/runtime/config.hpp>

#include <ndnboost/test/utils/runtime/cla/fwd.hpp>

namespace ndnboost {

namespace NDNBOOST_RT_PARAM_NAMESPACE {

namespace cla {

// ************************************************************************** //
// **************       runtime::cla::report_input_error       ************** //
// ************************************************************************** //

void report_input_error( argv_traverser const& tr, format_stream& msg );

//____________________________________________________________________________//

#define NDNBOOST_RT_CLA_VALIDATE_INPUT( b, tr, msg ) \
    if( b ) ; else ::ndnboost::NDNBOOST_RT_PARAM_NAMESPACE::cla::report_input_error( tr, format_stream().ref() << msg )

//____________________________________________________________________________//

} // namespace cla

} // namespace NDNBOOST_RT_PARAM_NAMESPACE

} // namespace ndnboost

#ifndef NDNBOOST_RT_PARAM_OFFLINE

#  define NDNBOOST_RT_PARAM_INLINE inline
#  include <ndnboost/test/utils/runtime/cla/validation.ipp>

#endif

#endif // NDNBOOST_RT_CLA_VALIDATION_HPP_062604GER
