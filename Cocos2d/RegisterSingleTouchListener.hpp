//
//  RegisterSingleTouchListener.hpp
//  NekoShiwake
//
//  Created by Atsumu Ono on 2016/09/27.
//
//

#ifndef RegisterSingleTouchListener_h
#define RegisterSingleTouchListener_h

#include "cocos2d.h"
#include "../Common/Macro.h"
#include "../type_traits/Identity.hpp"
#include <type_traits>

NS_LIBSPIRAL_BEGIN

namespace detail {

template<class T>
struct hasMovedTest {
    template<typename U = T, typename = Identity_t<decltype(std::declval<U>().onTouchMoved(nullptr, nullptr))>>
    static std::true_type test(int);
    static std::false_type test(...);
};

template<class T>
struct hasEndedTest {
    template<typename U = T, typename = Identity_t<decltype(std::declval<U>().onTouchEnded(nullptr, nullptr))>>
    static std::true_type test(int);
    static std::false_type test(...);
};

template<class T>
struct hasCancelledTest {
    template<typename U = T, typename = Identity_t<decltype(std::declval<U>().onTouchCancelled(nullptr, nullptr))>>
    static std::true_type test(int);
    static std::false_type test(...);
};

}

template<class T>
struct RegisterSingleTouchListener {
    
    static cocos2d::EventListenerTouchOneByOne* registerListener(T* target) {
        auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(T::onTouchBegan, target);
        registerMoved(listener, target);
        registerEnded(listener, target);
        registerCancelled(listener, target);
        target->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, target);
        
        return listener;
    }
    
    template<class U = T, typename = typename std::enable_if<Identity_t<decltype(detail::hasMovedTest<U>::test(0))>::value >::type>
    static void registerMoved(cocos2d::EventListenerTouchOneByOne* listener, T* target) {
        listener->onTouchMoved = CC_CALLBACK_2(U::onTouchMoved, target);
    }
    
    static void registerMoved(...) {}
    
    template<class U = T, typename = typename std::enable_if<Identity_t<decltype(detail::hasEndedTest<U>::test(0))>::value >::type>
    static void registerEnded(cocos2d::EventListenerTouchOneByOne* listener, T* target) {
        listener->onTouchEnded = CC_CALLBACK_2(U::onTouchEnded, target);
    }
    
    static void registerEnded(...) {}
    
    template<class U = T, typename = typename std::enable_if<Identity_t<decltype(detail::hasCancelledTest<U>::test(0))>::value >::type>
    static void registerCancelled(cocos2d::EventListenerTouchOneByOne* listener, T* target) {
        listener->onTouchEnded = CC_CALLBACK_2(U::onTouchEnded, target);
    }
    
    static void registerCancelled(...) {}
    
    
};

NS_LIBSPIRAL_END

#endif /* RegisterSingleTouchListener_h */
