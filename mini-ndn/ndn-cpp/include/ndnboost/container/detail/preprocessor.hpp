//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef NDNBOOST_CONTAINER_DETAIL_PREPROCESSOR_HPP
#define NDNBOOST_CONTAINER_DETAIL_PREPROCESSOR_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

#include <ndnboost/container/detail/config_begin.hpp>
#include <ndnboost/container/detail/workaround.hpp>
#include <ndnboost/move/utility.hpp>

#ifdef NDNBOOST_CONTAINER_PERFECT_FORWARDING
//#error "This file is not needed when perfect forwarding is available"
#endif   //NDNBOOST_CONTAINER_PERFECT_FORWARDING

#include <ndnboost/preprocessor/iteration/local.hpp>
#include <ndnboost/preprocessor/punctuation/paren_if.hpp>
#include <ndnboost/preprocessor/punctuation/comma_if.hpp>
#include <ndnboost/preprocessor/control/expr_if.hpp>
#include <ndnboost/preprocessor/cat.hpp>
#include <ndnboost/preprocessor/repetition/enum.hpp>
#include <ndnboost/preprocessor/repetition/enum_params.hpp>
#include <ndnboost/preprocessor/repetition/enum_trailing_params.hpp>
#include <ndnboost/preprocessor/repetition/enum_trailing.hpp>
#include <ndnboost/preprocessor/repetition/enum_shifted_params.hpp>
#include <ndnboost/preprocessor/repetition/enum_shifted.hpp>
#include <ndnboost/preprocessor/repetition/repeat.hpp>
#include <ndnboost/preprocessor/logical/not.hpp>
#include <ndnboost/preprocessor/arithmetic/sub.hpp>
#include <ndnboost/preprocessor/arithmetic/add.hpp>
#include <ndnboost/preprocessor/iteration/iterate.hpp>
#include <ndnboost/move/utility.hpp>

#define NDNBOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS 10

//Note:
//We define template parameters as const references to
//be able to bind temporaries. After that we will un-const them.
//This cast is ugly but it is necessary until "perfect forwarding"
//is achieved in C++0x. Meanwhile, if we want to be able to
//bind rvalues with non-const references, we have to be ugly
#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES
   #define NDNBOOST_CONTAINER_PP_PARAM_LIST(z, n, data) \
   NDNBOOST_PP_CAT(P, n) && NDNBOOST_PP_CAT(p, n) \
   //!
#else
   #define NDNBOOST_CONTAINER_PP_PARAM_LIST(z, n, data) \
   const NDNBOOST_PP_CAT(P, n) & NDNBOOST_PP_CAT(p, n) \
   //!
#endif   //#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES

#define NDNBOOST_CONTAINER_PP_CONST_REF_PARAM_LIST_Q(z, n, Data) \
const NDNBOOST_PP_CAT(Q, n) & NDNBOOST_PP_CAT(q, n) \
//!

#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES
   #define NDNBOOST_CONTAINER_PP_PARAM(U, u) \
   U && u \
   //!
#else
   #define NDNBOOST_CONTAINER_PP_PARAM(U, u) \
   const U & u \
   //!
#endif   //#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES

#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES

   #define NDNBOOST_CONTAINER_PP_PARAM_INIT(z, n, data) \
   NDNBOOST_PP_CAT(m_p, n) (::ndnboost::forward< NDNBOOST_PP_CAT(P, n) >( NDNBOOST_PP_CAT(p, n) ))           \
   //!

#else //NDNBOOST_NO_CXX11_RVALUE_REFERENCES

   #define NDNBOOST_CONTAINER_PP_PARAM_INIT(z, n, data) \
   NDNBOOST_PP_CAT(m_p, n) (const_cast<NDNBOOST_PP_CAT(P, n) &>(NDNBOOST_PP_CAT(p, n))) \
   //!
#endif   //#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES

#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES

   #if defined(NDNBOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

      namespace ndnboost {
      namespace container {
      namespace container_detail {
         template<class T>
         struct ref_holder;

         template<class T>
         struct ref_holder<T &>
         {
            explicit ref_holder(T &t)
               : t_(t)
            {}
            T &t_;
            T & get() {  return t_;   }
         };

         template<class T>
         struct ref_holder<const T>
         {
            explicit ref_holder(const T &t)
               : t_(t)
            {}
            const T &t_;
            const T & get() {  return t_;   }
         };

         template<class T>
         struct ref_holder<const T &&>
         {
            explicit ref_holder(const T &t)
               : t_(t)
            {}
            const T &t_;
            const T & get() {  return t_;   }
         };

         template<class T>
         struct ref_holder
         {
            explicit ref_holder(T &&t)
               : t_(t)
            {}
            T &t_;
            T && get() {  return ::ndnboost::move(t_);   }
         };

         template<class T>
         struct ref_holder<T &&>
         {
            explicit ref_holder(T &&t)
               : t_(t)
            {}
            T &t_;
            T && get()  { return ::ndnboost::move(t_); }
         };

      }  //namespace container_detail {
      }  //namespace container {
      }  //namespace ndnboost {

      #define NDNBOOST_CONTAINER_PP_PARAM_DEFINE(z, n, data)  \
         ::ndnboost::container::container_detail::ref_holder<NDNBOOST_PP_CAT(P, n)> NDNBOOST_PP_CAT(m_p, n);  \
      //!

   #else //NDNBOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG

      #define NDNBOOST_CONTAINER_PP_PARAM_DEFINE(z, n, data)  \
      NDNBOOST_PP_CAT(P, n) && NDNBOOST_PP_CAT(m_p, n);            \
      //!

   #endif //defined(NDNBOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

#else //NDNBOOST_NO_CXX11_RVALUE_REFERENCES

   #define NDNBOOST_CONTAINER_PP_PARAM_DEFINE(z, n, data)  \
   NDNBOOST_PP_CAT(P, n) & NDNBOOST_PP_CAT(m_p, n);             \
   //!
#endif   //#ifndef NDNBOOST_NO_CXX11_RVALUE_REFERENCES

#if !defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES) && defined(NDNBOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

   #define NDNBOOST_CONTAINER_PP_MEMBER_FORWARD(z, n, data) NDNBOOST_PP_CAT(this->m_p, n).get() \
   //!

#else //!defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES) && defined(NDNBOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

   #define NDNBOOST_CONTAINER_PP_MEMBER_FORWARD(z, n, data) \
   ::ndnboost::forward< NDNBOOST_PP_CAT(P, n) >( NDNBOOST_PP_CAT(this->m_p, n) ) \
   //!

#endif   //!defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES) && defined(NDNBOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG)

#define NDNBOOST_CONTAINER_PP_PARAM_INC(z, n, data)   \
  NDNBOOST_PP_CAT(++this->m_p, n)                     \
//!

#define NDNBOOST_CONTAINER_PP_IDENTITY(z, n, data) data


#define NDNBOOST_CONTAINER_PP_PARAM_FORWARD(z, n, data) \
::ndnboost::forward< NDNBOOST_PP_CAT(P, n) >( NDNBOOST_PP_CAT(p, n) ) \
//!

#define NDNBOOST_CONTAINER_PP_DECLVAL(z, n, data) \
::ndnboost::move_detail::declval< NDNBOOST_PP_CAT(P, n) >() \
//!

#define NDNBOOST_CONTAINER_PP_MEMBER_IT_FORWARD(z, n, data) \
NDNBOOST_PP_CAT(*this->m_p, n) \
//!

#define NDNBOOST_CONTAINER_PP_TEMPLATE_PARAM_VOID_DEFAULT(z, n, data)   \
  NDNBOOST_PP_CAT(class P, n) = void                                    \
//!

#define NDNBOOST_CONTAINER_PP_TEMPLATE_PARAM_WITH_DEFAULT(z, n, default_type) \
  NDNBOOST_PP_CAT(class P, n) = default_type                                  \
//!

#define NDNBOOST_CONTAINER_PP_STATIC_PARAM_REF_DECLARE(z, n, data) \
   static NDNBOOST_PP_CAT(P, n) & NDNBOOST_PP_CAT(p, n); \
//!

#define NDNBOOST_CONTAINER_PP_PARAM_PASS(z, n, data) \
   NDNBOOST_PP_CAT(p, n) \
//!

#define NDNBOOST_CONTAINER_PP_FWD_TYPE(z, n, data) \
   typename ::ndnboost::move_detail::forward_type< NDNBOOST_PP_CAT(P, n) >::type \
//!

#include <ndnboost/container/detail/config_end.hpp>

//#else

//#ifdef NDNBOOST_CONTAINER_PERFECT_FORWARDING
//#error "This file is not needed when perfect forwarding is available"
//#endif   //NDNBOOST_CONTAINER_PERFECT_FORWARDING

#endif //#ifndef NDNBOOST_CONTAINER_DETAIL_PREPROCESSOR_HPP
