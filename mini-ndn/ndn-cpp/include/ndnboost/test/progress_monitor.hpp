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
//  Description : defines simple text based progress monitor
// ***************************************************************************

#ifndef NDNBOOST_TEST_PROGRESS_MONITOR_HPP_020105GER
#define NDNBOOST_TEST_PROGRESS_MONITOR_HPP_020105GER

// Boost.Test
#include <ndnboost/test/test_observer.hpp>
#include <ndnboost/test/utils/trivial_singleton.hpp>

// STL
#include <iosfwd>   // for std::ostream&

#include <ndnboost/test/detail/suppress_warnings.hpp>

//____________________________________________________________________________//

namespace ndnboost {

namespace unit_test {

// ************************************************************************** //
// **************                progress_monitor              ************** //
// ************************************************************************** //

class NDNBOOST_TEST_DECL progress_monitor_t : public test_observer, public singleton<progress_monitor_t> {
public:
    // test observer interface
    void    test_start( counter_t test_cases_amount );
    void    test_finish() {}
    void    test_aborted();

    void    test_unit_start( test_unit const& ) {}
    void    test_unit_finish( test_unit const&, unsigned long );
    void    test_unit_skipped( test_unit const& );
    void    test_unit_aborted( test_unit const& ) {}

    void    assertion_result( bool ) {}
    void    exception_caught( execution_exception const& ) {}

    // configuration
    void    set_stream( std::ostream& );

private:
    NDNBOOST_TEST_SINGLETON_CONS( progress_monitor_t );
}; // progress_monitor_t

NDNBOOST_TEST_SINGLETON_INST( progress_monitor )

} // namespace unit_test

} // namespace ndnboost

//____________________________________________________________________________//

#include <ndnboost/test/detail/enable_warnings.hpp>

#endif // NDNBOOST_TEST_PROGRESS_MONITOR_HPP_020105GER

