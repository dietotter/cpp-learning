#pragma once

#include <functional>

namespace helper
{
    using IntFunction = std::function<int(int)>;
    void runTestLoop(IntFunction testedFunc, int n, int offset);
}
