//
//  SignalSlots.hpp
//  SpiralLibDevelop
//
//  Created by Atsumu Ono on 2016/10/07.
//  Copyright © 2016年 Atsumu Ono. All rights reserved.
//

#ifndef SignalSlots_h
#define SignalSlots_h

#include "../Common/Macro.h"
#include <vector>
#include <functional>
#include <algorithm>


NS_LIBSPIRAL_BEGIN

template<class Signature>
class Connection {
public:
    Connection(const std::function<Signature>& _f) : _slot(_f) {
        
    }
    
    template<class ... Args>
    typename std::function<Signature>::result_type operator()(Args&&... args) {
        return _slot(std::forward<Args>(args)...);
    }
    
    bool isLocked() { return lock; }
    
private:
    std::function<Signature> _slot;
    int key;
    bool lock{false};
};

template<class Signature>
class Signal {
public:
    struct FRONT{}front;
    struct BACK{}back;
    struct ORDERED{}ordered;
    
    Connection<Signature> connect(const std::function<Signature>& _f, FRONT) {
        auto connection = Connection<Signature>(_f);
        frontSlots.push_back(connection);
        return connection;
    }
    
    Connection<Signature> connect(const std::function<Signature>& _f, BACK) {
        auto connection = Connection<Signature>(_f);
        backSlots.push_back(connection);
        return connection;
    }
    
    Connection<Signature> connect(const std::function<Signature>& _f, ORDERED, int order) {
        auto connection = Connection<Signature>(_f);
        orderedSlots.push_back(connection);
        return connection;
        std::sort(ALL_RANGE(orderedSlots), [](const Connection<Signature>& lhs, const Connection<Signature>& rhs){ lhs.key < rhs.key; });
    }
    
    template<class... Args>
    void operator()(Args&&... args) {
        for(auto && f : frontSlots) {
            if(!f.isLocked) {
                f(libspiral::forward<Args>(args)...);
            }
        }
        for(auto && f : orderedSlots) {
            if(!f.isLocked) {
                f(libspiral::forward<Args>(args)...);
            }
        }
        for(auto && f : backSlots) {
            if(!f.isLocked) {
                f(libspiral::forward<Args>(args)...);
            }
        }
    }
    
private:
    std::vector<Connection<Signature>> frontSlots;
    std::vector<Connection<Signature>> orderedSlots;
    std::vector<Connection<Signature>> backSlots;
};

NS_LIBSPIRAL_END

#endif /* SignalSlots_h */
