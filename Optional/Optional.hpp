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
#include "../type_traits/Enabler.hpp"
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
        
        bool isInitialized() {
            return !(_value_ptr == nullptr);
        }
        
        void destroy() {
            destroy_impl(0);
        }
        
        void construct(optional_base& arg) {
            _value_ptr = new(addressOf(_storage)) value_type(arg);
        }
        
        void construct(optional_base&& arg) {
            _value_ptr = new(addressOf(_storage)) value_type(std::move(arg));
        }
        
        template<typename... Args>
        void construct(Args&&... args) {
            _value_ptr = new(addressOf(_storage)) value_type(forward<Args>(args)...);
        }
        
        void assign (value_type& val )
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
            new (addressOf(_storage)) value_type(forward<Args>(args)...);
        }
        
        void assign(optional_base& rhs) {
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
            return const_cast<value_type&>(*_value_ptr);
        }
        
        const value_type& get() const {
            return *_value_ptr;
        }
        
    private:
        template<class U = T, typename = enable_when_t<std::is_trivially_destructible<U>{}>>
        void destroy_impl() {
            _value_ptr->~value_type();
            _value_ptr = nullptr;
        }
        
        void destroy_impl(...) {
            _value_ptr = nullptr;
        }
        
        value_type* _value_ptr;
        typename std::aligned_storage<sizeof(value_type)>::type _storage;
    };
    
}

template<class T>
class optional : public detail::optional_base<T>
{
    typedef detail::optional_base<T> base;
    
public:
    typedef optional<T> this_type;
    typedef typename base::value_type value_type;

    
    optional() SPIRAL_NOEXCEPT : base() {}
    optional(nullopt_t) SPIRAL_NOEXCEPT : base() {}
    ~optional() = default;
    
    optional (const optional& rhs) {
        *this = rhs;
    }
    
    optional (const optional&& rhs) : base( forward<T>(rhs) )
    {}
    
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

    void swap(optional& rhs) SPIRAL_NOEXCEPT_IF(std::is_nothrow_move_constructible<T>::value && noexcept(std::swap(std::declval<T&>(), std::declval<T&>())))
    {
        if(base::isInitialized() && !base::isInitialized()) {
            rhs.construct(std::move(*this));
            base::destroy();
        }
        else if(!base::isInitialized() && rhs.isInitialized()) {
            construct(std::move(rhs));
            rhs.clear();
        }
        else if (base::isInitialized()  && rhs.isInitialized())  {
            std::swap(*this, rhs);
        }
   }

    explicit operator bool() const SPIRAL_NOEXCEPT { return base::isInitialized(); }
    bool operator!() const SPIRAL_NOEXCEPT { return !base::isInitialized(); }
    
    T operator ->() const {
        if(base::isInitialized) {
            return base::getPtr();
        }
        throw bad_optional_access("optional bad access");
    }
    
    optional& operator=(nullopt_t none) noexcept
    {
        base::assign(none);
        return *this;
    }
    
    optional& operator=(optional const& other) {
        base::assign(other);
        return *this;
    }
    
    optional& operator=(optional && other) {
        base::assign(std::move(other));
        return *this;
    }
    
    optional& operator=(value_type const& value) {
        base::assign(value);
        return *this;
    }
    
    optional& operator=(value_type&& value) {
        base::assign(std::move(value));
        return *this;
    }
    
    template<class U, typename = enable_null_t<std::is_convertible<value_type, U>{}>>
    optional& operator=(U&& rhs) noexcept
    {
        base::assign(std::move(static_cast<T>(value)));
        return *this;
    }
    
    value_type const& operator*() const {
        if(base::isInitialized) {
            return base::get();
        }
        throw bad_optional_access("optional bad access");
    }
    
    value_type& operator*() {
        return const_cast<value_type&>(*const_cast<optional const&>(*this));
    }
    
    value_type value() const&
    {
        return base::isInitialized ? base::get() : throw bad_optional_access("optional bad access");
    }
    
    template <class V>
    value_type value_or(V&& v) const&
    {
        return base::isInitialized ? base::get() : static_cast<T>(forward<V>(v));
    }
    
};

template<class T>
class optional<T&&>;

template<class T>
inline optional<T> make_optional ( T const& v  )
{
    return optional<T>(v);
}

NS_LIBSPIRAL_END
    
    
#endif /* Optional_h */
