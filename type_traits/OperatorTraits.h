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
#include "../type_traits/OperatorTraits.h"
#include "../Common/Macro.h"
#include "Identity.hpp"
#include "Enabler.hpp"

NS_LIBSPIRAL_BEGIN

template<class T>
struct hasAddressOpTest {
    template<typename U = T, typename = Identity_t<decltype(operator&(std::declval<U>()))>>
    static std::true_type test(int);
    static std::false_type test(...);
};

template<class T>
struct hasAddressOp : public Identity_t<decltype(hasAddressOpTest<T>::test(0))>
{};
                                      

NS_LIBSPIRAL_END

#endif /* OperatorTraits_h */
