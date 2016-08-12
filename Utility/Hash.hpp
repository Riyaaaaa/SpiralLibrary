/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Hash_hpp
#define Hash_hpp

#include "../Common/Macro.h"
#include "../Container/Array.hpp"
#include "../Common/Math.hpp"
#include "ArrayUtils.hpp"
#include "IndexSequence.hpp"

NS_LIBSPIRAL_BEGIN

template<class T, int Radix>
struct Hash;

#if defined(SPIRAL_CXX_14)

template<class T, unsigned long Size, int Radix>
struct Hash<Array<T, Size>, Radix> {
    SPIRAL_CXX14_CONSTEXPR unsigned long operator()(const Array<T, Size>& arr) {
        unsigned long hash = 0;
        for(int i = 0; i < Size; i++){
            hash += arr[i] * libspiral::pow(Radix, i);
        }
        return hash;
    }
};

#elif defined(SPIRAL_CXX_11)

template<class T, unsigned long Size, int Radix>
struct Hash<Array<T, Size>, Radix> {
private:
    template<class Type, int L>
    struct _impl;
    
public:
    SPIRAL_CONSTEXPR unsigned long operator()(const Array<T, Size>& arr) const {
        return _impl<T, Size>::calc( arr );
    }
    
private:
    template<class Type, int L>
    struct _impl {
        SPIRAL_STATIC_CONSTEXPR unsigned long calc(const Array<Type, L>& arr) {
            return arr[L - 1] * libspiral::pow(Radix, L - 1) + _impl<Type, L - 1>::calc( cutOutArray<L - 1, Type, L>(arr));
        }
    };
    template<class Type>
    struct _impl<Type, 1>{
        SPIRAL_STATIC_CONSTEXPR unsigned long calc(const Array<Type, 1>& arr) {
            return arr[0] * libspiral::pow(Radix, 0);
        }
    };
};

#endif

NS_LIBSPIRAL_END

#endif /* Hash_hpp */
