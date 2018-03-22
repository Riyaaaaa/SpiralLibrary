/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Macro_h
#define Macro_h

#define CLOCKWISE_8_FOR { libspiral::Index{-1, 0}, libspiral::Index{-1, 1}, libspiral::Index{0, 1}, libspiral::Index{1, 1}, libspiral::Index{1, 0}, libspiral::Index{1, -1}, libspiral::Index{0, -1}, libspiral::Index{-1, -1} }
#define CLOCKWISE_4_FOR { libspiral::Index{-1, 0}, libspiral::Index{0, 1}, libspiral::Index{1, 0}, libspiral::Index{0, -1} }

#define ALL_RANGE(n) n.begin(), n.end()

#define NS_LIBSPIRAL_BEGIN namespace libspiral {
#define NS_LIBSPIRAL_END }
#define USING_NS_LIBSPIRAL using namespace libspiral

#define SPIRAL_NOEXCEPT noexcept
#define SPIRAL_NOEXCEPT_IF(exp) noexcept(exp)

#if __cplusplus >= 201402L || _MSC_VER >= 1910
#define SPIRAL_CXX_14
#define SPIRAL_CXX14_CONSTEXPR constexpr
#define SPIRAL_CONSTEXPR constexpr
#define SPIRAL_STATIC_CONSTEXPR static constexpr

#elif __cplusplus >= 201103L || _MSC_VER >= 1900
#define SPIRAL_CXX_11
#define SPIRAL_CXX14_CONSTEXPR
#define SPIRAL_CONSTEXPR constexpr
#define SPIRAL_STATIC_CONSTEXPR static constexpr

#else
#define SPIRAL_CXX_03
#define SPIRAL_CXX14_CONSTEXPR
#define SPIRAL_CONSTEXPR
#define SPIRAL_STATIC_CONSTEXPR static
#endif

#endif /* Macro_h */
