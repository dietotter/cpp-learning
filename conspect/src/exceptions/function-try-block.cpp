#include <iostream>
 
class A
{
private:
	int m_x;
public:
	A(int x) : m_x(x)
	{
		if (x <= 0)
			throw 1;
	}
};
 
class B : public A
{
public:
	B(int x) try : A(x) // note addition of try keyword here
	{
		// we could also throw the exception here, and it would be caught by function try block
	}
	catch (...) // note this is at same level of indentation as the function itself
	{
        // Exceptions from member initializer list or constructor body are caught here
		// if we didn't have this function try block, main() would catch the exception
 
        std::cerr << "Exception caught\n";
 
        // If an exception isn't explicitly thrown here, the current exception will be implicitly rethrown
	}
};
 
int main()
{
	try
	{
		B b(0);
	}
	catch (int)
	{
		std::cout << "Oops\n";
	}
}