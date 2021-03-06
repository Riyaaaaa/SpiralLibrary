/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef LibSpiralTest_h
#define LibSpiralTest_h

#include "../Common/Macro.h"
#include "MultiArray_and_MultiIndexTest.hpp"
#include "RandomTest.hpp"
#include "StringTest.hpp"
#include "OptionalTest.hpp"
#include "MaybeCallTest.hpp"
#include "OpTraitsTest.hpp"
#include "ArrayUtilsTest.hpp"
#include "ConceptTest.hpp"
#include "AnyTest.hpp"
#include "DelayCallTest.hpp"
#include "SignalSlotsTest.hpp"

namespace testspiral {

static void libspiral_test() {
    //multiArrayAndIndexTest();
    //randomTest();
    //stringTest();
    //optionalTest();
    //maybeCallTest();
    //opTraitsTest();
    //ArrayUtilsTest();
    //ConceptTest();
    //AnyTest();
    delayCallTest();
}

}

#endif /* LibSpiralTest_h */
