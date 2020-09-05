//  (C) Copyright Gennadiy Rozental 2004-2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : basic_cstring class wrap C string and provide std_string like 
//                interface
// ***************************************************************************

#ifndef NDNBOOST_TEST_BASIC_CSTRING_FWD_HPP_071894GER
#define NDNBOOST_TEST_BASIC_CSTRING_FWD_HPP_071894GER

#include <ndnboost/detail/workaround.hpp>

namespace ndnboost {

namespace unit_test {

template<typename CharT> class      basic_cstring;
typedef basic_cstring<char const>   const_string;
#if NDNBOOST_WORKAROUND(__DECCXX_VER, NDNBOOST_TESTED_AT(60590041))
typedef const_string                literal_string;
#else
typedef const_string const          literal_string;
#endif

typedef char const* const           c_literal_string;

} // namespace unit_test

} // namespace ndnboost

#endif // NDNBOOST_TEST_BASIC_CSTRING_FWD_HPP_071894GER

