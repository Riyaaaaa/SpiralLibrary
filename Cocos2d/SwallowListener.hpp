//
//  SwallowListener.hpp
//  NekoShiwake
//
//  Created by Atsumu Ono on 2016/08/23.
//
//

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
