#include <iostream>
#include <cassert>
#include <array>

namespace config {
    constexpr int stackSize{ 10 };
}

class Point3d
{
private:
    int x{};
    int y{};
    int z{};

public:
    void setValues(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void print()
    {
        std::cout << '<' << x << ", " << y << ", " << z << '>';
    }

    bool isEqual(const Point3d &p)
    {
        return (x == p.x) && (y == p.y) && (z == p.z);
    }
};

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

int main()
{
    Point3d point1;
    point1.setValues(1, 2, 3);
 
    Point3d point2;
    point2.setValues(1, 2, 3);
 
    if (point1.isEqual(point2))
    {
        std::cout << "point1 and point2 are equal\n";
    }
    else
    {
        std::cout << "point1 and point2 are not equal\n";
    }
 
    Point3d point3;
    point3.setValues(3, 4, 5);
 
    if (point1.isEqual(point3))
    {
        std::cout << "point1 and point3 are equal\n";
    }
    else
    {
        std::cout << "point1 and point3 are not equal\n";
    }

    Stack stack;
	stack.reset();
 
	stack.print();
 
	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print();
 
	stack.pop();
	stack.print();
 
	stack.pop();
	stack.pop();
 
	stack.print();
 
    return 0;
}