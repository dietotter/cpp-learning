#include <array>
#include <iostream>
 
int main()
{
    std::array myArray { 7, 3, 1, 9, 5 };

    // Print the array in reverse order.
    // We can use auto, because we're not initializing i with 0.
    // Bad (creates infinite loop because i is unsigned):
    // for (auto i{ myArray.size() - 1 }; i >= 0; --i)
    // {
    //     std::cout << myArray[i] << ' ';
    // }
 
    // Print the array in reverse order.
    for (auto i{ myArray.size() }; i-- > 0; )
    {
        std::cout << myArray[i] << ' ';
    }
 
    std::cout << '\n';
 
    return 0;
}