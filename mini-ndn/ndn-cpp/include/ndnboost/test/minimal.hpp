//  (C) Copyright Gennadiy Rozental 2002-2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : simple minimal testing definitions and implementation
// ***************************************************************************

#ifndef NDNBOOST_TEST_MINIMAL_HPP_071894GER
#define NDNBOOST_TEST_MINIMAL_HPP_071894GER

#define NDNBOOST_CHECK(exp)       \
  ( (exp)                      \
      ? static_cast<void>(0)   \
      : ndnboost::minimal_test::report_error(#exp,__FILE__,__LINE__, NDNBOOST_CURRENT_FUNCTION) )

#define NDNBOOST_REQUIRE(exp)     \
  ( (exp)                      \
      ? static_cast<void>(0)   \
      : ndnboost::minimal_test::report_critical_error(#exp,__FILE__,__LINE__,NDNBOOST_CURRENT_FUNCTION))

#define NDNBOOST_ERROR( msg_ )    \
        ndnboost::minimal_test::report_error( (msg_),__FILE__,__LINE__, NDNBOOST_CURRENT_FUNCTION, true )
#define NDNBOOST_FAIL( msg_ )     \
        ndnboost::minimal_test::report_critical_error( (msg_),__FILE__,__LINE__, NDNBOOST_CURRENT_FUNCTION, true )

//____________________________________________________________________________//

// Boost.Test
#include <ndnboost/test/detail/global_typedef.hpp>
#include <ndnboost/test/impl/execution_monitor.ipp>
#include <ndnboost/test/impl/debug.ipp>
#include <ndnboost/test/utils/class_properties.hpp>
#include <ndnboost/test/utils/basic_cstring/io.hpp>

// Boost
#include <ndnboost/cstdlib.hpp>            // for exit codes#include <ndnboost/cstdlib.hpp>            // for exit codes
#include <ndnboost/current_function.hpp>   // for NDNBOOST_CURRENT_FUNCTION

// STL
#include <iostream>                     // std::cerr, std::endl
#include <string>                       // std::string

#include <ndnboost/test/detail/suppress_warnings.hpp>

//____________________________________________________________________________//

int test_main( int argc, char* argv[] );  // prototype for users test_main()

namespace ndnboost {
namespace minimal_test {

typedef ndnboost::unit_test::const_string const_string;

inline unit_test::counter_t& errors_counter() { static unit_test::counter_t ec = 0; return ec; }

inline void
report_error( const char* msg, const char* file, int line, const_string func_name, bool is_msg = false )
{
    ++errors_counter();
    std::cerr << file << "(" << line << "): ";

    if( is_msg )
        std::cerr << msg;
    else
        std::cerr << "test " << msg << " failed";

    if( func_name != "(unknown)" )
        std::cerr << " in function: '" << func_name << "'";

    std::cerr << std::endl;
}

inline void
report_critical_error( const char* msg, const char* file, int line, const_string func_name, bool is_msg = false )
{
    report_error( msg, file, line, func_name, is_msg );

    throw ndnboost::execution_aborted();
}

class caller {
public:
    // constructor
    caller( int argc, char** argv )
    : m_argc( argc ), m_argv( argv ) {}

    // execution monitor hook implementation
    int operator()() { return test_main( m_argc, m_argv ); }

private:
    // Data members
    int         m_argc;
    char**      m_argv;
}; // monitor

} // namespace minimal_test

} // namespace ndnboost

//____________________________________________________________________________//

int NDNBOOST_TEST_CALL_DECL main( int argc, char* argv[] )
{
    using namespace ndnboost::minimal_test;

    try {
        ::ndnboost::execution_monitor ex_mon;
        int run_result = ex_mon.execute( caller( argc, argv ) );

        NDNBOOST_CHECK( run_result == 0 || run_result == ndnboost::exit_success );
    }
    catch( ndnboost::execution_exception const& exex ) {
        if( exex.code() != ndnboost::execution_exception::no_error )
            NDNBOOST_ERROR( (std::string( "exception \"" ).
                            append( exex.what().begin(), exex.what().end() ).
                            append( "\" caught" ) ).c_str() );
        std::cerr << "\n**** Testing aborted.";
    }

    if( ndnboost::minimal_test::errors_counter() != 0 ) {
        std::cerr << "\n**** " << errors_counter()
                  << " error" << (errors_counter() > 1 ? "s" : "" ) << " detected\n";

        return ndnboost::exit_test_failure;
    }

    std::cout << "\n**** no errors detected\n";
    
    return ndnboost::exit_success;
}

//____________________________________________________________________________//

#include <ndnboost/test/detail/enable_warnings.hpp>

#endif // NDNBOOST_TEST_MINIMAL_HPP_071894GER
