#include <iostream>

class Base
{
public:
    Base() {}
};
 
class Derived: public Base
{
public:
    Derived() {}
};
 
int main()
{
    try
    {
        throw Derived();
    }
    catch (const Derived &derived)
    {
        std::cerr << "caught Derived";
    }
    catch (const Base &base)
    {
        std::cerr << "caught Base";
    }

    // if we were to reverse the order of the catch cases:
    //
    // try
    // {
    //     throw Derived();
    // }
    // catch (const Base &base)
    // {
    //     std::cerr << "caught Base";
    // }
    // catch (const Derived &derived)
    // {
    //     std::cerr << "caught Derived";
    // }
    //
    // The base would be caught. That's why, we need to put handlers
    // for derived exceptions first (because Derived is-a Base, but Base is-not-a Derived)
 
    return 0;
}