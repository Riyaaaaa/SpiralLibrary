/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef DelayCall_h
#define DelayCall_h

#include "../Utility/Forward.hpp"
#include "../Common/Macro.h"
#include "../TypeTraits/Identity.hpp"
#include "../TypeTraits/StdTraitsAlias.hpp"
#include <utility>
#include <functional>
#include <thread>
#include <chrono>

NS_LIBSPIRAL_BEGIN

namespace detail {
    
    template<class... Args>
    struct delay_impl {
        static void call(float t, const std::function<void(Args...)>& func, Args&&... args) {
            if(func) {
                std::chrono::system_clock::time_point _s = std::chrono::system_clock::now();
                std::thread thd = std::thread([&](){
                    while(true) {
                        if(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - _s).count() >= t) {
                            func(libspiral::forward<Args>(args)...);
                            break;
                        }
                    }
                });
                thd.detach();
            }
        }
    };
}

template<class... Args>
void delayCall(float t, const std::function<void(Args...)>& func, libspiral::remove_reference_t<Args>&&... args) {
    detail::delay_impl<Args...>::call(t, func, std::forward<Args>(args)...);
}

template<class... Args>
void delayCall(float t, const std::function<void(Args...)>& func, libspiral::remove_reference_t<Args>&... args) {
    detail::delay_impl<Args...>::call(t, func, std::forward<Args>(args)...);
}

void delayCall(float t, const std::function<void(void)>& func) {
    detail::delay_impl<>::call(t, func);
}

NS_LIBSPIRAL_END

#endif /* DelayCall_h */
