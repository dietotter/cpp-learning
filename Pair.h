#pragma once

template <class T, class S>
class Pair
{
private:
    T m_first;
    S m_second;

public:
    Pair(const T &first, const S &second)
        : m_first{ first }, m_second{ second }
    {
    }

    const T& first() const { return m_first; }
    const S& second() const { return m_second; }
};