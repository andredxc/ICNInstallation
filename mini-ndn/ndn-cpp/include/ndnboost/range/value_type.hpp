// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef NDNBOOST_RANGE_VALUE_TYPE_HPP
#define NDNBOOST_RANGE_VALUE_TYPE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <ndnboost/range/config.hpp>
#include <ndnboost/range/iterator.hpp>

#include <ndnboost/iterator/iterator_traits.hpp>

namespace ndnboost
{
    template< class T >
    struct range_value : iterator_value< typename range_iterator<T>::type >
    { };
}

#endif
