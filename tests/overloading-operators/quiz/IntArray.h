#pragma once

#include <iostream>

class IntArray
{
private:
    int *m_array;
    size_t m_size;

    void deepCopy(const IntArray &intArray);

public:
    IntArray(size_t size);
    IntArray(const IntArray &intArray);
    ~IntArray();

    size_t size() const { return m_size; }

    IntArray& operator=(const IntArray &intArray);
    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream &out, const IntArray &intArray);
};