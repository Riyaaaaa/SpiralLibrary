/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Any_h
#define Any_h

#include "../Common/Macro.h"
#include "../TypeTraits/StdTraitsAlias.hpp"
#include "../Optional/Optional.hpp"
#include "../Memory/AddressOf.hpp"
#include <typeindex>
#include <utility>
#include <exception>

NS_LIBSPIRAL_BEGIN

namespace detail {
    class placeholder {
    public:
        virtual ~placeholder() = default;
        virtual const std::type_index type() const SPIRAL_NOEXCEPT = 0;
        virtual placeholder* clone() const = 0;
    };
    
    template<typename T>
    class holder : public placeholder {
    public:
        holder(const T& value)
        : _value(value){}
        
        holder(T&& value)
        : _value(static_cast< T&& >(value)){}
        
        virtual const std::type_index type() const SPIRAL_NOEXCEPT
        {
            return typeid(T);
        }
        
        virtual placeholder* clone() const
        {
            return new holder(_value);
        }

        T _value;
        
    private:
        holder& operator=(const holder &);
    };
}

class Any {
public:
    Any() : _value_ptr(nullptr) {}
    
    template<class T>
    Any(const T& value) : _value_ptr(new detail::holder<remove_cv_t<decay_t<T>>>(value)) {}
    
    template<class T>
    Any(T&& value) : _value_ptr(new detail::holder<decay_t<T>>(value)) {}
    
    Any(Any&& other) : _value_ptr(other._value_ptr) {}
    
    Any(const Any& other) : _value_ptr(other._value_ptr ? other._value_ptr->clone() : nullptr) {}
    
    ~Any() SPIRAL_NOEXCEPT {
        delete _value_ptr;
    }
    
    Any& swap(Any& rhs) {
        std::swap(_value_ptr, rhs._value_ptr);
        return *this;
    }
    
    Any& operator=(const Any& rhs) {
        Any(rhs).swap(*this);
        return *this;
    }
    
    Any& operator=(Any&& rhs) {
        rhs.swap(*this);
        Any().swap(rhs);
        return *this;
    }
    
    template<class T>
    Any& operator=(T&& rhs) {
        Any(static_cast<T&&>(rhs)).swap(*this);
    }
    
    explicit operator bool() const SPIRAL_NOEXCEPT { return _value_ptr; }
    bool operator!() const SPIRAL_NOEXCEPT { return !_value_ptr; }
    
    void reset() {
        this->~Any();
        _value_ptr = nullptr;
    }
    
    template<class T>
    void emplace(T&& arg) {
        if(_value_ptr) {
            delete _value_ptr;
        }
        _value_ptr = new detail::holder<decay_t<T>>(arg);
    }
    
    template<class T>
    friend T* any_cast(Any*);
    
private:
    detail::placeholder* _value_ptr;
};

template<class T>
T* any_cast(Any* operand) {
    return operand && operand->_value_ptr->type() == typeid(T) ? &static_cast<detail::holder<T>*>(operand->_value_ptr)->_value : nullptr;
}

template<class T>
const T* any_cast(const Any* operand) {
    return any_cast<T>(const_cast<Any*>(operand));
}

template<typename T>
T any_cast(Any & operand)
{
    typedef typename std::remove_reference<T>::type nonref;
    
    nonref * result = any_cast<nonref>(libspiral::addressOf(operand));
    if(!result)
        throw std::bad_cast();
    
    return static_cast<conditional_t<alias<T>::is_reference_v, T, T&>>(*result);
}

template<class T>
inline T any_cast(const Any & operand) SPIRAL_NOEXCEPT
{
    typedef typename std::remove_reference<T>::type nonref;
    return any_cast<const nonref &>(const_cast<Any &>(operand));
}

template<class T>
Optional<T> any_cast_noexp(Any& operand) {
    remove_cv_t<T>* result = any_cast<remove_cv_t<T>>(&operand);
    if(!result) {
        return nullopt_t{};
    }
    return makeOptional(static_cast<conditional_t<alias<T>::is_reference_v, T, T&>>(*result));
}

template<class T>
Optional<T> any_cast_noexp(const Any& operand) SPIRAL_NOEXCEPT {
    return any_cast_noexp<const remove_reference_t<T>&>(const_cast<remove_reference_t<T>&>(operand));
}

NS_LIBSPIRAL_END

#endif /* Any_h */
