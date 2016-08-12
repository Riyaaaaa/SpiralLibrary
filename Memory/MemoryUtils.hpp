/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef MemoryUtils_h
#define MemoryUtils_h

#include "../Common/Macro.h"
#include <memory>
#include <type_traits>
#include <utility>

NS_LIBSPIRAL_BEGIN;

namespace detail {

template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args) {
    static_assert(std::extent<T>::value == 0,
                  "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");
    
    typedef typename std::remove_extent<T>::type U;
    return std::unique_ptr<T>(new U[sizeof...(Args)]{std::forward<Args>(args)...});
}
    
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return detail::make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);
}

NS_LIBSPIRAL_END;

#endif /* MemoryUtils_h */
