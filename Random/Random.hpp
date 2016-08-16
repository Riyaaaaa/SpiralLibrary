/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Random_h
#define Random_h

#include <random>
#include <type_traits>
#include "Macro.h"
#include "../Structure/Range.hpp"
#include "../type_traits/Enabler.hpp"

NS_LIBSPIRAL_BEGIN

template<class ENGINE = std::default_random_engine>
class Random {
public:
    template<typename T, typename std::enable_if<std::is_integral<T>{}>::type*& = enabler>
    static T getValue(Range<T> range) {
        std::uniform_int_distribution<T> dist(range.min, range.max);
        return dist(engine);
    }
    
    template<typename T, typename std::enable_if<std::is_floating_point<T>{}>::type*& = enabler>
    static T getValue(Range<T> range) {
        std::uniform_real_distribution<T> dist(range.min, range.max);
        return dist(engine);
    }
private:
    static std::random_device seed_gen;
    static ENGINE engine;
};

template<class ENGINE>
std::random_device Random<ENGINE>::seed_gen;

template<class ENGINE>
ENGINE Random<ENGINE>::engine = ENGINE(Random<ENGINE>::seed_gen());

NS_LIBSPIRAL_END


#endif /* Random_h */
