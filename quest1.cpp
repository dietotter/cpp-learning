#include "quest1.h"

#include <iostream>
#include <array>
#include <numeric>

namespace quest1 {

    // could also do the type alias:
    // using inventory_type = std::array<int, Items::total>;

    int countTotalItems(std::array<int, Items::total> &playerItems)
    {
        return std::accumulate(playerItems.begin(), playerItems.end(), 0); // std::reduce from C++17 (or C++20, i didn't understand)
    }

    int executeQuest1()
    {
        std::array playerItems{ 2, 5, 10 };

        std::cout << "Total items player has: " << countTotalItems(playerItems) << '\n';
        std::cout << "Player has this many torches: " << playerItems[Items::torch] << '\n';

        return 0;
    }

}