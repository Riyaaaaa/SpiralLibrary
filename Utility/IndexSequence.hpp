/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef IndexSequence_h
#define IndexSequence_h

#include"../Container/Array.hpp"
#include"../Common/Macro.h"

NS_LIBSPIRAL_BEGIN

template< std::size_t ... i >
struct index_sequence
{
    typedef std::size_t value_type;
    
    typedef index_sequence<i...> type;

    SPIRAL_STATIC_CONSTEXPR std::size_t size() noexcept
    {
        return sizeof ... (i);
    }
};


template< std::size_t s, typename IS >
struct doubled_index_sequence;

template< std::size_t s, std::size_t ... i >
struct doubled_index_sequence< s, index_sequence<i... > >
{
    typedef index_sequence<i..., (s + i)... > type;
};

template< bool NEED, typename IS >
struct inc_index_sequence;

template< typename IS >
struct inc_index_sequence<false, IS>{ typedef IS type; };

template< std::size_t ... i >
struct inc_index_sequence< true, index_sequence<i...> >
{
    typedef index_sequence<i..., sizeof...(i)> type;
};

template< std::size_t N >
struct make_index_sequence_impl :
inc_index_sequence< (N % 2 != 0),
typename doubled_index_sequence< N / 2,
typename make_index_sequence_impl< N / 2> ::type
>::type
>
{};
template<>struct make_index_sequence_impl<0>{ typedef index_sequence<> type; };

template< std::size_t N >
using make_index_sequence = typename make_index_sequence_impl<N>::type;

template< typename ... T >
using index_sequence_for = make_index_sequence< sizeof...(T) >;

template <std::size_t ...Indices>
SPIRAL_CONSTEXPR libspiral::Array<std::size_t, sizeof...(Indices)> _make_index_array(index_sequence<Indices...>)
{
    return libspiral::Array<std::size_t, sizeof...(Indices)>{Indices...};
}

NS_LIBSPIRAL_END

#endif /* IndexSequence_h */
