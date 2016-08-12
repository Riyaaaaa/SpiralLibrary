//
//  Test.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/10.
//
//

#ifndef Test_h
#define Test_h

#include"Common/Macro.h"
#include"Utility/Hash.hpp"
#include<iostream>

NS_LIBSPIRAL_BEGIN

void test() {
    Array<int, 4> arr = {0, 1, 1, 0};
    Hash<Array<int, 4>, 3> hash;
    
    std::cout << hash(arr) << std::endl;
}

NS_LIBSPIRAL_END

#endif /* Test_h */
