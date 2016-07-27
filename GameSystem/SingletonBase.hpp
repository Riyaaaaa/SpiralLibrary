//
//  SingletonBase.hpp
//  GambleLand
//
//  Created by Toshiki Suizu on 2016/04/13.
//
//

#ifndef SingletonBase_hpp
#define SingletonBase_hpp

template<class Extend>
class SingletonBase{
public:
    static Extend* _singletonInstancePointer;
    
    static Extend* getInstance() {
        if(!_singletonInstancePointer) {
            _singletonInstancePointer = new Extend;
        }
        return _singletonInstancePointer;
    };
    
    static void destroyInstance() {
        if(_singletonInstancePointer) {
            delete _singletonInstancePointer;
            _singletonInstancePointer = nullptr;
        }
    }
    
protected:
    
    SingletonBase()=default;
    SingletonBase(const SingletonBase& rhs)=default;

    virtual ~SingletonBase(){}
    

private:
};

template<class Extend>
Extend* SingletonBase<Extend>::_singletonInstancePointer = nullptr;




#endif /* SingletonBase_hpp */
