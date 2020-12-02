#include "Average.h"

Average& Average::operator+=(int number)
{
    m_sum += number;
    ++m_amount;

    return *this;
}

std::ostream& operator<<(std::ostream &out, const Average &av)
{
    out << av.average();

    return out;
}