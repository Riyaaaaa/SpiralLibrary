//
//  Identity.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/17.
//
//

#ifndef Identity_h
#define Identity_h

#include <type_traits>
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template<typename T>
struct Identity : std::true_type {
public:
    typedef T type;
};

template<typename T>
using Identity_t = typename Identity<T>::type;

NS_LIBSPIRAL_END

#endif /* Identity_h */
