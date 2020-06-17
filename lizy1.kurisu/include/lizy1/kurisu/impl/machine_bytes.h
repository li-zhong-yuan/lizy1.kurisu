namespace lizy1 { namespace kurisu { namespace impl_K {


    inline bool is_little_endian();
    template<typename T> inline T load_machine_bytes(std::istream &is);                     // thread-safe, instant, raise<LoadException>
    template<typename T> inline void dump_machine_bytes(std::ostream &os, T const& value);  // thread-safe, instant, raise<>


}}}


bool lizy1::kurisu::impl_K::is_little_endian()
{
    unsigned i = 1;
    return *reinterpret_cast<char *>(&i) != 0;
}


template<typename T> T lizy1::kurisu::impl_K::load_machine_bytes(std::istream &is)
{
    T value;
    char* p = reinterpret_cast<char*>(&value);
    if (is_little_endian())
        is.read(p, sizeof(value));
    else for (std::size_t i = sizeof(value); i > 0; i--)
        p[i - 1] = is.get();
    if (!is.good())
        throw LoadException("std::istream turns bad");
    return value;
}


template<typename T> void lizy1::kurisu::impl_K::dump_machine_bytes(std::ostream &os, T const& value)
{
    char const* p = reinterpret_cast<char const*>(&value);
    if (is_little_endian())
        os.write(p, sizeof(value));
    else for (std::size_t i = sizeof(value); i > 0; i--)
        os.put(p[i - 1]);
}
