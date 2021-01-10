#include <iostream>
 
template<class T>
class Auto_ptr4
{
	T* m_ptr;
public:
	Auto_ptr4(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}
 
	~Auto_ptr4()
	{
		delete m_ptr;
	}
 
	// Copy constructor
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr4(const Auto_ptr4& a)
	{
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}
 
	// Move constructor
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4(Auto_ptr4&& a) noexcept
		: m_ptr(a.m_ptr)
	{
		a.m_ptr = nullptr; // we'll talk more about this line below
	}
 
	// Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr4& operator=(const Auto_ptr4& a)
	{
		// Self-assignment detection
		if (&a == this)
			return *this;
 
		// Release any resource we're holding
		delete m_ptr;
 
		// Copy the resource
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
 
		return *this;
	}
 
	// Move assignment
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
	{
		// Self-assignment detection
		if (&a == this)
			return *this;
 
		// Release any resource we're holding
		delete m_ptr;
 
		// Transfer ownership of a.m_ptr to m_ptr
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr; // we'll talk more about this line below
 
		return *this;
	}
 
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
Auto_ptr4<Resource> generateResource()
{
	Auto_ptr4<Resource> res(new Resource);
	return res; // this return value will invoke the move constructor
}
 
int main()
{
	Auto_ptr4<Resource> mainres;
	mainres = generateResource(); // this assignment will invoke the move assignment
 
	return 0;
}

// This prints:
// 
// Resource acquired
// Resource destroyed

// If we only had the deep copy constructor and assignment operator, it would print:
//
// Resource acquired
// Resource acquired
// Resource destroyed
// Resource acquired
// Resource destroyed
// Resource destroyed

// What happens in this program using move semantics:
// 1) Inside generateResource(), local variable res is created and initialized with a dynamically allocated Resource, which causes the first “Resource acquired”.
// 2) Res is returned back to main() by value. Res is move constructed into a temporary object, transferring the dynamically created object stored in res to the temporary object. We’ll talk about why this happens below.
// 3) Res goes out of scope. Because res no longer manages a pointer (it was moved to the temporary), nothing interesting happens here.
// 4) The temporary object is move assigned to mainres. This transfers the dynamically created object stored in the temporary to mainres.
// 5) The assignment expression ends, and the temporary object goes out of expression scope and is destroyed. However, because the temporary no longer manages a pointer (it was moved to mainres), nothing interesting happens here either.
// 6) At the end of main(), mainres goes out of scope, and our final “Resource destroyed” is displayed.

// EXPLANATION TO LINE 31
// If “a” is a temporary r-value, why bother doing “cleanup” if parameter “a” is going to be destroyed anyway?
// Answer: When “a” goes out of scope, a’s destructor will be called, and a.m_ptr will be deleted.
// If at that point, a.m_ptr is still pointing to the same object as m_ptr, then m_ptr will be left as a dangling pointer.
// When the object containing m_ptr eventually gets used (or destroyed), we’ll get undefined behavior.
// 
// Also, there are cases where "a" can be l-value. In such a case, “a” wouldn’t be destroyed immediately, and could be queried further before its lifetime ends

// EXPLANATION TO generateResource()
// Automatic l-values returned by value may be moved instead of copied.
// In the generateResource() function of the Auto_ptr4 example above, when variable res is returned by value, it is moved instead of copied, even though res is an l-value.
// The C++ specification has a special rule that says automatic objects returned from a function by value can be moved even if they are l-values.
// This makes sense, since res was going to be destroyed at the end of the function anyway! We might as well steal its resources instead of making an expensive and unnecessary copy.
// 
// Although the compiler can move l-value return values, in some cases it may be able to do even better by simply eliding the copy altogether
// (which avoids the need to make a copy or do a move at all). In such a case, neither the copy constructor nor move constructor would be called.