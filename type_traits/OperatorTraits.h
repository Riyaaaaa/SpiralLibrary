//
//  OperatorTraits.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/17.
//
//

#ifndef OperatorTraits_h
#define OperatorTraits_h

#include<type_traits>
#include "../Common/Macro.h"
#include "Identity.hpp"
#include "Enabler.hpp"

NS_SPIRAL_BEGIN

template<class T, class U = Identity_t<decltype(operator&(std::declval<T>()))> >
struct hasAddressOp : std::true_type {};

template<class T, class U = T >
struct hasAddressOp : std::false_type {};

NS_SPIRAL_END

#endif /* OperatorTraits_h */
