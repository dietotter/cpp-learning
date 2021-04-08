#pragma once

#include <new>
#include <iterator>
#include <stdexcept> // for underflow_error

// ArrayList approach

template <class T>
class Stack
{
private:
    T *m_array;
    std::size_t m_size{ 0 };
    std::size_t m_arraySize{ 0 };

    void deepCopy(const Stack &stack)
    {
        delete[] m_array;

        // std::size didn't work for some reason (investigate later)
        // maybe because we can't get length of dynamic arrays with sizeof
        m_array = new T[stack.m_arraySize];
        m_size = stack.m_size;

        for (size_t i{ 0 }; i < m_size; ++i)
        {
            m_array[i] = stack.m_array[i];
        }
    }

public:
    Stack()
    {
        // Some info about operator new:
        // array = new T[size]; // throws bad_alloc exception
        // we could use nothrow from header <new>,
        // so that if allocation fails, nullptr is returned (no exception thrown):
        // array = new (std::nothrow) T[size];
    }

    Stack(const Stack &stack)
    {
        deepCopy(stack);
    }

    ~Stack()
    {
        delete[] m_array;
    }

    bool isEmpty() const { return m_size == 0; }
    std::size_t size() const { return m_size; }

    // Some info about passing element to LinkedList/Stack/etc:
    // The most efficient solution involves some code duplicate with 2 functions,
    // one taking const T& data, second taking T&& data
    // (https://stackoverflow.com/questions/18884269/adding-item-into-a-linked-list-pass-by-reference-or-value)
    // Also, some info that IO should be done asynchronously in such containers:
    // (https://stackoverflow.com/questions/50672771/is-it-better-to-pass-linked-list-object-by-reference-or-value)
    void push(T data)
    {
        if (m_arraySize == 0)
        {
            m_size = 1;
            m_arraySize = 1;
            m_array = new T[m_arraySize];

            m_array[0] = data;

            return;
        }

        if (m_size == m_arraySize)
        {
            m_arraySize *= 2;
            T *array{ new T[m_arraySize] };

            // can't use memcpy here, because if T is not a basic data type,
            // it would prevent T's copy constructor from running
            // (https://stackoverflow.com/questions/4772303/memcpy-and-c-class-templates-how-to-use-it)

            for (std::size_t i{ 0 }; i < m_size; ++i)
            {
                array[i] = m_array[i];
            }

            delete[] m_array;
            m_array = array;
        }

        m_array[m_size++] = data;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Trying to pop from an empty stack");
        }

        if (m_size <= m_arraySize / 4)
        {
            m_arraySize /= 2;
            T *array{ new T[m_arraySize] };
            
            for (std::size_t i{ 0 }; i < m_size; ++i)
            {
                array[i] = m_array[i];
            }

            delete[] m_array;
            m_array = array;
        }

        return m_array[m_size-- - 1];
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw std::underflow_error("Trying to peek an empty stack");
        }

        return m_array[m_size - 1];
    }

    Stack& operator=(const Stack &stack)
    {
        if (this != &stack)
        {
            deepCopy(stack);
        }

        return *this;
    }
};