// File lizy1.kurisu/example/example.struct_nodefctor.cpp

#include <lizy1/kurisu.h>
#include <sstream>

using lizy1::kurisu::load;
using lizy1::kurisu::dump;
using lizy1::kurisu::construct;

// a similar struct to the previous ExampleStruct but without default constructor
struct ExampleStruct_NoDefCtor
{
    ExampleStruct_NoDefCtor(int) {}
    int   d1 = 0;
    long  d2 = 0;
    float d3 = 0.0f;
};

// specialization of lizy1::kurisu::Case<> with T = ExampleStruct_NoDefCtor
// implements Kurisu Support for class type ExampleStruct_NoDefCtor
template<> struct lizy1::kurisu::Case<ExampleStruct_NoDefCtor>
{
    static void __load__(std::istream &is, ExampleStruct_NoDefCtor      & v) { load(is, v.d1, v.d2, v.d3); }
    static void __dump__(std::ostream &os, ExampleStruct_NoDefCtor const& v) { dump(os, v.d1, v.d2, v.d3); }

    // a __construct__() must be given in order to support lizy1::kurisu::construct(),
    // because ExampleStruct_NoDefCtor has no def ctor
    static ExampleStruct_NoDefCtor __construct__(std::istream &is)
    {
        ExampleStruct_NoDefCtor ret(0);  // firstly, construct a ExampleStruct_NoDefCtor
        __load__(is, ret);               // secondly, call Case::__load__() to load its value
        return ret;                      // finally, return
    }
};

int main()
{
    std::string binary_result;
    /// Serializing
    {
        std::ostringstream os;
        ExampleStruct_NoDefCtor example_struct_nodefctor(0);
        {
            example_struct_nodefctor.d1 = 4;
            example_struct_nodefctor.d2 = 5;
            example_struct_nodefctor.d3 = 6.0f;
        }
        dump(os, example_struct_nodefctor);
        binary_result = os.str();
    }
    /// Constructing
    {
        std::istringstream is(binary_result);
        ExampleStruct_NoDefCtor example_struct_nodefctor = construct<ExampleStruct_NoDefCtor>(is);
                                            // OK, will construct directly from 
                                            // Case<ExampleStruct_NoDefCtor>::__construct__()
    }
    return 0;
}