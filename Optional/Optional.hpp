/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Optional_h
#define Optional_h

#include "../Common/Macro.h"
#include "../Memory/AddressOf.hpp"
#include "../Utility/Forward.hpp"
#include "../TypeTraits/Enabler.hpp"
#include "OptionalExcept.hpp"
#include <utility>
#include <type_traits>

NS_LIBSPIRAL_BEGIN

struct nullopt_t {};

namespace detail {
    
    template<typename T>
    class optional_base {
    protected:
        typedef T value_type;
        
        optional_base() : _value_ptr(nullptr) {}
        
        optional_base(optional_base const& other) :
        _value_ptr(other ? new(addressOf(_storage)) value_type(*other) : nullptr) {}
        
        explicit optional_base(value_type const& value) :
        _value_ptr(new(addressOf(_storage)) value_type(value)) {}
        
        ~optional_base() {
            if(_value_ptr) {
                destroy();
            }
        }
        
        bool isInitialized() const {
            return !(_value_ptr == nullptr);
        }
        
        void destroy() {
            destroy_impl(0);
        }
        
        void construct(const optional_base& arg) {
            _value_ptr = new(addressOf(_storage)) value_type(arg);
        }
        
        void construct(optional_base&& arg) {
            _value_ptr = new(addressOf(_storage)) value_type(std::move(arg));
        }
        
        template<typename... Args>
        void construct(Args&&... args) {
            _value_ptr = new(addressOf(_storage)) value_type(libspiral::forward<Args&&>(args)...);
        }
        
        void assign (const value_type& val )
        {
            if (isInitialized()) {
                assign_value(val);
            }
            else {
                construct(val);
            }
        }
        
        void assign (value_type&& val )
        {
            if (_value_ptr)
                assign_value(std::move(val));
            else construct(std::move(val));
        }
        
        void assign (nullopt_t) {
            destroy();
        }
        
        void assign_value (const value_type& val ) {
            get() = val;
        }

        void assign_value (value_type&& val ) {
            get() = std::move(val);
        }
        
        template<class... Args>
        void emplace_assign (Args&&... args)
        {
            destroy();
            _value_ptr = new (addressOf(_storage)) value_type(forward<Args>(args)...);
        }
        
        void assign(const optional_base& rhs) {
            if (isInitialized())
            {
                if (rhs.isInitialized()) {
                    assign_value(rhs.get());
                }
                else destroy();
            }
            else
            {
                if (rhs.isInitialized()) {
                    construct(rhs.get());
                }
            }
        }
        
        void assign(optional_base&& rhs) {
            if (isInitialized())
            {
                if (rhs.isInitialized()) {
                    assign_value(std::move(rhs.get()));
                }
                else destroy();
            }
            else
            {
                if (rhs.isInitialized()) {
                    construct(std::move(rhs.get()));
                }
            }
        }
        
        value_type* getPtr() {
            return _value_ptr;
        }
        
        const value_type* getPtr() const {
            return _value_ptr;
        }
        
        value_type& get() {
			return *_value_ptr;
        }
        
        const value_type& get() const {
			return *_value_ptr;
        }
        
    private:
        template<class U = T, typename = enable_when_t<std::is_trivially_destructible<U>{}>>
        void destroy_impl(int) {
            _value_ptr = nullptr;
        }
        
        void destroy_impl(...) {
            _value_ptr->~value_type();
            _value_ptr = nullptr;
        }
        
        value_type* _value_ptr;
        typename std::aligned_storage<sizeof(value_type)>::type _storage;
    };
    
}

template<class T>
class Optional : public detail::optional_base<T>
{
    typedef detail::optional_base<T> base;
    
public:
    typedef Optional<T> this_type;
    typedef typename base::value_type value_type;

    
    Optional() SPIRAL_NOEXCEPT : base() {}
    Optional(nullopt_t) SPIRAL_NOEXCEPT : base() {}
    ~Optional() = default;
    
    Optional (const Optional& rhs) {
        *this = rhs;
    }
    
    Optional (Optional&& rhs) {
        base::assign(std::move(rhs));
    }
    
    Optional (const value_type& val) {
        base::assign(val);
    }
    
    Optional (value_type&& val) {
        base::assign(std::move(val));
    }
    
    void reset() {
        if(base::isInitialized()) {
            base::destroy();
        }
    }
    
    template<class... Args>
    void emplace (Args&&... args)
    {
        this->emplace_assign( forward<Args>(args)... );
    }
    
    void emplace ()
    {
        this->emplace_assign();
    }

    void swap(Optional& rhs) SPIRAL_NOEXCEPT_IF(std::is_nothrow_move_constructible<T>::value && noexcept(std::swap(std::declval<T&>(), std::declval<T&>())))
    {
        if(base::isInitialized() && !rhs.isInitialized()) {
            rhs.construct(std::move(value()));
            base::destroy();
        }
        else if(!base::isInitialized() && rhs.isInitialized()) {
            base::construct(std::move(rhs.value()));
            rhs.reset();
        }
        else if (base::isInitialized()  && rhs.isInitialized())  {
            std::swap(*this, rhs);
        }
   }

    explicit operator bool() const SPIRAL_NOEXCEPT { return base::isInitialized(); }
    bool operator!() const SPIRAL_NOEXCEPT { return !base::isInitialized(); }
    
    const T* operator ->() const {
        if(base::isInitialized()) {
            return base::getPtr();
        }
        throw bad_optional_access("optional bad access");
    }
    
    T* operator ->() {
        if(base::isInitialized()) {
            return base::getPtr();
        }
        throw bad_optional_access("optional bad access");
    }
    
    Optional& operator=(nullopt_t none) noexcept
    {
        base::assign(none);
        return *this;
    }
    
    Optional& operator=(Optional const& other) {
        base::assign(other);
        return *this;
    }
    
    Optional& operator=(Optional && other) {
        base::assign(std::move(other));
        return *this;
    }
    
    Optional& operator=(value_type const& value) {
        base::assign(value);
        return *this;
    }
    
    Optional& operator=(value_type&& value) {
        base::assign(std::move(value));
        return *this;
    }
    
    template<class U, typename = enable_null_t<std::is_convertible<value_type, U>{}>>
    Optional& operator=(U&& rhs) noexcept
    {
        base::assign(std::move(static_cast<T>(value)));
        return *this;
    }
    
    value_type const& operator*() const {
        if(base::isInitialized()) {
            return base::get();
        }
        throw bad_optional_access("optional bad access");
    }
    
    value_type& operator*() {
        return const_cast<value_type&>(*const_cast<Optional const&>(*this));
    }

    value_type* operator&() {
        return this->getPtr();
    }
    
    const value_type& value() const&
    {
        return base::isInitialized() ? base::get() : throw bad_optional_access("optional bad access");
    }

	value_type& value() &
	{
		return base::isInitialized() ? base::get() : throw bad_optional_access("optional bad access");
	}

	value_type&& value() &&
	{
		return base::isInitialized() ? base::get() : throw bad_optional_access("optional bad access");
	}
    
    template <class V>
    value_type value_or(V&& v) const&
    {
        return base::isInitialized() ? base::get() : static_cast<T>(forward<V>(v));
    }
    
};

template<class T>
class Optional<T&&>;

template<class T>
inline Optional<T> makeOptional ( T const& v  ) {
    return Optional<T>(v);
}

NS_LIBSPIRAL_END
    
    
#endif /* Optional_h */
