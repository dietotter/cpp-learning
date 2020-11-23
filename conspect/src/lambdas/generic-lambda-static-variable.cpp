#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
 
int main()
{
  // Print a value and count how many times @print has been called.
  auto print{
    [](auto value) {
      static int callCount{ 0 };
      std::cout << callCount++ << ": " << value << '\n';
    }
  };
 
  print("hello"); // 0: hello
  print("world"); // 1: world
 
  print(1); // 0: 1
  print(2); // 1: 2
 
  print("ding dong"); // 2: ding dong
 
  return 0;
}

/*
* In the above example, we define a lambda and then call it with two different parameters
* (a string literal parameter, and an integer parameter).
* This generates two different versions of the lambda
* (one with a string literal parameter, and one with an integer parameter).

* Most of the time, this is inconsequential.
* However, note that if the generic lambda uses static duration variables,
* those variables are not shared between the generated lambdas.

* We can see this in the example above, where each type
* (string literals and integers) has its own unique count!
* Although we only wrote the lambda once,
* two lambdas were generated -- and each has its own version of callCount.
* To have a shared counter between the two generated lambdas,
* we’d have to define a variable outside of the lambda.
* For now, this means defining the variable even outside of the function the lambda is defined in.
* In the above example, this means adding a global variable.
* We’ll be able to avoid the global variable after talking about lambda captures.
*/