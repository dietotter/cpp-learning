#include <iostream>
#include <memory> // for std::shared_ptr
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	// allocate a Resource object and have it owned by std::shared_ptr
	Resource *res = new Resource;
	std::shared_ptr<Resource> ptr1(res);
	{
        // std::shared_ptr<Resource> ptr2(res); // create ptr2 directly from res (instead of ptr1)
        // the commented line above would lead to undefined behaviour, because ptr2 will deallocate the resource ptr1 is still using
        // solution is using copy assignment or copy initialization:
		std::shared_ptr<Resource> ptr2(ptr1); // use copy initialization to make another std::shared_ptr pointing to the same thing
 
		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens
 
	std::cout << "Killing another shared pointer\n";
 
	return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed

// THE SAME EXAMPLE, BUT USING MAKE_SHARED:

// int main()
// {
// 	// allocate a Resource object and have it owned by std::shared_ptr
// 	auto ptr1 = std::make_shared<Resource>();
// 	{
// 		auto ptr2 = ptr1; // create ptr2 using copy initialization of ptr1
 
// 		std::cout << "Killing one shared pointer\n";
// 	} // ptr2 goes out of scope here, but nothing happens
 
// 	std::cout << "Killing another shared pointer\n";
 
// 	return 0;
// } // ptr1 goes out of scope here, and the allocated Resource is destroyed