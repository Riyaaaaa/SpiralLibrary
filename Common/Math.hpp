//
//  Math.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/10.
//
//

#ifndef Math_h
#define Math_h

#include "Macro.h"

NS_LIBSPIRAL_BEGIN

#if __cplusplus >= 201402L

template < typename T >
constexpr T sqrt( T s )
{
    T x = s / 2.0 ;
    T prev = 0.0 ;
    
    while ( x != prev )
    {
        prev = x ;
        x = (x + s / x ) / 2.0 ;
    }
    return x ;
}

template < typename T >
constexpr T pow(T s, T e);

template <>
constexpr int pow<int>(int s, int e)
{
    int ret = 1;
    while(0 < e)
    {
        if((e % 2) == 0)
        {
            s *= s;
            e >>= 1;
        }
        else
        {
            ret *= s;
            --e;
        }
    }
    return ret;
}

#elif __cplusplus > 199711L

template < typename T >
SPIRAL_CONSTEXPR T sqrt_impl( T s, T x, T prev ) {
    return x != prev ? sqrt_impl( s, static_cast<T>(( x + s / x ) / 2.0), x ) : x ;
}

template < typename T >
SPIRAL_CONSTEXPR  T sqrt( T s ) {
    return sqrt_impl( s, static_cast<T>(s / 2.0), s ) ;
}

template < typename T >
SPIRAL_CONSTEXPR  T pow(T s, T e);

template <>
SPIRAL_CONSTEXPR  int pow<int>(int s, int e)
{
    return e == 0 ? 1 : s * pow(s, e - 1);
}

#else

template < typename T >
T sqrt( T s )
{
    T x = s / 2.0 ;
    T prev = 0.0 ;
    
    while ( x != prev )
    {
        prev = x ;
        x = (x + s / x ) / 2.0 ;
    }
    return x ;
}

template < typename T >
T pow(T s, T e);

template <>
int pow<int>(int s, int e)
{
    int ret = 1;
    while(0 < e)
    {
        if((e % 2) == 0)
        {
            s *= s;
            e >>= 1;
        }
        else
        {
            ret *= s;
            --e;
        }
    }
    return ret;
}


#endif

NS_LIBSPIRAL_END

#endif /* Math_h */
