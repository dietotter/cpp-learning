#include <iostream>

int main()
{
    int outer{ 1 };
    while (outer <= 5)
    {
        // loop between 1 and outer
        int inner{ 5 };
        while (inner >= 1)
        {
            if (inner > outer)
            {
                std::cout << "  ";
                --inner;
            }
            else
            {
                std::cout << inner-- << ' ';
            }
        }
 
        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    }

    // int outer{ 5 };
    // while (outer >= 1)
    // {
    //     // loop between 1 and outer
    //     int inner{ outer };
    //     while (inner >= 1)
    //     {
    //         std::cout << inner-- << ' ';
    //     }
 
    //     // print a newline at the end of each row
    //     std::cout << '\n';
    //     --outer;
    // }
    
    // char letter{'a'};
    // while (letter <= 'z')
    // {
    //     std::cout << letter << ' ' << static_cast<int>(letter) << '\n';
    //     letter++;
    // }

    return 0;
}