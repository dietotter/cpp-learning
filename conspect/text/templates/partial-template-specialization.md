# Partial template specialization
- Consider:

        template <class T, int size> // size is the expression parameter
        class StaticArray
        {
        private:
            // The expression parameter controls the size of the array
            T m_array[size]{};
        
        public:
            T* getArray() { return m_array; }
        
            T& operator[](int index)
            {
                return m_array[index];
            }
        };
        
        // defined as non-member for this example's purpose
        template <typename T, int size>
        void print(StaticArray<T, size> &array)
        {
            for (int count{ 0 }; count < size; ++count)
                std::cout << array[count] << ' ';
        }

    `print()` runs without problem, if we use it with most types, for example, with ints. However:

        int main()
        {
            // declare a char array
            StaticArray<char, 14> char14{};
        
            std::strcpy(char14.getArray(), "Hello, world!");
        
            // Print the array
            print(char14);
        
            return 0;
        }

    When using chars, it will print `H e l l o ,   w o r l d !`. So with chars we should probably print without those whitespaces.

    We can't solve the issue using full template specialization, because all template parameters must be explicitly defined:
   
        template <>
        void print(StaticArray<char, 14> &array)
        {
            for (int count{ 0 }; count < 14; ++count)
                std::cout << array[count];
        }

    This will only work for `StaticArray<char, 14> char14{};`.

    Solution: partial template specialization.
- **Partial template specialization** allows us to specialize classes (but not individual functions) where some, but not all, template parameters have been explicitly defined:

        // overload of print() function for partially specialized StaticArray<char, size>
        template <int size> // size is still a templated expression parameter
        void print(StaticArray<char, size> &array) // we're explicitly defining type char here
        {
            for (int count{ 0 }; count < size; ++count)
                std::cout << array[count];
        }

    Full example: `conspect/src/templates/partial-template-specialization.cpp`

    **Note**: As of C++14, partial template specialization can only be used with classes, not template functions (functions must be fully specialized). Our `void print(StaticArray<char, size> &array)` example works because the print function is not partially specialized (it’s just an overloaded function using a class parameter that’s partially specialized).

## Partial template specialization for member functions
- The limitation on the partial specialization of functions can lead to some challenges when dealing with member functions. Consider:

        template <class T, int size> // size is the expression parameter
        class StaticArray
        {
        private:
            // The expression parameter controls the size of the array
            T m_array[size]{};
        
        public:
            T* getArray() { return m_array; }
        
            T& operator[](int index)
            {
                return m_array[index];
            }

            // print is a member function now
            void print()
            {
                for (int i{ 0 }; i < size; ++i)
                {
                    std::cout << m_array[i] << ' ';
                }
                std::cout << '\n';
            }
        };

        // Doesn't work
        template <int size>
        void StaticArray<double, size>::print()
        {
            for (int i{ 0 }; i < size; ++i)
                std::cout << std::scientific << m_array[i] << ' ';
            std::cout << '\n';
        }

    One workaround would be to partially specialize the entire class, but that would lead to a lot of duplicate code.

    The correct workaround would be to use inheritance and a common base class: see `conspect/src/templates/partial-template-specialization-for-members.cpp`

## Partial template specialization for pointers
- For pointer types (e.g. when we need to create specialized versions of constructor and destructor (e.g. for deep copy)), we can define special version of the class that works for pointer values. Example: `conspect/src/templates/partial-template-specialization-for-pointers.cpp`