#pragma once

class Point2d
{
private:
    double m_x{ 0.0 };
    double m_y{ 0.0 };

public:
    Point2d(double x = 0.0, double y = 0.0);
    void print() const;

    friend double distanceFrom(const Point2d &p1, const Point2d &p2);
};