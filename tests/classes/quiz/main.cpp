#include "Point2d.h"
#include "Monster.h"
#include "MonsterGenerator.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"

#include <iostream>
// for srand() for MonsterGenerator thing
#include <cstdlib>
#include <ctime>

// forward declare blackjack
void playBlackjack();

class HelloWorld
{
private:
    char *m_data{};

public:
    HelloWorld()
	{
	    m_data = new char[14];
        const char *init{ "Hello, World!" };
        for (int i = 0; i < 14; ++i)
        {
            m_data[i] = init[i];
        }
    }

    ~HelloWorld()
    {
        delete m_data;
    }
    
    void print() const
    {
        std::cout << m_data << '\n';
    }
};

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };
    first.print();
    second.print();
    std::cout << "Distance between two points: " << distanceFrom(first, second) << '\n';

    HelloWorld hello{};
    hello.print();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();
    Monster skeleton{ MonsterGenerator::generateMonster() };
    skeleton.print();

    playBlackjack();
    
    return 0;
}