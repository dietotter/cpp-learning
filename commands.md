# Compiling
- use flag -pedantic-errors to disable compiler extensions, so that the code runs the same on any system
- use flags -Wall -Weffc++ -Wextra -Wsign-conversion to increase the level of warnings
- use flag -Werror to treat warnings as errors
- use flag -std=c++17 to set C++ language standard (c++2a for C++ 2020)
- command: g++ -o main main.cpp -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -std=c++17

## Specify an alternate include directory
For header files from other directories than the currect cpp file.
- Use -I option: 
``` g++ -o main -I/source/includes main.cpp ```