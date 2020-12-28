#pragma once

#include "Shape.h"
#include "Point.h"

#include <iostream>

class Circle : public Shape
{
private:
    Point m_center;
    int m_radius{};

public:
    Circle(const Point &center, int radius)
        : m_center{ center }, m_radius{ radius }
    {
    }

    virtual std::ostream& print(std::ostream &out) const override
    {
        out << "Circle(" << m_center << ", radius " << m_radius << ')';
        return out;
    }

    int getRadius() const { return m_radius; }
};