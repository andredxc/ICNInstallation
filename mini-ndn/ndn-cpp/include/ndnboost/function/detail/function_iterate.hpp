// Boost.Function library

//  Copyright Douglas Gregor 2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org
#if !defined(NDNBOOST_PP_IS_ITERATING)
# error Boost.Function - do not include this file!
#endif

#define NDNBOOST_FUNCTION_NUM_ARGS NDNBOOST_PP_ITERATION()
#include <ndnboost/function/detail/maybe_include.hpp>
#undef NDNBOOST_FUNCTION_NUM_ARGS

