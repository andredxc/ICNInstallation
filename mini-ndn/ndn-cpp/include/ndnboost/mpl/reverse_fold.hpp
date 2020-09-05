
#ifndef NDNBOOST_MPL_REVERSE_FOLD_HPP_INCLUDED
#define NDNBOOST_MPL_REVERSE_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/begin_end.hpp>
#include <ndnboost/mpl/O1_size.hpp>
#include <ndnboost/mpl/arg.hpp>
#include <ndnboost/mpl/aux_/reverse_fold_impl.hpp>
#include <ndnboost/mpl/aux_/na_spec.hpp>

namespace ndnboost { namespace mpl {

template<
      typename NDNBOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename NDNBOOST_MPL_AUX_NA_PARAM(State)
    , typename NDNBOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_fold
{
    typedef typename aux::reverse_fold_impl<
          ::ndnboost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , BackwardOp
        , ForwardOp
        >::state type;

    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(3,reverse_fold,(Sequence,State,BackwardOp))
};

NDNBOOST_MPL_AUX_NA_SPEC(3, reverse_fold)

}}

#endif // NDNBOOST_MPL_REVERSE_FOLD_HPP_INCLUDED
