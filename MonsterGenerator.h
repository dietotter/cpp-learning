#pragma once

#include "Monster.h"

#include <array>

class MonsterGenerator
{
private:
    // Generate a random number between min and max (inclusive)
    // Assumes std::srand() has already been called
    // Assumes max - min <= RAND_MAX
    // IMPORTANT: for now moved this method's definition to header file
    // (because can't define the static private outside of class definition)
    // just so I have the example of such thing
    // But it would probs be better to separate declaration from definition
    // and just make getRandomNumber public (as it seems that compile times have gotten larger)
    static int getRandomNumber(int min, int max)
    {
        static constexpr double fraction{ 1.0 / (static_cast<double>(RAND_MAX) + 1.0) };  // static used for efficiency, so we only calculate this value once
        // evenly distribute the random number across our range
        return static_cast<int>(std::rand() * fraction * (max - min + 1) + min);
    }

public:
    static Monster generateMonster();
};