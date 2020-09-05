// Boost Lambda Library - lambda_config.hpp ------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef NDNBOOST_LAMBDA_LAMBDA_CONFIG_HPP
#define NDNBOOST_LAMBDA_LAMBDA_CONFIG_HPP

// add to ndnboost/config.hpp
// for now


# if defined __GNUC__
#   if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) 
#     define NDNBOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
#     define NDNBOOST_LAMBDA_INCORRECT_BIND_OVERLOADING
#   endif
#   if (__GNUC__ == 2 && __GNUC_MINOR__ <= 97) 
#     define NDNBOOST_NO_TEMPLATED_STREAMS
#     define NDNBOOST_LAMBDA_INCORRECT_BIND_OVERLOADING
#   endif
#   if (__GNUC__ == 2 && __GNUC_MINOR__ <= 95) 
#     define NDNBOOST_LAMBDA_FAILS_IN_TEMPLATE_KEYWORD_AFTER_SCOPE_OPER
#   endif
# endif  // __GNUC__
 

#if defined __KCC

#define NDNBOOST_NO_FDECL_TEMPLATES_AS_TEMPLATE_TEMPLATE_PARAMS

#endif  // __KCC

#endif







