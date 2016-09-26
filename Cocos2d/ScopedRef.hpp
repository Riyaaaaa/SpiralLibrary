/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef ScopedRef_h
#define ScopedRef_h

#include "../Common/Macro.h"
#include "../Memory/MemoryUtils.hpp"
#include <memory>

NS_LIBSPIRAL_BEGIN

template<class T>
class ScopedRef;

template<class T>
class ScopedRef {
    ScopedRef(const ScopedRef&) = delete;
public:
    operator T*() const {
        return _ref;
    }
    
    ScopedRef()
    :_ref(nullptr) {
        
    }
    
    template<class... Args>
    void setRef(Args&&... args) {
        _ref = T::create(std::forward<Args>(args)...);
        _ref->retain();
    }
    
    ~ScopedRef() {
        if(_ref) {
            _ref->release();
        }
    }
    
private:
    T* _ref;
};

NS_LIBSPIRAL_END

#endif /* ScopedRef_h */
