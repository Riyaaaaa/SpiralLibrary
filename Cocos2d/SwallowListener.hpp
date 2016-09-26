/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef SwallowListener_h
#define SwallowListener_h


#include "cocos2d.h"
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

class SwallowListener : public cocos2d::EventListenerTouchOneByOne {
public:
    CREATE_FUNC(SwallowListener);
    bool init() {
        if(!EventListenerTouchOneByOne::init()) {
            return false;
        }
        onTouchBegan = [](cocos2d::Touch*, cocos2d::Event*) {
            return true;
        };
        setSwallowTouches(true);
        return true;
    }
};

NS_LIBSPIRAL_END


#endif /* SwallowListener_h */
