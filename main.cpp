#include "helper.h"

#include <iostream>
#include <vector>

void printBinary(unsigned int x)
{
    if (x > 1)
    {
        printBinary(x / 2);
    }

    std::cout << x % 2;
}

int digitSum(int number)
{
    if (number <= 0)
    {
        return 0;
    }

    return digitSum(number / 10) + number % 10;
}

int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    return factorial(n - 1) * n;
    
}

int main()
{
    helper::runTestLoop(factorial, 7, 1);

    std::cout << "93427 => " << digitSum(93427) << '\n';

    std::cout << "-15 to binary: ";
    printBinary(static_cast<unsigned int>(-15));
    std::cout << '\n';
    
    return 0;
}
