/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef MultiIndex_h
#define MultiIndex_h

#include "../Common/Alias.h"
#include "../Container/Array.hpp"

NS_LIBSPIRAL_BEGIN

template<size_t _Rank>
struct MultiIndex {
    SPIRAL_STATIC_CONSTEXPR size_t Rank = _Rank;
    
    SPIRAL_CONSTEXPR MultiIndex(){}
    
    template<class... Args>
    SPIRAL_CONSTEXPR MultiIndex(Args... _indexes) :
    indexes({_indexes...})
    {
        
    }
    
    SPIRAL_CXX14_CONSTEXPR long& operator[](size_t index) {
        return indexes[index];
    }
    
    SPIRAL_CONSTEXPR const long& operator[](size_t index) const {
        return indexes[index];
    }
    
    template<size_t Rank>
    bool operator==(const MultiIndex<Rank>& rhs) {
        for(int i = 0; i < Rank; i++) {
            if((*this)[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    
    Array<long, Rank> indexes;
};

template<size_t _Rank>
class IndexRange
{
public:
    
    class iterator
    {
    private:
        const IndexRange<_Rank>& _IndexRange;
        MultiIndex<_Rank> _now;
    public:
        explicit iterator ( const IndexRange<_Rank>& IndexRange, const bool isBegin ) : _IndexRange( IndexRange )
        {
            this->_now  = IndexRange.getMin();
            if ( !isBegin ) this->_now[_Rank - 1] = IndexRange.getMax()[_Rank - 1] + 1;
        }
        
        MultiIndex<_Rank> operator * ( void )
        {
            return this->_now;
        }
        
        bool operator != ( const iterator& that )
        {
            return !(this->_now == that._now);
        }
        
        iterator&
        operator++( void )
        {
            this->step_forward();
            return *this;
        }
        private :
        void step_forward( void )
        {
            const MultiIndex<_Rank> bmin = this->_IndexRange.getMin();
            const MultiIndex<_Rank> bmax = this->_IndexRange.getMax();
            
            MultiIndex<_Rank>& pos = this->_now;
            if ( bmax[_Rank - 1] < pos[_Rank - 1] ) return;
            
            for(int i = 0; i < _Rank; i++) {
                pos[i] += 1;
                if(bmax[i] >= pos[i] || i == _Rank - 1) {
                    break;
                }
                pos[i] = bmin[i];
            }
        }
    };
private:
    MultiIndex<_Rank> _bmin;
    MultiIndex<_Rank> _bmax;
public:
    SPIRAL_CONSTEXPR IndexRange ( const MultiIndex<_Rank>& bmin , const MultiIndex<_Rank>& bmax ) : _bmin ( bmin ) , _bmax( bmax )
    {}
    
    SPIRAL_CONSTEXPR MultiIndex<_Rank> getMin( void ) const
    {
        return this->_bmin;
    }
    
    SPIRAL_CONSTEXPR MultiIndex<_Rank> getMax( void ) const
    {
        return this->_bmax;
    }
    
    SPIRAL_CXX14_CONSTEXPR iterator begin() {
        return IndexRange::iterator( *this, true );
    }
    
    SPIRAL_CXX14_CONSTEXPR iterator end() {
        return IndexRange::iterator( *this, false );
    }
    
    SPIRAL_CONSTEXPR const iterator begin() const {
        return IndexRange::iterator( *this, true );
    }
    
    SPIRAL_CONSTEXPR const iterator end() const {
       return IndexRange::iterator( *this, false );
    }
};

template<size_t Index, size_t Rank>
SPIRAL_CONSTEXPR size_t get(MultiIndex<Rank> indexes) {
    return indexes[Index];
}

NS_LIBSPIRAL_END





#endif /* MultiIndex_h */
