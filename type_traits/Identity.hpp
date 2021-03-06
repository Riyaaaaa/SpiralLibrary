/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Identity_h
#define Identity_h

#include <type_traits>
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template<typename T>
struct Identity : std::true_type {
public:
    typedef T type;
};

template<typename T>
using Identity_t = typename Identity<T>::type;

NS_LIBSPIRAL_END

#endif /* Identity_h */
