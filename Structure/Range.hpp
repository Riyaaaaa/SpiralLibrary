/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Range_h
#define Range_h

#include "../Common/Macro.h"
#include "../TypeTraits/Tag.hpp"

NS_LIBSPIRAL_BEGIN

template<class T, class Pred = default_t>
class Range {
public:
    T min, max;
    SPIRAL_CONSTEXPR bool isContains(T value) const {
        return (_pred(min, value) && !_pred(max, value)) ? true : false;
    }
private:
    Pred _pred;
};

template<class T>
class Range<T, default_t> {
public:
    T min, max;
    SPIRAL_CONSTEXPR bool isContains(T value) const {
        return (min <= value && !(max < value)) ? true : false;
    }
};

NS_LIBSPIRAL_END

#endif /* Range_h */
