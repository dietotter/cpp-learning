#pragma once

#include <random>
#include <ctime>

namespace myrandom
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}
