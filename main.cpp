#include <iostream>

int sumTo(int num)
{
    int sum{};

    for (int i{ i }; i <= num; ++i)
    {
        sum += i;
    }

    return sum;
}

int main()
{
    std::cout << sumTo(5);

    return 0;
}