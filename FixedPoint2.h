#pragma once

#include <iostream>
#include <cstdint>

class FixedPoint2
{
public:
    using int_part_t = std::int_least16_t;
    using fractional_part_t = std::int_least8_t;

private:
    int_part_t m_intPart{};
    fractional_part_t m_fractionalPart{};

public:
    FixedPoint2(int_part_t intPart = 0, fractional_part_t fractionalPart = 0);
    FixedPoint2(double d);

    FixedPoint2 operator-() const;
    operator double() const;

    friend bool operator==(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend FixedPoint2 operator+(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend std::ostream& operator<<(std::ostream& out, const FixedPoint2 &fp);
    friend std::istream& operator>>(std::istream& in, FixedPoint2 &fp);
};