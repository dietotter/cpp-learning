#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm>

std::string askForName()
{
    std::string name{};

    std::cout << "Enter dis nahme: ";
    std::cin >> name;

    return std::string{ name };
}

bool nameExists(const std::string_view (&nameArray)[4], std::string_view typedName)
{
    for (auto name : nameArray)
    {
        if (name == typedName)
        {
            return true;
        }
    }

    return false;
}
 
int main()
{
    constexpr std::string_view nameArray[]{ "Alex", "Huyalex", "Betty", "Huyetty" };

    std::string_view typedName{ askForName() };

    if (nameExists(nameArray, typedName))
    {
        std::cout << typedName << " was found.";
    }
    else
    {
        std::cout << typedName << " was not found.";
    }
 
    return 0;
}
