#include <array>
#include <cassert>
#include <iostream>

namespace config {
    constexpr int stackSize{ 10 };
}

class Stack
{
private:
    using ContainerType = std::array<int, config::stackSize>;
    using size_type = ContainerType::size_type;
private:
    ContainerType array;
    size_type nextIndex{ 0 };

public:
    void reset()
    {
        nextIndex = 0;
    }

    bool push(int value)
    {
        if (nextIndex == array.size())
        {
            return false;
        }

        array[nextIndex++] = value;
        return true;
    }

    int pop()
    {
        assert(nextIndex > 0 && "Can not pop an empty stack!");

        return array[nextIndex--];
    }

    void print()
    {
        std::cout << "The stack: ";

        for (size_type i{ 0 }; i < nextIndex; ++i)
        {
            std::cout << array[i] << ' ';
        }

        std::cout << '\n';
    }
};