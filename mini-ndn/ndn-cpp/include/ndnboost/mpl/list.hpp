
#ifndef NDNBOOST_MPL_LIST_HPP_INCLUDED
#define NDNBOOST_MPL_LIST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(NDNBOOST_MPL_PREPROCESSING_MODE)
#   include <ndnboost/mpl/limits/list.hpp>
#   include <ndnboost/mpl/aux_/na.hpp>
#   include <ndnboost/mpl/aux_/config/preprocessor.hpp>

#   include <ndnboost/preprocessor/inc.hpp>
#   include <ndnboost/preprocessor/cat.hpp>
#   include <ndnboost/preprocessor/stringize.hpp>

#if !defined(NDNBOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_LIST_HEADER \
    NDNBOOST_PP_CAT(list,NDNBOOST_MPL_LIMIT_LIST_SIZE).hpp \
    /**/
#else
#   define AUX778076_LIST_HEADER \
    NDNBOOST_PP_CAT(list,NDNBOOST_MPL_LIMIT_LIST_SIZE)##.hpp \
    /**/
#endif

#   include NDNBOOST_PP_STRINGIZE(ndnboost/mpl/list/AUX778076_LIST_HEADER)
#   undef AUX778076_LIST_HEADER
#endif

#include <ndnboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(NDNBOOST_MPL_PREPROCESSING_MODE)

#   define NDNBOOST_MPL_PREPROCESSED_HEADER list.hpp
#   include <ndnboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <ndnboost/mpl/limits/list.hpp>

#   define AUX778076_SEQUENCE_NAME list
#   define AUX778076_SEQUENCE_LIMIT NDNBOOST_MPL_LIMIT_LIST_SIZE
#   include <ndnboost/mpl/aux_/sequence_wrapper.hpp>

#endif // NDNBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // NDNBOOST_MPL_LIST_HPP_INCLUDED
