/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
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
    
    operator T() const SPIRAL_NOEXCEPT { return _value; }
public:
    
    SPIRAL_CXX14_CONSTEXPR iterator begin() SPIRAL_NOEXCEPT {
        return &_value;
    }
    
    SPIRAL_CXX14_CONSTEXPR iterator end() SPIRAL_NOEXCEPT {
        return &(_value) + 1;
    }
    
    SPIRAL_CONSTEXPR const_iterator begin() const SPIRAL_NOEXCEPT {
        return &_value;
    }
    
    SPIRAL_CONSTEXPR const_iterator end() const SPIRAL_NOEXCEPT {
        return &(_value) + 1;
    }
    
    SPIRAL_CONSTEXPR size_t size() const SPIRAL_NOEXCEPT {
        return 1;
    }
    
    SPIRAL_CXX14_CONSTEXPR value_type& operator=(const value_type& rhs) SPIRAL_NOEXCEPT {
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
    SPIRAL_CXX14_CONSTEXPR value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) SPIRAL_NOEXCEPT{
        return _value;
    }
    
    template<size_t ORIGIN_RANK>
    SPIRAL_CONSTEXPR const value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) const SPIRAL_NOEXCEPT {
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
    
    SPIRAL_CXX14_CONSTEXPR iterator begin() SPIRAL_NOEXCEPT{
        return _array[0].begin();
    }
    
    SPIRAL_CXX14_CONSTEXPR iterator end() SPIRAL_NOEXCEPT {
        return _array[First - 1].end();
    }
    
    SPIRAL_CONSTEXPR const_iterator begin() const SPIRAL_NOEXCEPT {
        return _array[0].begin();
    }
    
    SPIRAL_CONSTEXPR const_iterator end() const SPIRAL_NOEXCEPT {
        return _array[First - 1].end();
    }
    
    SPIRAL_CXX14_CONSTEXPR child& operator[](const size_t& index) SPIRAL_NOEXCEPT {
        return _array[index];
    }
    
    SPIRAL_CONSTEXPR const child& operator[](const size_t& index) const SPIRAL_NOEXCEPT {
        return _array[index];
    }
    
    SPIRAL_CONSTEXPR size_t size() const SPIRAL_NOEXCEPT {
        return First;
    }
    
    template<size_t ORIGIN_RANK>
    SPIRAL_CXX14_CONSTEXPR value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) SPIRAL_NOEXCEPT {
        return _array[get<Rank - 1>(indexes)][indexes];
    }
    
    template<size_t ORIGIN_RANK>
    SPIRAL_CONSTEXPR const value_type& operator[](const MultiIndex<ORIGIN_RANK>& indexes) const SPIRAL_NOEXCEPT {
        return _array[get<Rank - 1>(indexes)][indexes];
    }
    
};

NS_LIBSPIRAL_END

#endif /* MultiArray_h */
