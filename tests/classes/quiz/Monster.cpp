#include "Monster.h"

#include <iostream>

Monster::Monster(Type type, const std::string &name, const std::string &roar, int hp)
    : m_type{ type }, m_name{ name }, m_roar{ roar }, m_hp{ hp }
{
}

std::string_view Monster::getTypeString() const
{
    switch(m_type)
    {
        case Monster::Type::dragon:
            return "dragon";
        case Monster::Type::goblin:
            return "goblin";
        case Monster::Type::ogre:
            return "ogre";
        case Monster::Type::orc:
            return "orc";
        case Monster::Type::skeleton:
            return "skeleton";
        case Monster::Type::troll:
            return "troll";
        case Monster::Type::vampire:
            return "vampire";
        case Monster::Type::zombie:
            return "zombie";
        default:
            return "unknown monster";
    }
}

void Monster::print() const
{
    std::cout << m_name << " the " << getTypeString()
        << " has " << m_hp << " hp and says " << m_roar << '\n';
}