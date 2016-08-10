//
//  SingletonBase.hpp
//  GambleLand
//
//  Created by Toshiki Suizu on 2016/04/13.
//
//

#ifndef SingletonBase_hpp
#define SingletonBase_hpp

#include "../Common/Macro.h"
NS_LIBSPIRAL_BEGIN

template<class Extend>
class Destroyer {
public:
    Destroyer() : _deleteTarget(nullptr) {}
    
    void setObject(Extend* ptr) {
        _deleteTarget = ptr;
    }
    
    void removeObject() {
        _deleteTarget = nullptr;
    }
    
    ~Destroyer() {
        if(_deleteTarget) {
            delete _deleteTarget;
        }
    }
private:
    Extend* _deleteTarget;
};

template<class Extend>
class SingletonBase{
public:
    static Extend* _singletonInstancePointer;
    
    static Extend* getInstance() {
        if(!_singletonInstancePointer) {
            _singletonInstancePointer = new Extend;
            _destroyer.setObject(_singletonInstancePointer);
        }
        return _singletonInstancePointer;
    };
    
    static void destroyInstance() {
        if(_singletonInstancePointer) {
            delete _singletonInstancePointer;
            _singletonInstancePointer = nullptr;
            _destroyer.removeObject();
        }
    }
    
protected:
    SingletonBase() = default;
    SingletonBase(const SingletonBase& rhs)=default;
    virtual ~SingletonBase() {}

private:
    static Destroyer<Extend> _destroyer;
};

template<class Extend>
Extend* SingletonBase<Extend>::_singletonInstancePointer = nullptr;

template<class Extend>
Destroyer<Extend> SingletonBase<Extend>::_destroyer;


NS_LIBSPIRAL_END

#endif /* SingletonBase_hpp */
