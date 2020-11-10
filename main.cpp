#include <iostream>
#include <string>

bool passOrFail()
{
    static int userNum{ 1 };

    return userNum++ <= 3;
}

int main()
{
	std::cout << "Enter your name: ";
    std::string name{};
    std::getline(std::cin, name);

	std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

	std::cout << "You've lived " << static_cast<float>(age) / name.length() << " for each letter in your name";
 
	return 0;
}