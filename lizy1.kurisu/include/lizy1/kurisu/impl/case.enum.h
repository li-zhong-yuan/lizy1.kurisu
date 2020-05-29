namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class T, bool> struct Case_Enum_ :_mf {};
    template<class T>       struct Case_Enum  :Case_Enum_<T, std::is_enum<T>::value> {};


}}}


template<class T> struct lizy1::kurisu::impl_K::Case_Enum_<T, true>
{
    using type_underlying = typename std::underlying_type<T>::type;
    static constexpr bool is_matched = true;
    static void load(std::istream &is, T      & value) { type_underlying underlying; kurisu::load(is, underlying); value = static_cast<T>(underlying); }
    static void dump(std::ostream &os, T const& value) { kurisu::dump(os, static_cast<type_underlying>(value)); }
};
