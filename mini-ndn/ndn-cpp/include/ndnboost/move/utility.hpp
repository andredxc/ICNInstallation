//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef NDNBOOST_MOVE_MOVE_UTILITY_HPP
#define NDNBOOST_MOVE_MOVE_UTILITY_HPP

#include <ndnboost/move/detail/config_begin.hpp>
#include <ndnboost/move/core.hpp>
#include <ndnboost/move/detail/meta_utils.hpp>

#if defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

   namespace ndnboost {

   template<class T>
   struct enable_move_utility_emulation
   {
      static const bool value = true;
   };
    
   //////////////////////////////////////////////////////////////////////////////
   //
   //                            move()
   //
   //////////////////////////////////////////////////////////////////////////////

   template <class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && !has_move_emulation_enabled<T>::value, T&>::type
         move(T& x) NDNBOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value, rv<T>&>::type
         move(T& x) NDNBOOST_NOEXCEPT
   {
      return *static_cast<rv<T>* >(::ndnboost::move_detail::addressof(x));
   }

   template <class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value, rv<T>&>::type
         move(rv<T>& x) NDNBOOST_NOEXCEPT
   {
      return x;
   }

   //////////////////////////////////////////////////////////////////////////////
   //
   //                            forward()
   //
   //////////////////////////////////////////////////////////////////////////////

   template <class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && ::ndnboost::move_detail::is_rv<T>::value, T &>::type
         forward(const typename ::ndnboost::move_detail::identity<T>::type &x) NDNBOOST_NOEXCEPT
   {
      return const_cast<T&>(x);
   }

   template <class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && !::ndnboost::move_detail::is_rv<T>::value, const T &>::type
      forward(const typename ::ndnboost::move_detail::identity<T>::type &x) NDNBOOST_NOEXCEPT
   {
      return x;
   }

   }  //namespace ndnboost

#else    //#if defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

   #if defined(NDNBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)
      #include <utility>

      namespace ndnboost{

      using ::std::move;
      using ::std::forward;

      }  //namespace ndnboost

   #else //!NDNBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE

      #include <ndnboost/type_traits/remove_reference.hpp>

      namespace ndnboost {

      //! This trait's internal boolean `value` is false in compilers with rvalue references
      //! and true in compilers without rvalue references.
      //!
      //! A user can specialize this trait for a type T to false to SFINAE out `move` and `forward`
      //! so that the user can define a different move emulation for that type in namespace ndnboost
      //! (e.g. another Boost library for its types) and avoid any overload ambiguity.
      template<class T>
      struct enable_move_utility_emulation
      {
         static const bool value = false;
      };

      //////////////////////////////////////////////////////////////////////////////
      //
      //                                  move
      //
      //////////////////////////////////////////////////////////////////////////////

      #if defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)
         //! This function provides a way to convert a reference into a rvalue reference
         //! in compilers with rvalue references. For other compilers converts T & into
         //! <i>::ndnboost::rv<T> &</i> so that move emulation is activated.
         template <class T>
         rvalue_reference move(input_reference) noexcept;

      #elif defined(NDNBOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)

         //Old move approach, lvalues could bind to rvalue references
         template <class T>
         inline typename remove_reference<T>::type && move(T&& t) NDNBOOST_NOEXCEPT
         {  return t;   }

      #else //NDNBOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES

         template <class T>
         inline typename remove_reference<T>::type && move(T&& t) NDNBOOST_NOEXCEPT
         { return static_cast<typename remove_reference<T>::type &&>(t); }

      #endif   //NDNBOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES

      //////////////////////////////////////////////////////////////////////////////
      //
      //                                  forward
      //
      //////////////////////////////////////////////////////////////////////////////


      #if defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)
         //! This function provides limited form of forwarding that is usually enough for
         //! in-place construction and avoids the exponential overloading for
         //! achieve the limited forwarding in C++03.
         //!
         //! For compilers with rvalue references this function provides perfect forwarding.
         //!
         //! Otherwise:
         //! * If input_reference binds to const ::ndnboost::rv<T> & then it output_reference is
         //!   ::ndnboost::rv<T> &
         //!
         //! * Else, output_reference is equal to input_reference.
         template <class T> output_reference forward(input_reference) noexcept;
      #elif defined(NDNBOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)

         //Old move approach, lvalues could bind to rvalue references

         template <class T>
         inline T&& forward(typename ::ndnboost::move_detail::identity<T>::type&& t) NDNBOOST_NOEXCEPT
         {  return t;   }

      #else //Old move

         //Implementation #5 from N2951, thanks to Howard Hinnant

         template <class T, class U>
         inline T&& forward(U&& t
             , typename ::ndnboost::move_detail::enable_if_c<
               move_detail::is_lvalue_reference<T>::value ? move_detail::is_lvalue_reference<U>::value : true>::type * = 0/*
             , typename ::ndnboost::move_detail::enable_if_c<
               move_detail::is_convertible
                  <typename remove_reference<U>::type*, typename remove_reference<T>::type*>::value>::type * = 0*/) NDNBOOST_NOEXCEPT
         { return static_cast<T&&>(t);   }

      #endif   //NDNBOOST_MOVE_DOXYGEN_INVOKED

      }  //namespace ndnboost {

   #endif   //#if defined(NDNBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

#endif   //NDNBOOST_NO_CXX11_RVALUE_REFERENCES

#include <ndnboost/move/detail/config_end.hpp>

#endif //#ifndef NDNBOOST_MOVE_MOVE_UTILITY_HPP
