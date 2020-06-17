#pragma once


/*!
construct
    Only from default constructor (eg. std::set<int>::set())
    Construct then emplace(E&&)
    Suppress Kurisu Default Construct
*/


#include "string_like.h"


namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class C, class E>       struct SetLike;
    template<class C, class E, bool> struct SetLike_Load_And_Construct { static void __construct__(std::istream &) {}; };  // suppress Kurisu Default Construct


}}}


template<class C, class E> struct lizy1::kurisu::impl_K::SetLike_Load_And_Construct<C, E, true>
{
    static void __load__(std::istream &is, C &c) { c = __construct__(is); }

    static C __construct__(std::istream &is)
    {
        std::size_t size;
        load(is, size);
        C ret;
        for(std::size_t i = 0; i < size; i++)
            ret.emplace(construct<E>(is));
        return ret;
    }
};


template<class C, class E> struct lizy1::kurisu::impl_K::SetLike
    :lizy1::kurisu::impl_K::StringLike_Dump<C, lizy1::kurisu::IsDumpable<E>::value>,
     lizy1::kurisu::impl_K::SetLike_Load_And_Construct<C, E, lizy1::kurisu::IsConstructible<E>::value>
{
};
