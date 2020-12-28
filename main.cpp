#include "Point.h"
#include "Circle.h"
#include "Triangle.h"

#include <vector>
#include <iostream>

int getLargestRadius(const std::vector<Shape*> &v)
{
    int largestRadius{ 0 };

    for (const auto *shape : v)
    {
        if (auto *circle{ dynamic_cast<const Circle*>(shape) })
        {
            largestRadius = largestRadius < circle->getRadius() ? circle->getRadius() : largestRadius;
        }
    }

    return largestRadius;
}

int main()
{
	std::vector<Shape*> v{
        new Circle{Point{1, 2, 3}, 7},
        new Triangle{Point{1, 2, 3}, Point{4, 5, 6}, Point{7, 8, 9}},
        new Circle{Point{4, 5, 6}, 3}
    };

	// print each shape in vector v on its own line here
    for (const auto *shape : v)
    {
        std::cout << *shape << '\n';
    }

    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';

	// delete each element in the vector here
    for (const auto *shape : v)
    {
        delete shape;
    }

	return 0;
}