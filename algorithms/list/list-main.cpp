#include "LinkedList.h"

#include <iostream>
#include <exception>
#include <cstddef>

void noIteratorCheck()
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

void constListCheck()
{
    const algorithms::LinkedList<int> list{ 5, 3, 2 };

    if (list.contains(3))
    {
        std::cout << "Contains 3 with the list size of " << list.size() << '\n';
    }

    std::cout << "List index: " << list[2] << '\n';
}

void iteratorCheck()
{
    algorithms::LinkedList<int> list{ 1, 3, 5, 7 };

    for (auto kek : list)
    {
        std::cout << kek << ' ';
    }

    std::cout << '\n';
}

class Resource
{
private:
    int m_x{ 0 };

public:
    Resource() { std::cout << "Resource allocated\n"; }
    Resource(int x): m_x{ x } { std::cout << "Resource allocated\n"; }
    ~Resource() { std::cout << "Resource deallocated\n"; }

    friend bool operator==(const Resource &res1, const Resource &res2)
    {
        return res1.m_x == res2.m_x;
    }
};

void dynamicMemoryCheck()
{
    algorithms::LinkedList<Resource> list{ { 5 }, { 1 }, Resource() };

    std::cout << "Now, dynamic stuff\n";
    
    algorithms::LinkedList<Resource*> list2{ new Resource{ 5 }, new Resource{ 1 }, new Resource };

    for (auto elem : list2)
    {
        delete elem;
    }
}

void listMain()
{
    // noIteratorCheck();
    // constListCheck();
    // iteratorCheck();
    dynamicMemoryCheck();
}