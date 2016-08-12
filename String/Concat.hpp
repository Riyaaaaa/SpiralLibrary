//
//  Concat.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/07/29.
//
//

#ifndef Concat_h
#define Concat_h

#include "../Common/Macro.h"
#include "../Utility/IndexSequence.hpp"
#include "../Container/Array.hpp"

NS_LIBSPIRAL_BEGIN

namespace detail {

    template<unsigned long N1, unsigned long ... I1, unsigned long  N2, unsigned long ... I2>
    constexpr libspiral::Array<char const, N1 + N2 - 1> concat(char const (&a1)[N1], char const (&a2)[N2], libspiral::index_sequence<I1...>, libspiral::index_sequence<I2...>){
        return {{ a1[I1]..., a2[I2]... }};
    }

}

template<unsigned long N1, unsigned long N2>
constexpr libspiral::Array<char const, N1 + N2 - 1> concat(const char (&a1)[N1], const char (&a2)[N2]){
    return detail::concat(a1, a2, libspiral::make_index_sequence<N1 - 1>{}, libspiral::make_index_sequence<N2>{});
}

template<unsigned long N1>
constexpr unsigned long length(const char (&a1)[N1]){
    return N1;
}

NS_LIBSPIRAL_END

#endif /* Concat_h */
