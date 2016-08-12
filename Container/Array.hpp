/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Array_hpp
#define Array_hpp

#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template <typename T, unsigned long LENGTH>
struct Array {
    typedef T value_type;
    
    T v[LENGTH];
    
    SPIRAL_CONSTEXPR T const& operator[](unsigned long l) const {
        return v[l];
    }
    
    SPIRAL_CXX14_CONSTEXPR T& operator[](unsigned long l) {
        return v[l];
    }
    
    SPIRAL_STATIC_CONSTEXPR unsigned long size = LENGTH;
    
    SPIRAL_CONSTEXPR  const value_type* begin() const {
        return v;
    }
    
    SPIRAL_CONSTEXPR  const value_type* end() const {
        return v + LENGTH;
    }
    
    SPIRAL_CXX14_CONSTEXPR value_type* begin() {
        return v;
    }
    
    SPIRAL_CXX14_CONSTEXPR value_type* end() {
        return v + LENGTH;
    }
};

template<class T, unsigned long Dim>
class VectorMulitiDims {
    Array<T, Dim> vec;
};

NS_LIBSPIRAL_END

#endif /* Array_hpp */
