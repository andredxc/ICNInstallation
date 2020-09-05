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
//  Description : Facilities to perform interaction-based testing
// ***************************************************************************

#ifndef NDNBOOST_TEST_INTERACTION_BASED_HPP_112105GER
#define NDNBOOST_TEST_INTERACTION_BASED_HPP_112105GER

// Boost.Test
#include <ndnboost/test/detail/config.hpp>
#include <ndnboost/test/detail/global_typedef.hpp>

#include <ndnboost/test/utils/wrap_stringstream.hpp>

#include <ndnboost/test/detail/suppress_warnings.hpp>

// Boost
#include <ndnboost/lexical_cast.hpp>

//____________________________________________________________________________//

// ************************************************************************** //
// **************               NDNBOOST_ITEST_EPOINT             ************** //
// ************************************************************************** //

#define NDNBOOST_ITEST_EPOINT( description ) \
    ::ndnboost::itest::manager::instance().exception_point( NDNBOOST_TEST_L(__FILE__), __LINE__, description )
/**/

// ************************************************************************** //
// **************               NDNBOOST_ITEST_DPOINT             ************** //
// ************************************************************************** //

#define NDNBOOST_ITEST_DPOINT() \
    ::ndnboost::itest::manager::instance().decision_point( NDNBOOST_TEST_L(__FILE__), __LINE__ )
/**/

// ************************************************************************** //
// **************                NDNBOOST_ITEST_SCOPE             ************** //
// ************************************************************************** //

#define NDNBOOST_ITEST_SCOPE( scope_name ) \
    ::ndnboost::itest::scope_guard itest_scope_guard ## __LINE__( NDNBOOST_TEST_L(__FILE__), __LINE__, NDNBOOST_STRINGIZE(scope_name) )
/**/

// ************************************************************************** //
// **************                 NDNBOOST_ITEST_NEW              ************** //
// ************************************************************************** //

#define NDNBOOST_ITEST_NEW( type_name ) \
    new ( ::ndnboost::itest::location( NDNBOOST_TEST_L(__FILE__), __LINE__ ) ) type_name
/**/

// ************************************************************************** //
// **************              NDNBOOST_ITEST_DATA_FLOW           ************** //
// ************************************************************************** //

#define NDNBOOST_ITEST_DATA_FLOW( v ) \
    ::ndnboost::itest::manager::instance().generic_data_flow( v )
/**/

// ************************************************************************** //
// **************               NDNBOOST_ITEST_RETURN             ************** //
// ************************************************************************** //

#define NDNBOOST_ITEST_RETURN( type, default_value ) \
    ::ndnboost::itest::manager::instance().generic_return<type>( default_value )
/**/

// ************************************************************************** //
// **************              NDNBOOST_ITEST_MOCK_FUNC           ************** //
// ************************************************************************** //

#define NDNBOOST_ITEST_MOCK_FUNC( function_name )          \
    NDNBOOST_ITEST_SCOPE( function_name );                 \
    NDNBOOST_ITEST_EPOINT( 0 );                            \
    return ::ndnboost::itest::mock_object<>::prototype();  \
/**/

namespace ndnboost {

namespace itest { // interaction-based testing

using unit_test::const_string;

// ************************************************************************** //
// **************                    manager                   ************** //
// ************************************************************************** //

class NDNBOOST_TEST_DECL manager {
public:
    // instance access
    static manager&     instance() { return *instance_ptr(); }

    // Mock objects interface hooks
    virtual void        exception_point( const_string /*file*/, 
                                         std::size_t /*line_num*/, 
                                         const_string /*descr*/ ){}
    virtual bool        decision_point( const_string /*file*/, 
                                        std::size_t /*line_num*/ )          { return true; }
    virtual unsigned    enter_scope( const_string /*file*/, 
                                     std::size_t /*line_num*/,
                                     const_string /*scope_name*/){ return 0; }
    virtual void        leave_scope( unsigned )                             {}
    virtual void        allocated( const_string /*file*/, 
                                   std::size_t /*line_num*/, 
                                   void* /*p*/, std::size_t /*s*/ )         {}
    virtual void        freed( void* /*p*/ )                                {}
    virtual void        data_flow( const_string /*d*/ )                     {}
    virtual std::string return_value( const_string /*default_value */ )     { return ""; }

    template<typename T>
    void                generic_data_flow( T const& t )
    {
        wrap_stringstream ws;

        data_flow( (ws << t).str() );
    }
    template<typename T, typename DefaultValueType>
    T                   generic_return( DefaultValueType const& dv )
    {
        wrap_stringstream ws;

        std::string const& res = return_value( (ws << dv).str() );

        if( res.empty() )
            return dv;

        return lexical_cast<T>( res );
    }

protected:
    manager();
#if NDNBOOST_WORKAROUND(__BORLANDC__, NDNBOOST_TESTED_AT(0x564)) 
public:
#endif
    NDNBOOST_TEST_PROTECTED_VIRTUAL ~manager();

private:
    struct dummy_constr{};
    explicit manager( dummy_constr* ) {}

    static manager*     instance_ptr( bool reset = false, manager* ptr = 0 );
}; // manager

// ************************************************************************** //
// **************                  scope_guard                 ************** //
// ************************************************************************** //

class scope_guard {
public:
    // Constructor
    scope_guard( const_string file, std::size_t line_num, const_string scope_name )
    {
        m_scope_index = manager::instance().enter_scope( file, line_num, scope_name );
    }
    ~scope_guard()
    {
        manager::instance().leave_scope( m_scope_index );
    }

    unsigned m_scope_index;
};

// ************************************************************************** //
// **************                    location                  ************** //
// ************************************************************************** //

struct location {
    location( const_string file, std::size_t line ) 
    : m_file_name( file )
    , m_line_num( line )
    {}

    const_string    m_file_name;
    std::size_t     m_line_num;
};

}  // namespace itest

} // namespace ndnboost

// ************************************************************************** //
// **************              operator new overload           ************** //
// ************************************************************************** //

#if !defined(NDNBOOST_ITEST_NO_NEW_OVERLOADS)

// STL
#include <cstdlib>

# ifdef NDNBOOST_NO_STDC_NAMESPACE
namespace std { using ::malloc; using ::free; }
# endif
# ifdef _CRTDBG_MAP_ALLOC
namespace std { using ::_malloc_dbg; using ::_free_dbg; }
# endif

inline void*
operator new( std::size_t s, ::ndnboost::itest::location const& l )
{
    void* res = std::malloc(s ? s : 1);

    if( res )
        ::ndnboost::itest::manager::instance().allocated( l.m_file_name, l.m_line_num, res, s );
    else
        throw std::bad_alloc();
        
    return res;
}

//____________________________________________________________________________//

inline void*
operator new[]( std::size_t s, ::ndnboost::itest::location const& l )
{
    void* res = std::malloc(s ? s : 1);

    if( res )
        ::ndnboost::itest::manager::instance().allocated( l.m_file_name, l.m_line_num, res, s );
    else
        throw std::bad_alloc();
        
    return res;
}

//____________________________________________________________________________//

inline void
operator delete( void* p, ::ndnboost::itest::location const& )
{
    ::ndnboost::itest::manager::instance().freed( p );

    std::free( p );
}

//____________________________________________________________________________//

inline void
operator delete[]( void* p, ::ndnboost::itest::location const& )
{
    ::ndnboost::itest::manager::instance().freed( p );

    std::free( p );
}

//____________________________________________________________________________//

#endif

#include <ndnboost/test/detail/enable_warnings.hpp>

#endif // NDNBOOST_TEST_INTERACTION_BASED_HPP_112105GER
