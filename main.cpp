#include <iostream>
#include <iterator>

int askForNumber()
{
    int num{};

    while (true)
    {
        std::cout << "1 to 9, pls: ";
        std::cin >> num;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            
            std::cout << "The input is invalid, you DUMB RETARD! Try again.\n";
        }
        else if (num < 1 || num > 9)
        {
            std::cin.ignore(32767, '\n');

            std::cout << "The input is invalid, you DUMB RETARD! Try again.\n";
        }
        else
        {
            std::cin.ignore(32767, '\n');

            return num;
        }
    }
}

int main()
{
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
    constexpr int arrayLength{ std::size(array) };

    int num{ askForNumber() };
    
    for (int i = 0; i < arrayLength; ++i)
    {
        std::cout << array[i] << '\n';
    }
    
    for (int i = 0; i < arrayLength; ++i)
    {
        if (array[i] == num) {
            std::cout << "The index of " << num << " is " << i << '\n';
        }
    }

    constexpr int scores[]{ 84, 92, 76, 81, 56 };
    constexpr int numStudents{ static_cast<int>(std::size(scores)) };
 
    int maxIndex{ 0 }; // keep track of our largest score
 
    // now look for a larger score
    for (int student{ 1 }; student < numStudents; ++student)
    {
        if (scores[student] > scores[maxIndex])
        {
            maxIndex = student;
        }
    }
 
    std::cout << "The best score was " << scores[maxIndex] << '\n';
     
	return 0;
}