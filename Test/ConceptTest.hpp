/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef ConceptTest_h
#define ConceptTest_h

#include "../Concept/Concept.hpp"
#include "../Utility/ClassAttribute.hpp"
#include <iostream>

namespace testspiral {
    USING_NS_LIBSPIRAL;
    
    namespace detail {
        class noncopy : attribute::Noncopyable {};
        class noassgin : attribute::Nonassignable {};
        class nonDefauktConstruct {
            nonDefauktConstruct(int) {}
        };
        
        class conceptCheck {
            SPIRAL_CLASS_REQUIRE(int, concept, DefaultConstructible);
            SPIRAL_CLASS_REQUIRE(int, concept, CopyConstructible);
            SPIRAL_CLASS_REQUIRE(int, concept, Assignable);
            
            /* compile errors */
            //SPIRAL_CLASS_REQUIRE(nonDefauktConstruct, concept, DefaultConstructible);
            //SPIRAL_CLASS_REQUIRE(noncopy, concept, CopyConstructible);
            //SPIRAL_CLASS_REQUIRE(noassgin, concept, Assignable);
        };
    }
    
    static void ConceptTest() {
        functionRequires<concept::DefaultConstructible<int>>();
        functionRequires<concept::CopyConstructible<int>>();
        functionRequires<concept::Assignable<int>>();
        
        /* compile errors */
        //functionRequires<CopyConstructible<detail::noncopy>>();
        //functionRequires<DefaultConstructible<detail::nonDefauktConstruct>>();
        //functionRequires<Assignable<detail::noassgin>>();
    }
    
}


#endif /* ConceptTest_h */
