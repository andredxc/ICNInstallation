
// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <ndnboost/mpl/aux_/config/workaround.hpp>

#include <ndnboost/preprocessor/cat.hpp>
#include <ndnboost/preprocessor/stringize.hpp>

#   define AUX778076_HEADER \
    aux_/preprocessed/plain/NDNBOOST_MPL_PREPROCESSED_HEADER \
/**/

#if NDNBOOST_WORKAROUND(__IBMCPP__, NDNBOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING NDNBOOST_PP_STRINGIZE(ndnboost/mpl/list/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include NDNBOOST_PP_STRINGIZE(ndnboost/mpl/list/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef NDNBOOST_MPL_PREPROCESSED_HEADER
