//
//  Range.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/07/20.
//
//

#ifndef Range_h
#define Range_h

#include "../Common/Macro.h"
#include "../type_traits/Tag.hpp"

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
