#include <iostream>
#include <string>
 
// returns a lambda
auto makeWalrus(const std::string& name)
{
  // Capture name by reference and return the lambda.
  return [&]() {
    std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior
  };
}
 
int main()
{
  // Create a new walrus whose name is Roofus.
  // sayName is the lambda returned by makeWalrus.
  auto sayName{ makeWalrus("Roofus") };
 
  // Call the lambda function that makeWalrus returned.
  sayName();
 
  return 0;
}

// If we want the captured name to be valid when the lambda is used,
// we need to capture it by value instead (either explicitly or using a default-capture)