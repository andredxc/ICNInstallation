// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef NDNBOOST_RANGE_DETAIL_COMMON_HPP
#define NDNBOOST_RANGE_DETAIL_COMMON_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <ndnboost/range/config.hpp>
#include <ndnboost/range/detail/sfinae.hpp>
#include <ndnboost/type_traits/is_void.hpp>
#include <ndnboost/type_traits/detail/ice_or.hpp>
#include <ndnboost/mpl/if.hpp>
#include <ndnboost/mpl/int.hpp>
#include <cstddef>

//////////////////////////////////////////////////////////////////////////////
// missing partial specialization  workaround.
//////////////////////////////////////////////////////////////////////////////

namespace ndnboost 
{
    namespace range_detail 
    {        
        // 1 = std containers
        // 2 = std::pair
        // 3 = const std::pair
        // 4 = array
        // 5 = const array
        // 6 = char array
        // 7 = wchar_t array
        // 8 = char*
        // 9 = const char*
        // 10 = whar_t*
        // 11 = const wchar_t*
        // 12 = string
        
        typedef mpl::int_<1>::type    std_container_;
        typedef mpl::int_<2>::type    std_pair_;
        typedef mpl::int_<3>::type    const_std_pair_;
        typedef mpl::int_<4>::type    array_;
        typedef mpl::int_<5>::type    const_array_;
        typedef mpl::int_<6>::type    char_array_;
        typedef mpl::int_<7>::type    wchar_t_array_;
        typedef mpl::int_<8>::type    char_ptr_;
        typedef mpl::int_<9>::type    const_char_ptr_;
        typedef mpl::int_<10>::type   wchar_t_ptr_;
        typedef mpl::int_<11>::type   const_wchar_t_ptr_;
        typedef mpl::int_<12>::type   string_;
        
        template< typename C >
        struct range_helper
        {
            static C* c;
            static C  ptr;

            NDNBOOST_STATIC_CONSTANT( bool, is_pair_                = sizeof( ndnboost::range_detail::is_pair_impl( c ) ) == sizeof( yes_type ) );
            NDNBOOST_STATIC_CONSTANT( bool, is_char_ptr_            = sizeof( ndnboost::range_detail::is_char_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            NDNBOOST_STATIC_CONSTANT( bool, is_const_char_ptr_      = sizeof( ndnboost::range_detail::is_const_char_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            NDNBOOST_STATIC_CONSTANT( bool, is_wchar_t_ptr_         = sizeof( ndnboost::range_detail::is_wchar_t_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            NDNBOOST_STATIC_CONSTANT( bool, is_const_wchar_t_ptr_   = sizeof( ndnboost::range_detail::is_const_wchar_t_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            NDNBOOST_STATIC_CONSTANT( bool, is_char_array_          = sizeof( ndnboost::range_detail::is_char_array_impl( ptr ) ) == sizeof( yes_type ) );
            NDNBOOST_STATIC_CONSTANT( bool, is_wchar_t_array_       = sizeof( ndnboost::range_detail::is_wchar_t_array_impl( ptr ) ) == sizeof( yes_type ) );
            NDNBOOST_STATIC_CONSTANT( bool, is_string_              = (ndnboost::type_traits::ice_or<is_const_char_ptr_, is_const_wchar_t_ptr_>::value ));
            NDNBOOST_STATIC_CONSTANT( bool, is_array_               = ndnboost::is_array<C>::value );
            
        };
        
        template< typename C >
        class range
        {
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_pair_,
                                                                  ndnboost::range_detail::std_pair_,
                                                                  void >::type pair_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_array_,
                                                                    ndnboost::range_detail::array_,
                                                                    pair_t >::type array_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_string_,
                                                                    ndnboost::range_detail::string_,
                                                                    array_t >::type string_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_const_char_ptr_,
                                                                    ndnboost::range_detail::const_char_ptr_,
                                                                    string_t >::type const_char_ptr_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_char_ptr_,
                                                                    ndnboost::range_detail::char_ptr_,
                                                                    const_char_ptr_t >::type char_ptr_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_const_wchar_t_ptr_,
                                                                    ndnboost::range_detail::const_wchar_t_ptr_,
                                                                    char_ptr_t >::type const_wchar_ptr_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_wchar_t_ptr_,
                                                                    ndnboost::range_detail::wchar_t_ptr_,
                                                                    const_wchar_ptr_t >::type wchar_ptr_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_wchar_t_array_,
                                                                    ndnboost::range_detail::wchar_t_array_,
                                                                    wchar_ptr_t >::type wchar_array_t;
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::range_detail::range_helper<C>::is_char_array_,
                                                                    ndnboost::range_detail::char_array_,
                                                                    wchar_array_t >::type char_array_t;
        public:
            typedef NDNBOOST_RANGE_DEDUCED_TYPENAME   ndnboost::mpl::if_c< ::ndnboost::is_void<char_array_t>::value,
                                                                    ndnboost::range_detail::std_container_,
                                                                    char_array_t >::type type;  
        }; // class 'range' 
    }
}
        
#endif

