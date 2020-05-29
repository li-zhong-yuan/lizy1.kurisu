namespace lizy1 { namespace kurisu { namespace impl_K {


    /// _If: enable_if
    template<bool b, typename R = int> using _If = typename std::enable_if<b, R>::type;


    /// _b, _t, _f
    template<bool b> struct _b { static constexpr bool value = b; };
    using _t = _b<true>;
    using _f = _b<false>;


    /// _m, _mt, _mf
    template<bool b> struct _m { static constexpr bool is_matched = b; };
    using _mt = _m<true>;
    using _mf = _m<false>;


    /// _Star: and {0,}
    template<        bool... vs> struct __Star           :_t {};
    template<bool v, bool... vs> struct __Star<v, vs...> :_b<v && __Star<vs...>::value> {};
    template<bool... vs> using _Star = std::integral_constant<bool, __Star<vs...>::value>;


    /// _A: is plain type (not cv, not ref)
    template<class T> using _A = _b<std::is_same<T, typename std::remove_cv<typename std::remove_reference<T>::type>::type>::value>;


    /// _C: conditional
    template<bool b, class T, class U> using _C = typename std::conditional<b, T, U>::type;


    /// _S: is same
    template<class T, class U> using _S = typename std::is_same<T, U>::type;


    /// _R: remove ref
    template<class T> using _R = typename std::remove_reference<T>::type;


    /// _U: remove const
    template<class T> using _U = typename std::remove_const<T>::type;


    /// _V: remove ref & const
    template<class T> using _V = typename std::remove_const<typename std::remove_reference<T>::type>::type;


    /// _Is: int pack
    template<int... value> struct _Is;


    /// _Span
    template<int I, int J, class R>  struct __Span;
    template<int I, int... R>        struct __Span<I, I, _Is<R...>> { using type = _Is<R...>; };
    template<int I, int J, int... R> struct __Span<I, J, _Is<R...>> :__Span<I + 1, J, _Is<R..., I>> {};
    template<int I, int J> using _Span = typename __Span<I, J, _Is<>>::type;


    /// _c: is complete type (static_assert() fails if this evaluates to false)
    template<class T>                              constexpr bool __c(...) { return false; }
    template<class T, class = decltype(sizeof(T))> constexpr bool __c(int) { return true; }
    template<class T>                              constexpr bool _c()     { return __c<T>(0); }


}}}
