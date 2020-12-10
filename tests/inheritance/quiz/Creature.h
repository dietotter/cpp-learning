#pragma once

#include <string>
#include <string_view>

class Creature
{
protected:
    std::string m_name;
    char m_symbol;
    int m_hp;
    int m_damage;
    int m_gold;

public:
    Creature(std::string_view name, char symbol, int hp, int damage, int gold):
        m_name{ name },
        m_symbol{ symbol },
        m_hp{ hp },
        m_damage{ damage },
        m_gold{ gold }
    {
    }
    
    void reduceHealth(int byAmount) { m_hp -= byAmount; }
    bool isDead() { return m_hp <= 0; }
    void addGold(int goldToAdd) { m_gold += goldToAdd; }

    const std::string& name() const { return m_name; };
    char symbol() const { return m_symbol; };
    int hp() const { return m_hp; };
    int damage() const { return m_damage; };
    int gold() const { return m_gold; };
};