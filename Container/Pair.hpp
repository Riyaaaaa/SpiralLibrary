//
//  Pair.hpp
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/10.
//
//

#ifndef Pair_h
#define Pair_h

#include <utility>
#include <type_traits>
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template <typename T, typename U, bool isLiteral = std::is_literal_type<T>::value && std::is_literal_type<U>::value>
struct Pair;

template <typename T, typename U>
struct Pair<T, U, true>{
    T first;
    U second;
    
    SPIRAL_CONSTEXPR Pair():first(T{}), second(U{}){
    
    }
    
    SPIRAL_CONSTEXPR Pair(T first, U second)
    :first(first), second(second) {
        
    }
};

template <typename T, typename U>
struct Pair<T, U, false>{
    T first;
    U second;
    
    Pair(){}
    
    Pair(T&& first, U&& second)
    :first(first), second(second) {
        
    }
};

template <typename T, typename U>
SPIRAL_CONSTEXPR Pair<typename std::remove_reference<T>::type, typename std::remove_reference<U>::type> make_pair(T&& first, U&& second) {
    return Pair<typename std::remove_reference<T>::type, typename std::remove_reference<U>::type>(std::forward<T>(first), std::forward<U>(second));
}

struct secondGreaterOrder {
    template<class Key, class Value>
    SPIRAL_CXX14_CONSTEXPR bool operator()(const Pair<Key, Value>& lhs, const Pair<Key, Value>& rhs) const {
        return lhs.second > rhs.second;
    }
};
struct secondLessOrder {
    template<class Key, class Value>
    SPIRAL_CXX14_CONSTEXPR bool operator()(const Pair<Key, Value>& lhs, const Pair<Key, Value>& rhs) const {
        return lhs.second < rhs.second;
    }
};

NS_LIBSPIRAL_END

#endif /* Pair_h */
