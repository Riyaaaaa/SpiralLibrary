/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef MaybeCall_h
#define MaybeCall_h

#include "../Utility/Forward.hpp"
#include "../Optional/Optional.hpp"
#include "../Common/Macro.h"
#include <utility>
#include <functional>

NS_LIBSPIRAL_BEGIN

namespace detail {

template<class T, class... Args>
struct maybe_impl {
    static auto call(const std::function<T(Args...)>& func, Args&&... args)
    ->optional<decltype(func(args...))> {
        if(func) {
            return libspiral::make_optional(func(std::forward<Args>(args)...));
        }
        return optional<decltype(func(std::declval<Args>()...))>(nullopt_t{});
    }
};

template<class... Args>
struct maybe_impl<void, Args...> {
    static void call(const std::function<void(Args...)>& func, Args&&... args) {
        if(func) {
            func();
        }
    }
};

}
    
template<class T, class... Args>
auto maybeCall(const std::function<T(Args...)>& func, Args&&... args)
->decltype(detail::maybe_impl<T, Args...>::call(func, args...)) {
    return detail::maybe_impl<T, Args...>::call(func, forward<Args>(args)...);
}

NS_LIBSPIRAL_END

#endif /* MaybeCall_h */
