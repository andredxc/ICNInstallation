//  Boost integer_fwd.hpp header file  ---------------------------------------//

//  (C) Copyright Dave Abrahams and Daryle Walker 2001. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

#ifndef NDNBOOST_INTEGER_FWD_HPP
#define NDNBOOST_INTEGER_FWD_HPP

#include <climits>  // for UCHAR_MAX, etc.
#include <cstddef>  // for std::size_t

#include <ndnboost/config.hpp>  // for NDNBOOST_NO_INTRINSIC_WCHAR_T
#include <ndnboost/limits.hpp>  // for std::numeric_limits
#include <ndnboost/cstdint.hpp>  // For intmax_t


namespace ndnboost
{

#ifdef NDNBOOST_NO_INTEGRAL_INT64_T
     typedef unsigned long static_log2_argument_type;
     typedef          int  static_log2_result_type;
     typedef long          static_min_max_signed_type;
     typedef unsigned long static_min_max_unsigned_type;
#else
     typedef ndnboost::uintmax_t static_min_max_unsigned_type;
     typedef ndnboost::intmax_t  static_min_max_signed_type;
     typedef ndnboost::uintmax_t static_log2_argument_type;
     typedef int              static_log2_result_type;
#endif

//  From <ndnboost/cstdint.hpp>  ------------------------------------------------//

// Only has typedefs or using statements, with #conditionals


//  From <ndnboost/integer_traits.hpp>  -----------------------------------------//

template < class T >
    class integer_traits;

template <  >
    class integer_traits< bool >;

template <  >
    class integer_traits< char >;

template <  >
    class integer_traits< signed char >;

template <  >
    class integer_traits< unsigned char >;

#ifndef NDNBOOST_NO_INTRINSIC_WCHAR_T
template <  >
    class integer_traits< wchar_t >;
#endif

template <  >
    class integer_traits< short >;

template <  >
    class integer_traits< unsigned short >;

template <  >
    class integer_traits< int >;

template <  >
    class integer_traits< unsigned int >;

template <  >
    class integer_traits< long >;

template <  >
    class integer_traits< unsigned long >;

#if !defined(NDNBOOST_NO_INTEGRAL_INT64_T) && !defined(NDNBOOST_NO_INT64_T) && defined(NDNBOOST_HAS_LONG_LONG)
template <  >
class integer_traits<  ::ndnboost::long_long_type>;

template <  >
class integer_traits<  ::ndnboost::ulong_long_type >;
#elif !defined(NDNBOOST_NO_INTEGRAL_INT64_T) && !defined(NDNBOOST_NO_INT64_T) && defined(NDNBOOST_HAS_MS_INT64)
template <  >
class integer_traits<__int64>;

template <  >
class integer_traits<unsigned __int64>;
#endif


//  From <ndnboost/integer.hpp>  ------------------------------------------------//

template < typename LeastInt >
    struct int_fast_t;

template< int Bits >
    struct int_t;

template< int Bits >
    struct uint_t;

#if !defined(NDNBOOST_NO_INTEGRAL_INT64_T) && defined(NDNBOOST_HAS_LONG_LONG)
    template< ndnboost::long_long_type MaxValue >   // maximum value to require support
#else
  template< long MaxValue >   // maximum value to require support
#endif
    struct int_max_value_t;

#if !defined(NDNBOOST_NO_INTEGRAL_INT64_T) && defined(NDNBOOST_HAS_LONG_LONG)
  template< ndnboost::long_long_type MinValue >   // minimum value to require support
#else
  template< long MinValue >   // minimum value to require support
#endif
    struct int_min_value_t;

#if !defined(NDNBOOST_NO_INTEGRAL_INT64_T) && defined(NDNBOOST_HAS_LONG_LONG)
  template< ndnboost::ulong_long_type MaxValue >   // maximum value to require support
#else
  template< unsigned long MaxValue >   // maximum value to require support
#endif
    struct uint_value_t;


//  From <ndnboost/integer/integer_mask.hpp>  -----------------------------------//

template < std::size_t Bit >
    struct high_bit_mask_t;

template < std::size_t Bits >
    struct low_bits_mask_t;

template <  >
    struct low_bits_mask_t< ::std::numeric_limits<unsigned char>::digits >;

//  From <ndnboost/integer/static_log2.hpp>  ------------------------------------//

template <static_log2_argument_type Value >
    struct static_log2;

template <> struct static_log2<0u>;


//  From <ndnboost/integer/static_min_max.hpp>  ---------------------------------//

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
    struct static_signed_min;

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
    struct static_signed_max;

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
    struct static_unsigned_min;

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
    struct static_unsigned_max;

}  // namespace ndnboost


#endif  // NDNBOOST_INTEGER_FWD_HPP
