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

template<class HEAD, class... Args>
struct head_type {
    typedef HEAD type;
};

template<class T>
struct is_null_pointer : public std::false_type {};

template<>
struct is_null_pointer<std::nullptr_t> : public std::true_type {};

namespace detail {
    template<class T, bool isEnd, class HEAD, class... Args>
    struct is_all_convertible_impl;
    
    template<class T, class HEAD, class... Args>
    struct is_all_convertible_impl<T, false, HEAD, Args...> {
        static constexpr bool value = std::is_convertible<T, HEAD>::value ? is_all_convertible_impl<T, sizeof...(Args) == 2, Args...>::value : std::false_type{};
    };
    
    template<class T, class HEAD, class... Args>
    struct is_all_convertible_impl<T, true, HEAD, Args...> {
        static constexpr bool value = std::is_convertible<T, HEAD>::value;
    };
}

template<class T, class... Args>
struct is_all_convertible : detail::is_all_convertible_impl<T, sizeof...(Args) == 2, decay_t<Args>...>{};

NS_LIBSPIRAL_END


#endif /* TypeTraits_h */
