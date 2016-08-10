//
//  HFStateMachine.hpp
//  GambleLand
//
//  Created by Atsumu Ono on 2016/04/25.
//
//

#ifndef HFStateMachine_hpp
#define HFStateMachine_hpp

#include "StateInterface.hpp"
#include "StateMachineUtils.hpp"
#include <memory>
#include <vector>
#include <map>
#include <algorithm>

#include "../Common/Macro.h"
NS_LIBSPIRAL_BEGIN

template <class ContextType, class Event>
class HFStateMachine : public std::enable_shared_from_this<HFStateMachine<ContextType, Event>>
{
public:
    typedef ContextType context_t;
    typedef HFStateBase<context_t, Event> state_t;
    typedef SMUtils<context_t, Event> Utils;
    typedef actionInterface<context_t> action_t;
    typedef factoryInterface<context_t> factory_t;
    friend std::shared_ptr<context_t>;
    
    static std::shared_ptr<context_t> create(state_t* firstState) {
        auto context = std::make_shared<context_t>(new typename Utils::start);
        context->changeState(std::shared_ptr<state_t>(firstState));
        return context;
    }
    
    void setParent(std::shared_ptr<context_t> parent) {
        _parent = parent;
    }
    
    void addChild(std::shared_ptr<context_t> child) {
        child->setParent(derived());
        _children.push_back(child);
    }
    
    std::weak_ptr<context_t>& getParent() {
        return _parent;
    }
    
    const std::vector<std::shared_ptr<context_t>>& getChildren() {
        return _children;
    }
    
    const std::shared_ptr<state_t>& getState() {
        return _current;
    }
    
    void removeFromParent() {
        for(auto &&child: _children) {
            child->removeFromParent();
        }
        if(!_parent.expired()) {
            _parent.lock()->removeChild(derived());
        }
    }
    
    void removeChild(std::shared_ptr<context_t> child) {
        auto removeIt = std::find(_children.begin(), _children.end(), child);
        if(removeIt != _children.end()) {
            _children.erase(removeIt);
        }
    }
    
    void removeChildren() {
        _children.clear();
    }
    
    void update(float deltaTime)
    {
        const auto& _next = _current->update(deltaTime);
        changeState(_next);
        for(auto &&child: _children) {
            child->update(deltaTime);
        }
    }
    
    void changeState(const std::shared_ptr<state_t>& destState)
    {
        if(!destState) {
            return;
        }
        
        if( _current == destState ) {
            return;
        }
        
        _current->exit();
        _current->setNext(nullptr);
        
        removeChildren();
        
        destState->setNext(destState);
        destState->setContext(derived());
        
        _current = destState;
        
        destState->entry(derived());
    }
    
    std::shared_ptr<ContextType> derived()
    {
        return std::static_pointer_cast<ContextType>(this->shared_from_this());
    }
    
    bool dispatchEvent(const Event& e) {
        bool isSwallowed = false;
        if(!_children.empty()){
            for(auto &&child: _children){
                isSwallowed |= child->dispatchEvent(e);
            }
        }
        if(!isSwallowed) {
            return _current->processEvent(e);
        }
        return false;
    }
    
    void end() {
        _current->setNext(new struct Utils::end);
    }
    
protected:
    std::shared_ptr<state_t> _current;
    std::weak_ptr<context_t> _parent;
    
    std::vector<std::shared_ptr<context_t>> _children;
    
    HFStateMachine(state_t* firstState)
    : _current(firstState)
    {
        
    }
    virtual ~HFStateMachine() {
        _current->exit();
    }
};

NS_LIBSPIRAL_END

#endif /* HFStateMachine_hpp */
