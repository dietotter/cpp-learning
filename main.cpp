#include <utility> // for std::swap, use <algorithm> instead if before C++11
#include <iostream>
#include <iterator>

int main()
{
	int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
	constexpr int length{ static_cast<int>(std::size(array)) };
 
	for (int i = 0; i < length - 1; ++i)
    {
        bool isAlreadySorted{ true };

        for (int j = 0; j < length - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                std::swap(array[j], array[j + 1]);
                isAlreadySorted = false;
            }
        }

        if (isAlreadySorted)
        {
            std::cout << "Early termination on iteration " << i << '\n';
            break;
        }
    }
 
	// Now that the whole array is sorted, print our sorted array as proof it works
	for (int index{ 0 }; index < length; ++index)
		std::cout << array[index] << ' ';
 
	std::cout << '\n';
 
	return 0;
}