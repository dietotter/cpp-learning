#include <iostream>
#include <string_view>
 
class A
{
public:
    virtual std::string_view getName() const { return "A"; }
};
 
class B: public A
{
public:
    // note: no virtual keyword in B, C, and D
    std::string_view getName() const { return "B"; }
};
 
class C: public B
{
public:
    std::string_view getName() const { return "C"; }
};
 
class D: public C
{
public:
    std::string_view getName() const { return "D"; } 
};
 
int main()
{
    C c;
    B &rBase{ c };
    std::cout << rBase.getName() << '\n';
    // The line above will print "C".
    // Even though getName() of B and C aren't marked as virtual functions,
    // A::getName() is virtual, and B's and C's versions are overrides
 
    return 0;
}