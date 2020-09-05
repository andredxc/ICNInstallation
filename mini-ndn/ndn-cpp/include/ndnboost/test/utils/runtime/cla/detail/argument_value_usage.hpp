//  (C) Copyright Gennadiy Rozental 2005-2008.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.
  
//  See http://www.boost.org for updates, documentation, and revision history.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : argument usage printing helpers
// ***************************************************************************

#ifndef NDNBOOST_RT_CLA_ARGUMENT_VALUE_USAGE_HPP_062604GER
#define NDNBOOST_RT_CLA_ARGUMENT_VALUE_USAGE_HPP_062604GER

// Boost.Runtime.Parameter
#include <ndnboost/test/utils/runtime/config.hpp>
#include <ndnboost/test/utils/runtime/cla/argv_traverser.hpp>

// Boost.Test
#include <ndnboost/test/utils/basic_cstring/io.hpp>
#include <ndnboost/test/utils/basic_cstring/compare.hpp>

#include <ndnboost/lexical_cast.hpp>

// STL
// !! can we eliminate these includes?
#include <list>

namespace ndnboost {

namespace NDNBOOST_RT_PARAM_NAMESPACE {

namespace cla {

namespace rt_cla_detail {

// ************************************************************************** //
// **************             argument_value_usage             ************** //
// ************************************************************************** //

// generic case
template<typename T>
inline void
argument_value_usage( format_stream& fs, long, T* = 0 )
{
    fs << NDNBOOST_RT_PARAM_CSTRING_LITERAL( "<value>" );
}

//____________________________________________________________________________//

// specialization for list of values
template<typename T>
inline void
argument_value_usage( format_stream& fs, int, std::list<T>* = 0 )
{
    fs << NDNBOOST_RT_PARAM_CSTRING_LITERAL( "(<value1>, ..., <valueN>)" );
}

//____________________________________________________________________________//

// specialization for type bool
inline void
argument_value_usage( format_stream& fs,  int, bool* = 0 )
{
    fs << NDNBOOST_RT_PARAM_CSTRING_LITERAL( "yes|y|no|n" );
}

//____________________________________________________________________________//

} // namespace rt_cla_detail

} // namespace cla

} // namespace NDNBOOST_RT_PARAM_NAMESPACE

} // namespace ndnboost

#endif // NDNBOOST_RT_CLA_ARGUMENT_VALUE_USAGE_HPP_062604GER
