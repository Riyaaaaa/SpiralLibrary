/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef AnyTest_h
#define AnyTest_h

#include "../Any/Any.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    static void AnyTest() {
        Any a = 3;
        int* p = any_cast<int>(&a);
        if(p) {
            std::cout << *p << std::endl;
        }
        int b = any_cast<int>(a);
        std::cout << b << std::endl;
        
        Any a2 = std::string("aaa");
        Optional<std::string> b2 = any_cast_noexp<std::string>(a2);
        if(b2) {
            std::cout << b2.value() << std::endl;
        }
        Optional<char> b3 = any_cast_noexp<char>(a2);
        if(b3) {
            std::cout << b3.value() << std::endl;
        }
    }
    
}

#endif /* AnyTest_h */
