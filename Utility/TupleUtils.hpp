/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef TupleUtils_h
#define TupleUtils_h

#include<tuple>
#include"../Common/Macro.h"
#include"IndexSequence.hpp"

NS_LIBSPIRAL_BEGIN

template<class F,typename T, std::size_t... indices>
auto tupleVariadicImpl(F&& f, T&& t, index_sequence<indices...>)
->decltype(f(std::get<indices>(t)...))
{
    return f(std::get<indices>(t)...);
}


template <class F, class... Ts>
auto tupleVariadicApply(F&& f, std::tuple<Ts...>&& args)
->decltype(tupleVariadicImpl(f, std::forward<std::tuple<Ts...>&&>(args), index_sequence_for<Ts...>()))
{
    return tupleVariadicImpl(f, std::forward<std::tuple<Ts...>&&>(args), index_sequence_for<Ts...>());
}

template <class F, class... Ts>
auto tupleVariadicApply(F&& f, std::tuple<Ts...>& args)
->decltype(tupleVariadicImpl(f, std::forward<std::tuple<Ts...>&>(args), index_sequence_for<Ts...>()))
{
    return tupleVariadicImpl(f, std::forward<std::tuple<Ts...>&>(args), index_sequence_for<Ts...>());
}

namespace detail {
    
    template<std::size_t begin, std::size_t end, bool isEnd = begin + 1 == end>
    struct _partExecute;
    
    template<std::size_t begin, std::size_t end>
    struct _partExecute<begin, end, true>
    {
        template<typename Tuple, typename F, typename... Args>
        static void Execute(Tuple && tuple, F&& f, Args&&... args)
        {
            f(std::get<begin>(tuple),std::forward<Args>(args)...);
        }
    };
    
    template<std::size_t begin, std::size_t end>
    struct _partExecute<begin, end, false>
    {
        template<typename Tuple, typename F, typename... Args>
        static void Execute(Tuple&& tuple, F&& f, Args&&... args)
        {
            _partExecute<begin, (begin + end) / 2>::Execute
            (std::forward<Tuple>(tuple), std::forward<F>(f), std::forward<Args>(args)...);
            
            _partExecute<(begin + end) / 2, end>::Execute
            (std::forward<Tuple>(tuple), std::forward<F>(f), std::forward<Args>(args)...);
        }
    };
    
    template<std::size_t index, std::size_t end, bool isEnd = index == end>
    struct _forwardExecute;
    
    template<std::size_t index, std::size_t end>
    struct _forwardExecute<index, end, false>
    {
        template<typename Tuple, typename F, typename... Args>
        static void Execute(Tuple&& tuple, F&& f, Args&&... args)
        {
            f(std::get<index>(tuple),std::forward<Args>(args)...);
            _forwardExecute<index+1,end>::Execute(
                                                 std::forward<Tuple>(tuple),
                                                 std::forward<F>(f),
                                                 std::forward<Args>(args)...
                                                 );
            
        }
    };
    
    template<std::size_t index, std::size_t end>
    struct _forwardExecute<index, end, true>
    {
        template<typename Tuple, class F, typename... Args>
        static void Execute(Tuple&& tuple, F&& f, Args&&... args)
        {
            //end
        }
    };
    
    template<std::size_t index, std::size_t end, bool isEnd = index == end - 1>
    struct _backPropagateExecute;
    
    template<std::size_t index, std::size_t end>
    struct _backPropagateExecute<index, end, false>
    {
        template<typename Tuple, typename F, typename... Args>
        static auto Execute(Tuple&& tuple, F&& f, Args&&... args)
        ->decltype(f(tuple, args...))
        {
            return f(std::get<index>(tuple),std::forward<Args>(args)...)
                        +_backPropagateExecute<index+1,end>::Execute(
                                                  std::forward<Tuple>(tuple),
                                                  std::forward<F>(f),
                                                  std::forward<Args>(args)...
                                                  );
            
        }
    };
    
    template<std::size_t index, std::size_t end>
    struct _backPropagateExecute<index, end, true>
    {
        template<typename Tuple, class F, typename... Args>
        static auto Execute(Tuple&& tuple, F&& f, Args&&... args)
        ->decltype(f(tuple, args...))
        {
            return f(std::get<index>(tuple),std::forward<Args>(args)...);
        }
    };
}

template<std::size_t begin, std::size_t end,typename Tuple, typename F, typename... Args>
void partExecute(Tuple&& tuple, F&& f, Args&&... args)
{
    detail::_partExecute<begin, end>::Execute(
                                              std::forward<Tuple>(tuple),
                                              std::forward<F>(f),
                                              std::forward<Args>(args)...
                                              );
}



template< std::size_t begin, std::size_t end,typename Tuple, typename F,typename... Args>
void forwardExecute(Tuple&& tuple, F&& f, Args&&... args)
{
    detail::_forwardExecute<begin, end>::Execute(
                                        std::forward<Tuple>(tuple),
                                        std::forward<F>(f),
                                        std::forward<Args>(args)...
                                        );
}

template< std::size_t begin, std::size_t end,typename Tuple, typename F,typename... Args>
auto backPropagateExecute(Tuple&& tuple, F&& f, Args&&... args)
->decltype(f(tuple, args...))
{
    return detail::_backPropagateExecute<begin, end>::Execute(
                                                 std::forward<Tuple>(tuple),
                                                 std::forward<F>(f),
                                                 std::forward<Args>(args)...
                                                 );
}

NS_LIBSPIRAL_END

#endif /* TupleUtils_h */
