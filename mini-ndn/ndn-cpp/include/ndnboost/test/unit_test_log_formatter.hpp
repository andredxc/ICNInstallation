//  (C) Copyright Gennadiy Rozental 2003-2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : 
// ***************************************************************************

#ifndef NDNBOOST_TEST_UNIT_TEST_LOG_FORMATTER_HPP_071894GER
#define NDNBOOST_TEST_UNIT_TEST_LOG_FORMATTER_HPP_071894GER

// Boost.Test
#include <ndnboost/test/detail/global_typedef.hpp>
#include <ndnboost/test/detail/log_level.hpp>
#include <ndnboost/test/detail/fwd_decl.hpp>

#include <ndnboost/test/execution_monitor.hpp>

// STL
#include <iosfwd>
#include <string> // for std::string

#include <ndnboost/test/detail/suppress_warnings.hpp>

//____________________________________________________________________________//

namespace ndnboost {

namespace unit_test {

// ************************************************************************** //
// **************                log_entry_data                ************** //
// ************************************************************************** //

struct NDNBOOST_TEST_DECL log_entry_data {
    log_entry_data()
    {
        m_file_name.reserve( 200 );
    }

    std::string     m_file_name;
    std::size_t     m_line_num;
    log_level       m_level;

    void clear()
    {
        m_file_name.erase();
        m_line_num      = 0;
        m_level     = log_nothing;
    }
};

// ************************************************************************** //
// **************                checkpoint_data               ************** //
// ************************************************************************** //

struct NDNBOOST_TEST_DECL log_checkpoint_data
{
    const_string    m_file_name;
    std::size_t     m_line_num;
    std::string     m_message;

    void clear()
    {
        m_file_name.clear();
        m_line_num    = 0;
        m_message = std::string();
    }
};

// ************************************************************************** //
// **************            unit_test_log_formatter           ************** //
// ************************************************************************** //

class NDNBOOST_TEST_DECL unit_test_log_formatter {
public:
    enum log_entry_types { NDNBOOST_UTL_ET_INFO, 
                           NDNBOOST_UTL_ET_MESSAGE,
                           NDNBOOST_UTL_ET_WARNING,
                           NDNBOOST_UTL_ET_ERROR,
                           NDNBOOST_UTL_ET_FATAL_ERROR };

    // Destructor
    virtual             ~unit_test_log_formatter() {}

    // Formatter interface
    virtual void        log_start( std::ostream&, counter_t test_cases_amount ) = 0;
    virtual void        log_finish( std::ostream& ) = 0;
    virtual void        log_build_info( std::ostream& ) = 0;

    virtual void        test_unit_start( std::ostream&, test_unit const& tu ) = 0;
    virtual void        test_unit_finish( std::ostream&, test_unit const& tu, unsigned long elapsed ) = 0;
    virtual void        test_unit_skipped( std::ostream&, test_unit const& ) = 0;

    virtual void        log_exception( std::ostream& os, log_checkpoint_data const& cd, execution_exception const& ex )
    {
        // for backward compatibility
        log_exception( os, cd, ex.what() );
    }
    virtual void        log_exception( std::ostream&, log_checkpoint_data const&, const_string /* explanation */ ) {}

    virtual void        log_entry_start( std::ostream&, log_entry_data const&, log_entry_types let ) = 0;
    virtual void        log_entry_value( std::ostream&, const_string value ) = 0;
    virtual void        log_entry_value( std::ostream&, lazy_ostream const& value ); // there is a default impl
    virtual void        log_entry_finish( std::ostream& ) = 0;
};

} // namespace unit_test

} // namespace ndnboost

//____________________________________________________________________________//

#include <ndnboost/test/detail/enable_warnings.hpp>

#endif // NDNBOOST_TEST_UNIT_TEST_LOG_FORMATTER_HPP_071894GER

