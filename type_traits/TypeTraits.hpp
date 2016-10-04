/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

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
    
    template<class T, bool isEnd, class HEAD, class... Args>
    struct is_all_same_impl;
    
    template<class T, class HEAD, class... Args>
    struct is_all_same_impl<T, false, HEAD, Args...> {
        static constexpr bool value = std::is_same<T, HEAD>::value ? is_all_same_impl<T, sizeof...(Args) == 2, Args...>::value : std::false_type{};
    };
    
    template<class T, class HEAD, class... Args>
    struct is_all_same_impl<T, true, HEAD, Args...> {
        static constexpr bool value = std::is_same<T, HEAD>::value;
    };
 }

template<class T, class... Args>
struct is_all_convertible : std::conditional<sizeof...(Args) == 1,
                                            std::is_convertible<T, typename head_type<Args...>::type>,
                                            detail::is_all_convertible_impl<T, sizeof...(Args) == 2, Args...>
                                            >::type{};

template<class T, class... Args>
struct is_all_same : std::conditional<sizeof...(Args) == 1,
                                    std::is_same<T, typename head_type<Args...>::type>,
                                    detail::is_all_same_impl<T, sizeof...(Args) == 2, Args...>
                                    >::type{};

NS_LIBSPIRAL_END


#endif /* TypeTraits_h */
