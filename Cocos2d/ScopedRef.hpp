
//
//  ScopedRef.h
//  NekoShiwake
//
//  Created by Atsumu Ono on 2016/09/21.
//
//

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
        _ref->release();
    }
    
private:
    T* _ref;
};

NS_LIBSPIRAL_END

#endif /* ScopedRef_h */
