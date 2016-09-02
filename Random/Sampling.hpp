//
//  Sampling.hpp
//  NekoShiwake
//
//  Created by Atsumu Ono on 2016/09/01.
//
//

#ifndef Sampling_h
#define Sampling_h

#include <random>
#include <type_traits>
#include <assert.h>
#include "../Common/Macro.h"
#include "../Structure/Range.hpp"
#include "../type_traits/Enabler.hpp"

NS_LIBSPIRAL_BEGIN

template<class ENGINE = std::default_random_engine>
class Sampling {
public:
    template<class T, class Array1, class Array2>
    static T getValue(const Array1& probabilities, const Array2& resource) {
        assert(probabilities.size() == resource.size());
        std::discrete_distribution<std::size_t> dist(
                                                        probabilities.begin(),
                                                        probabilities.end()
                                                     );
        return resource[dist(engine)];
    }
    
private:
    static std::random_device seed_gen;
    static ENGINE engine;
};

template<class ENGINE>
std::random_device Sampling<ENGINE>::seed_gen;

template<class ENGINE>
ENGINE Sampling<ENGINE>::engine = ENGINE(Sampling<ENGINE>::seed_gen());

NS_LIBSPIRAL_END

#endif /* Sampling_h */
