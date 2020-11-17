#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm>

std::size_t askForNamesAmount()
{
    std::cout << "How many nameZZZ: ";

    std::size_t nameAmount{};
    std::cin >> nameAmount;

    return nameAmount;
}

void fillInNames(std::string *nameArray, std::size_t length)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // so that previous std::cin doesn't fuck us up

    for (std::size_t counter = 0; counter < length; ++counter)
    {
        std::cout << "Enter dis nahme #" << counter + 1 << " plssz: ";
        std::getline(std::cin, nameArray[counter]);
    }
}

void printNames(std::string *nameArray, std::size_t length)
{
    for (std::size_t counter = 0; counter < length; ++counter)
    {
        std::cout << "Sorted nahme #" << counter + 1 << ": " << nameArray[counter] << '\n';
    }
}
 
int main()
{
    std::size_t nameAmount{ askForNamesAmount() };

    auto *nameArray{ new std::string[nameAmount]{} };

    fillInNames(nameArray, nameAmount);

    std::sort(nameArray, nameArray + nameAmount);

    printNames(nameArray, nameAmount);

    delete[] nameArray;
 
    return 0;
}
