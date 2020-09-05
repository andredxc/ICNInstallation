/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_cas_based.hpp
 *
 * This header contains CAS-based implementation of the \c operations template.
 */

#ifndef NDNBOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_
#define NDNBOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_

#include <ndnboost/memory_order.hpp>
#include <ndnboost/atomic/detail/config.hpp>

#ifdef NDNBOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace ndnboost {
namespace atomics {
namespace detail {

template< typename Base >
struct cas_based_operations :
    public Base
{
    typedef typename Base::storage_type storage_type;

    static NDNBOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) NDNBOOST_NOEXCEPT
    {
        storage_type old_val = Base::load(storage, memory_order_relaxed);
        while (!Base::compare_exchange_weak(storage, old_val, old_val + v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static NDNBOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) NDNBOOST_NOEXCEPT
    {
        storage_type old_val = Base::load(storage, memory_order_relaxed);
        while (!Base::compare_exchange_weak(storage, old_val, old_val - v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static NDNBOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) NDNBOOST_NOEXCEPT
    {
        storage_type old_val = Base::load(storage, memory_order_relaxed);
        while (!Base::compare_exchange_weak(storage, old_val, v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static NDNBOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) NDNBOOST_NOEXCEPT
    {
        storage_type old_val = Base::load(storage, memory_order_relaxed);
        while (!Base::compare_exchange_weak(storage, old_val, old_val & v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static NDNBOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) NDNBOOST_NOEXCEPT
    {
        storage_type old_val = Base::load(storage, memory_order_relaxed);
        while (!Base::compare_exchange_weak(storage, old_val, old_val | v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static NDNBOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) NDNBOOST_NOEXCEPT
    {
        storage_type old_val = Base::load(storage, memory_order_relaxed);
        while (!Base::compare_exchange_weak(storage, old_val, old_val ^ v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static NDNBOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) NDNBOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static NDNBOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) NDNBOOST_NOEXCEPT
    {
        Base::store(storage, (storage_type)0, order);
    }
};

} // namespace detail
} // namespace atomics
} // namespace ndnboost

#endif // NDNBOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_
