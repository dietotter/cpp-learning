#include <iostream>
#include <string>

enum class Race
{
    orc, goblin, troll, ogre, skeleton
};
 
int main()
{
  auto myRace { Race::troll };

  std::cout << static_cast<int>(myRace);
 
  return 0;
}