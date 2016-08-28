/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Format_h
#define Format_h

#include <cstdio>
#include <string>
#include <stdexcept>
#include <memory>
#include "../Common/Macro.h"

NS_LIBSPIRAL_BEGIN;

namespace detail
{
    static constexpr int MAX_BUFFER = 1024 * 100;
    template <typename... Args>
    std::unique_ptr<char[]> formatImpl(char const* formatCStr, Args&&... args)
    {
        std::unique_ptr<char[]> buf(new char[MAX_BUFFER]);
        size_t writtenLen = snprintf(buf.get(), MAX_BUFFER, formatCStr, args...);
        
        if (writtenLen > 0 && writtenLen < MAX_BUFFER)
        {
            return buf;
        } else {
            throw std::runtime_error("Buffer Over Flow");
        }
    }
}

template <typename... Args>
std::string format(const std::string& formatString, Args&&... args)
{
    std::unique_ptr<char[]> chars = detail::formatImpl(formatString.c_str(), args...);
    return std::string(chars.get());
}

NS_LIBSPIRAL_END;

#endif /* Format_h */
