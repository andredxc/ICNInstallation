//  (C) Copyright John Maddock 2002 - 2003. 
//  (C) Copyright Jens Maurer 2002 - 2003. 
//  (C) Copyright Beman Dawes 2002 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Comeau STL:

#if !defined(__LIBCOMO__)
#  include <ndnboost/config/no_tr1/utility.hpp>
#  if !defined(__LIBCOMO__)
#      error "This is not the Comeau STL!"
#  endif
#endif

//
// std::streambuf<wchar_t> is non-standard
// NOTE: versions of libcomo prior to beta28 have octal version numbering,
// e.g. version 25 is 21 (dec)
#if __LIBCOMO_VERSION__ <= 22
#  define NDNBOOST_NO_STD_WSTREAMBUF
#endif

#if (__LIBCOMO_VERSION__ <= 31) && defined(_WIN32)
#define NDNBOOST_NO_SWPRINTF
#endif

#if __LIBCOMO_VERSION__ >= 31
#  define NDNBOOST_HAS_HASH
#  define NDNBOOST_HAS_SLIST
#endif

//  C++0x headers not yet implemented
//
#  define NDNBOOST_NO_CXX11_HDR_ARRAY
#  define NDNBOOST_NO_CXX11_HDR_CHRONO
#  define NDNBOOST_NO_CXX11_HDR_CODECVT
#  define NDNBOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define NDNBOOST_NO_CXX11_HDR_FORWARD_LIST
#  define NDNBOOST_NO_CXX11_HDR_FUTURE
#  define NDNBOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define NDNBOOST_NO_CXX11_HDR_MUTEX
#  define NDNBOOST_NO_CXX11_HDR_RANDOM
#  define NDNBOOST_NO_CXX11_HDR_RATIO
#  define NDNBOOST_NO_CXX11_HDR_REGEX
#  define NDNBOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define NDNBOOST_NO_CXX11_HDR_THREAD
#  define NDNBOOST_NO_CXX11_HDR_TUPLE
#  define NDNBOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define NDNBOOST_NO_CXX11_HDR_TYPEINDEX
#  define NDNBOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define NDNBOOST_NO_CXX11_HDR_UNORDERED_SET
#  define NDNBOOST_NO_CXX11_NUMERIC_LIMITS
#  define NDNBOOST_NO_CXX11_ALLOCATOR
#  define NDNBOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define NDNBOOST_NO_CXX11_SMART_PTR
#  define NDNBOOST_NO_CXX11_HDR_FUNCTIONAL
#  define NDNBOOST_NO_CXX11_HDR_ATOMIC
#  define NDNBOOST_NO_CXX11_STD_ALIGN
#  define NDNBOOST_NO_CXX11_ADDRESSOF

//
// Intrinsic type_traits support.
// The SGI STL has it's own __type_traits class, which
// has intrinsic compiler support with SGI's compilers.
// Whatever map SGI style type traits to boost equivalents:
//
#define NDNBOOST_HAS_SGI_TYPE_TRAITS

#define NDNBOOST_STDLIB "Comeau standard library " NDNBOOST_STRINGIZE(__LIBCOMO_VERSION__)


