/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef noexp_assign_h
#define noexp_assign_h

#include "Macro.h"

NS_LIBSPIRAL_BEGIN

#define NOEXP_ASSIGN(T) \
if(this != &rhs) T(rhs).swap(*this)

NS_LIBSPIRAL_END

#endif /* noexp_swap_h */
