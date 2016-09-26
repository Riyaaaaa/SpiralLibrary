/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef ModalLayer_h
#define ModalLayer_h

#include "cocos2d.h"
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

class ModalLayer : public cocos2d::LayerColor {
public:
    CREATE_FUNC(ModalLayer);
    bool init() override {
        
        if(!LayerColor::initWithColor(cocos2d::Color4B(0, 0, 0, 64))) {
            return false;
        }
        _listener = cocos2d::EventListenerTouchOneByOne::create();
        _listener->onTouchBegan = [=](cocos2d::Touch* t, cocos2d::Event* e){
            if(onTouchBegan) {
                return onTouchBegan(t, e);
            }
            return true;
        };
        _listener->onTouchEnded = [=](cocos2d::Touch* t, cocos2d::Event* e){
            if(onTouchEnded) {
                onTouchEnded(t, e);
            }
        };
        _listener->setSwallowTouches(true);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
        
        return true;
    }
    
    std::function<bool(cocos2d::Touch*, cocos2d::Event*)> onTouchBegan;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchEnded;
    
    CC_SYNTHESIZE(cocos2d::EventListenerTouchOneByOne*, _listener, Listener);
    
};

NS_LIBSPIRAL_END

#endif /* ModalLayer_h */
