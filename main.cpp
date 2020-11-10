#include <iostream>
#include <string>
 
enum class MonsterType
{
    ogre, dragon, orc, giantSpider, slime
};

struct Monster
{
    MonsterType type { MonsterType::ogre };
    std::string name { "Default Dude" };
    int health { 10 };
};

void printMonster(Monster monster)
{
    std::string monsterTypeName;
    if (monster.type == MonsterType::ogre)
    {
        monsterTypeName = "Ogre";
    } else if (monster.type == MonsterType::dragon)
    {
        monsterTypeName = "Dragon";
    } else if (monster.type == MonsterType::orc)
    {
        monsterTypeName = "Orc";
    } else if (monster.type == MonsterType::giantSpider)
    {
        monsterTypeName = "Giant spider";
    } else
    {
        monsterTypeName = "Slime";
    }

    std::cout << "This " << monsterTypeName << " is named "
        << monster.name << " and has " << monster.health << " health.\n";
}

int main()
{
    Monster ogre{};
    Monster slime{ MonsterType::slime, "Ryan", 140 };

    printMonster(ogre);
    printMonster(slime);

    return 0;
}