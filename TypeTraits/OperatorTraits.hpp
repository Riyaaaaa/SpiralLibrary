/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef OperatorTraits_h
#define OperatorTraits_h

#include<type_traits>
#include "../Common/Macro.h"
#include "Identity.hpp"
#include "Enabler.hpp"

NS_LIBSPIRAL_BEGIN

namespace detail {
    
    template<class T>
    struct hasAddressOpTest {
        template<typename U = T, typename = Identity_t<decltype((std::declval<U>().operator&()))>>
        static std::true_type test(int);
        static std::false_type test(...);
    };
    
    template<class T>
    struct hasNotOpTest {
        template<typename U = T, typename = Identity_t<decltype((std::declval<U>().operator!()))>>
        static std::true_type test(int);
        static std::false_type test(...);
    };
    
    template<class T>
    struct hasRShiftOpTest {
        template<typename U = T, typename = Identity_t<decltype((std::declval<U>().operator>>()))>>
        static std::true_type test(int);
        static std::false_type test(...);
    };
    
    template<class T>
    struct hasLShiftOpTest {
        template<typename U = T, typename = Identity_t<decltype((std::declval<U>().operator<<()))>>
        static std::true_type test(int);
        static std::false_type test(...);
    };
    
}

template<class T>
struct hasAddressOp : public Identity_t<decltype(detail::hasAddressOpTest<T>::test(0))>
{};

template<class T>
struct hasNotOp : public Identity_t<decltype(detail::hasNotOpTest<T>::test(0))>
{};

template<class T>
struct hasRShiftOp : public Identity_t<decltype(detail::hasRShiftOpTest<T>::test(0))>
{};

template<class T>
struct hasLShiftOp : public Identity_t<decltype(detail::hasLShiftOpTest<T>::test(0))>
{};

NS_LIBSPIRAL_END

#endif /* OperatorTraits_h */
