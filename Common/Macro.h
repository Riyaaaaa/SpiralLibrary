//
//  Macro.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/06.
//
//

#ifndef Macro_h
#define Macro_h

#define CLOCKWISE_8_FOR { Index{-1, 0}, Index{-1, 1}, Index{0, 1}, Index{1, 1}, Index{1, 0}, Index{1, -1}, Index{0, -1}, Index{-1, -1} } 
#define CLOCKWISE_4_FOR { Index{-1, 0}, Index{0, 1}, Index{1, 0}, Index{0, -1} }

#define NS_LIBSPIRAL_BEGIN namespace libspiral {
#define NS_LIBSPIRAL_END }
#define USING_NS_LIBSPIRAL using namespace libspiral

#if __cplusplus >= 201402L
#define SPIRAL_CXX_14
#define SPIRAL_CXX14_CONSTEXPR constexpr
#define SPIRAL_CONSTEXPR constexpr
#define SPIRAL_STATIC_CONSTEXPR static constexpr

#elif __cplusplus >= 201103L
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
