/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef MaybeCallTest_h
#define MaybeCallTest_h

#include "OptionalTest.hpp"
#include "../Function/MaybeCall.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    static void maybeCallTest() {
        Optional<int> op1, op2, op3;
        std::function<int()> f1;
        std::function<int()> f2 = [](){ return 1; };
        std::function<int(int)> f3 = [](int n){ return n; };
        
        op1 = maybeCall(f1);
        op2 = maybeCall(f2);
        op3 = maybeCall(f3, 10);
        
        detail::printOpt(op1);
        detail::printOpt(op2);
        detail::printOpt(op3);
    }
}

#endif /* MaybeCallTest_h */
