#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
 
int main()
{
  constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  };
 
  // Search for two consecutive months that start with the same letter.
  const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                                      [](const auto& a, const auto& b) {
                                        return (a[0] == b[0]);
                                      }) };
 
  // Make sure that two months were found.
  if (sameLetter != months.end())
  {
    // std::next returns the next iterator after sameLetter
    std::cout << *sameLetter << " and " << *std::next(sameLetter)
              << " start with the same letter\n";
  }

  // =========================================
  // In the above example, we use auto parameters to capture our strings by const reference.
  // Because all string types allow access to their individual characters via operator[],
  // we don’t need to care whether the user is passing in a std::string, C-style string, or something else.
  // This allows us to write a lambda that could accept any of these, meaning if we change the type of months later, we won’t have to rewrite the lambda.
  // However, auto isn't always the best choice:
  // =========================================

  constexpr std::array months2{ // pre-C++17 use std::array<const char*, 12>
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  };
 
  // Count how many months consist of 5 letters
  const auto fiveLetterMonths{ std::count_if(months2.begin(), months2.end(),
                                       [](std::string_view str) {
                                         return (str.length() == 5);
                                       }) };
 
  std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";

  // =========================================
  // In this example, using auto would infer a type of const char*.
  // C-style strings aren’t easy to work with (apart from using operator[]).
  // In this case, we prefer to explicitly define the parameter as a std::string_view,
  // which allows us to work with the underlying data much more easily
  // (e.g. we can ask the string view for its length, even if the user passed in a C-style array)
  // =========================================
 
  return 0;
}