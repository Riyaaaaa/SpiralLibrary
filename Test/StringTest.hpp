/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef StringTest_h
#define StringTest_h

#include "../String/Concat.hpp"
#include "../String/Format.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    static void stringTest() {
        static constexpr char HEAD[] = "head";
        static constexpr char TAIL[] = "tail";
        std::cout << "----------- concat test -----------" << std::endl;
        std::cout << concatToString(HEAD, TAIL) << std::endl;
        std::cout << &concat(HEAD, TAIL)[0] << std::endl;
        std::cout << "-----------             -----------" << std::endl;
        
        std::cout << "----------- format test -----------" << std::endl;
        std::cout << format("%s%d%s", HEAD, 100, TAIL) << std::endl;
        std::cout << "-----------             -----------" << std::endl;
    }
}

#endif /* StringTest_h */
