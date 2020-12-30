# Why it may be a good idea to pass errors back to the caller
Different applications may want to handle errors in different ways. A console application may want to print a text message. A windows application may want to pop up an error dialog. In one application, this may be a fatal error, and in another application it may not be. By passing the error back up the stack, each application can handle an error from mySqrt() in a way that is the most context appropriate for it! Ultimately, this keeps mySqrt() as modular as possible, and the error handling can be placed in the less-modular parts of the code

        #include <cmath> // for sqrt() function
        #include <iostream>
 
        // A modular square root function
        double mySqrt(double x)
        {
            // If the user entered a negative number, this is an error condition
            if (x < 0.0)
                throw "Can not take sqrt of negative number"; // throw exception of type const char*
        
            return sqrt(x);
        }
        
        int main()
        {
            std::cout << "Enter a number: ";
            double x;
            std::cin >> x;
        
            try // Look for exceptions that occur within try block and route to attached catch block(s)
            {
                double d = mySqrt(x);
                std::cout << "The sqrt of " << x << " is " << d << '\n';
            }
            catch (const char* exception) // catch exceptions of type const char*
            {
                std::cerr << "Error: " << exception << std::endl;
            }
        
            return 0;
        }