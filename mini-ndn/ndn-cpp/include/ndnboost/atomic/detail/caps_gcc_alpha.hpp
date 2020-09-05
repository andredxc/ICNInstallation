/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_alpha.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef NDNBOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_
#define NDNBOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_

#include <ndnboost/atomic/detail/config.hpp>

#ifdef NDNBOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define NDNBOOST_ATOMIC_INT8_LOCK_FREE 2
#define NDNBOOST_ATOMIC_INT16_LOCK_FREE 2
#define NDNBOOST_ATOMIC_INT32_LOCK_FREE 2
#define NDNBOOST_ATOMIC_INT64_LOCK_FREE 2
#define NDNBOOST_ATOMIC_POINTER_LOCK_FREE 2

#define NDNBOOST_ATOMIC_THREAD_FENCE 2
#define NDNBOOST_ATOMIC_SIGNAL_FENCE 2

#endif // NDNBOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_
