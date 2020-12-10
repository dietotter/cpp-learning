#pragma once

#include "Creature.h"
#include "myrandom.h"

#include <array>
#include <random>

class Monster : public Creature
{
public:
    enum class Type
    {
        dragon,
        orc,
        slime,
        maxTypes
    };

private:
    // lookup table
    static const Creature& getDefaultCreature(Type type)
    {
        static std::array<Creature, static_cast<std::size_t>(Type::maxTypes)> monsterData{
            {
                { "dragon", 'D', 20, 4, 100 },
                { "orc", 'o', 4, 2, 25 },
                { "slime", 's', 1, 1, 10 }
            }
        };

        return monsterData.at(static_cast<std::size_t>(type));
    }

public:
    Monster(Type type)
        : Creature{ getDefaultCreature(type) }
    {
    }

    static Monster getRandomMonster()
    { 
	    static std::uniform_int_distribution typeDie{ 0, static_cast<int>(Type::maxTypes) - 1 };

        return { static_cast<Type>(typeDie(myrandom::mt)) };
    }

};