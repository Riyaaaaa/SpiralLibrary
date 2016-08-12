/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef MultiArray_and_MultiIndexTest_h
#define MultiArray_and_MultiIndexTest_h

#include "../Common/Macro.h"
#include "../Container/MultiArray.hpp"
#include "../Structure/MultiIndex.hpp"
#include <iostream>

enum class StoneType {
    None = 0,
    Black,
    White
};

namespace testspiral {
    USING_NS_LIBSPIRAL;
static void multiArrayAndIndexTest() {
    MultiArray<int, 2> arr;
    MultiArray<int, 7, 7> arr1; //default constructor
    MultiArray<int, 2, 2, 1> arr2 = {1, 1, 1, 1}; //initializer_list
    SPIRAL_CONSTEXPR MultiArray<unsigned long, 2, 2, 2> arr3 = {4ul, 3ul, 1ul, 1ul, 1ul, 1ul, 10ul, 20ul}; //constexpr expression

    SPIRAL_CONSTEXPR MultiIndex<2> index = {0};
    SPIRAL_CONSTEXPR MultiIndex<2> index1 = {1, 0};
    SPIRAL_CONSTEXPR MultiIndex<3> index2 = {0, 0, 1};
    
    SPIRAL_CONSTEXPR IndexRange<2> indexRange1(libspiral::MultiIndex<2>(0, 0), libspiral::MultiIndex<2>(1, 1));
    
    std::cout << "----------Multi Array And Index Test-----------" << std::endl;
    
    arr[0] = 1;
    arr1[0][1] = 10;
    arr2[1][0][0] = 100;
    
    std::cout << "[] access: " << arr[0] << " index access: " << arr[index] << std::endl;
    std::cout << "[] access: " << arr1[0][1] << " index access: " << (int)arr1[index1] << std::endl;
    std::cout << "[] access: " << arr2[1][0][0] << " index access: " << arr2[index2] << std::endl;
    

    std::cout << "init: nested for loop / output: base-ranged-for" << std::endl;
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            arr1[i][j] = 100;
        }
    }
    
    for(auto && n : arr1) {
        std::cout << (int)n << " ,";
    }
    std::cout << std::endl;
    
    std::cout << "output: index-iterating-base-ranged for loop" << std::endl;
    for(auto && index : indexRange1) {
        std::cout << arr1[index] << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "output: readonly base-ranged for loop" << std::endl;
    for(auto && n : arr3) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
}

}

#endif /* MultiArray_and_MultiIndexTest_h */
