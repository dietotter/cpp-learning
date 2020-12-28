#pragma once

#include "Shape.h"
#include "Point.h"

#include <iostream>

class Triangle : public Shape
{
private:
    Point m_a;
    Point m_b;
    Point m_c;

public:
    Triangle(const Point &a, const Point &b, const Point &c)
        : m_a{ a }, m_b{ b }, m_c{ c }
    {
    }

    virtual std::ostream& print(std::ostream &out) const override
    {
        out << "Triangle(" << m_a << ", " << m_b << ", " << m_c << ')';
        return out;
    }
};