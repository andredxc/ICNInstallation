
#ifndef NDNBOOST_MPL_FOR_EACH_HPP_INCLUDED
#define NDNBOOST_MPL_FOR_EACH_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <ndnboost/mpl/is_sequence.hpp>
#include <ndnboost/mpl/begin_end.hpp>
#include <ndnboost/mpl/apply.hpp>
#include <ndnboost/mpl/bool.hpp>
#include <ndnboost/mpl/next_prior.hpp>
#include <ndnboost/mpl/deref.hpp>
#include <ndnboost/mpl/identity.hpp>
#include <ndnboost/mpl/assert.hpp>
#include <ndnboost/mpl/aux_/config/gpu.hpp>
#include <ndnboost/mpl/aux_/unwrap.hpp>

#include <ndnboost/type_traits/is_same.hpp>
#include <ndnboost/utility/value_init.hpp>

namespace ndnboost { namespace mpl {

namespace aux {

template< bool done = true >
struct for_each_impl
{
    template<
          typename Iterator
        , typename LastIterator
        , typename TransformFunc
        , typename F
        >
    NDNBOOST_MPL_CFG_GPU_ENABLED
    static void execute(
          Iterator*
        , LastIterator*
        , TransformFunc*
        , F
        )
    {
    }
};

template<>
struct for_each_impl<false>
{
    template<
          typename Iterator
        , typename LastIterator
        , typename TransformFunc
        , typename F
        >
    NDNBOOST_MPL_CFG_GPU_ENABLED
    static void execute(
          Iterator*
        , LastIterator*
        , TransformFunc* 
        , F f
        )
    {
        typedef typename deref<Iterator>::type item;
        typedef typename apply1<TransformFunc,item>::type arg;
    
        // dwa 2002/9/10 -- make sure not to invoke undefined behavior
        // when we pass arg.
        value_initialized<arg> x;
        aux::unwrap(f, 0)(ndnboost::get(x));
        
        typedef typename mpl::next<Iterator>::type iter;
        for_each_impl<ndnboost::is_same<iter,LastIterator>::value>
            ::execute( static_cast<iter*>(0), static_cast<LastIterator*>(0), static_cast<TransformFunc*>(0), f);
    }
};

} // namespace aux

// agurt, 17/mar/02: pointer default parameters are necessary to workaround 
// MSVC 6.5 function template signature's mangling bug
template<
      typename Sequence
    , typename TransformOp
    , typename F
    >
NDNBOOST_MPL_CFG_GPU_ENABLED
inline
void for_each(F f, Sequence* = 0, TransformOp* = 0)
{
    NDNBOOST_MPL_ASSERT(( is_sequence<Sequence> ));

    typedef typename begin<Sequence>::type first;
    typedef typename end<Sequence>::type last;

    aux::for_each_impl< ndnboost::is_same<first,last>::value >
        ::execute(static_cast<first*>(0), static_cast<last*>(0), static_cast<TransformOp*>(0), f);
}

template<
      typename Sequence
    , typename F
    >
NDNBOOST_MPL_CFG_GPU_ENABLED
inline
void for_each(F f, Sequence* = 0)
{
  // jfalcou: fully qualifying this call so it doesnt clash with ndnboostphoenix::for_each
  // ons ome compilers -- done on 02/28/2011
  ndnboost::mpl::for_each<Sequence, identity<> >(f);
}

}}

#endif // NDNBOOST_MPL_FOR_EACH_HPP_INCLUDED
