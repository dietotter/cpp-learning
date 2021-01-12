#pragma once

#include <cstddef>

namespace algorithms {
    
    template <class T>
    class List
    {
    public:
        // for iteration purposes
        // virtual const T* begin() const = 0;
        // virtual const T* end() const = 0;

        virtual void add(const T& element) = 0;
        virtual T remove(std::size_t index) = 0;
        virtual std::size_t size() const = 0;
        virtual bool contains(const T& element) const = 0;

        virtual T& operator[](std::size_t index) const = 0;

        virtual ~List() {} 
    };
    
}