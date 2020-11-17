#include <algorithm>
#include <array>
#include <iostream>
 
void doubleNumber(int &i)
{
  i *= 2;
}
 
int main()
{
  std::array arr{ 1, 2, 3, 4 };
 
  std::for_each(arr.begin(), arr.end(), doubleNumber); // Before C++20
  // std::ranges::for_each(arr, doubleNumber); // Since C++20, we don't have to use begin() and end()
 
  for (int i : arr)
  {
    std::cout << i << ' ';
  }
 
  std::cout << '\n';
 
  return 0;
}

// Lets compare std::for_each to a range-based for loop:
// 
// std::ranges::for_each(arr, doubleNumber);
// 
// for (auto& i : arr)
// {
//   doubleNumber(i);
// }