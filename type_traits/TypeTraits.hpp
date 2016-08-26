//
//  CXX14Traits.hpp
//  SpiralLibDevelop
//
//  Created by Atsumu Ono on 2016/08/25.
//  Copyright © 2016年 Atsumu Ono. All rights reserved.
//

#ifndef TypeTraits_h
#define TypeTraits_h

#include "../Common/Macro.h"
#include "StdTraitsAlias.hpp"
#include <type_traits>

NS_LIBSPIRAL_BEGIN

template<class T>
struct is_null_pointer : public std::false_type {};

template<>
struct is_null_pointer<std::nullptr_t> : public std::true_type {};

template<class T, class... Args>
struct is_all_convertible : std::true_type {};

template<class T, class HEAD, class... Args>
struct is_all_convertible {
    static constexpr bool value = std::is_convertible<T, HEAD>::value ? std::is_all_convertible<T, Args...>::value : std::false_type{};
};

template<class T, class Args...>
static constexpr bool is_all_convertible_test(T&& arg1, Args&&... args) {
    return is_all_convertible<T, Args...>::value;
}

NS_LIBSPIRAL_END


#endif /* TypeTraits_h */
