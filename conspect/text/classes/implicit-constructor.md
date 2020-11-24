If your class has no constructors, C++ will automatically generate a public default constructor for you. This is sometimes called an **implicit constructor** (or *implicitly generated constructor*).

Consider the following class:

`class Date { private: int m_year; int m_month; int m_day; };`

This class has no constructor. Therefore, the compiler will generate a constructor that allows us to create a Date object without arguments.

This particular implicit constructor allows us to create a Date object with no arguments, but doesn’t initialize any of the members unless we create the Date object with direct- or list-initialization (because all of the members are fundamental types, and those don’t get initialized upon creation). If *Date* had members that are `class`-types themselves, for example `std::string`, the constructors of those members would be called automatically.

To make sure the member variables get initialized, we can initialize them at their declaration.

`class Date { private: int m_year{ 1900 }; int m_month{ 1 }; int m_day{ 1 }; };`

If your class has any other constructors, the implicitly generated constructor will not be provided.