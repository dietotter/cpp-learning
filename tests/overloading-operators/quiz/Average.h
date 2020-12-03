#pragma once

#include <iostream>
#include <cstdint>

class Average
{
private:
    std::int_least32_t m_sum{ 0 };
    std::int_least8_t m_amount{ 0 };

    double average() const { return static_cast<double>(m_sum) / m_amount; };

public:
    Average& operator+=(int number);

    friend std::ostream& operator<<(std::ostream &out, const Average &av);
};