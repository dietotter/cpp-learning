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
//
// With std::for_each, intentions are clear.
// Also, we could avoid mistakes caused by having to work with additional variable i.
// Additionally, std::for_each can skip elems at the beginning or end of container.
// For example, to skip the first elem of arr, use std::next:
// 
// std::for_each(std::next(arr.begin()), arr.end(), doubleNumber);
// 
// The first element wasn't doubled.