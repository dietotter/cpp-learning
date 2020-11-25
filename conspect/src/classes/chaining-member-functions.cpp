#include <iostream>

class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() { return m_value; }
};

int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4);

    std::cout << calc.getValue() << '\n';
    return 0;
}

// Note: this is essentially how std::cout is implemented. std::cout is an object,
// and overloaded operator<< is a member function that operates on that object.
// 
// The compiler evaluates
// std::cout << calc.getValue() << '\n';
// to
// (std::cout << calc.getValue()) << '\n';
//
// First, operator<< uses std::cout and calc.getValue() to print the value to the console.
// If operator<< then returned void, we'd end up with
// (void) << '\n';
//
// Instead, operator<< returns *this, which in this context is the std::cout object.
// That way, after the first operator<< has been evaluated, we get:
// (std::cout) << '\n';
// Which then prints the newline.
//
// In this way, we only need to specify the object (in this case, std::cout) once,
// and each function call passes it on to the next function to work with,
// allowing us to chain multiple commands together.