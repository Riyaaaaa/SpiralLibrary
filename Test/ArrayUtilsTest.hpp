/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef ArrayUtilsTest_h
#define ArrayUtilsTest_h

#include "../Utility/ArrayUtils.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    static void ArrayUtilsTest() {
        auto array = makeArray(1.0f, 2.12f, 3.0f);
        for(auto elm: array) {
            std::cout << elm << ',';
        }
        std::cout << std::endl;
        
        auto array2 = makeArray<int>(1.0f, 2.12f, 'a');
        for(auto elm: array2) {
            std::cout << elm << ',';
        }
        std::cout << std::endl;
    }
    
}

#endif /* ArrayUtilsTest_h */
