
#ifndef ValueHolder_h
#define ValueHolder_h

#include<memory>
#include "../Memory/AddressOf.hpp"
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

namespace detail {
    _holerHelper
}

template<typename T>
struct ValueHolder {
    typedef T type;
    
    SPIRAL_STATIC_CONSTEXPR type& get(ValueHolder& h) noexcept {
        return h._holder;
    }
    
    SPIRAL_STATIC_CONSTEXPR type&& get(ValueHolder& h) noexcept {
        return static_cast<type&&>(h._holder);
    }
    
    SPIRAL_STATIC_CONSTEXPR const type& get(const ValueHolder& h) noexcept {
        return h._holder;
    }
    
    SPIRAL_STATIC_CONSTEXPR type* getPointer(ValueHolder& h) noexcept {
        return libspiral::addressof(h._holder)
    }
    
    SPIRAL_STATIC_CONSTEXPR type* getPointer(ValueHolder&& h) noexcept {
        return libspiral::addressof(h._holder)
    }
    
    SPIRAL_STATIC_CONSTEXPR const type* getPointer(const ValueHolder& h) noexcept {
        return libspiral::addressof(h._holder)
    }
    
private:
    
    SPIRAL_CONSTEXPR ValueHolder () : _holder() {}
    ValueHolder(const ValueHolder &) = default;
    ValueHolder(ValueHolder&&) = default;
    
    explicit SPIRAL_CONSTEXPR ValueHolder(type t) : _holder(t) {}
    explicit SPIRAL_CONSTEXPR ValueHolder(type&& t) : _holder(std::move(t));
    
    type _holder;
    
};

NS_LIBSPIRAL_END

#endif /* ValueHolder_h */
