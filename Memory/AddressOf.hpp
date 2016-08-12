/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef AddressOf_h
#define AddressOf_h

#include<memory>
#include "../type_traits/OperatorTraits.h"
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

namespace detail {

template<typename T>
typename std::enable_if< hasAddressOp<T>::value, T* >::type
_addressof_impl(T& t) noexcept {
return std::addressof(t);
}

template<typename T>
typename std::enable_if< !hasAddressOp<T>::value, T*>::type
_addressof_impl(T& t) noexcept {
return &t;
}

}

template<typename T>
SPIRAL_CONSTEXPR T* addressOf(T& t) noexcept {
    return detail::_addressof_impl(t);
}

NS_LIBSPIRAL_END

#endif /* AddressOf_h */
