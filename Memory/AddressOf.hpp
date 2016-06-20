
#ifndef AddressOf_h
#define AddressOf_h

#include<memory>
#include "../Common/Macro.h"

NS_SPIRAL_BEGIN

namespace detail {

template<typename T>
typename std::enable_if< libspiral::hasAddressOp<T>::value, T* >::type
_addressof_impl(T& t) noexcept {
return std::addressof(t);
}

template<typename T> typename std::enable_if< !libspiral::hasAddressOp<T>::value, T*>::type
_addressof_impl(T& t) noexcept {
return &t;
}

}

template<typename T>
SPIRAL_CONSTEXPR addressOf(T& t) noexcept {
    return detail::_addressof_impl(t);
}

NS_SPIRAL_END

#endif /* AddressOf_h */
