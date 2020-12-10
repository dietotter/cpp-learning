#pragma once

#include "Creature.h"

#include <string_view>

class Player : public Creature
{
private:
    int m_level{ 1 };

public:
    Player(std::string_view name):
        Creature{ name, '@', 10, 1, 0 }
    {
    }

    bool hasWon() const { return m_level >= 20; }
    void levelUp()
    {
        ++m_level;
        ++m_damage;
    }

    int level() const { return m_level; }
};