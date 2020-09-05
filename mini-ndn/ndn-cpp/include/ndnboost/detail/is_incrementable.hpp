// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef IS_INCREMENTABLE_NDNBOOST_DWA200415_HPP
# define IS_INCREMENTABLE_NDNBOOST_DWA200415_HPP

# include <ndnboost/type_traits/detail/template_arity_spec.hpp>
# include <ndnboost/type_traits/remove_cv.hpp>
# include <ndnboost/mpl/aux_/lambda_support.hpp>
# include <ndnboost/mpl/bool.hpp>
# include <ndnboost/detail/workaround.hpp>

// Must be the last include
# include <ndnboost/type_traits/detail/bool_trait_def.hpp>

namespace ndnboost { namespace detail { 

// is_incrementable<T> metafunction
//
// Requires: Given x of type T&, if the expression ++x is well-formed
// it must have complete type; otherwise, it must neither be ambiguous
// nor violate access.

// This namespace ensures that ADL doesn't mess things up.
namespace is_incrementable_
{
  // a type returned from operator++ when no increment is found in the
  // type's own namespace
  struct tag {};
  
  // any soaks up implicit conversions and makes the following
  // operator++ less-preferred than any other such operator that
  // might be found via ADL.
  struct any { template <class T> any(T const&); };

  // This is a last-resort operator++ for when none other is found
# if NDNBOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0 && __GNUC_PATCHLEVEL__ == 2
  
}

namespace is_incrementable_2
{
  is_incrementable_::tag operator++(is_incrementable_::any const&);
  is_incrementable_::tag operator++(is_incrementable_::any const&,int);
}
using namespace is_incrementable_2;

namespace is_incrementable_
{
  
# else
  
  tag operator++(any const&);
  tag operator++(any const&,int);
  
# endif 

# if NDNBOOST_WORKAROUND(__MWERKS__, NDNBOOST_TESTED_AT(0x3202)) 
#  define NDNBOOST_comma(a,b) (a)
# else 
  // In case an operator++ is found that returns void, we'll use ++x,0
  tag operator,(tag,int);  
#  define NDNBOOST_comma(a,b) (a,b)
# endif 

# if defined(NDNBOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable:4913) // Warning about operator,
# endif 

  // two check overloads help us identify which operator++ was picked
  char (& check_(tag) )[2];
  
  template <class T>
  char check_(T const&);
  

  template <class T>
  struct impl
  {
      static typename ndnboost::remove_cv<T>::type& x;

      NDNBOOST_STATIC_CONSTANT(
          bool
        , value = sizeof(is_incrementable_::check_(NDNBOOST_comma(++x,0))) == 1
      );
  };

  template <class T>
  struct postfix_impl
  {
      static typename ndnboost::remove_cv<T>::type& x;

      NDNBOOST_STATIC_CONSTANT(
          bool
        , value = sizeof(is_incrementable_::check_(NDNBOOST_comma(x++,0))) == 1
      );
  };

# if defined(NDNBOOST_MSVC)
#  pragma warning(pop)
# endif 

}

# undef NDNBOOST_comma

template<typename T> 
struct is_incrementable 
NDNBOOST_TT_AUX_BOOL_C_BASE(::ndnboost::detail::is_incrementable_::impl<T>::value)
{ 
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(::ndnboost::detail::is_incrementable_::impl<T>::value)
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_incrementable,(T))
};

template<typename T> 
struct is_postfix_incrementable 
NDNBOOST_TT_AUX_BOOL_C_BASE(::ndnboost::detail::is_incrementable_::impl<T>::value)
{ 
    NDNBOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(::ndnboost::detail::is_incrementable_::postfix_impl<T>::value)
    NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_postfix_incrementable,(T))
};

} // namespace detail

NDNBOOST_TT_AUX_TEMPLATE_ARITY_SPEC(1, ::ndnboost::detail::is_incrementable)
NDNBOOST_TT_AUX_TEMPLATE_ARITY_SPEC(1, ::ndnboost::detail::is_postfix_incrementable)

} // namespace ndnboost

# include <ndnboost/type_traits/detail/bool_trait_undef.hpp>

#endif // IS_INCREMENTABLE_NDNBOOST_DWA200415_HPP
