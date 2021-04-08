#include "Stack.h"

#include <iostream>
#include <exception>

void stackMain()
{
    Stack<int> stack{};

    try
    {
        stack.pop();
    }
    catch(const std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }

    try
    {
        stack.peek();
    }
    catch(const std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }

    std::cout << "Is stack empty: " << stack.isEmpty() << '\n';

    stack.push(2);
    stack.push(3);
    std::cout << "Just popped: " << stack.pop() << '\n';

    stack.push(4);
    std::cout << "Just popped: " << stack.pop() << '\n';

    std::cout << "Last element is " << stack.peek() << " with the stack size of " << stack.size() << '\n';

    Stack<int> stack2{ stack };

    stack2.push(10);
    std::cout << "Last element of copied stack is " << stack2.peek() << " with the stack size of " << stack2.size() << '\n';

    stack = stack2;
    std::cout << "Last element of assigned stack is " << stack.peek() << " with the stack size of " << stack.size() << '\n';
}