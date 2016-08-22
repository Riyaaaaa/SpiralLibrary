/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef OptionalTest_h
#define OptionalTest_h

#include "../Optional/Optional.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    namespace detail {
        template<class T>
        void printOpt(const Optional<T>& op) {
            if(op) {
                std::cout << *op << std::endl;
            }
            else {
                std::cout << "op is not initialized" << std::endl;
            }
        }
    }
    
    static void optionalTest() {
        Optional<int> op;
        
        detail::printOpt(op);
        
        op = 3;
        detail::printOpt(op);
        
        op = nullopt_t{};
        detail::printOpt(op);
        std::cout << op.value_or(10) << std::endl;
        
        op.emplace(3);
        detail::printOpt(op);
        
        Optional<int> op2;
        op.swap(op2);
        detail::printOpt(op);
        
        op = op2;
        std::cout << op.value() << std::endl;
        
        op.reset();
        detail::printOpt(op);
        
    }
}

#endif /* OptionalTest_h */
