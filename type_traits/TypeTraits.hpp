//
//  CXX14Traits.hpp
//  SpiralLibDevelop
//
//  Created by Atsumu Ono on 2016/08/25.
//  Copyright © 2016年 Atsumu Ono. All rights reserved.
//

#ifndef TypeTraits_h
#define TypeTraits_h

#include "../Common/Macro.h"
#include "StdTraitsAlias.hpp"
#include <type_traits>

NS_LIBSPIRAL_BEGIN

template<class T>
struct is_null_pointer : public std::false_type {};

template<>
struct is_null_pointer<std::nullptr_t> : public std::true_type {};

NS_LIBSPIRAL_END


#endif /* TypeTraits_h */
