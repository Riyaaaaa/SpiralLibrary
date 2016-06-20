//
//  Print.hpp
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/14.
//
//

#ifndef Print_h
#define Print_h

#include <iostream>
#include <sstream>

#include "../Container/Array.hpp"
#include "../Container/Pair.hpp"
#include "../Structure/Index.h"

template<class T, class U>
std::ostream& operator<<(std::ostream& os, libspiral::Pair<T, U> pair) {
    os << "(" << pair.first << "," << pair.second << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, libspiral::Index index);

template<class T, unsigned long Size>
std::ostream& operator<<(std::ostream& os, libspiral::Array<T, Size> arr) {
    for(int i = 0; i < Size; i++) {
        os << arr[i];
    }
    return os;
}

#endif /* Print_h */
