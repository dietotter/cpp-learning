#include "helper.h"

#include <iostream>

namespace helper {

    // Tests *testedFunc* function *n* times, with *offset* offset to iteration value,
    // and prints the results
    // E.g. for n = 7 and offset 1, testedFunc will run 7 times, for values 1 to 7
    void runTestLoop(IntFunction testedFunc, int n, int offset)
    {
        for (int i{ 0 + offset }; i < (n + offset); ++i)
        {
            std::cout << testedFunc(i) << ' ';
        }

        std::cout << '\n';
    }
}