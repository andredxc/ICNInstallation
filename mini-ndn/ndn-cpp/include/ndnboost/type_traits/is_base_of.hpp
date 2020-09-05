
//  (C) Copyright Rani Sharoni 2003-2005.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.
 
#ifndef NDNBOOST_TT_IS_BASE_OF_HPP_INCLUDED
#define NDNBOOST_TT_IS_BASE_OF_HPP_INCLUDED

#include <ndnboost/type_traits/is_base_and_derived.hpp>
#include <ndnboost/type_traits/is_same.hpp>
#include <ndnboost/type_traits/is_class.hpp>
#include <ndnboost/type_traits/detail/ice_or.hpp>
#include <ndnboost/type_traits/detail/ice_and.hpp>

// should be the last #include
#include <ndnboost/type_traits/detail/bool_trait_def.hpp>

namespace ndnboost {

   namespace detail{
      template <class B, class D>
      struct is_base_of_imp
      {
          typedef typename remove_cv<B>::type ncvB;
          typedef typename remove_cv<D>::type ncvD;
          NDNBOOST_STATIC_CONSTANT(bool, value = (::ndnboost::type_traits::ice_or<      
            (::ndnboost::detail::is_base_and_derived_impl<ncvB,ncvD>::value),
            (::ndnboost::type_traits::ice_and< ::ndnboost::is_same<ncvB,ncvD>::value, ::ndnboost::is_class<ncvB>::value>::value)>::value));
      };
   }

NDNBOOST_TT_AUX_BOOL_TRAIT_DEF2(
      is_base_of
    , Base
    , Derived
    , (::ndnboost::detail::is_base_of_imp<Base, Derived>::value))

NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_of,Base&,Derived,false)
NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_of,Base,Derived&,false)
NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_of,Base&,Derived&,false)

} // namespace ndnboost

#include <ndnboost/type_traits/detail/bool_trait_undef.hpp>

#endif // NDNBOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED
