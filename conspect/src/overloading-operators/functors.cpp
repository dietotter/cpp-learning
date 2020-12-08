#include <iostream>

class Accumulator
{
private:
    int m_counter{ 0 };
 
public:
    int operator() (int i) { return (m_counter += i); }
};
 
int main()
{
    Accumulator acc{};
    std::cout << acc(10) << '\n'; // prints 10
    std::cout << acc(20) << '\n'; // prints 30
 
    return 0;
}

// We could implement preservation of data between calls
// with static local variable in function,
// but because functions only have one global instance,
// we'd be limited to using it for one thing at a time.
// With functors, we can instantiate as many
// separate functor objects as we need.