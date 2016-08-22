/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Concat_h
#define Concat_h

#include "../Common/Macro.h"
#include "../Utility/IndexSequence.hpp"
#include "../Container/Array.hpp"
#include <string>

NS_LIBSPIRAL_BEGIN

namespace detail {

    template<unsigned long N1, unsigned long ... I1, unsigned long  N2, unsigned long ... I2>
    constexpr libspiral::Array<char const, N1 + N2 - 1> concat(char const (&a1)[N1], char const (&a2)[N2], libspiral::index_sequence<I1...>, libspiral::index_sequence<I2...>) SPIRAL_NOEXCEPT {
        return {{ a1[I1]..., a2[I2]... }};
    }

}

template<unsigned long N1, unsigned long N2>
constexpr libspiral::Array<char const, N1 + N2 - 1> concat(const char (&a1)[N1], const char (&a2)[N2]) SPIRAL_NOEXCEPT {
    return detail::concat(a1, a2, libspiral::make_index_sequence<N1 - 1>{}, libspiral::make_index_sequence<N2>{});
}

template<unsigned long N1, unsigned long N2>
std::string concatToString(const char (&a1)[N1], const char (&a2)[N2]) SPIRAL_NOEXCEPT {
    return std::string(&detail::concat(a1, a2, libspiral::make_index_sequence<N1 - 1>{}, libspiral::make_index_sequence<N2>{})[0]);
}

template<unsigned long N1>
constexpr unsigned long length(const char (&a1)[N1]) SPIRAL_NOEXCEPT {
    return N1;
}

NS_LIBSPIRAL_END

#endif /* Concat_h */
