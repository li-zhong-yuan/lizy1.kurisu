namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class T, class U> void case_integral_msvc_c4800(T t, U    &u) { u = static_cast<U>(t); }
    template<class T>          void case_integral_msvc_c4800(T t, bool &b) { b = t != 0; }


    template<class T, bool> struct Case_Integral_ :_mf {};
    template<class T>       struct Case_Integral  :Case_Integral_<T, std::is_integral<T>::value> {};


}}}


template<class T> struct lizy1::kurisu::impl_K::Case_Integral_<T, true>
{
protected:
    using bA  = typename std::is_signed<T>::type;            // A: is signed
    using bB0 = _S<T, char>;                                 // B: is byte
    using bB1 = _S<T, signed char>;
    using bB2 = _S<T, unsigned char>;
    using bB3 = _S<T, std::uint8_t>;
    using bB4 = _S<T, std::int8_t>;
    using bB  = _b<bB0::value || bB1::value || bB2::value || bB3::value || bB4::value>;
    using bC  = _S<T, bool>;                                 // C: is bool
    using tD0 = _C<bA::value, std::int64_t, std::uint64_t>;  // D: type_repr
    using tD1 = _C<bB::value, T, tD0>;
    using tD  = _C<bC::value, unsigned char, tD1>;

public:
    using type_repr = tD;
    static constexpr bool is_matched = true;
    static void load(std::istream &is, T      & value) { case_integral_msvc_c4800(load_machine_bytes<type_repr>(is), value); }
    static void dump(std::ostream &os, T const& value) { dump_machine_bytes(os, static_cast<type_repr>(value)); }
};
