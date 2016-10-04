/*=============================================================================
 Copyright (c) 2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef StdTraitsAlias_h
#define StdTraitsAlias_h

#include <type_traits>
#include "../TypeTraits/Tag.hpp"
#include "../Common/Macro.h"

#define VALUE_ALIAS(TRAITS) static constexpr bool TRAITS##_v = std::TRAITS<T>::value;
#define VALUE_ALIAS2(TRAITS) static constexpr bool TRAITS##_v = std::TRAITS<T, U>::value;
#define TYPE_ALIAS(TRAITS) template<class T> using TRAITS##_t = typename std::TRAITS<T>::type;

NS_LIBSPIRAL_BEGIN

//VALUE_ALIAS2(is_final); require GNU Compiler Collection

TYPE_ALIAS(remove_const);
TYPE_ALIAS(remove_volatile);
TYPE_ALIAS(remove_cv);
TYPE_ALIAS(add_const);
TYPE_ALIAS(add_volatile);
TYPE_ALIAS(add_cv);
TYPE_ALIAS(remove_reference);
TYPE_ALIAS(add_lvalue_reference);
TYPE_ALIAS(add_rvalue_reference);
TYPE_ALIAS(make_signed);
TYPE_ALIAS(make_unsigned);
TYPE_ALIAS(remove_extent);
TYPE_ALIAS(remove_all_extents);
TYPE_ALIAS(add_pointer);
TYPE_ALIAS(remove_pointer);
TYPE_ALIAS(decay);
TYPE_ALIAS(underlying_type);
TYPE_ALIAS(result_of);

namespace detail {
#if __GNUC__ >= 5 || (__clang_major__ >= 5 && __clang_minor__ >= 0)
    template <class _Tp>
    struct align_type
    {
        static const size_t value = std::alignment_of<_Tp>::value;
        typedef _Tp type;
    };
    
    template <class _Hp, class _Tp>
    struct type_list
    {
        typedef _Hp _Head;
        typedef _Tp _Tail;
    };
    
    struct nat
    {
        nat() = delete;
        nat(const nat&) = delete;
        nat& operator=(const nat&) = delete;
        ~nat() = delete;
    };

    struct __struct_double {long double __lx;};
    struct __struct_double4 {double __lx[4];};

typedef
type_list<align_type<unsigned char>,
type_list<align_type<unsigned short>,
type_list<align_type<unsigned int>,
type_list<align_type<unsigned long>,
type_list<align_type<unsigned long long>,
type_list<align_type<double>,
type_list<align_type<long double>,
type_list<align_type<__struct_double>,
type_list<align_type<__struct_double4>,
type_list<align_type<int*>,
nat
> > > > > > > > > > __all_types;

    
    template <class _TL, size_t _Len> struct __find_max_align;
    
    template <class _Hp, size_t _Len>
    struct __find_max_align<type_list<_Hp, nat>, _Len> : public std::integral_constant<size_t, _Hp::value> {};
#endif
}

#if __GNUC__ >= 5 || (__clang_major__ >= 5 && __clang_minor__ >= 0)
template <std::size_t Len, std::size_t Align = detail::__find_max_align<detail::__all_types, Len>::value>
using aligned_storage_t = std::aligned_storage<Len, Align>;

template <std::size_t Len, class... Types>
using aligned_union_t = typename std::aligned_union<Len, Types...>::type;
#endif

template <bool Condition, class T = void>
using enable_if_t = typename std::enable_if<Condition, T>::type;

template <bool B, class T, class F>
using conditional_t = typename std::conditional<B, T, F>::type;

template <class... T>
using common_type_t = typename std::common_type<T...>::type;

template<class T, class U = default_t>
struct alias;

template<class T>
struct alias<T, default_t> {
    VALUE_ALIAS(is_void);
    VALUE_ALIAS(is_integral);
    VALUE_ALIAS(is_floating_point);
    VALUE_ALIAS(is_array);
    VALUE_ALIAS(is_pointer);
    VALUE_ALIAS(is_lvalue_reference);
    VALUE_ALIAS(is_rvalue_reference);
    VALUE_ALIAS(is_member_object_pointer);
    VALUE_ALIAS(is_member_function_pointer);
    VALUE_ALIAS(is_enum);
    VALUE_ALIAS(is_union);
    VALUE_ALIAS(is_class);
    VALUE_ALIAS(is_function);
    VALUE_ALIAS(is_reference);
    VALUE_ALIAS(is_arithmetic);
    VALUE_ALIAS(is_fundamental);
    VALUE_ALIAS(is_object);
    VALUE_ALIAS(is_scalar);
    VALUE_ALIAS(is_member_pointer);
    VALUE_ALIAS(is_const);
    VALUE_ALIAS(is_volatile);
    VALUE_ALIAS(is_trivial);
    VALUE_ALIAS(is_standard_layout);
    VALUE_ALIAS(is_pod);
    VALUE_ALIAS(is_literal_type);
    VALUE_ALIAS(is_empty);
    VALUE_ALIAS(is_polymorphic);
    VALUE_ALIAS(is_abstract);
    VALUE_ALIAS(is_signed);
    VALUE_ALIAS(is_unsigned);
    VALUE_ALIAS(is_constructible);
    VALUE_ALIAS(is_default_constructible);
    VALUE_ALIAS(is_copy_constructible);
    VALUE_ALIAS(is_move_constructible);
    VALUE_ALIAS(is_destructible);
#if __GNUC__ >= 5 || (__clang_major__ >= 5 && __clang_minor__ >= 0)
    VALUE_ALIAS(is_trivially_copyable);
    VALUE_ALIAS(is_trivially_constructible);
    VALUE_ALIAS(is_trivially_default_constructible);
    VALUE_ALIAS(is_trivially_copy_constructible);
    VALUE_ALIAS(is_trivially_move_constructible);
    VALUE_ALIAS(is_trivially_destructible);
    VALUE_ALIAS(is_trivially_copy_assignable);
    VALUE_ALIAS(is_trivially_move_assignable);
#endif
    VALUE_ALIAS(is_nothrow_constructible);
    VALUE_ALIAS(is_nothrow_default_constructible);
    VALUE_ALIAS(is_nothrow_copy_constructible);
    VALUE_ALIAS(is_nothrow_move_constructible);
    VALUE_ALIAS(is_nothrow_destructible);
    VALUE_ALIAS(is_nothrow_copy_assignable);
    VALUE_ALIAS(is_nothrow_move_assignable);
    VALUE_ALIAS(has_virtual_destructor);
    VALUE_ALIAS(alignment_of);
    VALUE_ALIAS(rank);
};

template<class T, class U>
struct alias {
    VALUE_ALIAS2(is_assignable);
#if __GNUC__ >= 5 || (__clang_major__ >= 5 && __clang_minor__ >= 0)
    VALUE_ALIAS2(is_trivially_assignable);
#endif
    VALUE_ALIAS2(is_nothrow_assignable);
    VALUE_ALIAS2(is_same);
    VALUE_ALIAS2(is_base_of);
    VALUE_ALIAS2(is_convertible);
};

NS_LIBSPIRAL_END

#endif /* StdTraitsAlias_h */
