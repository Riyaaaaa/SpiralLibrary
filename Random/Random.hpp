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
#include "../Common/Macro.h"
#include "../Structure/Range.hpp"
#include "../TypeTraits/Enabler.hpp"

NS_LIBSPIRAL_BEGIN

template<class ENGINE = std::default_random_engine>
class Random {
public:
    template<typename T, typename libspiral::enable_null_t<std::is_integral<T>{}> = nullptr>
    static T getValue(Range<T> range) {
        std::uniform_int_distribution<T> dist(range.min, range.max);
        return dist(engine);
    }
    
    template<typename T, typename libspiral::enable_null_t<std::is_floating_point<T>{}> = nullptr>
    static T getValue(Range<T> range) {
        std::uniform_real_distribution<T> dist(range.min, range.max);
        return dist(engine);
    }
    
    template<typename T, typename libspiral::enable_null_t<std::is_integral<T>{}> = nullptr>
    static T getValue(T min, T max) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(engine);
    }
    
    template<typename T, typename libspiral::enable_null_t<std::is_floating_point<T>{}> = nullptr>
    static T getValue(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
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
