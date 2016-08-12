//
//  GameManagerBase.hpp
//  SlotMachine
//
//  Created by Atsumu Ono on 2016/04/07.
//
//

#ifndef GameManagerBase_hpp
#define GameManagerBase_hpp

#include "cocos2d.h"
#include "../GameSystem/SingletonBase.hpp"
#include "../Common/Macro.h"
NS_LIBSPIRAL_BEGIN

template<class Manager, class Scene_t>
class GameManagerBase : public SingletonBase<Manager>{
public:
    GameManagerBase() {
    }
    virtual ~GameManagerBase() = default;
    virtual void runScene();
    void onExitScene();
    virtual void update(float) {};
    
    Scene_t* getScene() {
        return _scene;
    }
    
protected:
    Scene_t* _scene;
};

template<class Manager, class Scene_t>
void GameManagerBase<Manager, Scene_t>::runScene() {
    _scene = Scene_t::createScene();
    
    _scene->setOnExitCallback(CC_CALLBACK_0(GameManagerBase<Manager, Scene_t>::onExitScene, this));
    
    auto scheduler = cocos2d::Director::getInstance()->getScheduler();
    scheduler->schedule(CC_CALLBACK_1(Manager::update, SingletonBase<Manager>::_singletonInstancePointer), this, 0.0f, false, "SCENE");
    
    cocos2d::Director::getInstance()->replaceScene(_scene);
}

template<class Manager, class Scene_t>
void GameManagerBase<Manager, Scene_t>::onExitScene() {
    _scene = nullptr;
    auto scheduler = cocos2d::Director::getInstance()->getScheduler();
    scheduler->unscheduleAllForTarget(this);
    Manager::destroyInstance();
}

NS_LIBSPIRAL_END

#endif /* GameManagerBase_hpp */
