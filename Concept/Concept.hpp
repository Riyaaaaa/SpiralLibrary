/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Concept_h
#define Concept_h

#include "../Common/Macro.h"

#include "../type_traits/TypeTraits.hpp"
#include "../type_traits/StdTraitsAlias.hpp"

NS_LIBSPIRAL_BEGIN

namespace detail {
    template <class Concept>
    struct usage_requirements
    {
        ~usage_requirements() { ((Concept*)0)->~constraint(); }
    };
}

template <class T> inline void ignore_unused_variable_warning(T const&) {}
template <class Concept>
void function_requires()
{
    void (Concept::*fptr)() = &Concept::constraints;
    ignore_unused_variable_warning(fptr);
}


#define SPIRAL_CLASS_REQUIRE(TT, Concept) \
        typedef void (Concept <TT>::* func##type_var##Concept)(); \
        template <func##TT##Concept _Tp1> \
        struct Concept_checking_##TT##Concept { }; \
        typedef Concept_checking_##TT##Concept< \
        & Concept<TT>::constraints> \
        Concept_checking_typedef_##TT##Concept

#define CONCEPT(Concept, TT) \
template<class TT> \
class Concept

#define CONSTRAINT() \
void constraint()

CONCEPT(DefaultConstructible, TT) {
    CONSTRAINT() {
        TT a;
        ignore_unused_variable_warning(a);
    }
};

NS_LIBSPIRAL_END

#endif /* Concept_h */
