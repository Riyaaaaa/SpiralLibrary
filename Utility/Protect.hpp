/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Protect_h
#define Protect_h

#include <functional>
#include <utility>
#include <type_traits>
#include"../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template<typename T>
struct protect_wrapper : T {
    protect_wrapper(const T& t) : T(t) {}
    protect_wrapper(T&& t) : T(std::move(t)) {}
};

template<typename T, typename U = typename std::decay<T>::type >
SPIRAL_CONSTEXPR typename std::enable_if< !std::is_bind_expression< U >::value, T&& >::type protect(T&& t) SPIRAL_NOEXCEPT {
    return std::forward<T>(t);
}

template<typename T, typename U = typename std::decay<T>::type >
SPIRAL_CONSTEXPR typename std::enable_if< std::is_bind_expression< U >::value, protect_wrapper< U > >::type protect(T&& t) SPIRAL_NOEXCEPT {
    return protect_wrapper<U>(std::forward<T>(t));
}


NS_LIBSPIRAL_END

#endif /* Protect_h */
