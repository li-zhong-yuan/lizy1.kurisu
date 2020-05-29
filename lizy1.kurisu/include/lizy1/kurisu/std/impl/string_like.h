#pragma once


/*!
construct
    Only from default constructor (eg. std::string::string())
    Resize() then load()
    Suppress Kurisu Default Construct
*/


#include <lizy1/kurisu.h>


namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class C, class E> struct StringLike;
    template<class C, bool>    struct StringLike_Dump               {};
    template<class C, bool>    struct StringLike_Load_And_Construct { static void __construct__(std::istream &); };  // suppress Kurisu Default Construct


}}}


template<class C> struct lizy1::kurisu::impl_K::StringLike_Dump<C, true>
{
    static void __dump__(std::ostream &os, C const& c)
    {
        dump(os, static_cast<std::size_t>(c.size()));
        for (auto &item : c)
            dump(os, item);
    }
};


template<class C> struct lizy1::kurisu::impl_K::StringLike_Load_And_Construct<C, true>
{
    static void __load__(std::istream &is, C &c) { c = __construct__(is); }

    static C __construct__(std::istream &is)
    {
        std::size_t size;
        load(is, size);
        C ret;
        ret.resize(size);
        for (auto &item : ret)
            load(is, item);
        return ret;
    }
};


template<class C, class E> struct lizy1::kurisu::impl_K::StringLike
    :lizy1::kurisu::impl_K::StringLike_Dump<C, lizy1::kurisu::IsDumpable<E>::value>,
     lizy1::kurisu::impl_K::StringLike_Load_And_Construct<C, lizy1::kurisu::IsLoadable<E>::value>
{
};
