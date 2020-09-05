// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef NDNBOOST_RANGE_ITERATOR_HPP
#define NDNBOOST_RANGE_ITERATOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <ndnboost/range/config.hpp>
#include <ndnboost/range/range_fwd.hpp>
#include <ndnboost/range/mutable_iterator.hpp>
#include <ndnboost/range/const_iterator.hpp>
#include <ndnboost/type_traits/is_const.hpp>
#include <ndnboost/type_traits/remove_const.hpp>
#include <ndnboost/mpl/eval_if.hpp>

namespace ndnboost
{

#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, == 1310)  

    namespace range_detail_vc7_1  
    {  
       template< typename C, typename Sig = void(C) >  
       struct range_iterator  
       {  
           typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   
               mpl::eval_if_c< is_const<C>::value,   
                               range_const_iterator< typename remove_const<C>::type >,  
                               range_mutable_iterator<C> >::type type;  
       };  
    
       template< typename C, typename T >  
       struct range_iterator< C, void(T[]) >  
       {  
           typedef T* type;  
       };       
    }  
    
#endif  

    template< typename C, typename Enabler=void >
    struct range_iterator
    {
#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, == 1310)
  
        typedef NDNBOOST_RANGE_DEDUCED_TYPENAME  
               range_detail_vc7_1::range_iterator<C>::type type;  
           
#else  

    private:
        typedef typename remove_reference<C>::type param_t;

    public:
        typedef typename mpl::eval_if_c<
            is_const<param_t>::value,
            range_const_iterator<typename remove_const<param_t>::type>,
            range_mutable_iterator<param_t>
        >::type type;
        
#endif         
    };
    
} // namespace ndnboost

#endif
