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

template<class T>
using enable_when_t = typename std::enable_if<T::value>::type*&;

template<class T>
using enable_null_t = typename std::enable_if<T::value, std::nullptr_t>::type;

NS_LIBSPIRAL_END

#endif /* Enabler_h */
