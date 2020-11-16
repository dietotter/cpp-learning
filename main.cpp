#include <iostream>
#include <iterator>

// std::find is found in <algorithm> header
int* find(int *first, int *last, int value)
{
    for (int *i{ first }; i < last; ++i)
    {
        if (*i == value)
        {
            return i;
        }
    }
    
    return last;
}
 
int main()
{
    char c{ 'Q' };
    std::cout << &c;
 
    return 0;
}
