//
//  MultiArray.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/07/15.
//
//

#ifndef MultiArray_h
#define MultiArray_h

#include <utility>
#include "../Structure/MultiIndex.h"
#include "../Common/Stream.hpp"

NS_LIBSPIRAL_BEGIN

template<class T, size_t... Dims>
class MultiArray {
public:
    typedef T  value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type  child;
    const std::size_t RANK = 0;
    value_type _value;
public:
    
    SPIRAL_CXX14_CONSTEXPR iterator begin() {
        return &_value;
    }
    SPIRAL_CXX14_CONSTEXPR iterator end() {
        return &(_value + 1);
    }
    
    SPIRAL_CONSTEXPR const_iterator begin() const {
        return &_value;
    }
    
    SPIRAL_CONSTEXPR const_iterator end() const {
        return &(_value + 1);
    }
    
    value_type& operator=(const value_type& rhs){
        _value = rhs;
        return _value;
    }
    operator value_type&(){
        return _value;
    }
    
    template<size_t ORIGIN_RANK>
    value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) {
        return _value;
    }
    
    template<size_t ORIGIN_RANK>
    const value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) const {
        return _value;
    }
};

template<class T, size_t First, size_t... Dims>
class MultiArray<T, First, Dims...>{
public:
    typedef T  value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef MultiArray<value_type, Dims...> child;
    
public:
    static constexpr size_t Rank = sizeof...(Dims) + 1;
    child _array[First];
    
public:
    
    SPIRAL_CXX14_CONSTEXPR iterator begin() {
        return _array[0].begin();
    }
    
    SPIRAL_CXX14_CONSTEXPR iterator end() {
        return _array[First].begin();
    }
    
    SPIRAL_CONSTEXPR const_iterator begin() const {
        return _array[0].begin();
    }
    
    SPIRAL_CONSTEXPR const_iterator end() const {
        return _array[First].begin();
    }
    
    child& operator[](const size_t& index){
        return _array[index];
    }
    
    const child& operator[](const size_t& index) const {
        return _array[index];
    }
    
    template<size_t ORIGIN_RANK>
    value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) {
        return _array[get<Rank - 1>(indexes)][indexes];
    }
    
    template<size_t ORIGIN_RANK>
    const value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) const {
        return _array[get<Rank - 1>(indexes)][indexes];
    }
    
};

NS_LIBSPIRAL_END

#endif /* MultiArray_h */
