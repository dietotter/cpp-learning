#include "quest1.h"
#include "quest2.h"
#include "quest6.h"
#include "quest7.h"

#include <iostream>

namespace quest3 {

    void swap(int &x, int &y)
    {
        int temp{ x };
        x = y;
        y = temp;
    }

    void executeQuest3()
    {
        int x{ 2 };
        int y{ -3 };
        swap(x, y);
        std::cout << "x is " << x << ", y is " << y << '\n';
    }

}

namespace quest4 {

    void printStringByChar(const char *str)
    {
        while (*str != '\0')
        {
            std::cout << *str << ' ';
            ++str;
        }
    }

    void executeQuest4()
    {
        printStringByChar("Hello, bitches!");
        std::cout << '\n';
    }

}

int main()
{
    std::cout << "Question 1\n\n";
    quest1::executeQuest1();

    std::cout << "\n==============================\n\nQuestion 2\n\n";
    quest2::executeQuest2();

    std::cout << "\n==============================\n\nQuestion 3\n\n";
    quest3::executeQuest3();

    std::cout << "\n==============================\n\nQuestion 4\n\n";
    quest4::executeQuest4();

    std::cout << "\n==============================\n\nQuestion 6\n\n";
    quest6::card_deck_t deck{ quest6::getShuffledDeck() };

    std::cout << "\n==============================\n\nQuestion 7\n\n";
    quest7::playBlackjack(deck);

    return 0;
}