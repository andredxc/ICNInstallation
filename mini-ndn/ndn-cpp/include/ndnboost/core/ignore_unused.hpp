// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NDNBOOST_CORE_IGNORE_UNUSED_HPP
#define NDNBOOST_CORE_IGNORE_UNUSED_HPP

#include <ndnboost/config.hpp>

namespace ndnboost {

#ifndef NDNBOOST_NO_CXX11_VARIADIC_TEMPLATES

template <typename... Ts>
inline void ignore_unused(Ts const& ...)
{}

template <typename... Ts>
inline void ignore_unused()
{}

#else

template <typename T1>
inline void ignore_unused(T1 const&)
{}

template <typename T1, typename T2>
inline void ignore_unused(T1 const&, T2 const&)
{}

template <typename T1, typename T2, typename T3>
inline void ignore_unused(T1 const&, T2 const&, T3 const&)
{}

template <typename T1, typename T2, typename T3, typename T4>
inline void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&)
{}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&, T5 const&)
{}

template <typename T1>
inline void ignore_unused()
{}

template <typename T1, typename T2>
inline void ignore_unused()
{}

template <typename T1, typename T2, typename T3>
inline void ignore_unused()
{}

template <typename T1, typename T2, typename T3, typename T4>
inline void ignore_unused()
{}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline void ignore_unused()
{}

#endif

} // namespace ndnboost

#endif // NDNBOOST_CORE_IGNORE_UNUSED_HPP
