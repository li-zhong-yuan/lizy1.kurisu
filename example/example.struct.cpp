// File lizy1.kurisu/example/example.struct.cpp

#include <lizy1/kurisu.h>
#include <sstream>

using lizy1::kurisu::load;
using lizy1::kurisu::dump;
using lizy1::kurisu::construct;

struct ExampleStruct  // a customer struct
{
    int   d1 = 0;
    long  d2 = 0;
    float d3 = 0.0f;
};

// specialization of lizy1::kurisu::Case<> with T = ExampleStruct
// implements Kurisu Support for class type ExampleStruct
template<> struct lizy1::kurisu::Case<ExampleStruct>
{
    static void __load__(std::istream &is, ExampleStruct      & v) { load(is, v.d1, v.d2, v.d3); }
    static void __dump__(std::ostream &os, ExampleStruct const& v) { dump(os, v.d1, v.d2, v.d3); }
};

int main()
{
    std::string binary_result;
    /// Serializing
    {
        std::ostringstream os;
        ExampleStruct example_struct = { 1, 2, 3.0f };
        dump(os, example_struct);
        binary_result = os.str();
    }
    /// Deserializing
    {
        std::istringstream is(binary_result);
        ExampleStruct example_struct;
        load(is, example_struct);
    }
    /// Constructing
    {
        std::istringstream is(binary_result);
        ExampleStruct example_struct = construct<ExampleStruct>(is);
                                     // OK, Kurisu calls ExampleStruct::ExampleStruct(), then load()
    }
    return 0;
}