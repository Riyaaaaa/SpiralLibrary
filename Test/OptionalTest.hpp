//
//  OptionalTest.hpp
//  SpiralLibTest
//
//  Created by Riya.Liel on 2016/08/22.
//  Copyright © 2016年 Riya.Liel. All rights reserved.
//

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
