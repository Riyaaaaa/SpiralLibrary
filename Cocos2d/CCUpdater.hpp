/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef CocosUpdater_h
#define CocosUpdater_h

#include "cocos2d.h"
#include "../Common/Macro.h"
NS_LIBSPIRAL_BEGIN

class CCUpdater {
public:
    template<class T>
    static void scheduleStart(T* target, const std::string& key = "CCUpdater") {
        scheduleStart(target, CC_CALLBACK_1(T::update, target), key);
    }
    static void scheduleStart(void* target, std::function<void(float)> func, const std::string& key = "CCUpdater") {
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule(func, target, 0.0f, false, key);
    }
    static void scheduleStartInterval(void* target, std::function<void(float)> func, float interval, const std::string& key = "CCUpdater") {
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule(func, target, interval, CC_REPEAT_FOREVER, 0.0f, false, key);
    }
    static void scheduleOnce(void* target, std::function<void(float)> func, float delay, const std::string& key = "CCUpdater") {
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule(func, target, 0, 0, delay, false, key);
    }
    static void scheduleStop(void* target, const std::string& key = "CCUpdater") {
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->unschedule(key, target);
    }
};

NS_LIBSPIRAL_END

#endif /* CocosUpdater_h */
