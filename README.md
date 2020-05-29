# Lizy1 - Kurisu
Serialization & Deserialization Library for C++11

- [Features](#Features)
- [Function](#Function)
  - [Serializing & Deserialing Fundamental Types, Enums and Arrays](#Serializing-&-Deserialing-Fundamental-Types-Enums-and-Arrays)
  - [Serializing & Deserialing Class Types](#Serializing-&-Deserialing-Class-Types)
  - [Kurisu Support for C++ Standard Library](#Kurisu-Support-for-C++-Standard-Library)
  - [Meta Support](#Meta-Support)
  - [Error Handling](#Error-Handling)

## Features

Basic features:
- **C++11**.  This library is designed in the domain of C++11.
- **Compatible**. This library should keep good compatibility between different versions.  Code that uses a older version should alway be free to update to any newer version. The goal is to cause less problems, when different parts of a system, a program, or a compilation unit are designed with different versions of this library.
- **Header only library**. And no dependencies.
- **Thread-Safe**. This library is thread-safe, and can be used in multi-thread environment without additional sync operation.

Other features:

- **Light weight**. The core is only 500 lines of code.

- **Simple**. Interfaces are kept as simple as possible.

## Function

### Serializing & Deserialing Fundamental Types, Enums and Arrays

Fundamental Types, Enums and Arrays are basic types, which are supported natively by the core of Kurisu.

```cpp
// File lizy1.kurisu/example/example.basic.cpp

#include <lizy1/kurisu.h>  // include the core of Lizy1.Kurisu
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
    }
    return 0;
}
```

### Serializing & Deserialing Class Types

For a customer class/struct, a fully (or partial) specialization of class template `lizy1::kurisu::Case<>` must be defined in order to implement Kurisu Support for that type.

```cpp
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
```

If the customer class/struct has no accessible default constructor,  the type is not constructible. Unless a static member function `__construct__()` is defined in the specialization of class template `lizy1::kurisu::Case<>`.

```cpp
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
```

### Kurisu Support for C++ Standard Library

Kurisu is responsible for implementing Kurisu Support for C++ Standard Library. To include support for a specific standard header, just include the same named file in directory <lizy1/kurisu/std>.

```cpp
// File lizy1.kurisu/example/example.std.string.cpp

#include <lizy1/kurisu/std/string>  // including Kurisu Support for <string>
#include <string>                   // this is optional as <lizy1/kurisu/std/string> already includes it
#include <stdio.h>
#include <sstream>

int main()
{
    std::string binary_result;
    /// serializing
    {
        std::ostringstream os;
        std::string s = "Hello Kurisu";
        lizy1::kurisu::dump(os, s);
        binary_result = os.str();
    }
    /// constructing
    {
        std::istringstream is(binary_result);
        std::string s = lizy1::kurisu::construct<std::string>(is);
        printf("Constructed String: %s\n", s.c_str());  // print: "Constructed String: Hello Kurisu"
    }
    return 0;
}
```

### Meta Support

Interfaces exposed by this library also include meta support for diagnosing Kurisu Support for a given type at compile time.

```cpp
using lizy1::kurisu::IsLoadable;
using lizy1::kurisu::IsDumpable;
using lizy1::kurisu::IsConstructible;
    
static_assert(IsLoadable<unsigned[5]>::value, "");         // IsLoadable<unsigned[5]> yields to std::true_type
// static_assert(IsLoadable<std::string>::value, "");      // ERROR, Case<std::string> is not complete, won't compile
static_assert(IsDumpable<int, float, double>::value, "");  // IsDumpable<int, float, double> yields to std::true_type
static_assert(!IsConstructible<unsigned[5]>::value, "");   // IsLoadable<unsigned[5]> yields to std::false_type
```

### Error Handling

This library achieves error handling using C++ Exceptions. All exceptions defined by this library:

- `KurisuException`: This is the base class of all other exceptions defined by Kurisu.

- `LoadException`:   This exception is thrown by load() and construct().

- `DumpException`:   This exception is thrown by dump().

```cpp
// File lizy1.kurisu/example/example.exception_handling.cpp

#include <lizy1/kurisu.h>
#include <stdio.h>
#include <sstream>

using namespace lizy1::kurisu;

int main()
{
    std::ostringstream os;
    dump(os, 1, 2, 3);  // dump 3 values
    try
    {
        std::istringstream is(os.str());
        int array_int_4[4];
        load(is, array_int_4);  // will throw LoadException.
                                // Because only 3 int values are available
                                // but 4 int values are required
                                // `is` will meet EOF and turn bad
    }
    catch(LoadException &e)
    {
        printf("Failed loading: %s\n", e.what());  // print: Failed loading: std::istream turns bad
    }
    return 0;
}
```

Users of this library should always deal with these exceptions carefully, especially when the input (std::istream &, or the object to dump) is not reliable. You can throw these exceptions in your definition of `__load__()`, `__dump__()` and `__construct__()`, as long as following all of these rules:

- `__load__()`: Only raises `LoadException` (including subclasses).

- `__dump__()`:   Only raises `DumpException` (including subclasses).
- `__construct__()`:   Only raises `LoadException` (including subclasses).


