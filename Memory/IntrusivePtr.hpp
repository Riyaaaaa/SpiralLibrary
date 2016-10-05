/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/


#ifndef intrusive_ptr_h
#define intrusive_ptr_h

#include "../Common/Macro.h"
#include "../Concept/Concept.hpp"
#include "../TypeTraits/Enabler.hpp"
#include "../TypeTraits/StdTraitsAlias.hpp"
#include "../Common/NoExpAssign.hpp"

NS_LIBSPIRAL_BEGIN

template<class T>
class IntrusivePtr {
    SPIRAL_CLASS_REQUIRE(T, libspiral::concept, CanSafeAllocatable);
    
public:
    
    IntrusivePtr() SPIRAL_NOEXCEPT : _ptr(nullptr) {}
    IntrusivePtr(T* ptr) : _ptr(ptr) {
        if(_ptr) {
            _ptr->addRef();
        }
    }
    IntrusivePtr(const IntrusivePtr& rhs) : _ptr(rhs.get()) {
        if(_ptr) {
            _ptr->addRef();
        }
    }
    template<class U, enable_null_t<alias<U, T>::convertible_v> = nullptr>
    IntrusivePtr(const IntrusivePtr<U>& rhs) : _ptr(rhs.get()) {
        if(_ptr) {
            _ptr->addRef();
        }
    }
    ~IntrusivePtr() {
        if(_ptr) {
            _ptr->release();
        }
    }
    IntrusivePtr(IntrusivePtr&& rhs) SPIRAL_NOEXCEPT : _ptr(rhs.get()){
        rhs._ptr = nullptr;
    }
    
    IntrusivePtr& operator=(const IntrusivePtr& rhs) {
        NOEXP_ASSIGN(IntrusivePtr);
        return *this;
    }
    
    template<class U, enable_null_t<alias<U, T>::convertible_v> = nullptr>
    IntrusivePtr& operator=(const IntrusivePtr<U>& rhs) {
        NOEXP_ASSIGN(IntrusivePtr);
        return *this;
    }
    
    IntrusivePtr& operator=(IntrusivePtr&& rhs) SPIRAL_NOEXCEPT {
        IntrusivePtr(static_cast<IntrusivePtr&&>(rhs)).swap(*this);
        return *this;
    }
    
    IntrusivePtr& operator=(T* rhs) {
        NOEXP_ASSIGN(IntrusivePtr);
        return *this;
    }
    
    void reset() SPIRAL_NOEXCEPT {
        if(_ptr) {
            _ptr->release();
        }
    }
    
    void reset(T* rhs) {
        NOEXP_ASSIGN(IntrusivePtr);
    }
    
    T* get() {
        return _ptr;
    }
    
    T& operator*() const {
        assert(_ptr);
        return *_ptr;
    }
    
    T* operator->() const {
        assert(_ptr);
        return _ptr;
    }
    
    explicit operator bool() const SPIRAL_NOEXCEPT {
        return _ptr;
    }
    
    bool operator!() const SPIRAL_NOEXCEPT {
        return !_ptr;
    }
    
    void swap(IntrusivePtr& rhs) SPIRAL_NOEXCEPT {
        T* tmp = _ptr;
        _ptr = rhs.get();
        rhs._ptr = tmp;
    }
    
private:
    T* _ptr;
};

NS_LIBSPIRAL_END

#endif /* intrusive_ptr_h */
