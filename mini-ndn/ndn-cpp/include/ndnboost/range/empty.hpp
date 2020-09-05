// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef NDNBOOST_RANGE_EMPTY_HPP
#define NDNBOOST_RANGE_EMPTY_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <ndnboost/range/config.hpp>
#include <ndnboost/range/begin.hpp>
#include <ndnboost/range/end.hpp>

namespace ndnboost 
{ 

    template< class T >
    inline bool empty( const T& r )
    {
        return ndnboost::begin( r ) == ndnboost::end( r );
    }

} // namespace 'boost'


#endif
