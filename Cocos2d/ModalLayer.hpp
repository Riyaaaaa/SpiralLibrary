//
//  ModalLayer.h
//  NekoShiwake
//
//  Created by Atsumu Ono on 2016/08/17.
//
//

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
        auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [=](cocos2d::Touch* t, cocos2d::Event* e){
            if(onTouchBegan) {
                return onTouchBegan(t, e);
            }
            return true;
        };
        listener->onTouchEnded = [=](cocos2d::Touch* t, cocos2d::Event* e){
            if(onTouchEnded) {
                onTouchEnded(t, e);
            }
        };
        listener->setSwallowTouches(true);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
        return true;
    }
    
    std::function<bool(cocos2d::Touch*, cocos2d::Event*)> onTouchBegan;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchEnded;
private:
};

NS_LIBSPIRAL_END

#endif /* ModalLayer_h */
