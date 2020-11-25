#include <vector>

class MyClass
{
public:
	static std::vector<char> s_mychars;
 
public:
 
	class init_static // we're defining a nested class named init_static
	{
	public:
		init_static() // the init constructor will initialize our static variable
		{
			for (char ch{ 'a' }; ch <= 'z'; ++ch)
			{
				s_mychars.push_back(ch);
			}
		}
	} ;
 
private:
	static init_static s_initializer; // we'll use this static object to ensure the init_static constructor is called
};
 
std::vector<char> MyClass::s_mychars{}; // define our static member variable
MyClass::init_static MyClass::s_initializer{}; // define our static initializer, which will call the init_static constructor, which will initialize s_mychars

// When static member s_initializer is defined, the init_static() default constructor will be called
// (because s_initializer is of type init_static). We can use this constructor to initialize any static member variables.
// The nice thing about this solution is that all of the initialization code is kept hidden inside the original class with the static member.