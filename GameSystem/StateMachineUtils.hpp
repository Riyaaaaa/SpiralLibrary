//
//  Header.h
//  DHU_pvp
//
//  Created by Atsumu Ono on 2016/05/20.
//
//

#ifndef StateMachineUtils_h
#define StateMachineUtils_h

#include "StateInterface.hpp"

template<class context_t, class event_t>
struct SMUtils {
    typedef actionInterface<context_t> action_t;
    typedef HFStateBase<context_t, event_t> state_t;
public:
    struct releaseChildMachines : public action_t {
        void exe(const std::shared_ptr<context_t>& context) {
            context->removeChildren();
        }
    };
    
    struct start : public state_t {
        
    };
    
    struct end : public state_t{
        void entry(const std::shared_ptr<context_t>& context) override{
            context->removeChildren();
            context->removeFromParent();
        }
    };
};

#endif /* StateMachineUtils_h */
