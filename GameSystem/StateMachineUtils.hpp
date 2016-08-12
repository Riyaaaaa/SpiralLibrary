/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef StateMachineUtils_h
#define StateMachineUtils_h

#include "StateInterface.hpp"
#include "../Common/Macro.h"
NS_LIBSPIRAL_BEGIN

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

NS_LIBSPIRAL_END

#endif /* StateMachineUtils_h */
