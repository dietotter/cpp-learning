// for strcpy_s
#define __STDC_WANT_LIB_EXT1__ 1

#include <cstring>
#include <iostream>

void useStrcpy()
{
    char source[]{ "Copy this!" };
    char dest[50];
    std::strcpy(dest, source);
    std::cout << dest << '\n'; // prints "Copy this!"

     // if dest would have the length of 5, array overflow would occur
     // We could use strncpy() instead, which allows to specify the size of the buffer
     // Though, strncpy() doesn't ensure strings are null terminated, which still
     // leaves plenty of room for array overflow.
}

// in C++11, strcpy_s() is preferred, but not all compilers support this,
// and to use it, we have to define __STDC_WANT_LIB_EXT1__ with value 1
void useStrcpyS()
{
    char source[]{ "Copy this!" };
    char dest[5]; // note that the length of dest is only 5 chars!
    strcpy_s(dest, 5, source); // A runtime error will occur in debug mode
    std::cout << dest << '\n';

    // because not all compilers support strcpy_s(), strlcpy() is a popular alternative
    // - though it's non-standard, and thus not included in a lot of compilers
}

int main()
{
 
    return 0;
}