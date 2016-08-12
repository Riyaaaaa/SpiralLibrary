/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Print_h
#define Print_h

#include <iostream>
#include <sstream>

#include "../Container/Array.hpp"
#include "../Container/Pair.hpp"
#include "../Structure/Index.hpp"

template<class T, class U>
std::ostream& operator<<(std::ostream& os, libspiral::Pair<T, U> pair) {
    os << "(" << pair.first << "," << pair.second << ")";
    return os;
}

template<class T, unsigned long Size>
std::ostream& operator<<(std::ostream& os, libspiral::Array<T, Size> arr) {
    for(int i = 0; i < Size; i++) {
        os << arr[i];
    }
    return os;
}

#endif /* Print_h */
