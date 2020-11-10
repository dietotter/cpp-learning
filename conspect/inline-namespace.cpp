#include <iostream>
 
inline namespace v1 // declare an inline namespace named v1
{
    void doSomething()
    {
        std::cout << "v1\n";
    }
}
 
namespace v2 // declare a normal namespace named v2
{
    void doSomething()
    {
        std::cout << "v2\n";
    }
}
 
int main()
{
    v1::doSomething(); // calls the v1 version of doSomething()
    v2::doSomething(); // calls the v2 version of doSomething()
 
    doSomething(); // calls the inline version of doSomething() (which is v1)
 
    return 0;
}

/*  prints:
*       v1
*       v2
*       v1
*/