//  common_type.hpp  ---------------------------------------------------------//

//  Copyright 2008 Howard Hinnant
//  Copyright 2008 Beman Dawes

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef NDNBOOST_TYPE_TRAITS_COMMON_TYPE_HPP
#define NDNBOOST_TYPE_TRAITS_COMMON_TYPE_HPP

#include <ndnboost/config.hpp>

#if defined(__SUNPRO_CC) && !defined(NDNBOOST_COMMON_TYPE_DONT_USE_TYPEOF)
#  define NDNBOOST_COMMON_TYPE_DONT_USE_TYPEOF
#endif
#if defined(__IBMCPP__) && !defined(NDNBOOST_COMMON_TYPE_DONT_USE_TYPEOF)
#  define NDNBOOST_COMMON_TYPE_DONT_USE_TYPEOF
#endif

//----------------------------------------------------------------------------//
#if defined(NDNBOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(NDNBOOST_COMMON_TYPE_ARITY)
#define NDNBOOST_COMMON_TYPE_ARITY 3
#endif

//----------------------------------------------------------------------------//
#if defined(NDNBOOST_NO_CXX11_DECLTYPE) && !defined(NDNBOOST_COMMON_TYPE_DONT_USE_TYPEOF)
#include <ndnboost/typeof/typeof.hpp>   // boost wonders never cease!
#endif

//----------------------------------------------------------------------------//
#ifndef NDNBOOST_NO_CXX11_STATIC_ASSERT
#define NDNBOOST_COMMON_TYPE_STATIC_ASSERT(CND, MSG, TYPES) static_assert(CND,MSG)
#elif defined(NDNBOOST_COMMON_TYPE_USES_MPL_ASSERT)
#include <ndnboost/mpl/assert.hpp>
#include <ndnboost/mpl/bool.hpp>
#define NDNBOOST_COMMON_TYPE_STATIC_ASSERT(CND, MSG, TYPES)                                 \
    NDNBOOST_MPL_ASSERT_MSG(ndnboost::mpl::bool_< (CND) >::type::value, MSG, TYPES)
#else
#include <ndnboost/static_assert.hpp>
#define NDNBOOST_COMMON_TYPE_STATIC_ASSERT(CND, MSG, TYPES) NDNBOOST_STATIC_ASSERT(CND)
#endif

#if !defined(NDNBOOST_NO_CXX11_STATIC_ASSERT) || !defined(NDNBOOST_COMMON_TYPE_USES_MPL_ASSERT)
#define NDNBOOST_COMMON_TYPE_MUST_BE_A_COMPLE_TYPE "must be complete type"
#endif

#if defined(NDNBOOST_NO_CXX11_DECLTYPE) && defined(NDNBOOST_COMMON_TYPE_DONT_USE_TYPEOF)
#include <ndnboost/type_traits/detail/common_type_imp.hpp>
#include <ndnboost/type_traits/remove_cv.hpp>
#endif
#include <ndnboost/mpl/if.hpp>
#include <ndnboost/utility/declval.hpp>
#include <ndnboost/type_traits/add_rvalue_reference.hpp>

//----------------------------------------------------------------------------//
//                                                                            //
//                           C++03 implementation of                          //
//             20.9.7.6 Other transformations [meta.trans.other]              //
//                          Written by Howard Hinnant                         //
//      Adapted for Boost by Beman Dawes, Vicente Botet and  Jeffrey Hellrung //
//                                                                            //
//----------------------------------------------------------------------------//

namespace ndnboost {

// prototype
#if !defined(NDNBOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<typename... T>
    struct common_type;
#else // or no specialization
    template <class T, class U = void, class V = void>
    struct common_type
    {
    public:
        typedef typename common_type<typename common_type<T, U>::type, V>::type type;
    };
#endif


// 1 arg
    template<typename T>
#if !defined(NDNBOOST_NO_CXX11_VARIADIC_TEMPLATES)
    struct common_type<T>
#else
    struct common_type<T, void, void>

#endif
    {
        NDNBOOST_COMMON_TYPE_STATIC_ASSERT(sizeof(T) > 0, NDNBOOST_COMMON_TYPE_MUST_BE_A_COMPLE_TYPE, (T));
    public:
        typedef T type;
    };

// 2 args
namespace type_traits_detail {

    template <class T, class U>
    struct common_type_2
    {
    private:
        NDNBOOST_COMMON_TYPE_STATIC_ASSERT(sizeof(T) > 0, NDNBOOST_COMMON_TYPE_MUST_BE_A_COMPLE_TYPE, (T));
        NDNBOOST_COMMON_TYPE_STATIC_ASSERT(sizeof(U) > 0, NDNBOOST_COMMON_TYPE_MUST_BE_A_COMPLE_TYPE, (U));
        static bool declval_bool();  // workaround gcc bug; not required by std
        static typename add_rvalue_reference<T>::type declval_T();  // workaround gcc bug; not required by std
        static typename add_rvalue_reference<U>::type declval_U();  // workaround gcc bug; not required by std
        static typename add_rvalue_reference<bool>::type declval_b();  

#if !defined(NDNBOOST_NO_CXX11_DECLTYPE)
    public:
        typedef decltype(declval<bool>() ? declval<T>() : declval<U>()) type;
#elif defined(NDNBOOST_COMMON_TYPE_DONT_USE_TYPEOF)
    public:
    typedef typename detail_type_traits_common_type::common_type_impl<
          typename remove_cv<T>::type,
          typename remove_cv<U>::type
      >::type type;
#else
    public:
        typedef NDNBOOST_TYPEOF_TPL(declval_b() ? declval_T() : declval_U()) type;
#endif

#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 3
    public:
        void public_dummy_function_just_to_silence_warning();
#endif
    };

    template <class T>
    struct common_type_2<T, T>
    {
        typedef T type;
    };
    }

#if !defined(NDNBOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class T, class U>
    struct common_type<T, U>
#else
    template <class T, class U>
    struct common_type<T, U, void>
#endif
    : public type_traits_detail::common_type_2<T,U>
    { };


// 3 or more args
#if !defined(NDNBOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<typename T, typename U, typename... V>
    struct common_type<T, U, V...> {
    public:
        typedef typename common_type<typename common_type<T, U>::type, V...>::type type;
    };
#endif
}  // namespace ndnboost

#endif  // NDNBOOST_TYPE_TRAITS_COMMON_TYPE_HPP
