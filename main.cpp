#include <iostream>
#include <limits> // for std::numeric_limits and std::streamsize
#include <random>
#include <ctime>

namespace MyRandom {
    // Initialize our mersenne twister with a random seed based on the clock (once at startup)
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

int envisionRandomNumber(int min, int max)
{
    std::uniform_int_distribution die{ min, max };
	return die(MyRandom::mersenne);
}

int askForGuess(int tryNum)
{
    int usersGuess{};

    while (true)
    {
        std::cout << "Guess #" << tryNum << ": ";
        std::cin >> usersGuess;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            
            std::cout << "The input is invalid, you DUMB RETARD! Try again.\n";
        }
        else
        {
            std::cin.ignore(32767, '\n');

            return usersGuess;
        }
    }
}

bool askToPlayAgain()
{
    char usersAnswer{};

    while (true)
    {
        std::cout << "Do you want to play again? (y\\n) ";
        std::cin >> usersAnswer;

        switch (usersAnswer)
        {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "OMG is it so hard to type 'y' or 'n'? Try again.\n";
        }
    }
}

bool isGuessCorrect(int guess, int envisionedNum)
{
    if (guess > envisionedNum)
    {
        std::cout << "Your guess is too high, DUMBASS!\n";
    }
    else if (guess < envisionedNum)
    {
        std::cout << "Your guess is too low, HAHAHAHA!\n";
    }
    else
    {
        return true;
    }

    return false;
}

void playHiLo()
{
    int min{ 1 };
    int max{ 100 };

    std::cout << "Let's play a game.  I'm thinking of a number from "
        << min << " to " << max << ".  You have 7 tries to guess what it is.\n";

    int envisionedNum{ envisionRandomNumber(min, max) };
    bool hasUserWon{ false };

    for (int i = 1; i <= 7; i++)
    {
        int usersGuess{ askForGuess(i) };
        if (isGuessCorrect(usersGuess, envisionedNum))
        {
            hasUserWon = true;
            break;
        }
    }

    if (hasUserWon)
    {
        std::cout << "You WIN, motherfucker!\n";
    }
    else
    {
        std::cout << "You LOST! I knew you were stupid! The number was " << envisionedNum << '\n';
    }
}

void gameLoop()
{
    bool isUserPlaying{ true };

    while (isUserPlaying)
    {
        playHiLo();

        isUserPlaying = askToPlayAgain();
    }
}

int main()
{
    gameLoop();
 
	return 0;
}