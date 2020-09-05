
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/aux_/config/compiler.hpp>
#include <ndnboost/mpl/aux_/config/preprocessor.hpp>
#include <ndnboost/mpl/aux_/config/workaround.hpp>
#include <ndnboost/preprocessor/cat.hpp>
#include <ndnboost/preprocessor/stringize.hpp>

#if !defined(NDNBOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_PREPROCESSED_HEADER \
    NDNBOOST_MPL_CFG_COMPILER_DIR/NDNBOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_PREPROCESSED_HEADER \
    NDNBOOST_PP_CAT(NDNBOOST_MPL_CFG_COMPILER_DIR,/)##NDNBOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if NDNBOOST_WORKAROUND(__IBMCPP__, NDNBOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING NDNBOOST_PP_STRINGIZE(ndnboost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include NDNBOOST_PP_STRINGIZE(ndnboost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#endif

#   undef AUX778076_PREPROCESSED_HEADER

#undef NDNBOOST_MPL_PREPROCESSED_HEADER
