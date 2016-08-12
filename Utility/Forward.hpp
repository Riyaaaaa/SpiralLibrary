/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Forward_h
#define Forward_h

#include "../Common/Macro.h"
#include <type_traits>

NS_LIBSPIRAL_BEGIN

template <class T>
SPIRAL_CONSTEXPR T&& forward(typename std::remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

template <class T>
SPIRAL_CONSTEXPR T&& forward(typename std::remove_reference<T>::type&& t) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, "Can not forward an rvalue as an lvalue.");
    return static_cast<T&&>(t);
}

NS_LIBSPIRAL_END

#endif /* Forward_h */
