/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef ClassAttribute_h
#define ClassAttribute_h

#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

namespace attribute {
    
    class Noncopyable {
    protected:
        SPIRAL_CONSTEXPR Noncopyable() = default;
        ~Noncopyable() = default;
        
        Noncopyable(const Noncopyable&) = delete;
        Noncopyable& operator=(const Noncopyable&) = delete;
    };
    
    class Nonassignable {
    protected:
        Nonassignable& operator= (const Nonassignable& other) = delete;
        Nonassignable& operator= (Nonassignable other) = delete;
    };
    
}

NS_LIBSPIRAL_END

#endif /* ClassAttribute_h */
