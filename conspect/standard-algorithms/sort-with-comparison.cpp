#include <functional> // std::function
#include <iostream>
#include <iterator>
#include <utility>
 
// sort accepts a comparison function
void sort(int *begin, int *end, std::function<bool(int, int)> compare)
{
  for (auto startElement{ begin }; startElement != end; ++startElement)
  {
    auto smallestElement{ startElement };
    
    for (auto currentElement{ std::next(startElement) }; currentElement != end; ++currentElement)
    {
      // the comparison function is used to check if the current element should be ordered
      // before the currently "smallest" element.
      if (compare(*currentElement, *smallestElement))
      {
        smallestElement = currentElement;
      }
    }
 
    std::swap(*startElement, *smallestElement);
  }
}
 
int main()
{
  int array[]{ 2, 1, 9, 4, 5 };
 
  // use std::greater to sort in descending order
  // (We have to use the global namespace selector to prevent a collision
  // between our sort function and std::sort.)
  ::sort(std::begin(array), std::end(array), std::greater{});
 
  for (auto i : array)
  {
    std::cout << i << ' ';
  }
 
  std::cout << '\n';
 
  return 0;
}