// File lizy1.kurisu/example/example.basic.cpp

#include <lizy1/kurisu.h>  // include the core of Lizy1.Kurisu
#include <stdio.h>
#include <cstdint>         // because we use std::int16_t
#include <sstream>

enum class EA { A, B, C, D, E };

int main()
{
    // The following assumes that, on the target platform, char is signed
    using lizy1::kurisu::load;                           // this is the function for deserializing
    using lizy1::kurisu::dump;                           // this is the function for serializing
    using lizy1::kurisu::construct;                      // this is the function for constructing
    std::string binary_result;
    /// Serializing
    {
        std::ostringstream os;                           // create a std::ostream that acts as the destination of the dump()s
        char char_v = '1';                               // a char value, which is a Fundamental Type
        dump(os, char_v);                                // os now stores { '1' }
        int int_v = 2;                                   // a int value, which is a Fundamental Type
        dump(os, int_v);                                 // os now stores { '1', 2, 0, 0, 0, 0, 0, 0, 0 }
        dump(os, -1);                                    // OK, dump a integer literal
                                                         // os now stores { '1', 2, ..., 0, -1, -1, -1, -1, -1, -1, -1, -1 }
        float float_v = 3.0f;                            // a float value, which is a Fundamental Type
        double double_v = 4.0;                           // a double value, which is a Fundamental Type
        dump(os, float_v, double_v);                     // dump multiple values, in order
        dump(os, EA::C);                                 // dump a Enum value
        const char array_char_v[] = "Hello Kurisu";      // a array of const char
        const char array_array_char_v[][7] = {           // a array of const char[7]
            "Hello ", "Kurisu"
        };
        dump(os, array_char_v, array_array_char_v);      // dump both arrays
                                                         // os now stores { ..., 's', 'u', '\0', 'H', 'e', 'l', 'l', 'o',
                                                         // ' ', '\0', 'K', 'u', 'r', 'i', 's', 'u', '\0' }
        binary_result = os.str();                        // save the result into a std::string
    }
    /// Deserializing & Constructing
    {
        std::istringstream is(binary_result);            // create a std::istream that acts as the source of the load()s
        char char_v;
        load(is, char_v);                                // char_v == '1'
        int int_v;
        load(is, int_v);                                 // int_v == 2
        std::int16_t int16_v;
        load(is, int16_v);                               // OK, load a int16_t from a int type. int16_v == -1
        float float_v;
        double double_v;
        load(is, float_v, double_v);                     // load multiple values, in order. float_v == 3.0, double_v == 4.0
        EA ea_v = construct<EA>(is);                     // construct a Enum value. ea_v == EA::C
        // auto array_char_v = construct<char[11]>(is);  // ERROR, array types are not constructible
        char array_char_v[13] = {};
        char array_array_char_v[2][7] = {};
        load(is, array_char_v, array_array_char_v);      // OK, works
        printf(
            "char_v               : %c\n"
            "int_v                : %d\n"
            "int16_v              : %d\n"
            "float_v              : %f\n"
            "double_v             : %f\n"
            "ea_v == EA::C        : %s\n"
            "array_char_v         : \"%s\"\n"
            "array_array_char_v[0]: \"%s\"\n"
            "array_array_char_v[1]: \"%s\"\n",
            char_v,
            int_v,
            static_cast<int>(int16_v),
            float_v,
            double_v,
            ea_v == EA::C ? "true" : "false",
            array_char_v,
            array_array_char_v[0],
            array_array_char_v[1]
        );
    }
    return 0;
}