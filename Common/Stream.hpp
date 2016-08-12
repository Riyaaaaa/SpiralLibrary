//
//  Stream.hpp
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/07/19.
//
//

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
