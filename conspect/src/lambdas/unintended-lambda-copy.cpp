#include <iostream>
#include <functional>
 
int main()
{
  int i{ 0 };
 
  // Create a new lambda named count
  auto count{ [i]() mutable {
    std::cout << ++i << '\n';
  } };
 
  count(); // invoke count
 
  auto otherCount{ count }; // create a copy of count
 
  // invoke both count and the copy
  count();
  otherCount();
 
  return 0;
}

// Rather than printing 1, 2, 3, the code prints 2 twice. When we created otherCount as a copy of count,
// we created a copy of count in its current state. count‘s i was 1, so otherCount‘s i is 1 as well.
// Since otherCount is a copy of count, they each have their own i.

// Another (less obvious) example:
void invoke(const std::function<void(void)>& fn)
{
    fn();
}
 
int runExample()
{
    int i{ 0 };
 
    // Increments and prints its local copy of @i.
    auto count{ [i]() mutable {
      std::cout << ++i << '\n';
    } };
 
    invoke(count);
    invoke(count);
    invoke(count);
 
    return 0;
}

// The comment to last example is in conspect/text/unintended-lambda-copy.md