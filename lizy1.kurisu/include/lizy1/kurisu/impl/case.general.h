/*!
signature
    void load(std::istream &is, T &value)
    void dump(std::ostream &os, T const& value)
    T construct(std::istream &is);
*/


namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class T> constexpr bool test_returnable(...)         { return false; }
    template<class C> constexpr bool test_load(...)               { return false; }
    template<class C> constexpr bool test_dump(...)               { return false; }
    template<class C> constexpr bool test_construct(...)          { return false; }
    template<class C> constexpr bool test_suppress_construct(...) { return false; }


    template<class T, class = T(*)()>                  constexpr bool test_returnable(int) { return true; }
    template<class C, class = decltype(&C::load)>      constexpr bool test_load(int)       { return true; }
    template<class C, class = decltype(&C::dump)>      constexpr bool test_dump(int)       { return true; }
    template<class C, class = decltype(&C::construct)> constexpr bool test_construct(int)  { return true; }
    template<class C, class = _If<_S<decltype(C::construct(*(std::istream *)0)), void>::value>> constexpr bool test_suppress_construct(int) { return true; }


    template<class T>       struct Case_General_Deduce;
    template<class T, bool> struct Case_General_Default_Construct {};


}}}


template<class T> struct lizy1::kurisu::impl_K::Case_General_Deduce
{
protected:
    using bA  = _A<T>;                                                                   // A: is T plain
    using eB0 = _C<bA::value, T, int>;                                                   // B: T if T is plain else int
    using bC  = _b<_c<eB0>()>;                                                           // C: is B complete
    using eB  = _C<bC::value, eB0, int>;                                                 // B: B if B is complete else int
    using eD0 = Case_Integral<eB>;                                                       // D: case
    using eD1 = _C<eD0::is_matched, eD0, Case_Floating<eB>>;
    using eD2 = _C<eD1::is_matched, eD1, Case_Enum<eB>>;
    using eD3 = _C<eD2::is_matched, eD2, Case_Array<eB>>;
    using eD4 = _C<eD3::is_matched, eD3, Case_Struct<eB>>;
    using eD  = _C<eD4::is_matched, eD4, _mf>;
    using bE  = _b<test_returnable<eB>(0) && std::is_move_constructible<eB>::value>;     // E: is returnable
    using bF  = _b<test_load<eD>(0)>;                                                    // F: does C::load() exist
    using bG  = _b<test_dump<eD>(0)>;                                                    // G: does C::dump() exist
    using bH  = _b<test_construct<eD>(0)>;                                               // H: does C::construct() exist
    using bI  = _b<test_suppress_construct<eD>(0)>;                                      // I: is construct suppressed
    using bJ  = _b<bE::value && bH::value && !bI::value>;                                // J: is C::construct() valid
    using bK  = _b<std::is_default_constructible<eB>::value && bE::value && bF::value>;  // K: can implement default constructor
    using bL  = _b<!bI::value && !bJ::value && bK::value>;                               // L: is_default_construct
    using bM  = _b<bJ::value || bL::value>;                                              // M: is_constructible

    static_assert(bA::value, "Case_General_Deduce<T>: lizy1::kurisu requires that T is not const, not volatile, and not reference");
    static_assert(bC::value, "Case_General_Deduce<T>: lizy1::kurisu requires that T is complete");

    /// Output
public:
    using type_case = eD;
    static constexpr bool is_loadable          = bA::value && bC::value && bF::value;
    static constexpr bool is_dumpable          = bA::value && bC::value && bG::value;
    static constexpr bool is_constructible     = bA::value && bC::value && bM::value;
    static constexpr bool is_default_construct = bA::value && bC::value && bL::value;
};


template<class T> struct lizy1::kurisu::impl_K::Case_General_Default_Construct<T, true>
{
    static T construct(std::istream &is)
    {
        T ret;
        load(is, ret);
        return ret;
    }
};


template<class T> struct lizy1::kurisu::impl_K::Case_General
    :lizy1::kurisu::impl_K::Case_General_Deduce<T>,
     lizy1::kurisu::impl_K::Case_General_Deduce<T>::type_case,
     lizy1::kurisu::impl_K::Case_General_Default_Construct<T, lizy1::kurisu::impl_K::Case_General_Deduce<T>::is_default_construct>
{
};
