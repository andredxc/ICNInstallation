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
//  Description : simple facilities for accessing type information at runtime
// ***************************************************************************

#ifndef NDNBOOST_TEST_RTTI_HPP_062604GER
#define NDNBOOST_TEST_RTTI_HPP_062604GER

#include <cstddef>

namespace ndnboost {

namespace rtti {

// ************************************************************************** //
// **************                   rtti::type_id              ************** //
// ************************************************************************** //

typedef std::ptrdiff_t id_t;

namespace rtti_detail {

template<typename T>
struct rttid_holder {
    static id_t id() { return reinterpret_cast<id_t>( &inst() ); }

private:
    struct rttid {};

    static rttid const& inst() { static rttid s_inst;  return s_inst; }
};

} // namespace rtti_detail

//____________________________________________________________________________//

template<typename T>   
inline id_t
type_id()
{
    return rtti_detail::rttid_holder<T>::id();
}

//____________________________________________________________________________//

#define NDNBOOST_RTTI_SWITCH( type_id_ ) if( ::ndnboost::rtti::id_t switch_by_id = type_id_ )
#define NDNBOOST_RTTI_CASE( type )       if( switch_by_id == ::ndnboost::rtti::type_id<type>() )

//____________________________________________________________________________//

} // namespace rtti

} // namespace ndnboost

#endif // NDNBOOST_RT_RTTI_HPP_062604GER
