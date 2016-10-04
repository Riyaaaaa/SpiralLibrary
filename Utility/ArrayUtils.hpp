/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef ArrayUtils_h
#define ArrayUtils_h

#include "../Common/Macro.h"
#include "../Container/Array.hpp"
#include "../Utility/Forward.hpp"
#include "../TypeTraits/TypeTraits.hpp"

NS_LIBSPIRAL_BEGIN

template<class... Args>
SPIRAL_CONSTEXPR Array<typename head_type<Args...>::type, sizeof...(Args)> makeArray(Args&&... args) {
    static_assert(is_all_same<decay_t<typename head_type<Args...>::type>, decay_t<Args>...>::value, "type error");
    return Array<decay_t<typename head_type<Args...>::type>, sizeof...(Args)>{args...};
}

template<class T, class... Args>
SPIRAL_CONSTEXPR Array<T, sizeof...(Args)> makeArray(Args&&... args) {
    static_assert(is_all_convertible<T, decay_t<Args>...>::value, "type error");
    return Array<T, sizeof...(Args)>{static_cast<T>(args)...};
}

template<class T, unsigned long Size>
SPIRAL_CXX14_CONSTEXPR Array<T, Size> arrayTruncate(Array<T, Size> source, unsigned long n){
    for(unsigned long i = n; i < Size; i++){
        source[i - n] = source[i];
    }
    return source;
}


#if defined(SPIRAL_CXX_14)

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
