/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Enabler_h
#define Enabler_h

#include "../Common/Macro.h"
#include <type_traits>

NS_LIBSPIRAL_BEGIN

extern void * enabler;

template<bool enable, typename T>
using disable_if = std::enable_if<!enable, T>;

template<typename Enabler, typename T>
using disable_if_m = std::enable_if<!Enabler::value, T>;

template<typename Enabler, typename T>
using enable_if_m = std::enable_if<Enabler::value, T>;

template<bool enable>
using enable_when_t = typename std::enable_if<enable>::type*&;

template<bool enable>
using enable_null_t = typename std::enable_if<enable, std::nullptr_t>::type;

NS_LIBSPIRAL_END

#endif /* Enabler_h */
