//  (C) Copyright Gennadiy Rozental 2001-2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : defines singleton class unit_test_log and all manipulators.
//  unit_test_log has output stream like interface. It's implementation is
//  completely hidden with pimple idiom
// ***************************************************************************

#ifndef NDNBOOST_TEST_UNIT_TEST_LOG_HPP_071894GER
#define NDNBOOST_TEST_UNIT_TEST_LOG_HPP_071894GER

// Boost.Test
#include <ndnboost/test/test_observer.hpp>

#include <ndnboost/test/detail/global_typedef.hpp>
#include <ndnboost/test/detail/log_level.hpp>
#include <ndnboost/test/detail/fwd_decl.hpp>

#include <ndnboost/test/utils/wrap_stringstream.hpp>
#include <ndnboost/test/utils/trivial_singleton.hpp>
#include <ndnboost/test/utils/lazy_ostream.hpp>

// Boost
#include <ndnboost/utility.hpp>

// STL
#include <iosfwd>   // for std::ostream&

#include <ndnboost/test/detail/suppress_warnings.hpp>

//____________________________________________________________________________//

namespace ndnboost {

namespace unit_test {

// ************************************************************************** //
// **************                log manipulators              ************** //
// ************************************************************************** //

namespace log {

struct NDNBOOST_TEST_DECL begin {
    begin( const_string fn, std::size_t ln )
    : m_file_name( fn )
    , m_line_num( ln )
    {}

    const_string m_file_name;
    std::size_t m_line_num;
};

struct end {};

} // namespace log

// ************************************************************************** //
// **************             entry_value_collector            ************** //
// ************************************************************************** //

namespace ut_detail {

class NDNBOOST_TEST_DECL entry_value_collector {
public:
    // Constructors
    entry_value_collector() : m_last( true ) {}
    entry_value_collector( entry_value_collector const& rhs ) : m_last( true ) { rhs.m_last = false; }
    ~entry_value_collector();

    // collection interface
    entry_value_collector const& operator<<( lazy_ostream const& ) const;
    entry_value_collector const& operator<<( const_string ) const;

private:
    // Data members
    mutable bool    m_last;
};

} // namespace ut_detail

// ************************************************************************** //
// **************                 unit_test_log                ************** //
// ************************************************************************** //

class NDNBOOST_TEST_DECL unit_test_log_t : public test_observer, public singleton<unit_test_log_t> {
public:
    // test_observer interface implementation
    void                test_start( counter_t test_cases_amount );
    void                test_finish();
    void                test_aborted();

    void                test_unit_start( test_unit const& );
    void                test_unit_finish( test_unit const&, unsigned long elapsed );
    void                test_unit_skipped( test_unit const& );
    void                test_unit_aborted( test_unit const& );

    void                assertion_result( bool passed );
    void                exception_caught( execution_exception const& );

    virtual int         priority() { return 1; }

    // log configuration methods
    void                set_stream( std::ostream& );
    void                set_threshold_level( log_level );
    void                set_format( output_format );
    void                set_formatter( unit_test_log_formatter* );

    // test progress logging
    void                set_checkpoint( const_string file, std::size_t line_num, const_string msg = const_string() );

    // entry logging
    unit_test_log_t&    operator<<( log::begin const& );        // begin entry 
    unit_test_log_t&    operator<<( log::end const& );          // end entry
    unit_test_log_t&    operator<<( log_level );                // set entry level
    unit_test_log_t&    operator<<( const_string );             // log entry value
    unit_test_log_t&    operator<<( lazy_ostream const& );      // log entry value

    ut_detail::entry_value_collector operator()( log_level );   // initiate entry collection

private:
    bool            log_entry_start();

    NDNBOOST_TEST_SINGLETON_CONS( unit_test_log_t );
}; // unit_test_log_t

NDNBOOST_TEST_SINGLETON_INST( unit_test_log )

// helper macros
#define NDNBOOST_TEST_LOG_ENTRY( ll )                                                  \
    (::ndnboost::unit_test::unit_test_log                                              \
        << ::ndnboost::unit_test::log::begin( NDNBOOST_TEST_L(__FILE__), __LINE__ ))(ll)  \
/**/

} // namespace unit_test

} // namespace ndnboost

// ************************************************************************** //
// **************       Unit test log interface helpers        ************** //
// ************************************************************************** //

#define NDNBOOST_TEST_MESSAGE( M )                                 \
    NDNBOOST_TEST_LOG_ENTRY( ::ndnboost::unit_test::log_messages )    \
    << (::ndnboost::unit_test::lazy_ostream::instance() << M)      \
/**/

//____________________________________________________________________________//

#define NDNBOOST_TEST_PASSPOINT()                                  \
    ::ndnboost::unit_test::unit_test_log.set_checkpoint(           \
        NDNBOOST_TEST_L(__FILE__),                                 \
        static_cast<std::size_t>(__LINE__) )                    \
/**/

//____________________________________________________________________________//

#define NDNBOOST_TEST_CHECKPOINT( M )                              \
    ::ndnboost::unit_test::unit_test_log.set_checkpoint(           \
        NDNBOOST_TEST_L(__FILE__),                                 \
        static_cast<std::size_t>(__LINE__),                     \
        (::ndnboost::wrap_stringstream().ref() << M).str() )       \
/**/

//____________________________________________________________________________//

#include <ndnboost/test/detail/enable_warnings.hpp>

#endif // NDNBOOST_TEST_UNIT_TEST_LOG_HPP_071894GER

