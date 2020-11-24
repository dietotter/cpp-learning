#include "helper.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <cmath>

using SequenceType = std::vector<int>;

namespace config {
    // number range for generating random multiplication value
    constexpr int minRandom{ 2 };
    constexpr int maxRandom{ 4 };
    // the range in which to print the nearest number if user was close
    constexpr int finalGuessRange{ 4 };
}

int getRandomNumber(int min, int max)
{
    static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::uniform_int_distribution die{ min, max };

	return die(mersenne);
}

SequenceType generateSequence(const int startingNumber, const int numberAmount, const int randomNumber)
{
    SequenceType sequence(static_cast<SequenceType::size_type>(numberAmount));

    int i{ startingNumber };

    for (auto &number : sequence)
    {
        number = randomNumber * i * i;
        ++i;
    }

    return sequence;
}

void printNearestNumber(const SequenceType &sequence, const int usersGuess)
{
    // if user was close (final guess was in range of finalGuessRange), print the nearest number
    auto nearestNumber{
        std::min_element(sequence.begin(), sequence.end(),
            [=](const int a, const int b) {
                return std::abs(a - usersGuess) < std::abs(b - usersGuess);
            })
    };

    if (std::abs(*nearestNumber - usersGuess) <= config::finalGuessRange)
    {
        std::cout << " Try " << *nearestNumber << " next time.";
    }
}

void playGuessingGame(SequenceType &sequence)
{

    while(true)
    {
        // let user guess and search for the guessed value in sequence
        int usersGuess{};
        std::cin >> usersGuess;

        auto found{ std::find(sequence.begin(), sequence.end(), usersGuess) };

        if (found == sequence.end())
        {
            // if user didn't guess, end the game
            std::cout << usersGuess << " is wrong!";

            printNearestNumber(sequence, usersGuess);
            
            std::cout << '\n';
            break;
        }

        sequence.erase(found);

        // if user guessed, see how many numbers there are left to guess
        auto currentSize{ sequence.size() };

        if (currentSize == 0)
        {
            // if there are 0 numbers left, user won
            std::cout << "Nice! You found all numbers, good job!\n";

            break;
        }

        std::cout << "Nice! " << currentSize << " numbers left.\n";
        // repeat until user guesses all numbers
    }
}

int main()
{

    const int randomNumber{ getRandomNumber(config::minRandom, config::maxRandom) };

    int startingNumber{};
    std::cout << "Start where? ";
    std::cin >> startingNumber;

    int numberAmount{};
    std::cout << "How many? ";
    std::cin >> numberAmount;

    SequenceType sequence{ generateSequence(startingNumber, numberAmount, randomNumber) };
    
    std::cout << "I generated " << numberAmount << " square numbers. Do you know what each number is after multiplying it by " << randomNumber << "?\n";
    playGuessingGame(sequence);

    return 0;
}
