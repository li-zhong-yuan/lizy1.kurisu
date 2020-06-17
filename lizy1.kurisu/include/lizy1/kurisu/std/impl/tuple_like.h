#pragma once


/*!
construct
    Only from direct construct (eg. std::tuple<...>::tuple(items...))
    Suppress Kurisu Default Construct
*/


#include <lizy1/kurisu.h>


namespace lizy1 { namespace kurisu { namespace impl_K {


    static constexpr int tuple_like_category_no_limit     = 0b0000;
    static constexpr int tuple_like_category_no_load      = 0b0001;
    static constexpr int tuple_like_category_no_construct = 0b0010;


    template<class P>                 struct TupleLike;
    template<class...>                struct TupleLike_Deduce                   { static constexpr int category = tuple_like_category_no_limit; };
    template<int, class P, class...>  struct TupleLike_;
    template<bool, class P, class>    struct TupleLike_Load                     {};
    template<bool, class P, class>    struct TupleLike_Dump                     {};
    template<bool, class P, class...> struct TupleLike_Construct                { static void __construct__(std::istream &) {}; };  // suppress Kurisu Default Construct
    template<class T, class... Ts>    struct TupleLike_Deduce<T, Ts...>         { static constexpr int category = TupleLike_Deduce<Ts...>::category; };
    template<class T, class... Ts>    struct TupleLike_Deduce<const T, Ts...>   { static constexpr int category = tuple_like_category_no_load | TupleLike_Deduce<Ts...>::category; };
    template<class T, class... Ts>    struct TupleLike_Deduce<T &, Ts...>       { static constexpr int category = tuple_like_category_no_construct | TupleLike_Deduce<Ts...>::category; };
    template<class T, class... Ts>    struct TupleLike_Deduce<T &&, Ts...>      { static constexpr int category = tuple_like_category_no_construct | TupleLike_Deduce<Ts...>::category; };
    template<class T, class... Ts>    struct TupleLike_Deduce<T const&, Ts...>  { static constexpr int category = tuple_like_category_no_load | tuple_like_category_no_construct; };
    template<class T, class... Ts>    struct TupleLike_Deduce<T const&&, Ts...> { static constexpr int category = tuple_like_category_no_load | tuple_like_category_no_construct; };
    template<class P, int... I>       struct TupleLike_Load<true, P, _Is<I...>> { static void __load__(std::istream &is, P      & tuple) { load(is, std::get<I>(tuple)...); } };
    template<class P, int... I>       struct TupleLike_Dump<true, P, _Is<I...>> { static void __dump__(std::ostream &os, P const& tuple) { dump(os, std::get<I>(tuple)...); } };
    template<class P, class... T>     struct TupleLike_Construct<true, P, T...> { static P __construct__(std::istream &is) { return P{ construct<T>(is)... }; } };


}}}


template<template<class...> class C, class... Ts> struct lizy1::kurisu::impl_K::TupleLike<C<Ts...>>
    :lizy1::kurisu::impl_K::TupleLike_<lizy1::kurisu::impl_K::TupleLike_Deduce<Ts...>::category, C<Ts...>, Ts...>
{
};


template<class P, class... Ts> struct lizy1::kurisu::impl_K::TupleLike_<lizy1::kurisu::impl_K::tuple_like_category_no_limit, P, Ts...>
    :lizy1::kurisu::impl_K::TupleLike_Load<lizy1::kurisu::IsLoadable<Ts...>::value, P, lizy1::kurisu::impl_K::_Span<0, sizeof...(Ts)>>,
     lizy1::kurisu::impl_K::TupleLike_Dump<lizy1::kurisu::IsDumpable<Ts...>::value, P, lizy1::kurisu::impl_K::_Span<0, sizeof...(Ts)>>,
     lizy1::kurisu::impl_K::TupleLike_Construct<lizy1::kurisu::IsConstructible<Ts...>::value, P, Ts...>
{
};


template<class P, class... Ts> struct lizy1::kurisu::impl_K::TupleLike_<lizy1::kurisu::impl_K::tuple_like_category_no_load, P, Ts...>
    :lizy1::kurisu::impl_K::TupleLike_Dump<lizy1::kurisu::IsDumpable<lizy1::kurisu::impl_K::_U<Ts>...>::value, P, lizy1::kurisu::impl_K::_Span<0, sizeof...(Ts)>>,
     lizy1::kurisu::impl_K::TupleLike_Construct<lizy1::kurisu::IsConstructible<lizy1::kurisu::impl_K::_U<Ts>...>::value, P, lizy1::kurisu::impl_K::_U<Ts>...>
{
};


template<class P, class... Ts> struct lizy1::kurisu::impl_K::TupleLike_<lizy1::kurisu::impl_K::tuple_like_category_no_construct, P, Ts...>
    :lizy1::kurisu::impl_K::TupleLike_Load<lizy1::kurisu::IsLoadable<lizy1::kurisu::impl_K::_R<Ts>...>::value, P, lizy1::kurisu::impl_K::_Span<0, sizeof...(Ts)>>,
     lizy1::kurisu::impl_K::TupleLike_Dump<lizy1::kurisu::IsDumpable<lizy1::kurisu::impl_K::_R<Ts>...>::value, P, lizy1::kurisu::impl_K::_Span<0, sizeof...(Ts)>>,
     lizy1::kurisu::impl_K::TupleLike_Construct<false, void>
{
};


template<class P, class... Ts> struct lizy1::kurisu::impl_K::TupleLike_<lizy1::kurisu::impl_K::tuple_like_category_no_load | lizy1::kurisu::impl_K::tuple_like_category_no_construct, P, Ts...>
    :lizy1::kurisu::impl_K::TupleLike_Dump<lizy1::kurisu::IsDumpable<lizy1::kurisu::impl_K::_V<Ts>...>::value, P, lizy1::kurisu::impl_K::_Span<0, sizeof...(Ts)>>,
     lizy1::kurisu::impl_K::TupleLike_Construct<false, void>
{
};
