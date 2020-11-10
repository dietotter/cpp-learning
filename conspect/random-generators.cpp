#include <iostream>
#include <random> // for std::mt19937
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()

namespace MyRandom {
    // Initialize our mersenne twister with a random seed based on the clock (once at startup)
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

int getRandomNumber(int min, int max)
{
    // from C++17, we can use uniform_int_distribution without the <>
    // prior to C++17, we need <> here
	std::uniform_int_distribution<> die{ min, max }; // we can create a distribution in any function that needs it
	return die(MyRandom::mersenne); // and then generate a random number from our global generator
}
 
int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    // Due to a flaw in some compilers, we need to call std::rand() once
    // here to get "better" random numbers.
    std::rand();
 
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << std::rand() << '\t';
 
        // If we've printed 5 numbers, start a new row
        if (count % 5 == 0)
            std::cout << '\n';
	}

    // use Mersenne Twister
    std::cout << getRandomNumber(1, 6) << '\n';
	std::cout << getRandomNumber(1, 10) << '\n';
	std::cout << getRandomNumber(1, 20) << '\n';
 
    return 0;
}