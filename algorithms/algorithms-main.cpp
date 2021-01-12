#include "list/LinkedList.h"

#include <iostream>
#include <cstddef>
#include <exception>

void algorithmsRun()
{
    algorithms::LinkedList<int> list{ 1, 2, 3, 4, 5 };

    list.add(120);

    try
    {
        list.remove(4);
        list.remove(10);
        list.add(-240);
        list.remove(0);
    }
    catch (const std::exception &exception)
    {
        std::cerr << "Exception: " << exception.what() << '\n';
    }

    if (list.contains(3))
    {
        std::cout << "List contains 3!\n";
    }
    else
    {
        std::cout << "There is no 3 in the list!\n";
    }

    try
    {
        list[0] = -69;
        list[99] = 12;
    }
    catch (const std::exception &exception)
    {
        std::cerr << "Exception: " << exception.what() << '\n';
    }

    list.add(17);
    
    for (std::size_t i{ 0 }; i < list.size(); ++i)
    {
        std::cout << list[i] << ' ';
    }

    std::cout << '\n';
}