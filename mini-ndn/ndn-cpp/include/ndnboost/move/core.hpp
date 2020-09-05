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

//! \file core.hpp
//! This header implements macros to define movable classes and
//! move-aware functions

#ifndef NDNBOOST_MOVE_CORE_HPP
#define NDNBOOST_MOVE_CORE_HPP

#include <ndnboost/move/detail/config_begin.hpp>

//boost_move_no_copy_constructor_or_assign typedef
//used to detect noncopyable types for other Boost libraries.
#ifdef NDNBOOST_NO_CXX11_DELETED_FUNCTIONS
   #define NDNBOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE) \
      private:\
      TYPE(TYPE &);\
      TYPE& operator=(TYPE &);\
      public:\
      typedef int boost_move_no_copy_constructor_or_assign; \
      private:\
   //
#else
   #define NDNBOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE) \
      public:\
      TYPE(TYPE const &) = delete;\
      TYPE& operator=(TYPE const &) = delete;\
      public:\
      typedef int boost_move_no_copy_constructor_or_assign; \
      private:\
   //
#endif   //NDNBOOST_NO_CXX11_DELETED_FUNCTIONS

#if defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

   #include <ndnboost/move/detail/meta_utils.hpp>

   //Move emulation rv breaks standard aliasing rules so add workarounds for some compilers
   #if defined(__GNUC__) && (__GNUC__ >= 4)
      #define NDNBOOST_MOVE_ATTRIBUTE_MAY_ALIAS __attribute__((__may_alias__))
   #else
      #define NDNBOOST_MOVE_ATTRIBUTE_MAY_ALIAS
   #endif

   namespace ndnboost {

   //////////////////////////////////////////////////////////////////////////////
   //
   //                            struct rv
   //
   //////////////////////////////////////////////////////////////////////////////
   template <class T>
   class rv
      : public ::ndnboost::move_detail::if_c
         < ::ndnboost::move_detail::is_class_or_union<T>::value
         , T
         , ::ndnboost::move_detail::empty
         >::type
   {
      rv();
      ~rv();
      rv(rv const&);
      void operator=(rv const&);
   } NDNBOOST_MOVE_ATTRIBUTE_MAY_ALIAS;


   //////////////////////////////////////////////////////////////////////////////
   //
   //                            move_detail::is_rv
   //
   //////////////////////////////////////////////////////////////////////////////

   namespace move_detail {

   template <class T>
   struct is_rv
      : ::ndnboost::move_detail::integral_constant<bool, false>
   {};

   template <class T>
   struct is_rv< rv<T> >
      : ::ndnboost::move_detail::integral_constant<bool, true>
   {};

   template <class T>
   struct is_rv< const rv<T> >
      : ::ndnboost::move_detail::integral_constant<bool, true>
   {};

   }  //namespace move_detail {

   //////////////////////////////////////////////////////////////////////////////
   //
   //                               has_move_emulation_enabled
   //
   //////////////////////////////////////////////////////////////////////////////
   template<class T>
   struct has_move_emulation_enabled
      : ::ndnboost::move_detail::is_convertible< T, ::ndnboost::rv<T>& >
   {};

   template<class T>
   struct has_move_emulation_enabled<T&>
      : ::ndnboost::move_detail::integral_constant<bool, false>
   {};

   template<class T>
   struct has_move_emulation_enabled< ::ndnboost::rv<T> >
      : ::ndnboost::move_detail::integral_constant<bool, false>
   {};

   }  //namespace ndnboost {

   #define NDNBOOST_RV_REF(TYPE)\
      ::ndnboost::rv< TYPE >& \
   //

   #define NDNBOOST_RV_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      ::ndnboost::rv< TYPE<ARG1, ARG2> >& \
   //

   #define NDNBOOST_RV_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      ::ndnboost::rv< TYPE<ARG1, ARG2, ARG3> >& \
   //

   #define NDNBOOST_RV_REF_BEG\
      ::ndnboost::rv<   \
   //

   #define NDNBOOST_RV_REF_END\
      >& \
   //

   #define NDNBOOST_FWD_REF(TYPE)\
      const TYPE & \
   //

   #define NDNBOOST_COPY_ASSIGN_REF(TYPE)\
      const ::ndnboost::rv< TYPE >& \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_BEG \
      const ::ndnboost::rv<  \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_END \
      >& \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      const ::ndnboost::rv< TYPE<ARG1, ARG2> >& \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      const ::ndnboost::rv< TYPE<ARG1, ARG2, ARG3> >& \
   //

   #define NDNBOOST_CATCH_CONST_RLVALUE(TYPE)\
      const ::ndnboost::rv< TYPE >& \
   //

   namespace ndnboost {
   namespace move_detail {

   template <class Ret, class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      <  ::ndnboost::move_detail::is_lvalue_reference<Ret>::value ||
        !::ndnboost::has_move_emulation_enabled<T>::value
      , T&>::type
         move_return(T& x) NDNBOOST_NOEXCEPT
   {
      return x;
   }

   template <class Ret, class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      < !::ndnboost::move_detail::is_lvalue_reference<Ret>::value &&
         ::ndnboost::has_move_emulation_enabled<T>::value
      , ::ndnboost::rv<T>&>::type
         move_return(T& x) NDNBOOST_NOEXCEPT
   {
      return *static_cast< ::ndnboost::rv<T>* >(::ndnboost::move_detail::addressof(x));
   }

   template <class Ret, class T>
   inline typename ::ndnboost::move_detail::enable_if_c
      < !::ndnboost::move_detail::is_lvalue_reference<Ret>::value &&
         ::ndnboost::has_move_emulation_enabled<T>::value
      , ::ndnboost::rv<T>&>::type
         move_return(::ndnboost::rv<T>& x) NDNBOOST_NOEXCEPT
   {
      return x;
   }

   }  //namespace move_detail {
   }  //namespace ndnboost {

   #define NDNBOOST_MOVE_RET(RET_TYPE, REF)\
      ndnboost::move_detail::move_return< RET_TYPE >(REF)
   //

   //////////////////////////////////////////////////////////////////////////////
   //
   //                         NDNBOOST_MOVABLE_BUT_NOT_COPYABLE
   //
   //////////////////////////////////////////////////////////////////////////////
   #define NDNBOOST_MOVABLE_BUT_NOT_COPYABLE(TYPE)\
      NDNBOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE)\
      public:\
      operator ::ndnboost::rv<TYPE>&() \
      {  return *static_cast< ::ndnboost::rv<TYPE>* >(this);  }\
      operator const ::ndnboost::rv<TYPE>&() const \
      {  return *static_cast<const ::ndnboost::rv<TYPE>* >(this);  }\
      private:\
   //

   //////////////////////////////////////////////////////////////////////////////
   //
   //                         NDNBOOST_COPYABLE_AND_MOVABLE
   //
   //////////////////////////////////////////////////////////////////////////////

   #define NDNBOOST_COPYABLE_AND_MOVABLE(TYPE)\
      public:\
      TYPE& operator=(TYPE &t)\
      {  this->operator=(static_cast<const ::ndnboost::rv<TYPE> &>(const_cast<const TYPE &>(t))); return *this;}\
      public:\
      operator ::ndnboost::rv<TYPE>&() \
      {  return *static_cast< ::ndnboost::rv<TYPE>* >(this);  }\
      operator const ::ndnboost::rv<TYPE>&() const \
      {  return *static_cast<const ::ndnboost::rv<TYPE>* >(this);  }\
      private:\
   //

   #define NDNBOOST_COPYABLE_AND_MOVABLE_ALT(TYPE)\
      public:\
      operator ::ndnboost::rv<TYPE>&() \
      {  return *static_cast< ::ndnboost::rv<TYPE>* >(this);  }\
      operator const ::ndnboost::rv<TYPE>&() const \
      {  return *static_cast<const ::ndnboost::rv<TYPE>* >(this);  }\
      private:\
   //

#else    //NDNBOOST_NO_CXX11_RVALUE_REFERENCES

   //Compiler workaround detection
   #if !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)
      #if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 5) && !defined(__clang__)
         //Pre-standard rvalue binding rules
         #define NDNBOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES
      #elif defined(_MSC_VER) && (_MSC_VER == 1600)
         //Standard rvalue binding rules but with some bugs
         #define NDNBOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG
         #define NDNBOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG
         //Use standard library for MSVC to avoid namespace issues as
         //some move calls in the STL are not fully qualified.
         //#define NDNBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      #elif defined(_MSC_VER) && (_MSC_VER == 1700)
         #define NDNBOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG
      #endif
   #endif

   //! This macro marks a type as movable but not copyable, disabling copy construction
   //! and assignment. The user will need to write a move constructor/assignment as explained
   //! in the documentation to fully write a movable but not copyable class.
   #define NDNBOOST_MOVABLE_BUT_NOT_COPYABLE(TYPE)\
      NDNBOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE)\
      public:\
      typedef int boost_move_emulation_t;\
   //

   //! This macro marks a type as copyable and movable.
   //! The user will need to write a move constructor/assignment and a copy assignment
   //! as explained in the documentation to fully write a copyable and movable class.
   #define NDNBOOST_COPYABLE_AND_MOVABLE(TYPE)\
   //

   #if !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)
   #define NDNBOOST_COPYABLE_AND_MOVABLE_ALT(TYPE)\
   //
   #endif   //#if !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

   namespace ndnboost {

   //!This trait yields to a compile-time true boolean if T was marked as
   //!NDNBOOST_MOVABLE_BUT_NOT_COPYABLE or NDNBOOST_COPYABLE_AND_MOVABLE and
   //!rvalue references are not available on the platform. False otherwise.
   template<class T>
   struct has_move_emulation_enabled
   {
      static const bool value = false;
   };

   }  //namespace ndnboost{

   //!This macro is used to achieve portable syntax in move
   //!constructors and assignments for classes marked as
   //!NDNBOOST_COPYABLE_AND_MOVABLE or NDNBOOST_MOVABLE_BUT_NOT_COPYABLE
   #define NDNBOOST_RV_REF(TYPE)\
      TYPE && \
   //

   //!This macro is used to achieve portable syntax in move
   //!constructors and assignments for template classes marked as
   //!NDNBOOST_COPYABLE_AND_MOVABLE or NDNBOOST_MOVABLE_BUT_NOT_COPYABLE.
   //!As macros have problems with comma-separated template arguments,
   //!the template argument must be preceded with NDNBOOST_RV_REF_BEG
   //!and ended with NDNBOOST_RV_REF_END
   #define NDNBOOST_RV_REF_BEG\
         \
   //

   //!This macro is used to achieve portable syntax in move
   //!constructors and assignments for template classes marked as
   //!NDNBOOST_COPYABLE_AND_MOVABLE or NDNBOOST_MOVABLE_BUT_NOT_COPYABLE.
   //!As macros have problems with comma-separated template arguments,
   //!the template argument must be preceded with NDNBOOST_RV_REF_BEG
   //!and ended with NDNBOOST_RV_REF_END
   #define NDNBOOST_RV_REF_END\
      && \

   //!This macro is used to achieve portable syntax in copy
   //!assignment for classes marked as NDNBOOST_COPYABLE_AND_MOVABLE.
   #define NDNBOOST_COPY_ASSIGN_REF(TYPE)\
      const TYPE & \
   //

   //! This macro is used to implement portable perfect forwarding
   //! as explained in the documentation.
   #define NDNBOOST_FWD_REF(TYPE)\
      TYPE && \
   //

   #if !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

   #define NDNBOOST_RV_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      TYPE<ARG1, ARG2> && \
   //

   #define NDNBOOST_RV_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      TYPE<ARG1, ARG2, ARG3> && \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_BEG \
      const \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_END \
      & \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      const TYPE<ARG1, ARG2> & \
   //

   #define NDNBOOST_COPY_ASSIGN_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      const TYPE<ARG1, ARG2, ARG3>& \
   //

   #define NDNBOOST_CATCH_CONST_RLVALUE(TYPE)\
      const TYPE & \
   //


   #endif   //#if !defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

   #if !defined(NDNBOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG) || defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

      //!This macro is used to achieve portable move return semantics.
      //!The Standard allows implicit move returns when the object to be returned 
      //!is designated by an lvalue and:
      //!   - The criteria for elision of a copy operation are met OR
      //!   - The criteria would be met save for the fact that the source object is a function parameter
      //!
      //!For C++11 conforming compilers this macros only yields to REF:
      //! <code>return NDNBOOST_MOVE_RET(RET_TYPE, REF);</code> -> <code>return REF;</code>
      //!
      //!For compilers without rvalue references
      //!this macro does an explicit move if the move emulation is activated
      //!and the return type (RET_TYPE) is not a reference.
      //!
      //!For non-conforming compilers with rvalue references like Visual 2010 & 2012,
      //!an explicit move is performed if RET_TYPE is not a reference.
      //!
      //! <b>Caution</b>: When using this macro in a non-conforming or C++03
      //!compilers, a move will be performed even if the C++11 standard does not allow it
      //!(e.g. returning a static variable). The user is responsible for using this macro
      //!only used to return local objects that met C++11 criteria.
      #define NDNBOOST_MOVE_RET(RET_TYPE, REF)\
         (REF)
      //

   #else //!defined(NDNBOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG) || defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

      #include <ndnboost/move/detail/meta_utils.hpp>

      namespace ndnboost {
      namespace move_detail {

      template <class Ret, class T>
      inline typename ::ndnboost::move_detail::enable_if_c
         <  ::ndnboost::move_detail::is_lvalue_reference<Ret>::value
         , T&>::type
            move_return(T& x) NDNBOOST_NOEXCEPT
      {
         return x;
      }

      template <class Ret, class T>
      inline typename ::ndnboost::move_detail::enable_if_c
         < !::ndnboost::move_detail::is_lvalue_reference<Ret>::value
         , Ret && >::type
            move_return(T&& t) NDNBOOST_NOEXCEPT
      {
         return static_cast< Ret&& >(t);
      }

      }  //namespace move_detail {
      }  //namespace ndnboost {

      #define NDNBOOST_MOVE_RET(RET_TYPE, REF)\
         ndnboost::move_detail::move_return< RET_TYPE >(REF)
      //

   #endif   //!defined(NDNBOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG) || defined(NDNBOOST_MOVE_DOXYGEN_INVOKED)

#endif   //NDNBOOST_NO_CXX11_RVALUE_REFERENCES

#include <ndnboost/move/detail/config_end.hpp>

#endif //#ifndef NDNBOOST_MOVE_CORE_HPP
