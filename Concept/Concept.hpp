/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Concept_h
#define Concept_h

#include "../Common/Macro.h"

#include "../TypeTraits/TypeTraits.hpp"
#include "../TypeTraits/StdTraitsAlias.hpp"

NS_LIBSPIRAL_BEGIN

template <class T> inline void ignore_unused_variable_warning(T const&) {}
template <class Concept>
void functionRequires()
{
    void (Concept::*fptr)() = &Concept::constraint;
    ignore_unused_variable_warning(fptr);
}

namespace concept {
    
#define SPIRAL_CLASS_REQUIRE(TT, NS, Concept) \
typedef void (NS::Concept <TT>::* func##TT##Concept)(); \
template <func##TT##Concept _Tp1> \
struct Concept_checking_##TT##Concept { }; \
typedef Concept_checking_##TT##Concept< \
& NS::Concept<TT>::constraint> \
Concept_checking_typedef_##TT##Concept
    
#define CONCEPT(Concept, TT) \
template<class TT> \
class Concept
    
#define CONSTRAINT() \
public: void constraint()
    
#define CONST_CONSTRAINT(TT) \
void constConstraint(const TT & x)
    
    CONCEPT(DefaultConstructible, TT) {
        CONSTRAINT() {
            TT a;
            ignore_unused_variable_warning(a);
        }
    };
    
    CONCEPT(Assignable, TT) {
        CONSTRAINT() {
            a = b;
            constConstraint(b);
        }
        
    private:
        CONST_CONSTRAINT(TT) {
            ignore_unused_variable_warning(x);
        }
        TT a;
        TT b;
    };
    
    CONCEPT(CopyConstructible, TT) {
        CONSTRAINT() {
            TT a(b);
            TT* ptr = &a;
            constConstraint(a);
            ignore_unused_variable_warning(ptr);
        }
        
    private:
        CONST_CONSTRAINT(TT) {
            TT c(x);
            const TT* ptr = &x;
            ignore_unused_variable_warning(c);
            ignore_unused_variable_warning(ptr);
        }
        TT b;
    };
    
    CONCEPT(EqualityComparable, TT) {
        CONSTRAINT() {
            bool r;
            r = a == b;
            r = a != b;
            ignore_unused_variable_warning(r);
        }
    private:
        TT a, b;
    };
    
    CONCEPT(LessThanComparable, TT) {
        CONSTRAINT() {
            bool r = a < b;
            ignore_unused_variable_warning(r);
        }
    private:
        TT a, b;
    };
    
    CONCEPT(CanSafeAllocatable, TT) {
        CONSTRAINT() {
            TT* a {nullptr};
            a->addRef();
            a->release();
        }
    private:
        TT a;
    };
    
}

NS_LIBSPIRAL_END

#endif /* Concept_h */
