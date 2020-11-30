#pragma once

#include <string>
#include <string_view>

class Monster
{
public:
    enum class Type
    {
        dragon, goblin, ogre, orc, skeleton, troll, vampire, zombie, maxTypes
    };

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hp{};

public:
    Monster(Type type, const std::string &name, const std::string &roar, int hp);
    // We're returning strings that are known at compile-time.
    // Returning std::string could add a considerable run-time cost.
    std::string_view getTypeString() const;
    void print() const;
};