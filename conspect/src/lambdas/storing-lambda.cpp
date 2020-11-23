#include <iostream>
#include <functional>

// We don't know what fn will be. std::function works with regular functions and lambdas.
void repeat(int repetitions, const std::function<void(int)>& fn)
{
  for (int i{ 0 }; i < repetitions; ++i)
  {
    fn(i);
  }
}
 
int main()
{
  // A regular function pointer. Only works with an empty capture clause.
  double (*addNumbers1)(double, double){
    [](double a, double b) {
      return (a + b);
    }
  };
 
  addNumbers1(1, 2);
 
  // Using std::function. The lambda could have a non-empty capture clause (Next lesson).
  std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
    [](double a, double b) {
      return (a + b);
    }
  };
 
  addNumbers2(3, 4);
 
  // Using auto. Stores the lambda with its real type.
  auto addNumbers3{
    [](double a, double b) {
      return (a + b);
    }
  };
 
  addNumbers3(5, 6);

  // We can't always use auto. In cases where lambda is unknown, we can't use auto
  // (e.g. because we’re passing a lambda to a function as a parameter and the caller determines what lambda will be passed in)
  // in such cases, std::function should be used
  repeat(3, [](int i) {
    std::cout << i << '\n';
  });
 
  return 0;
}