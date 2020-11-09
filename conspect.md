# Data
- Data is any information, that can be processed, stored and moved by computer.
- Value is a single piece of data, stored somewhere in memory
- Variable is a named region of memory
- Variable is instantiated when it is created and assigned a memory address
- For some advanced data types, direct initialization (int a(5)) can perform better than copy initialization (int a = 5). Prior to C++11, direct initialization was the recommended way.
- Direct brace initialization (int a{5}) is the preferred way, because compiler shows error if we try to put a wrong value (int a{4.5}). int a{} initializes variable a with 0.
- If we never initialize a variable (int x;), it will contain some unexpected value.
- bit = `bi`nary digi`t`

# CIN/COUT
- '\n' is preferred to std::endl (doesn't do the redundant flush endl does)

# Variable
- Variable scope is a compile-time property, lifetime - is a runtime property

# Functions
- If we want the compiler to see the function which is defined after it is called:

``` int main()              ```
``` {                       ```
```     add(1, 2);          ```
```                         ```
```     return 0;           ```
``` }                       ```

``` int add(int x, int y)   ```
``` {                       ```
```     return x + y;       ```
``` }                       ```

We need to either place add() declaration before the main(), or use a forward declaration:

``` int add(int x, int y);  ```

The line of code above is called a function prototype

## Declaration vs Definition
- Definition implements function/type identifiers and instantiates variable identifiers (int x; (don't confuse with initialization))
- Declaration is a statement that tells the compiler about the existence of an identifier and its type
- All definitions serve as declarations

# Compilation/translation/linking
- Code file ==(translation)==> translation unit ==(compilation)==> object file ==(linking)==> executable
- All translation phases: https://en.cppreference.com/w/cpp/language/translation_phases

# Header files
- Headers typically contain only function and variable declarations, not definitions (otherwise it would violate the One Definition Rule). Exception - symbolic constants
- When including headers, use <> to include those that come with the compiler, and "" for other.
- Best practise for include order: my own headers first, then 3rd party library, then standard library headers.
- Header guards prevent multiple definitions to occur. They look like (add.h):

``` #ifndef ADD_H ```

``` #define ADD_H ```

``` // code here  ```

``` #endif        ```

or

``` #pragma once  ```

(not all compilers support the pragma version, though most modern compilers do)

# Debugging
- When printing debug information, use std::cerr instead of std::cout, because cerr (unlike cout) is unbuffered - it doesn't need to flush to print information, so prints it immediately.

# Data types
- To convert between fundamental data types, we use a type case called a static cast: `static_cast<int>('a')`

## Integers
- `int getValue(void)` is deprecated; use `int getValue()`
- Minimum size of an integer is 2 bytes, not 4, as I assumed. Though, on most modern machines (including mine), it is 4 bytes.
- Unsigned integers (>=0) should be avoided, except for some cases, like bit manipulation, array indexing, and, probably, some embedded system (like Arduino, for performance reasons)
- In `<cstdint>`, there are fixed-width integer (usual integers don't have fixed size on different machines). `std::int32_t` and similar types should not be used, as they are less portable. Instead, to have a variable with particular size, we should use `std::int_fast32_t` to favor performance and `int_least32_t` to favor memory conservation. There are also unsigned versions for these: `uint_fast32_t`.
- We should avoid using 8-bit fixed-width variables (`int8_t`), as they often behave as chars.
- We should avoid compiler-specific fixed-width integers: e.g. Visual Studio's `__int16`
- `std::size_t` - unsigned integral type, used to represent the size or length of objects.`size_t`'s maximum size will most likely be equivalent to address-width of the app: e.g. for 32-bit apps, it will be a 32-bit unsigned integer. It is defined to be big enough to hold the size of the largest object creatable on the system.

## Scientific notation
- Takes form of: significand x 10^exponent
- 34.50 = 3.450e1
- 0.004000 = 4.000e-3
- 123.005 = 1.23005e2
- 146000 = 1.46e5 (or 1.46000e5; trailing zeros in a whole number with no decimal are not significant, but good for documentation)
- 0.0000000008 = 8e-10
- 34500.0 = 3.45000e4
- The above versions look the same in code, for example, if we assign the value to double type variable
- We keep trailing zeros, if the original number had a decimal point. We do this because of more precision (87.00 is more precise than 87, as in the first case, the number might be between 86.50 and 87.49, and in the second, it can be between 86.9950 and 87.0049). However, in C++ these numbers are treated exactly the same, and the compiler will store the same value for each.

## Floats
- When using floating point literals, we should include at least one decimal place to help compiler understand that the number is float (`double x{5.0}; float y{5.0f};`)
- Precision defines how many significant digits it can represent without information loss (in 1.23005e2, there are 6 significant digits). `std::cout` has a default precision of 6.
- Doubles are more precise than floats (they occupy more significant digits)
- As most floating point numbers can not be stored precisely, rounding errors occur. Which, for example, makes floating point comparisons very hard
- There are special floating point nums: inf, -inf and nan. They are only available if the compiler uses a specific format (IEEE 754)
- When comparing floats, we need to compare using both absolute epsilon - really small number, which will be bigger than `|x - y|`, and relative epsilon - like absolute epsilon, but relative to the biggest of the pair (x, y). Read more: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/. We should never compare floats by using operator ==.

## Booleans
- `true` or `false` are std::cout printed as 1 or 0. If we want them printed as "true" or "false", we could use `std::cout << std::boolalpha;` beforehand (and `std::noboolalpha` to turn it back off)
- You can't `bool b{ 4 };`, but you can `bool b = 4;` (equals to true)
- `std::cin` takes 0 and 1 for boolean values; true or false will both result in 0.
- If we pass a non-zero value to if(), it will be equal to true (if the type is convertible to bool)

## Chars
- If user enters to `std::cin << ch` something like "asdf", then it will only grab 'a' and assign it to `ch`. The rest is left in cin buffer. If we do the `std::cin << ch` again, it will not ask the user for input, but grab the next letter in the buffer ('s')
- If you want to work with Unicode chars, there are types char8_t, char16_t, and char32_t

## Literals
- If we want to change the default type of a literal, we can add a suffix to it: (e.g. `5u` - unsigned int; `2.4f` - float (`2.4` - double))
- C-style string literals are concatenated: `"Hey, " "shithead"`. Also, we shouldn't assign them to variables or pass them to functions.
- Octal literals are prefixed by 0: `012` in octal = `10` in decimal. To assign hexadecimal, we use prefix 0x: `0xF` = `15`. We can also assign binary literal using hexadecimal: `int bin{0x01};` - binary 0000 0001; `int bin{0xF770};` - binary 1111 0111 0111 0000. From C++14 - binary literals, using 0b: `0b11` = 0000 0011
- Also, from C++14 we can add a digit separator `'`: `2'012'673'123`, `0b1011'0010`
- We can print in decimal, octal and hex: `std::dec`, `std::oct`, `std::hex`
- With binary:

`#include <bitset>`

`...`

`std::bitset<8> bin1{ 0xC5 };`

`std::bitset<4> bin2{ 0b1010 };`

then `std::cout << bin1 << ' ' << bin2 << '\n';` gets us `11000101 1010`

Note: we could also declare bin1, bin2 as unsigned int, but we would need to `std::bitset<4>{ bin2 }` when doint `std::cout`.

## Constants
- Runtime constants are those whose values are resolved at runtime. Example:

`int kek{};`

`std::cin >> kek;`

`const int lol{kek};`

- Compile-time constants are those whose values are resolved at compile-time. Example:

`const double gravity { 9.8 };`

Compile-time constants should be declared as constexpr: `constexpr double gravity{9.8};`

- To create symbolic constants (ones which will replace magic numbers if we need them), we use constexpr: `constexpr int maxBoostersInBundle{10};`

- Nice way to use symbolic constants in multi-file program: see `constants-example.h`.

# Preprocessor directives
- Macros like `#define MY_NAME Nik` should be avoided. 1. The value would not show up in the debugger. 2. Macros could conflict with normal code, for example if defined in header.

# Operators
- In ternary operator, both expressions mush either match by their type, or the second expression must be convertible to the type of the first expression (`x != 5 ? x : "x is 5"` won't compile)
- We should never use expressions with side effects (those for example which change the variable value after they are executed) in the same statements as the variables they have side effects on. For example, `int y{ foo(++x, x) };`. We don't know which order parameters of foo() are evaluated in (not specified in C++). That's why, the second argument may be x or x+1 because of the first argument - unclear behaviour.

# Bit manipulation
- `std::bitset` is also used for storing flags (since booleans waste 7 bits, as they weigh 1 byte, but use only 1 bit to store `true` or `false` value). E.g. `std::bitset<8> mybitset { 0b0001'0011};` stores 0001 0011, and we can `set(2)` => 0001 0111; `flip(2)` => 0001 0011; `reset(0)` => 0001 0010; `test(4)` => returns 1; `test(3)` => returns 0.
- We have bitwise operators:
    - left shift: `0011 << 1 = 0110`; `0011 << 3 = 1000` (bits shifted off the end are lost)
    - right shift: `1100 >> 1 = 0110`; `1100 >> 3 = 0001` (same thing)
    - NOT: `~0000 0100 = 1111 1011`
    - OR: `0101 | 0110 = 0111`
    - AND: `0101 | 0110 = 0100`
    - XOR: `0101 | 0110 = 0011`. When evaluating bitwise numbers in column, if there is even number of 1 bits in one column, the result is 0, if odd - result is 1.
    - and their assignment counterparts: `x <<= 1;` and so on
- Prior to C++, don't shift signed integers (and then still it's better to use unsigned)
- Convert binary to decimal: 0001 0101 => 0*2^7 + 0*2^6 + 0*2^5 + 1*2^4 + 0*2^3 + 1*2^2 + 0*2^1 + 1*2^0 = 1*2^4 + 1*2^2 + 1*2^0 = 16 + 4 + 1 = 21
- Convert decimal to binary:
    1. Writing down remainders from the bottom up:
        - 41 / 2 = 20 r1
        - 20 / 2 = 10 r0
        - 10 / 2 = 5 r0
        - 5 / 2 = 2 r1
        - 2 / 2 = 1 r0
        - 1 / 2 = 0 r1

        101001 => 0010 1001 = 41 in decimal
    2. The largest power of 2 that's smaller than 41 is 32. Start from it:
        - 41 >= 32? Yes, so the 32 bit must be 1. 41 - 32 = 9
        - 9 >= 16? No, so the 16 bit is 0.
        - 9 >= 8? Yes, the 8 bit is 1. 9 - 8 = 1
        - 1 >= 4? No, the 4 bit is 0
        - 1 >= 2? No, the 2 bit is 0
        - 1 >= 1? Yes, the 1 bit is 1

        101001 => 0010 1001 = 41 in decimal

- Adding binary numbers is as usual - in column:

    0110 +

    0111 =

    1101

- To represent signed numbers, we use the method called `two's complement` - the leftmost (most significant) bit represents a sign - 0 means the number is positive, 1 - negative. Negative numbers are bitwise inverse of the positive number, plus 1. E.g., representing -5:
    - Representation of regular 5: 0000 0101
    - Invert all the bits: 1111 1010
    - Add 1: 1111 1011
- We add 1 to have only one representation of 0. (if we didn't, zero would be both 0000 0000 and 1111 1111. This way, zero is always 0000 0000. And -1 is 1111 1111 (without adding one, it would be 1111 1110 - just the inverse of a regular 1 - 0000 0001))
- To convert binary two's complement to integer, look at the sign bit. If 0 - convert as regular, if 1:
    - Representation of -5: 1111 1011
    - Invert the bits: 0000 0100
    - Add 1: 0000 0101
    - Convert to decimal: 1*2^2 + 1*2^0 = 5
    - Write the original minus sign: -5


## Bit masks and flags
- See `bitmask.cpp`
- Using bit flags is useful because:
    - We save memory. If we have 100 objects with each having 8 booleans defined, we'd use 800 bytes of memory. With bit flags, we'd use 8 bytes for the bit mask + 100 bytes for bit flag variables, which each weighs one byte
    - It's easier and more performant when, for example, passing flags to function. Instead of 32 arguments, we can pass only one

# Scopes
- It's a good idea to keep block nesting level to 3 or less (the maximum number of blocks you can be inside in a function)
- Scope defines where a single declaration can be seen and used

## Namespaces
- We can use the scope resolution operator `::` without the preceding namespace. In this case, the identifier is looked for in global namespace (most of the times, `::print()` is equal to `print()`)
- Namespaces can be nested. Also, in C++17 nested namespaces can be declared like this: `namespace foo::goo{ ... }`
- You can have namespace aliases: `namespace boo = foo:goo;`. Now we can `std::cout << boo::add(1, 2);`
- Namespaces should be used to separate application-specific code from reusable code (e.g. math and physics functions could go into separate namespace `math::`). Also, if a library or code will be distributed to others, its better to write it in own namespace

## Storage duration
- **Storage duration** determines what rules govern how and when a variable is created and destroyed. In most cases, variable's duration directly determines its lifetime.
- Variables with **dynamic duration** are created and destroyed by programmer request (dynamically allocated variables)

## Local variables
- Local variables have **automatic storage duration**, which means they are created at the point of definition and are destroyed when the block ends. That's why they're sometimes called automatic variables.
- Identifiers **linkage** determines whether other declarations of that name refer to the same object or nor. Local variables have no linkage, which means that each declaration refers to a unique object. E.g.: `conspect/local-variables.cpp`
- Uninitialized by default (`int x;` - uninitialized; `int x{};` - zero-initialized; `int x{1};` - initialized with value)

## Global variables
- Global variables are variables declared outside of a function
- They have file scope (also informally - global namespace scope)
- Because defined outside of a function, they are considered to be part of the global namespace
- They are created when the program starts, and are destroyed when it ends. This is called **static duration**. Variables with *static duration* are sometimes called **static variables**
- Zero-initialized by default (`int gX;` - zero-initialized). If constant - must be initialized
- Local variables can shadow the global variables (if local variable x is created with the same name as global, when you try to access using their identifier `x`, local variable is accessed). However, unlike local variables shadowing in inner blocks, you can still access global variable by using `::x`. Still, variable **shadowing** should be avoided
- Global variables are initialized as a part of program startup, before the main function. This happens in two phases:
    1. In **static initialization** phase, global variables with constexpr initializers (including literals) are initialized to those values, and global vars without initializers are zero-initialized.
    2. In **dynamic initialization**, global variables with non-constexpr initializers are initialized (though the phase is more complex and nuanced)
- Within a single file, global variables are mostly initialized in order of definition. The order of initialization across different files is not defined
- Dynamic initialization of global variables should be avoided whenever possible
- Non-contant global variables should be avoided almost always
- Advices for all global variables:
    1. Put them into namespaces
    2. Encapsulate the variable: make its linkage internal (if its not already), then provide external global access function - these functions can ensure proper usage (e.g. do input validation etc). `double getGravity() { ...; return constants::gravity; }`
    3. When writing otherwise standalone function, that uses global var, don't use the var directly in function body, rather pass it as an argument. This way if we need to use another value, we can just change the argument.
    
    ` double instantVelocity(int time, double gravity) { return gravity * time } `

    ` int main() { std::cout << instantVelocity(5, constants::gravity);} `

## Linkage
- Identifier with **internal linkage** is not accessible from other files (not exposed too the linker). This means that if two files have identically named identifiers with internal linkage, those identifiers will be treated as independent
- Const and constexpr global variables have internal linkage by default
- Use `static` to make a non-constant global variable internal (`static int gX;`)

    ### Storage class specifier
    - **Storage class specifier** sets both the identifier's linkage and its storage duration (but not its scope). The most commonly used keywords are `static`, `extern` and `mutable`.

- Internal objects and functions don't violate the one-definition rule.
- Functions also default to external linkage, and can be made internal using `static`

## External linkage
- To make external variable (accessible by other files), we can use `extern` keyword: `extern const int gY{ 3 };` (non-constant globals are external by default: `int gX{ 2 };`)
- To forward declare a variable, use `extern` keyword, with no initialization value: `extern int gX; extern const int gY;`
- `constexpr` globals can be defined by extern, but this is useless, because they can not be forward declared
- Informally, the term "file scope" is more often applied to global variables with internal linkage, and "global scope" to those with external linkage.

## Global constants and inline variables
- We can define global constants in a header using constexpr (see `symbolic-constants.h`). In smaller programs this is OK, in bigger - they increase the compile times, as every source file including constants header will be recompiled on every small change in header. Also, if they can't be optimized away by a compiler, this can use a lot of memory. If we have 20 constants, and they take a lot of space, they are defined every time we include header in source file.
- Another method - define constants in .cpp file as `extern const` (constexpr can't be extern), then do the forward declarations in .h file using `extern const` without initialization. The downsides are:
    1. These constants are now considered compile-time constants only within the .cpp file they are defined in, not anywhere else, and thus can't be used anywhere that requires a compile-time constant.
    2. The compiler may not optimize these as much (*side note* - for example, compiler can optimize constants by replacing the places where constants are used with their values, avoiding having to create and initialize a variable)
- The best method (since C++17) - **inline variables** (see `symbolic-constants.h`)
- The term *inline* has evolved to mean "multiple definitions are allowed"
- Two restrictions of inline variables:
    1. All definitions of the inline variable must be identical
    2. Its definition (not forward declaration) must be present in any file that uses the variable
- Inline global variables have external linkage by default
- The linker will consolidate all inline definitions into single variable definition, so we can define variables in a header file and have them treated as if there was only one definition in .cpp file somewhere

## Static local variables
- `static` keyword changes a local variable's duration from *automatic* to *static*. This means the variable is now created at the start of the program, and destroyed at the end (like a global variable). Thus, it will retain its value when going out of scope
- Avoid static local variables, unless the var never needs to be reset.

## Using statements
- Using directives (`using namespace std;`) and using declarations (`using std::cout;`) can be used inside blocks
- Feature of using declarations: if there's a naming conflict between `std::cout` (which is being `using`'ed) and some other `cout`, std::cout is preferred (unlike using directives, where this would be an ambiguity error)
- Avoid using directives; using declarations are O.K. to use inside blocks