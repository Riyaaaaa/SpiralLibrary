/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef StateMachine_hpp
#define StateMachine_hpp

#include "../Utility/TupleUtils.hpp"
#include <map>
#include <memory>
#include <type_traits>

#include "../Common/Macro.h"
NS_LIBSPIRAL_BEGIN

template <class ContextType>
class actionInterface;

template <class ContextType>
class actionInterface {
public:
    virtual void exe(const std::shared_ptr<ContextType>& context) = 0;
};

template <class ContextType>
class factoryInterface {
public:
    virtual std::shared_ptr<typename ContextType::state_t> create(const std::shared_ptr<ContextType>& context) = 0;
};

template<class ContextType, class State, bool hasDefaultConstructor, class... Args>
class _factoryDefault;

template<class ContextType, class State, class... Args>
using factoryDefault = _factoryDefault<ContextType, State, std::is_default_constructible<State>::value, Args...>;

template<class ContextType, class State, class... Args>
class _factoryDefault<ContextType, State, true, Args...> : public factoryInterface<ContextType>{
public:
    std::shared_ptr<typename ContextType::state_t> create(const std::shared_ptr<ContextType>& context) {
        return std::make_shared<State>();
    }
};

template<class ContextType, class State, class... Args>
class _factoryDefault<ContextType, State, false, Args...> : public factoryInterface<ContextType>{
public:
    _factoryDefault(Args... args) : _arguments(std::tie(args...)){}
    std::shared_ptr<typename ContextType::state_t> create(const std::shared_ptr<ContextType>& context) {
        return libspiral::tupleVariadicApply(static_cast<std::shared_ptr<State> (&)(Args&...)>(std::make_shared<State>), _arguments);
    }
    std::tuple<Args...> _arguments;
};

template<class Enumration>
class EventBase {
public:
    EventBase(Enumration value) : _value(value) {}
    
    bool operator==(EventBase const& lhs)const;
    bool operator<(EventBase const& lhs)const;
    
private:
    Enumration _value;
};

template<class Enumration>
bool EventBase<Enumration>::operator==(EventBase const& lhs)const{
    return _value == lhs._value;
}

template<class Enumration>
bool EventBase<Enumration>::operator<(EventBase const& lhs)const{
    return _value < lhs._value;
}

template < class ContextType, class Event >
class HFStateBase : public std::enable_shared_from_this<HFStateBase<ContextType, Event>>
{
public:
    typedef ContextType context_t;
    typedef HFStateBase state_t;
    typedef actionInterface<ContextType> action_t;
    typedef factoryInterface<ContextType> factory_t;
    typedef std::map<Event, std::shared_ptr<factory_t>> transition_map;
    typedef std::map<Event, std::shared_ptr<action_t>> action_map;
    
    HFStateBase(){}
    virtual ~HFStateBase() = default;
    
    virtual void entry(const std::shared_ptr<ContextType>& context){
        setContext(context);
    }
    
    virtual void exit(const std::shared_ptr<ContextType>& context){}
    
    virtual std::shared_ptr<HFStateBase> update(float deltaTime) {
        if(_next) {
            return _next;
        }
        return this->shared_from_this();
    }
    
    void setContext(const std::shared_ptr<context_t>& context) {
        _context = context;
    }
    
    std::weak_ptr<context_t> getContext() {
        return _context;
    }
    
    void setNext(const std::shared_ptr<state_t>& state) {
        _next = state;
    }
    
    void addTransition(const Event& e, factory_t* factory) {
        _transition.insert(std::make_pair(e, std::shared_ptr<factory_t>(factory)));
    }
    
    void addAction(const Event& e, action_t* act) {
        _action.insert( std::make_pair(e, std::shared_ptr<action_t>(act)) );
    }
    
    bool processEvent(const Event& e) {
        auto itAction = _action.find(e);
        auto itTrans = _transition.find(e);
        
        if(itAction == _action.end() && itTrans == _transition.end()) {
            return false;
        }
        
        if(itAction != _action.end()) {
            itAction->second->exe(_context.lock());
        }
        if(itTrans != _transition.end()) {
            _next =  itTrans->second->create(_context.lock());
        }
        return true;
    }

protected:
    std::shared_ptr<state_t> _next;
    std::weak_ptr<context_t> _context;
    transition_map _transition;
    action_map _action;
    
};

NS_LIBSPIRAL_END


#endif /* StateMachine_hpp */
