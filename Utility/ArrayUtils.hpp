//
//  ArrayUtils.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/10.
//
//

#ifndef ArrayUtils_h
#define ArrayUtils_h

#include "../Common/Macro.h"
#include "../Container/Array.hpp"

NS_LIBSPIRAL_BEGIN

#if defined(SPIRAL_CXX_14)

template<class T, unsigned long Size>
SPIRAL_CXX14_CONSTEXPR Array<T, Size> arrayTruncate(Array<T, Size> source, unsigned long n){
    for(unsigned long i = n; i < Size; i++){
        source[i - n] = source[i];
    }
    return source;
}

template<unsigned long CutSize, class T, unsigned long Size>
SPIRAL_CXX14_CONSTEXPR Array<T, CutSize> cutOutArray(Array<T, Size> source){
    Array<T, CutSize> dest;
    for(int i = 0; i < CutSize; i++){
        dest[i] = source[i];
    }
    return dest;
}

#elif defined(SPIRAL_CXX_11)

namespace detail {
    
    template<class Arr1, class Arr2>
    SPIRAL_CONSTEXPR Arr1 _elementCopy(Arr1 arr1, Arr2 arr2, unsigned long index) {
        return (arr1[index] = arr2[index]) ? arr1 : arr1;
    }
    
    template<class T, unsigned long CutSize, unsigned long Size, unsigned long index, bool isEnd = index == CutSize>
    struct _cutOutArray {
        SPIRAL_CONSTEXPR Array<T, CutSize> operator()(Array<T, CutSize> dest, Array<T, Size> source) const {
            return _cutOutArray<T, CutSize, Size, index + 1>()(_elementCopy(dest, source, index), source);
        }
    };
    
    template<class T, unsigned long CutSize, unsigned long Size, unsigned long index>
    struct _cutOutArray<T, CutSize, Size, index, true> {
        SPIRAL_CONSTEXPR Array<T, CutSize> operator()(Array<T, CutSize> dest, Array<T, Size> source) const {
            return dest;
        }
    };
}
template<unsigned long CutSize, class T, unsigned long Size>
SPIRAL_CONSTEXPR Array<T, CutSize> cutOutArray(Array<T, Size> source){
    return detail::_cutOutArray<T, CutSize, Size, 0>()(Array<T, CutSize>{}, source);
}

#endif


NS_LIBSPIRAL_END

#endif /* ArrayUtils_h */
