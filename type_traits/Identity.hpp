//
//  Identity.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/17.
//
//

#ifndef Identity_h
#define Identity_h

#include "../Common/Macro.h"

NS_SPIRAL_BEGIN

template<typename T>
struct Identity {
public:
    typedef T type;
};

template<typename T>
using Identity_t = typename Identity<T>::type;

NS_SPIRAL_END

#endif /* Identity_h */
