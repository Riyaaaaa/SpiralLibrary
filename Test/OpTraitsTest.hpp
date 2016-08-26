
#ifndef OpTraitsTest_h
#define OpTraitsTest_h

#include "../type_traits/OperatorTraits.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    static void opTraitsTest() {
        struct hasAddressOpClass {
            hasAddressOpClass* operator&() {
                return this;
            }
        };
        struct hasNotOpClass {
            bool operator!() {
                return true;
            }
        };
        
        static_assert(hasAddressOp<hasAddressOpClass>{}, "!!");
        static_assert(hasNotOp<hasNotOpClass>{}, "!!");
        static_assert(!hasAddressOp<int>{}, "!!");
        static_assert(!hasNotOp<double>{}, "!!");
        
        std::cout << "All traits test passed" << std::endl;
    }
    
}

#endif /* OpTraitsTest_h */
