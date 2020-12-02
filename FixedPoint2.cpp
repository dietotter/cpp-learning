#include "FixedPoint2.h"

#include <cmath>

FixedPoint2::FixedPoint2(int_part_t intPart, fractional_part_t fractionalPart)
{
    bool isNegative{ intPart < 0 || fractionalPart < 0 };

    // assign non-fractional part
    m_intPart = isNegative && intPart >= 0 ? -intPart : intPart;
    
    int absFractionalPart{ std::abs(fractionalPart) };

    // assign fractional part. If the incoming number is > 99, reduce it to 2 digits
    if (absFractionalPart < 100)
    {
        m_fractionalPart = isNegative ? -absFractionalPart : absFractionalPart;
    }
    else
    {
        // we can do it like this, because we know abs(fractionalPart) won't be bigger than 128
        // If it could, we would need to do this in a while loop
        int tempFractionalPart{ absFractionalPart / 10 };

        if (absFractionalPart % 10 >= 5)
        {
            tempFractionalPart += 1;
        }

        m_fractionalPart = isNegative ? -tempFractionalPart : tempFractionalPart;
    }
}

FixedPoint2::FixedPoint2(double d):
    m_intPart{ static_cast<int_part_t>(d) },
    m_fractionalPart{ static_cast<fractional_part_t>(std::round((d - static_cast<int_part_t>(d)) * 100)) }
{
}

FixedPoint2 FixedPoint2::operator-() const
{
    return {
        static_cast<std::int_least16_t>(-m_intPart),
        static_cast<std::int_least8_t>(-m_fractionalPart)
    };
}

FixedPoint2::operator double() const
{
    return m_intPart + 0.01 * m_fractionalPart;
}

bool operator==(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return (fp1.m_intPart == fp2.m_intPart) && (fp2.m_fractionalPart == fp2.m_fractionalPart);
}

FixedPoint2 operator+(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return { static_cast<double>(fp1) + static_cast<double>(fp2) };
}

std::ostream& operator<<(std::ostream &out, const FixedPoint2 &fp)
{
    out << static_cast<double>(fp);

    return out;
}

std::istream& operator>>(std::istream &in, FixedPoint2 &fp)
{
    double d{};
    in >> d;

    fp = FixedPoint2{ d };

    return in;
}