/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Pair_h
#define Pair_h

#include <utility>
#include <type_traits>
#include "../Common/Macro.h"
#include "../Utility/Forward.hpp"

NS_LIBSPIRAL_BEGIN

template <typename T, typename U, bool isMoveAssignable = std::is_move_assignable<T>::value && std::is_move_assignable<U>::value>
struct Pair;

template <typename T, typename U>
struct Pair<T, U, false>{
    T first;
    U second;
};

template <typename T, typename U>
struct Pair<T, U, true>{
    T first;
    U second;
    
    SPIRAL_CXX14_CONSTEXPR Pair& operator=(Pair&& other) SPIRAL_NOEXCEPT(std::is_nothrow_move_assignable<T>::value &&
                                            std::is_nothrow_move_assignable<U>::value) {
        if(this != &other) {
            first = libspiral::forward<T>(other.first);
            second = libspiral::forward<U>(other.second);
        }
        return *this;
    }

    SPIRAL_CXX14_CONSTEXPR Pair(Pair&& other) = default;
    SPIRAL_CXX14_CONSTEXPR Pair(const Pair& other) = default;
    SPIRAL_CONSTEXPR Pair() = default;
    
    template<class T2, class U2,
    class = typename std::enable_if<std::is_convertible<T2, T>::value && std::is_convertible<U2, U>::value>::type >
    SPIRAL_CONSTEXPR Pair(T2&& t, U2&& u) SPIRAL_NOEXCEPT
    : first(libspiral::forward<T2>(t)),
    second(libspiral::forward<U2>(u))
    {}
    
    template<class T2, class U2,
    class = typename std::enable_if<std::is_convertible<T2, T>::value && std::is_convertible<U2, U>::value>::type >
    SPIRAL_CONSTEXPR Pair(Pair<T2, U2>&& p) SPIRAL_NOEXCEPT
    : first(libspiral::forward<T2>(p.first)),
    second(libspiral::forward<U2>(p.second))
    {}
    
};

template <typename T, typename U>
SPIRAL_CONSTEXPR Pair<typename std::remove_reference<T>::type, typename std::remove_reference<U>::type> make_pair(T&& first, U&& second)
SPIRAL_NOEXCEPT(std::is_nothrow_move_assignable<T>::value &&
                std::is_nothrow_move_assignable<U>::value)
{
    return Pair<typename std::remove_reference<T>::type, typename std::remove_reference<U>::type>(libspiral::forward<T>(first), libspiral::forward<U>(second));
}

struct secondGreaterOrder {
    template<class Key, class Value>
    SPIRAL_CXX14_CONSTEXPR bool operator()(const Pair<Key, Value>& lhs, const Pair<Key, Value>& rhs) const SPIRAL_NOEXCEPT {
        return lhs.second > rhs.second;
    }
};
struct secondLessOrder {
    template<class Key, class Value>
    SPIRAL_CXX14_CONSTEXPR bool operator()(const Pair<Key, Value>& lhs, const Pair<Key, Value>& rhs) const SPIRAL_NOEXCEPT {
        return lhs.second < rhs.second;
    }
};

NS_LIBSPIRAL_END

#endif /* Pair_h */
