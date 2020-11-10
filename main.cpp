#include <iostream>
#include <string>

enum class Animal
{
    pig, chicken, goat, cat, dog, ostrich, centipede
};

std::string getAnimalName(Animal animal)
{
    switch(animal)
    {
        case Animal::pig:
            return "pig";
        case Animal::chicken:
            return "chicken";
        case Animal::goat:
            return "goat";
        case Animal::cat:
            return "cat";
        case Animal::dog:
            return "dog";
        case Animal::ostrich:
            return "ostrich";
        default:
            std::cout << "No such animal T_T\n";
            return "???";
    }
}

void printLegs(Animal animal)
{
    std::cout << getAnimalName(animal) << " has ";

    switch(animal)
    {
        case Animal::ostrich:
        case Animal::chicken:
            std::cout << '2';
            break;
        case Animal::pig:
        case Animal::goat:
        case Animal::cat:
        case Animal::dog:
            std::cout << '4';
            break;
        default:
            std::cout << "no idea how many";
    }

    std::cout << " legs\n";
}

int calculate(int x, int y, char op)
{
    switch(op)
    {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        default:
            std::cout << "Incorrect operator! Returning -1...\n";
            return -1;
    }
}

int main()
{
    printLegs(Animal::cat);
    printLegs(Animal::chicken);
    printLegs(Animal::centipede);

    return 0;
}