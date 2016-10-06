/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef DelayCallTest_h
#define DelayCallTest_h

#include "../Function/DelayCall.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    static void delayCallTest() {
        std::function<void()> f1 = [](){ std::cout << "called" << std::endl; };
        std::function<void(int)> f2 = [](int n){ std::cout << "value: " << n << std::endl; };

        delayCall(100.0f, f1);
        delayCall(500.0f, f2, 10);
        
        for(int i = 0; i < 1000000000; i++);
    }
}

#endif /* DelayCallTest_h */
