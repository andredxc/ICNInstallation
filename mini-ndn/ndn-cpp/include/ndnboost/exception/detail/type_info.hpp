//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NDNBOOST_UUID_C3E1741C754311DDB2834CCA55D89593
#define NDNBOOST_UUID_C3E1741C754311DDB2834CCA55D89593
#if (__GNUC__*100+__GNUC_MINOR__>301) && !defined(NDNBOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma GCC system_header
#endif
#if defined(_MSC_VER) && !defined(NDNBOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(push,1)
#endif

#include <ndnboost/detail/sp_typeinfo.hpp>
#include <ndnboost/current_function.hpp>
#include <ndnboost/config.hpp>
//#ifndef NDNBOOST_NO_TYPEID
//#include <ndnboost/units/detail/utility.hpp>
//#endif
#include <string>

namespace
ndnboost
    {
    template <class T>
    inline
    std::string
    tag_type_name()
        {
#ifdef NDNBOOST_NO_TYPEID
        return NDNBOOST_CURRENT_FUNCTION;
#else
        return /*units::detail::demangle*/(typeid(T*).name());
#endif
        }

    template <class T>
    inline
    std::string
    type_name()
        {
#ifdef NDNBOOST_NO_TYPEID
        return NDNBOOST_CURRENT_FUNCTION;
#else
        return /*units::detail::demangle*/(typeid(T).name());
#endif
        }

    namespace
    exception_detail
        {
        struct
        type_info_
            {
            detail::sp_typeinfo const * type_;

            explicit
            type_info_( detail::sp_typeinfo const & type ):
                type_(&type)
                {
                }

            friend
            bool
            operator<( type_info_ const & a, type_info_ const & b )
                {
                return 0!=(a.type_->before(*b.type_));
                }
            };
        }
    }

#define NDNBOOST_EXCEPTION_STATIC_TYPEID(T) ::ndnboost::exception_detail::type_info_(NDNBOOST_SP_TYPEID(T))

#ifndef NDNBOOST_NO_RTTI
#define NDNBOOST_EXCEPTION_DYNAMIC_TYPEID(x) ::ndnboost::exception_detail::type_info_(typeid(x))
#endif

#if defined(_MSC_VER) && !defined(NDNBOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif
