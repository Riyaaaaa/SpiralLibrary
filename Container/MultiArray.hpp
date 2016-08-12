/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef MultiArray_h
#define MultiArray_h

#include <utility>
#include "../Structure/MultiIndex.hpp"
#include "../Common/Stream.hpp"
#include "../Memory/AddressOf.hpp"

NS_LIBSPIRAL_BEGIN

template<class T, size_t... Dims>
class MultiArray {
public:
    typedef T  value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    SPIRAL_STATIC_CONSTEXPR size_t RANK = 0;
    value_type _value;
    
    operator T() const { return _value; }
public:
    
    SPIRAL_CXX14_CONSTEXPR iterator begin() {
        return &_value;
    }
    
    SPIRAL_CXX14_CONSTEXPR iterator end() {
        return &(_value) + 1;
    }
    
    SPIRAL_CONSTEXPR const_iterator begin() const {
        return &_value;
    }
    
    SPIRAL_CONSTEXPR const_iterator end() const {
        return &(_value) + 1;
    }
    
    SPIRAL_CXX14_CONSTEXPR value_type& operator=(const value_type& rhs) {
        _value = rhs;
        return _value;
    }
    
    const value_type* operator &() const {
        return addressOf(_value);
    }
    
    value_type* operator &() {
        return addressOf(_value);
    }
    
    template<size_t ORIGIN_RANK>
    SPIRAL_CXX14_CONSTEXPR value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) {
        return _value;
    }
    
    template<size_t ORIGIN_RANK>
    SPIRAL_CONSTEXPR const value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) const {
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
    SPIRAL_STATIC_CONSTEXPR size_t Rank = sizeof...(Dims) + 1;
    libspiral::Array<child, First> _array;
    
public:
    
    SPIRAL_CXX14_CONSTEXPR iterator begin() {
        return _array[0].begin();
    }
    
    SPIRAL_CXX14_CONSTEXPR iterator end() {
        return _array[First - 1].end();
    }
    
    SPIRAL_CONSTEXPR const_iterator begin() const {
        return _array[0].begin();
    }
    
    SPIRAL_CONSTEXPR const_iterator end() const {
        return _array[First - 1].end();
    }
    
    SPIRAL_CXX14_CONSTEXPR child& operator[](const size_t& index){
        return _array[index];
    }
    
    SPIRAL_CONSTEXPR const child& operator[](const size_t& index) const {
        return _array[index];
    }
    
    template<size_t ORIGIN_RANK>
    SPIRAL_CXX14_CONSTEXPR value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) {
        return _array[get<Rank - 1>(indexes)][indexes];
    }
    
    template<size_t ORIGIN_RANK>
    SPIRAL_CONSTEXPR const value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) const {
        return _array[get<Rank - 1>(indexes)][indexes];
    }
    
};

NS_LIBSPIRAL_END

#endif /* MultiArray_h */
