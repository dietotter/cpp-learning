#include <iostream>

int main()
{
    // You can declare (but not initialize) variables inside the switch, both before and after the case labels:
    switch (1)
    {
        int a; // okay, declaration is allowed before the case labels
        int b{ 5 }; // illegal, initialization is not allowed before the case labels
    
        case 1:
            int y; // okay, declaration is allowed within a case
            y = 4; // okay, this is an assignment
            break;
    
        case 2:
            y = 5; // okay, y was declared above, so we can use it here too
            break;
    
        case 3:
            int z{ 4 }; // illegal, initialization is not allowed within a case
            break;
    
        default:
            std::cout << "default case\n";
            break;
    }

    // When you define a local variable like “int y;”, it is not visible (in scope) until the point of declaration.
    // The declaration statement doesn’t need to execute -- it just tells the compiler that the variable can be used past that point.
    // The declaration statement only has to execute if the variable has an initializer, because in that case, the variable must be initialized at the declaration.
    // If the variable does not have an initializer, execution can skip over its declaration because executing the declaration wouldn’t do anything anyway.
    // So with that in mind, it’s a little less weird that a variable declared in one case statement can be used in another cases statement, even if the case statement that declares the variable is never executed.

    // Initialization of variables directly underneath a case label is disallowed and will cause a compile error.
    // This is because initializing a variable does require execution, and the case statement containing the initialization may not be executed!

    // If a case needs to define and/or initialize a new variable, best practice is to do so inside a block underneath the case statement:
    switch (1)
    {
        case 1:
        { // note addition of block here
            int x{ 4 }; // okay, variables can be initialized inside a block inside a case
            std::cout << x;
            break;
        }
        default:
            std::cout << "default case\n";
            break;
    }
}