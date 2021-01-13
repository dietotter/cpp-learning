#include "LinkedList.h"

#include <stdexcept>
#include <string>

namespace algorithms {

    template <class T>
    LinkedList<T>::LinkedList(std::initializer_list<T> list)
    {
        for (auto &element : list)
        {
            auto node{ new Node{ element } };
            if (!m_first)
            {
                m_first = node;
            }

            if (m_last)
            {
                m_last->next = node;
            }

            m_last = node;
            ++m_length;
        }
    }

    template <class T>
    LinkedList<T>::~LinkedList()
    {
        if (m_first)
        {
            Node *node{ m_first };
            while(node)
            {
                Node *tempo{ node->next };
                delete node;
                node = tempo;
            }
        }
    }

    template <class T>
    void LinkedList<T>::add(const T& element)
    {
        auto node{ new Node{ element } };
        if (!m_first)
        {
            m_first = node;
        }

        if (m_last)
        {
            m_last->next = node;
        }

        m_last = node;
        ++m_length;
    }

    template <class T>
    T LinkedList<T>::remove(std::size_t index)
    {
        Node *previousNode{ nullptr };
        auto node{ m_first };
        std::size_t i{ 0 };
        while (i < index && node)
        {
            previousNode = node;
            node = node->next;
            ++i;
        }

        if (!node)
        {
            throw std::out_of_range("Out of LinkedList bounds. Index: " + std::to_string(index));
        }

        if (m_first == node)
        {
            m_first = node->next;
        }

        if (m_last == node)
        {
            m_last = previousNode;
        }

        if (previousNode)
        {
            previousNode->next = node->next;
        }

        T contents{ node->value };

        delete node;
        --m_length;

        return contents;
    }

    template <class T>
    std::size_t LinkedList<T>::size() const
    {
        return m_length;
    }

    template <class T>
    bool LinkedList<T>::contains(const T& element) const
    {
        if (m_first)
        {
            Node *node{ m_first };
            while(node)
            {
                if (node->value == element)
                {
                    return true;
                }

                node = node->next;
            }
        }

        return false;
    }

    template <class T>
    T& LinkedList<T>::operator[](std::size_t index)
    {
        auto node{ m_first };
        std::size_t i{ 0 };
        while (i < index && node)
        {
            node = node->next;
            ++i;
        }

        if (!node)
        {
            throw std::out_of_range("Out of LinkedList bounds. Index: " + std::to_string(index));
        }

        return node->value;
    }

    template <class T>
    const T& LinkedList<T>::operator[](std::size_t index) const
    {
        auto node{ m_first };
        std::size_t i{ 0 };
        while (i < index && node)
        {
            node = node->next;
            ++i;
        }

        if (!node)
        {
            throw std::out_of_range("Out of LinkedList bounds. Index: " + std::to_string(index));
        }

        return node->value;
    }

}