#pragma once

namespace quest1 {

    // we use enum rather than enum class because we want to index the array
    // (otherwise, we'd have to do static_cast on the enumerators)
    enum Items
    {
        healthPotion, torch, arrow, total
    };

    int executeQuest1();

}