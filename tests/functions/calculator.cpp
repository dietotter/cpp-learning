#include <iostream>
#include <limits>
#include <functional>

int askForNumber()
{
    int usersNum{};
    std::cout << "Enter an int: ";
    std::cin >> usersNum;
        
    return usersNum;
};

char askForOperator()
{
    char usersOp{};

    while (true)
    {
        std::cout << "Enter operator (+, -, *, /): ";
        std::cin >> usersOp;

        switch (usersOp)
        {
            case '+':
            case '-':
            case '*':
            case '/':
                return usersOp;
            default:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect input.\n";
                break;
        }
    }
}

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int divide(int x, int y)
{
    return x / y;
}

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char op)
{
    switch (op)
    {
        default:
        case '+':
            return add;
        case '-':
            return subtract;
        case '*':
            return multiply;
        case '/':
            return divide;
    }
}

int main()
{
    int num1{ askForNumber() };
    char op{ askForOperator() };
    int num2{ askForNumber() };

    ArithmeticFunction arithmeticFunc{ getArithmeticFunction(op) };

    std::cout << num1 << ' ' <<  op << ' ' << num2 << " = " << arithmeticFunc(num1, num2) << '\n';
    
    return 0;
}
