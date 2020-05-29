namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class T, bool> struct Case_Array_Load          {};
    template<class T, bool> struct Case_Array_Dump          {};
    template<class T>       struct Case_Array               :_mf {};
    template<class T>       struct Case_Array_Load<T, true> { static void load(std::istream &is, T      & value) { for(auto &x : value) kurisu::load(is, x); } };
    template<class T>       struct Case_Array_Dump<T, true> { static void dump(std::ostream &os, T const& value) { for(auto &x : value) kurisu::dump(os, x); } };


}}}


template<class T, int N> struct lizy1::kurisu::impl_K::Case_Array<T[N]>
    :lizy1::kurisu::impl_K::_mt,
     lizy1::kurisu::impl_K::Case_Array_Load<T[N], lizy1::kurisu::impl_K::Case_General<T>::is_loadable>,
     lizy1::kurisu::impl_K::Case_Array_Dump<T[N], lizy1::kurisu::impl_K::Case_General<T>::is_dumpable>
{
};
