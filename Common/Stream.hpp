/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/
#ifndef Stream_h
#define Stream_h

#include <iostream>
#include "Macro.h"
#include "../Structure/MultiIndex.hpp"

NS_LIBSPIRAL_BEGIN

template<size_t _Rank>
std::ostream& operator<<(std::ostream& os, MultiIndex<_Rank> indexes) {
    
    for(int i = 0; i < _Rank; i++) {
        os << indexes[i] << ", ";
    }
    
    return os;
}

NS_LIBSPIRAL_END

#endif /* Stream_h */
