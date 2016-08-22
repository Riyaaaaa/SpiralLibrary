/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef OptionalExcept_h
#define OptionalExcept_h

#include "../Common/Macro.h"
#include <stdexcept>

NS_LIBSPIRAL_BEGIN

class bad_optional_access : public std::logic_error {
public:
    explicit bad_optional_access(const std::string& what_arg) : std::logic_error{what_arg} {}
    explicit bad_optional_access(const char* what_arg) : std::logic_error{what_arg} {}
};

NS_LIBSPIRAL_END

#endif /* OptionalExcept_h */
