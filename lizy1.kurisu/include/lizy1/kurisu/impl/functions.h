namespace lizy1 { namespace kurisu { namespace impl_K {


    inline void load_(std::istream &is) {}
    inline void dump_(std::ostream &os) {}
    template<class T, class... Ts> inline void load_(std::istream &is, T      & value, Ts      &... values) { Case_General<T>::load(is, value); load_(is, values...); }
    template<class T, class... Ts> inline void dump_(std::ostream &os, T const& value, Ts const&... values) { Case_General<T>::dump(os, value); dump_(os, values...); }


}}}


template<class... Ts, class> void lizy1::kurisu::load(std::istream &is, Ts      &... values) { impl_K::load_(is, values...); }
template<class... Ts, class> void lizy1::kurisu::dump(std::ostream &os, Ts const&... values) { impl_K::dump_(os, values...); }
template<class T, class>     T lizy1::kurisu::construct(std::istream &is)                    { return impl_K::Case_General<T>::construct(is); }
