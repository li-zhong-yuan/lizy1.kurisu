namespace lizy1 { namespace kurisu { namespace impl_K {


    template<class T, class C> constexpr bool test_case_loadable(...) { return false; }
    template<class T, class C> constexpr bool test_case_dumpable(...) { return false; }
    template<class T, class C> constexpr bool test_case_constructible(...) { return false; }
    template<class T, class C> constexpr bool test_case_suppress_construct(...) { return false; }


    template<class T, class C, class = decltype(C::__load__(*(std::istream *)0, *(T      *)0))> constexpr bool test_case_loadable(int) { return true; }
    template<class T, class C, class = decltype(C::__dump__(*(std::ostream *)0, *(T const*)0))> constexpr bool test_case_dumpable(int) { return true; }
    template<class T, class C, class R = decltype(C::__construct__(*(std::istream *)0)), _If<_S<R,    T>::value> = 0> constexpr bool test_case_constructible(int)      { return true; }
    template<class T, class C, class R = decltype(C::__construct__(*(std::istream *)0)), _If<_S<R, void>::value> = 0> constexpr bool test_case_suppress_construct(int) { return true; }


    struct Default_Struct {};
    template<class T>       struct Case_Struct_Match;
    template<class T, bool> struct Case_Struct_Load      {};
    template<class T, bool> struct Case_Struct_Dump      {};
    template<class T, int>  struct Case_Struct_Construct {};


    template<class T> struct Case_Struct_Load<T, true>   { static void load(std::istream &is, T      & value) { kurisu::Case<T>::__load__(is, value); } };
    template<class T> struct Case_Struct_Dump<T, true>   { static void dump(std::ostream &os, T const& value) { kurisu::Case<T>::__dump__(os, value); } };
    template<class T> struct Case_Struct_Construct<T, 1> { static void construct(std::istream &is) {                                            } };
    template<class T> struct Case_Struct_Construct<T, 2> { static    T construct(std::istream &is) { return kurisu::Case<T>::__construct__(is); } };


}}}


template<> struct lizy1::kurisu::Case<lizy1::kurisu::impl_K::Default_Struct>
{
};


template<class T> struct lizy1::kurisu::impl_K::Case_Struct_Match
{
protected:
    using bA  = _b<std::is_class<T>::value || std::is_union<T>::value>;  // A: is_matched
    using eB0 = _C<bA::value, T, Default_Struct>;                        // B: T if is_matched else Default_Struct
    using bC  = _b<_c<Case<eB0>>()>;                                     // C: is Case<B> complete
    using eB  = _C<bC::value, eB0, Default_Struct>;                      // B: B if B is complete else Default_Struct
    using eD = Case<eB>;                                                 // D: Case<B>
    using bE = _b<test_case_loadable<eB, eD>(0)>;                        // E: test_case_loadable()
    using bF = _b<test_case_dumpable<eB, eD>(0)>;                        // F: test_case_dumpable()
    using bG = _b<test_case_constructible<eB, eD>(0)>;                   // G: test_case_constructible()
    using bH = _b<test_case_suppress_construct<eB, eD>(0)>;              // H: test_case_suppress_construct()
    using bI = typename std::is_move_constructible<eB>::type;            // I: is_move_constructible<B>

    static_assert(bC::value, "Case_Struct_Match<T>: lizy1::kurisu::Case<T> is not complete. To solve this problem, include header files that implements Kurisu Support for type T");

public:
    static constexpr bool is_matched          = bA::value;
    static constexpr bool is_case_loadable    = bA::value && bC::value && bE::value;
    static constexpr bool is_case_dumpable    = bA::value && bC::value && bF::value;
    static constexpr int  type_case_construct = !(bA::value && bC::value) ? 0 : (bH::value ? 1 : (bG::value && bI::value ? 2 : 0));
};


template<class T> struct lizy1::kurisu::impl_K::Case_Struct
    :lizy1::kurisu::impl_K::_m<lizy1::kurisu::impl_K::Case_Struct_Match<T>::is_matched>,
     lizy1::kurisu::impl_K::Case_Struct_Load<T, lizy1::kurisu::impl_K::Case_Struct_Match<T>::is_case_loadable>,
     lizy1::kurisu::impl_K::Case_Struct_Dump<T, lizy1::kurisu::impl_K::Case_Struct_Match<T>::is_case_dumpable>,
     lizy1::kurisu::impl_K::Case_Struct_Construct<T, lizy1::kurisu::impl_K::Case_Struct_Match<T>::type_case_construct>
{
};
