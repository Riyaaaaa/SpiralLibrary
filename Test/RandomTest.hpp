/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef RandomTest_h
#define RandomTest_h

#include "../Random/Random.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    static void randomTest() {
        std::cout << "default engine random value (Range 0 - 100)" << std::endl;
        for(int i = 0; i < 100; i++) {
            std::cout << Random<>::getValue(Range<int>{0, 100}) << ',';
        }
        std::cout << "\n ------------------- \n" <<std::endl;
        std::cout << "mt19937 engine random value (Range 0.0 - 100.0)" << std::endl;
        for(int i = 0; i < 100; i++) {
            std::cout << Random<std::mt19937>::getValue(Range<float>{0.0f, 100.0f}) << ',';
        }
        std::cout << "\n ------------------- \n" <<std::endl;
    }
    
}

#endif /* RandomTest_h */
