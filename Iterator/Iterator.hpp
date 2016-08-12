/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Iterator_hpp
#define Iterator_hpp

#include<iterator>

template<class Container>
class IndexIterator : public std::iterator<std::random_access_iterator_tag, Container::value_t> {
public:
    typedef Container container_t;
    typedef std::iterator<std::random_access_iterator_tag, Container::value_t> base_t;
    typedef typename base_t::iterator_category iterator_category;
    typedef typename base_t::value_type value_t;
    typedef typename base_t::difference_type difference_t;
    typedef typename base_t::pointer pointer;
    typedef typename base_t::reference reference;
    typedef value_t* value_ptr;
    
    IndexIterator(const IndexIterator& iterator) {
        
    }
    
    SPIRAL_CONSTEXPR difference_t index() const {
        return index_;
    }
    
    SPIRAL_CONSTEXPR IndexIterator next() const {
        return IndexIterator(_ptr, index_ + 1);
    }
    
    SPIRAL_CONSTEXPR IndexIterator prev() const {
        return IndexIterator(_ptr, index_ - 1);
    }
        
    SPIRAL_CXX14_CONSTEXPR IndexIterator& operator++() {
        *this = next();
        return *this;
    }
    
    SPIRAL_CXX14_CONSTEXPR IndexIterator operator++(int) {
        IndexIterator result(*this);
        ++*this;
        return result;
    }
    
    SPIRAL_CXX14_CONSTEXPR  IndexIterator& operator--() {
        *this = prev();
        return *this;
    }
    
    SPIRAL_CXX14_CONSTEXPR  IndexIterator operator--(int) {
        IndexIterator result(*this);
        --*this;
        return result;
    }
    
    
private:
    value_t* _ptr;
    std::size_t _index;
    
    IndexIterator() {
        
    }
    IndexIterator(value_t* value, std::size_t index) : _ptr(value), _index(index){
        
    }
};

#endif /* Iterator_hpp */
