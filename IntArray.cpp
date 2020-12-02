#include "IntArray.h"

#include <cassert>

void IntArray::deepCopy(const IntArray &intArray)
{
    // deleting is only needed for overloaded assignment,
    // but since deleting nullptr is fine, it does no harm for copy constructor
    delete[] m_array;

    m_size = intArray.m_size;

    if (intArray.m_array)
    {
        m_array = new int[m_size];

        for (size_t i{ 0 }; i < m_size; i++)
        {
            m_array[i] = intArray.m_array[i];
        }
    }
    else
    {
        m_array = nullptr;
    }
    
}

IntArray::IntArray(size_t size): m_size{ size }
{
    m_array = new int[size];
}

IntArray::IntArray(const IntArray &intArray)
{
    deepCopy(intArray);
}

IntArray::~IntArray()
{
    delete[] m_array;
}

IntArray& IntArray::operator=(const IntArray &intArray)
{
    if (this != &intArray)
    {
        deepCopy(intArray);
    }

    return *this;
}

int& IntArray::operator[](size_t index)
{
    assert(index < m_size && "IntArray out of bounds");

    return m_array[index];
}

const int& IntArray::operator[](size_t index) const
{
    assert(index < m_size && "IntArray out of bounds");

    return m_array[index];
}

std::ostream& operator<<(std::ostream &out, const IntArray &intArray)
{
    for(size_t i{ 0 }; i < intArray.m_size; ++i)
    {
        out << intArray[i] << ' ';
    }

    return out;
}