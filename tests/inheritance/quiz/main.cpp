#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "myrandom.h"

#include <iostream>
#include <string>
#include <random>

bool attackMonster(Player &p, Monster &m)
{
    m.reduceHealth(p.damage());

    std::cout << "You hit the " << m.name() << " for " << p.damage() << " damage.\n";

    if (m.isDead())
    {
        p.levelUp();
        p.addGold(m.gold());

        std::cout << "You killed the " << m.name() << ".\n";
        std::cout << "You are now level " << p.level() << ".\n";
        std::cout << "You found " << m.gold() << " gold.\n";

        return true;
    }

    return false;
}

bool attackPlayer(Player &p, const Monster &m)
{
    p.reduceHealth(m.damage());

    std::cout << "The " << m.name() << " hit you for " << m.damage() << " damage.\n";

    if (p.isDead())
    {
        std::cout << "You dies at level " << p.level() << " and with " << p.gold() << " gold.\n";
        std::cout << "Too bad you SUCK and NO GOLD FOR YOUR DEAD ASS!\n";

        return false;
    }

    return true;
}

bool fightMonster(Player &p)
{
    Monster m{ Monster::getRandomMonster() };

    std::cout << "You have encountered a " << m.name() << " (" << m.symbol() << ").\n";

	static std::uniform_int_distribution runDie{ 0, 1 };

    while (true)
    {
        char playersChoice{};
        std::cout << "(R)un or (F)ight: ";
        std::cin >> playersChoice;

        bool ableToRun{};
        switch(playersChoice)
        {
            case 'R':
            case 'r':
                ableToRun = static_cast<bool>(runDie( myrandom::mt ));
                
                if (ableToRun)
                {
                    std::cout << "You successfully fled.\n";
                    return true;
                }

                std::cout << "You failed to flee.\n";

                if (!attackPlayer(p, m))
                {
                    return false;
                }

                break;
            case 'F':
            case 'f':
            default:
                if (attackMonster(p, m))
                {
                    return true;
                }

                break;
        }
    }
}

int main()
{
    std::string name{};
    std::cout << "Enter your name: ";
    std::cin >> name;

    Player p{ name };
    std::cout << "Welcome, " << p.name() << ".\n";

    while (!p.hasWon())
    {
        if (!fightMonster(p))
        {
            break;
        }
    }
    
    if (p.hasWon())
    {
        std::cout << "Nice, you won with " << p.gold() << " to spend on onlyfans you LOSER!\n";
    }

	return 0;
}