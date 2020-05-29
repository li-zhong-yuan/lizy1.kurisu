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