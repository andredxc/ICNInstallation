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
//  Description : implements facility to hide input traversing details
// ***************************************************************************

#ifndef NDNBOOST_RT_CLA_ARGV_TRAVERSER_IPP_070604GER
#define NDNBOOST_RT_CLA_ARGV_TRAVERSER_IPP_070604GER

// Boost.Runtime.Parameter
#include <ndnboost/test/utils/runtime/trace.hpp>

#include <ndnboost/test/utils/runtime/cla/argv_traverser.hpp>

// STL
#include <memory>
#include <cstring>

#ifdef NDNBOOST_NO_STDC_NAMESPACE
namespace std { using ::memcpy; }
#endif

namespace ndnboost {

namespace NDNBOOST_RT_PARAM_NAMESPACE {

namespace cla {

// ************************************************************************** //
// **************          runtime::cla::argv_traverser        ************** //
// ************************************************************************** //

NDNBOOST_RT_PARAM_INLINE
argv_traverser::argv_traverser()
: p_ignore_mismatch( false ), p_separator( NDNBOOST_RT_PARAM_LITERAL( ' ' ) )
{
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE void
argv_traverser::init( int argc, char_type** argv )
{
    for( int index = 1; index < argc; ++index ) {
        m_buffer += argv[index];
        if( index != argc-1 )
            m_buffer += NDNBOOST_RT_PARAM_LITERAL( ' ' );
    }

    m_remainder.reset( new char_type[m_buffer.size()+1] );
    m_remainder_size    = 0;
    m_work_buffer       = m_buffer;
    m_commited_end      = m_work_buffer.begin();

    NDNBOOST_RT_PARAM_TRACE( "Input buffer: " << m_buffer );

    next_token();
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE void
argv_traverser::remainder( int& argc, char_type** argv )
{
    argc = 1;
    std::size_t pos = 0;
    while(pos < m_remainder_size ) {
        argv[argc++] = m_remainder.get() + pos;

        pos = std::find( m_remainder.get() + pos, m_remainder.get() + m_remainder_size, 
                         NDNBOOST_RT_PARAM_LITERAL( ' ' ) ) - m_remainder.get();
        m_remainder[pos++] = NDNBOOST_RT_PARAM_LITERAL( '\0' );
    }
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE cstring
argv_traverser::token() const
{
    return m_token;
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE void
argv_traverser::next_token()
{
    if( m_work_buffer.is_empty() )
        return;

    m_work_buffer.trim_left( m_token.size() ); // skip remainder of current token

    if( m_work_buffer.size() != m_buffer.size() ) // !! is there a better way to identify first token
        m_work_buffer.trim_left( 1 ); // skip separator if not first token;

    m_token.assign( m_work_buffer.begin(),
                    std::find( m_work_buffer.begin(), m_work_buffer.end(), p_separator ) );
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE cstring
argv_traverser::input() const
{
    return m_work_buffer;
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE void
argv_traverser::trim( std::size_t size )
{
    m_work_buffer.trim_left( size );

    if( size <= m_token.size() )
        m_token.trim_left( size );
    else {
        m_token.assign( m_work_buffer.begin(),
                        std::find( m_work_buffer.begin(), m_work_buffer.end(), p_separator ) );
    }
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE bool
argv_traverser::match_front( cstring str )
{
    return m_work_buffer.size() < str.size() ? false : m_work_buffer.substr( 0, str.size() ) == str;
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE bool
argv_traverser::match_front( char_type c )
{
    return first_char( m_work_buffer ) == c;
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE bool
argv_traverser::eoi() const
{
    return m_work_buffer.is_empty();
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE void
argv_traverser::commit()
{
    m_commited_end = m_work_buffer.begin();
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE void
argv_traverser::rollback()
{
    m_work_buffer.assign( m_commited_end, m_work_buffer.end() );
    m_token.assign( m_work_buffer.begin(),
                    std::find( m_work_buffer.begin(), m_work_buffer.end(), p_separator ) );

}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE std::size_t
argv_traverser::input_pos() const
{
    return m_work_buffer.begin() - m_commited_end;
}

//____________________________________________________________________________//

NDNBOOST_RT_PARAM_INLINE bool
argv_traverser::handle_mismatch()
{
    if( !p_ignore_mismatch )
        return false;

    std::memcpy( m_remainder.get() + m_remainder_size, token().begin(), token().size() );
    m_remainder_size += token().size();
    m_remainder[m_remainder_size++] = p_separator;

    next_token();
    commit();

    return true;
}

//____________________________________________________________________________//

} // namespace cla

} // namespace NDNBOOST_RT_PARAM_NAMESPACE

} // namespace ndnboost

#endif // NDNBOOST_RT_CLA_ARGV_TRAVERSER_IPP_070604GER
