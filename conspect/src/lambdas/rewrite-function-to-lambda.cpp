#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
 
static bool containsNut(std::string_view str) // static means internal linkage in this context
{
  // std::string_view::find returns std::string_view::npos if it doesn't find
  // the substring. Otherwise it returns the index where the substring occurs
  // in str.
  return (str.find("nut") != std::string_view::npos);
}
 
int main()
{
  constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };
 
  // std::find_if takes a pointer to a function
  // const auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };

  // Define the function right where we use it.
  const auto found{ std::find_if(arr.begin(), arr.end(),
                           [](std::string_view str) // here's our lambda, no capture clause
                           {
                             return (str.find("nut") != std::string_view::npos);
                           }) };
  // We have omitted the trailing type, but since operator!= returns a bool, a lambda will return a bool too

 
  if (found == arr.end())
  {
    std::cout << "No nuts\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }
 
  return 0;
}