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
    static constexpr unsigned long size = LENGTH;
    
    const value_type* begin() const {
        return v;
    }
    
    const value_type* end() const {
        return v + LENGTH;
    }
    
    value_type* begin() {
        return v;
    }
    
    value_type* end() {
        return v + LENGTH;
    }
};

template<class T, unsigned long Dim>
class VectorMulitiDims {
    Array<T, Dim> vec;
};

NS_LIBSPIRAL_END

#endif /* Array_hpp */
