#pragma once

#include "List.h"

#include <cstddef>
#include <initializer_list>

namespace algorithms {

    template <class T>
    class LinkedList : public List<T>
    {
    private:
        struct Node
        {
            T value;
            Node *next{ nullptr };
        };

        Node* m_first{ nullptr };
        Node* m_last{ nullptr };
        std::size_t m_length{ 0 };

    public:
        LinkedList() = default;
        LinkedList(std::initializer_list<T> list);
        LinkedList(const LinkedList &list) = delete; // temporarily deleted
        virtual ~LinkedList();

        virtual void add(const T& element) override;
        virtual T remove(std::size_t index) override;
        virtual std::size_t size() const override;
        virtual bool contains(const T& element) const override;

        virtual T& operator[](std::size_t index) const override;
        LinkedList& operator=(std::initializer_list<T> list) = delete; // temporarily deleted
        LinkedList& operator=(const LinkedList& list) = delete; // temporarily deleted
    };

}

#include "LinkedList.inl"