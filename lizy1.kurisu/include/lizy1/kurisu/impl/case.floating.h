namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class T, bool> struct Case_Floating_ :_mf {};
    template<class T>       struct Case_Floating  :Case_Floating_<T, std::is_floating_point<T>::value> {};


}}}


template<class T> struct lizy1::kurisu::impl_K::Case_Floating_<T, true>
{
    static constexpr bool is_matched = true;
    static void load(std::istream &is, T      & value) { value = load_machine_bytes<T>(is); }
    static void dump(std::ostream &os, T const& value) { dump_machine_bytes(os, value); }
};
