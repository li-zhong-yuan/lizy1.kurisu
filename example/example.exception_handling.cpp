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