#include <iostream>
#include <memory> // for std::shared_ptr

// class Something; // assume Something is a class that can throw an exception
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	auto ptr1{ std::make_shared<Resource>() };
	std::shared_ptr<Resource> ptr2{ ptr1 };

	// doSomething(std::make_shared<Something>(), std::make_shared<Something>());
 
	return 0;
}