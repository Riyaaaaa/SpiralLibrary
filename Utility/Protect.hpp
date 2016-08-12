//
//  Protect.hpp
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/10.
//
//

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
SPIRAL_CONSTEXPR typename std::enable_if< !std::is_bind_expression< U >::value, T&& >::type protect(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U = typename std::decay<T>::type >
SPIRAL_CONSTEXPR typename std::enable_if< std::is_bind_expression< U >::value, protect_wrapper< U > >::type protect(T&& t) {
    return protect_wrapper<U>(std::forward<T>(t));
}


NS_LIBSPIRAL_END

#endif /* Protect_h */
