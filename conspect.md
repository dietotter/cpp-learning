# Some terminology
- Yield - отдавать/выдавать. Пример: Taking the address of a pointer yields the memory address of the pointer variable - Если мы возьмем адрес у указателя (имеется ввиду с помощью &), нам выдас адрес переменной, которая хранит этот указатель.

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
- Header guards prevent multiple definitions to occur in single file. They look like (add.h):

``` #ifndef ADD_H ```

``` #define ADD_H ```

``` // code here  ```

``` #endif        ```

or

``` #pragma once  ```

(not all compilers support the pragma version, though most modern compilers do)
- Taking example above, *add.h* is included in *add.cpp* and *main.cpp*. When preprocessing *add.cpp*, `ADD_H` will be defined until the end of *add.cpp* (preventing *add.h* to be incuded into *add.cpp* the second time). Once *add.cpp* is finished, `ADD_H` is no longer defined, so when preprocessor runs on *main.cpp*, it will be defined again

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
- Identifiers **linkage** determines whether other declarations of that name refer to the same object or nor. Local variables have no linkage, which means that each declaration refers to a unique object. E.g.: `conspect/src/local-variables.cpp`
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

# Type conversion
## Typedefs
- **Typedef** is an alias for type name. `typedef double distance_t;`. Now, `double howFar;` is equivalent to `distance_t howFar;`
- **Type alias**: `using distance_t = double;`. Functionaly is equivalent to typedefs; doesn't have anything to do with using statements.
- Type aliases should be favored to typedefs
- Usage:
    1. Legibility for some return values (`int gradeTest()` vs `testScore_t gradeTest()`)
    2. Easier code maintenance (if we decide to change student id values to int from short, we can do it in one place: `using studentID_t = short;` => `using studentID_t = long;`)
    3. Platform independent coding (that's how types with fixed sizes are defined - `int16_t` etc) - see `conspect/src/typedef-demo.cpp`
    4. To make complex types simple (`using pairlist_t = std::vector<std::pair<std::string, int> >;`)

## Auto keyword
- When initializing a var, the `auto` keyword can be used in place of the type to tell the compiler to infer the variable's type from the initializer's type. This is called **type inference** (or type deduction): `auto d{ 5.0 };` or `auto i{ 1 + 2 };` or `auto sum{ add(5, 6) };`
- Since C++14, `auto` was extended to be able to deduce a function's return type from return statements in function body: `auto add(int x, int y){ return x + y; }`. This should be avoided though.
- **Trailing return syntax**: `auto add(int x, int y) -> int { return (x + y); }`. Traditional return syntax is preferred, though trailing one is used in lambdas. Lambdas also supported `auto` parameters since C++14.
- Prior to C++20, generic functions that work with a variety of different types could be created using `function templates`
- From C++20, we can use `auto` (which in this case does not perform type inference): `void addAndPrint(auto x, auto y){ std::cout << x + y; }`. You can use it as `addAndPrint(2, 3)` or `addAndPrint(2.5, 5.2)`

## Implicit type converstion (coercion)
- Is performed whenever one data type is expected, but a different one is provided. (e.g. `float f{ 3 };` If the compiler can figure out how to do the conversion - it will, otherwise - a compile error.
- Two types: *promotion* and *conversion*
- **Numeric promotion** (or *widening* for integers) is when a value of one fundamental data type is converted into a value of a larger fundamental data type from the same family. E.g. *int* => *long* (`long l{ 64 };`), *float* => *double* (`double d{ 0.12f };`)
    - Integral promotion involves the conversion of integral types narrower than `int` (bool, char, unsigned char, signed char, unsigned short, signed short) to `int` or an `unsigned int`
    - Floating point promotion - float => double
- Under the hood, promotions generally involve extending the binary representation of a number (for integers, adding leading 0s)
- **Numeric conversion** - when we convert a value from a larger type to a similar smaller, or between different types. Unlike promotion, could result in information loss (called *narrowing conversion*). Brace initialization doesn't allow narrowing conversions.
- When evaluating expressions, compiler breaks down each expression into individual subexpressions. Arithmetic operators require their operands to be of the same type. To ensure this, compiler uses the following rules:
    - If an operand is an integer narrower than `int`, it undergoes integral promotion to int/unsigned int
    - If the operands still don't match, compiler finds the highest priority operand and implicitly converts the other operand to match. Priorities:
        - long double (highest)
        - double
        - float
        - unsigned long long
        - long long
        - unsigned long
        - long
        - unsigned int
        - int (lowest)
- The problem that could arise and why not to use unsigned integers: `std::cout << 5u - 10;` (*5u* - treat 5 as unsigned integer) evaluates to 4294967291 instead of -5, as 5u is higher priority than 10 and thus 10 is converted to unsigned int, and then the operation is performed

## Explicit type conversion (casting) and static_cast
- E.g.: `float f = 10 / 4;`. Will evaluate to *2.0*, because the operands are already of the same type (int), thus the operation will be performed, evaluating to 2, and then implicitly converted to 2.0
- To tell compiler to use floating point division, we should use *type casting operator* (*cast*) to do **explicit type conversion**
- There are 5 types of casts: *C-style casts*, *static casts*, *dynamic casts*, *const casts*, *reinterpret casts*. The latter 2 should be avoided, unless a very good reason to use them.
- C-style casts: `int i1{ 10 }; int i2{ 4 }; float f{ (float)i1 / i2 };` (or `float(i1)`). Under the hood, it can perform a variety of different conversions depending on context. So avoid C-style casts.
- **static_cast** provides compile-time checking. `float f{ static_cast<float>(i1) / i2 };`
- We can use static_cast to make implicit type conversions clear. `int i{ 48 }; char ch = i;` - casting an int (4 bytes) to char (1 byte), the compiler would print a warning (if using list initialization `char ch{ i };` - an error). We explicitly tell the compiler that the conversion is intended, and hence no warnings/errors: `char ch{ static_cast<char>(i) };`

## Unnamed and inline namespaces
- **Unnamed namespace** (`namespace { void doSomething(){} }`) is treated as if it is a part of the parent namespace. The other effect is that all the identifiers inside it are treated as if they had *internal linkage*. This is also currently the only way to keep *user-defined types* local to the file
- **Inline namespace** is like unnamed, but doesn't give everything *internal linkage*. Used to give ways to use newer versions of functions without breaking the existing programs (see `conspect/src/inline-namespace.cpp`)

# Strings
- `std::cin` doesn't work correctly with strings having whitespaces in it, as it will return characters it meets before the first whitespace encountered. The other characters are left inside cin buffer until the next extraction.
- To correctly get full line of string to input, we should use *std::getline()*: `std::string name{}; std::getline(std::cin, name);`
- Using both *std::cin* and *std::getline* can result in unexpected behaviour, as *std::cin* captures the string as `"2\n"` (if you, for example, entered "2" to std::cin). Then, if we call `std::getline` to get some new string, it sees `'\n'` in buffer and thinks we entered an empty string. That's why, we need to remove the newline from the stream: `std::cin.ignore(32767, '\n'); // ignore up to 32767 chars until a \n is removed`. 32767 - the largest signed value guaranteed to fit a 2-byte integer on all platforms. The more correct, but more complex way would be: `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore unlimited characters until a \n is removed`
- To get the length of the string: `myString.length()` (seems like the return type is `size_t`)
- `std::string` is a typedef to `std::basic_string<char>`

# Enums
- PRIOR TO C++11: Enumerators are placed into the same namespace as their enumeration, so enumerator name can't be used in multiple enumerations. That's why it's common to name enumerators with a prefix like "color" (`enum Color { colorRed, colorBlue };`)
- FROM C++11: define `enum class` instead. Has strong typing rules, so each enum class is considered a unique type. No need to use prefixes for enumerators.
- If we want to use different integer type for enum, we can specify it: `enum Color : std::uint8_least8_t { ... };`
- If we want to forward declare the enum, we need to specidy the base: `enum Color : int;`. Because Color was forward declared, we need to specify the base at the definition too: `enum Color : int { ... };`
- Because defining an enum doesn't allocate any memory, it's fine to define the enum in a header, and #include that header wherever needed
- Enum class = enum struct

# Structs
- **Aggregate data type** is a data type that groups multiple individual variables together
- Struct declarations don't take up any memory, so can be defined in header and included where needed
- The minima; size of a struct is the sum of all its members (but not always, as for optimization purposes the compiler might add some bytes of padding. Read more: https://en.wikipedia.org/wiki/Data_structure_alignment)
- See `conspect/src/structs.cpp`. The structs declared there are sometimes called *plain old data structs* (POD structs) since the members are all data (variable) members

# Control flow
- **Execution path** (or *path*) - the sequence of statements that the CPU execures (from the top of main())
- **Straight-line programs** have **sequential flow** - they take the same path (execute the same statements) every time they are run
- **Control flow statements** (or *flow control statements*) allow the programmer to change the CPU's path through the program
    - **Halt** tells the program to quit running immediately. In C++: `std::exit(int exitCode)`
    - **Jump** unconditionally causes the CPU to jump to another statement. Keywords: `goto`, `break`, `continue`. Functions also cause jump-like behaviour - the CPU jumps to the top of the function when it is being called
    - **Conditional branch** is a statement that causes the program to change the path based on the value of an expression. E.g. `if statement`, `switch`
    - **Loop** causes the program to repeatedly execute series of statements until a given condition is false. E.g. `while`, `do while`, `for`. From C++11: `for each`
    - **Exceptions** are triggered when an error occurs in a function that the function cannot handle. This causes the CPU to jump to the nearest block of code that handles exceptions of that type.
- **Null statement** is a statement with no body, is declared by a single semicolon in place of the statement. It's typically placed on its own line:

`if (x > 10) `

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;` ; // this is a null statement`
- **Init statement** (since C++17) can be used before the condition in if-statement:

`if (std::string fullName{ firstName + ' ' + lastName}; fullName.length() > 20) { ... }`

Its accessible in the entire if-statement (e.g. in `else{...}` too)

## Switch
- The expression in `switch(...)` should evaluate to integral type
- Switch variable declaration nuances: see `conspect/src/switch.cpp`

## Goto
- *Goto statements* have **function scope** - they and the corresponding *statement labels* should appear in the same function
- To see how goto statements and statement labels are used, see `conspect/src/goto.cpp`
- Gotos should be avoided

## While loops
- For performance reasons, it's better to define non-fundamental variables (such as structs and classes) before the loop

## For loops
- Variables in for loops have **loop scope** - they exist only within the loop

# Random number generation
- To produce random results, **pseudo-random number generators** (**PRNG**) should be **seeded** only once
- `std::rand()` isn't a good PRNG, though the implementation can vary depending on compiler
    - Has a relatively short **period** - the length of sequence before PRNG starts to repeat itself
    - Small RAND_MAX - usually 32767 (15-bits)
    - Isn't good to generate random floating number (usually used when doing statistical modelling)
- When debugging, it is useful to set the seed (e.g. via `std::srand`) to a specific value (e.g. 0), to produce the same results
- It's better to use Mersenne Twister (`std::mt19937`) or some other algorithm from `#include <random>`, provided from C++11, or some 3rd party library
- Using a non-const global variable to create a global random number generator (so that it's only seeded once) is one of the exceptions, when it's O.K. to use a non-const global variable. It should be created in a namespace.
- To have a different seed each time we run a program, we could use the number of seconds passed since Jan 1, 1970 - `static_cast<unsigned int>(std::time(nullptr))` for `std::srand()`. *std::time* is from `#include <ctime>`.
- See the usage of std::rand() and Mersenne Twister in `conspect/src/random-generators.cpp`

# std::cin, extraction and dealing with invalid text input
- **Buffer** (*data buffer*) is a piece of memory set aside for storing data temporarily while it's moved from one place to another
- When the extraction operator is used with *cin*, the following happens:
    - If there is data in the buffer already, that data is used for extraction
    - If input buffer contains no data, user is asked to input data for extraction. When user hits enter, '\n' char will be placed in the input buffer
    - *Operator>>* extracts as much data from buffer as it can into the variable (ignoring leading spaces, tabs, \n)
    - Any data that couldn't be extracted is left in the buffer for the next extraction

E.g.: `int x{}; std::cin >> x;` If user enters "5a", 5 will be extracted, converted to int, and assigned to var x. "a\n" will be left in the input stream.
- Basic ways to do input validation:
    - Inline (as the user types): prevent the user from typing invalid input
    - Post-entry:
        - Let the user enter anything into a string, validate the string. If correct, convert it to final variable form
        - Let the user enter anything, let `std::cin >>` try to extract it, handle the error cases
- With `std::cin` such things could happen:
    - The extraction could fail (lower on that)
    - The user enters more input than expected (`12 asdasds s` instead of `12`)
    - The user enters meaningless input (`k` instead of `*/+/-`)
    - The user could overflow an input
- If you try to extract invalid data into a variable using *std::cin* (e.g. user types letter 'a' when assigning to a `double` type variable, OR the user overflows some `short` variable), *cin* goes into failure mode. To fix the failure mode: `if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(32767, '\n'); }`. Also, from C++11, a failed extraction zero-initialized a variable (prior to it it would stay uninitialized)

# Testing
- Tips:
    - Write programs in small, well defined units (functions), and compile-test along the way
    - **Code coverage** refers to how much of the source code is executed while testing. Tip: Aim for 100% statement coverage
    - Aim for 100% branch coverage (all branches should be visited while testing, e.g. in if-ifelse-else statement)
    - Aim for 100% loop coverage. Usually, it's good to perform the "0, 1, 2 test" - ensure that the loop works properly when it iterates 0, 1 or 2 times. 2 times usually means that 2+ times will work as well
    - Ensure testing different categories of input
    - Write test functions that contain both the tests and the expected answers (automated test functions)

# Array
- **Fixed array** is an array whose length is known at the compile time
- To access elements or the array, we use **subscript operator** (`[]`) with a parameter, called **subscript** (**index**). This is called **subscripting** (**indexing**)
- Array's **range** - array elements are numbered 0 through N-1
- When declaring a fixed array, the length must be a compile-time constant (literal constant, symbolic constant etc). Non-const variables or runtime constants (`int temp{ 5 }; const int length{ temp };`) can't be used. This is because fixed array have memory allocated to them at compile-time.
- `int array[5]{ 1, 2, 3 };` - other 2 values will zero-initialize. Also, it's always better to explicitly initialize arrays (`int array[5]{};`), even if they would be initialized later anyway.
- We can omit length if we have initializer list: `int array[]{ 2, 3, 5, 7, 11 };` - will initialize array with length 5
- To give indices a meaning, arrays can be set up with enums: see `conspect/src/arrays/array-enum.cpp`
- Fixed arrays aren't copied, when passed to functions, the actual array is passed. To ensure that function does not modify the array, we can make the array const: `void passArray(const int prime[5]) { ... }`
- `std::size(array)` from `#include <iterator>` is used to determine the length of the array. This function won't work for arrays passed to functions
- `std::size()` can be used since C++17. Prior to that, the length of the array can be accessed by: `sizeof(array) / sizeof(array[0])` (this also doesn't work correctly for arrays passed to functions, as *sizeof* will return the size of pointer)
- `std::size()` returns unsigned value. Since C++20, we could get signed value using `std::ssize()`
- Std array sort function: `std::sort(std::begin(array), std::end(array));` from `#include <algorithm>`

## Two-dimensional array
- Two-dimensional arrays with initializer lists can only omit the leftmost length specification: `int array[][3]{ { 1, 2 }, { 3, 4 }, { 8, 7 } };`

## C-style string
- **C-style string** is an array of chars, that uses a null terminator ('*\0*', ascii code 0), used to indicate the end of the string. C-style string is also called a *null-terminated string*.
- To define it: `char myString[] { "string" };` (it will have length 7, not 6, as C++ automatically adds a null terminator to the end)
- You can change individual characters: `myString[1] = 'p';`, but you can accidentally rewrite null terminator (in this case, by assigning to `myString[6]`). This way, std::cout will keep printing everything in adjacent memory until it happens to hit a null terminator.
- It's fine if the array is larger than the string it contains (`char name[20]{ "Shrek" };`). std::cout will print "Shrek" and stop at null terminator, ignoring the rest.
- The recommended way of reading C-style strings using *cin*: `char name[255]; std::cin.getline(name, std::size(name));` - this way, *getline()* will read up to 254 characters (leaving room for null terminator), and discard the excessing chars.
- Functions to manipulate C-style strings are in `#include <cstring>`.
- To copy a string to another string, see `conspect/src/arrays/copy-c-string.cpp`
- `std::strlen()` returns the length of the C-style string (without the null terminator) (whereas `std::size`, for example, would return the size of the array, when used on a C-style string)
- Some other functions:
    - `strcat()` - append one string to another (dangerous)
    - `strncat()` - append one string to another (with buffer length check)
    - `strcmp()` - compare 2 strings (returns 0 if equal)
    - `strncmp()` - compare 2 strings up to a specific number of chars (returns 0 if equal)
- Unless I have a specific reason to use C-style strings, it's better to avoid them, and use `std::string` from `#include <string>`. If I need to work with fixed buffer sizes and C-style strings (e.g. for memory-limited devices), it'd be better to use a well-tested 3rd party library, or `std::string_view`

## std::string_view
- Instead of C-style strings, use `std::string_view` (see `conspect/src/arrays/string-view.cpp`)
- Prefer *std::string_view* over *std::string* for read-only strings, unless you already have a *std::string*
- *std::string_view* can work with non-null-terminated strings (it's safe)
- When using string_view, we need to make sure that the underlying string does not go out of scope and isn't modified.
- *string_view* can be explicitly converted to *string*: `std::string_view sv{ "ball" }; std::string str{ sv }; std::string str2{ static_cast<std::string>(sv) };`
- To convert to a c-style string, we need to first convert the string_view to string. Then `auto scNullTerminated{ str.c_str() };` This can be used, for example, for `strlen()` function, which expects c-style string. However, this should be avoided if possible.
- We can use *std::string_view*'s `data()` function to access the underlying string, which returns a C-style string. But it should only be used if the string_view's view hasn't been modified, and the string being viewed is null-terminated.

# Pointers
- **Address-of operator** (**&**) allows us to see what memory address is assigned to a variable: `&x` => smth like `0x7ffee76787e8`
- **Indirection operator** (**&ast;**), also called *dereference operator* allows us to access the value at a particular address: `*(&x)`
- **Pointer** is a variable that holds a *memory address* as its value: `int *iPtr{};` The asterisk here is *not* an indirection, it's part of the pointer declaration syntax.
- When declaring a pointer variable, it's better to put the asterisk next to the variable name: `double *dPtr{};`
- When returning a pointer from function, it's clearer to put the asterisk next to the return type: `int* doSomething();`
- Pointer nomenclature: "X pointer" is a common shorthand for "pointer to an X". *An integer pointer* means *a pointer to an integer*
- You can't directly convert literal memory addresses to a pointer: `double *dPtr{ 0x0012FF7C };` is not allowed
- Operator `&` doesn't return the address as a literal. It returns a pointer. (`int x{ 4 };`. `&x` will return an integer pointer, containing the address)
- Indirection through a pointer evaluates to the contents of the address it is pointing to: `int *ptr{ &x };`. `*ptr` will contain the value 4 (assigned in a previous example)
    - `ptr` <=> `&x`; `*prt` <=> `x`
    - Because `*ptr` is treated the same as x, you can assign values to it just as if it was a variable `x`: `*ptr = 7; std::cout << x;` will print 7
- The size of pointer is dependent upon the architecture the executable is compiled for - 32-bit executable uses 32-bit memory addresses. Consequently, a pointer on a 32-bit machine is 32 bits (4 bytes). This is regardless of the size of the object being pointed to.
- Pointers are used for such cases as:
    1. Arrays are implemented using pointers. Pointers can be used to iterate through an array (as an alternative to array indices)
    2. They are the only way you can dynamically allocate memory in C++ (the most common use)
    3. They can be used to pass a large amount of data to a function without ineffician copying of the data.
    4. They can be used to pass a function as a parameter to another function.
    5. They can be used to achieve polymorphism when dealing with inheritance.
    6. They can be used to have one struct/class point to another struct/class to form a chain. Useful for some advanced data structures, such as trees or linked lists.

## Null pointer
- **Null value** is a special value that means the pointer isn't holding anything. Such pointer is called a **null pointer**
- In C++: `float *ptr{ 0 };` or `float *ptr2; // ptr2 is uninitialized` next line: `ptr2 = 0;`. Both ptr and ptr2 are null pointers. Pointers convert to boolean false if they are null; to true if they are non-null.
- Initialize pointers to a null value if not giving them another value.
- Indirection through a null pointer results in undefined behaviour
- `#include <cstddef>` has a preprocessor macro `NULL`: `double *ptr{ NULL };` The value of *NULL* is implementation defined, but it is usually defined as the integer constant 0. Because it is implementation defined, we should avoid using it.
- From C++11, NULL can be defined as `nullptr`. This should be favored instead of 0 or NULL.
- C++11 also introduces a type called `std::nullptr_t` (from header `<cstddef>`). It can only hold 1 value - nullptr. Useful when we eant a function that only accepts a nullptr argument: `void doSomething(std::nullptr_t ptr) { ... }`
- Deleting null pointer is fine (it won't do anything)

## Arrays and pointers
- In all but 2 cases, when a fixed array is used in expression, it will **decay** (be implicitly converted) into a pointer that points to the first element of the array. `int array[3] { 5, 3, 4 };`. Then, `std::cout << &array[0]` and `std::cout << array` will both print the address of the first element in the array.
- Array and a pointer to the array are not identical. Array is of type `int[5]` and its *value* is the array elements themselves. A pointer to the array is of type `int *` and its value would be the address of the first element of the array.
- Information derived from array's type (such as it's length) can't be accessed from the pointer.
- We can assign the pointer to point at the array: `int array[3]{ 4, 3, 5 }; int *ptr{ array };`. `std::cout << *array` will print 9. `std::cout << *ptr` will print 9. This works because the array decays into a pointer of type `int *`.
- Differences between pointers and fixed arrays:
    - The primary difference occurs when using the sizeof() operator. When used on a fixed array, it returns the size of the entire array (length * element size). When used on a pointer, sizeof returns the size of a memory address in bytes.
    - The second difference occurs when using the address-of operator (&). If we take the address of the pointer (&ptr), we will get the memory address of that pointer variable (memory address of ptr). Taking the address of the array returns a pointer to the entire array. This pointer also points to the first element of the array, but the type information is different (e.g., the type of the above array is `int(*)[3]`)
- When passing an array as an argument to function, fixed array decays into a pointer and the pointer is passed to the function (even if the parameter in function is declared as a fixed array: `void printSize(int array[]) {...}` <=> `void printSize(int *array) {...}`). The recommendation is to favor the pointer syntax (*), because it is clearer, that the parameter will operate as a pointer.
- The last point is also the reason why changing an array in a function changes the actual array argument passed in. `void changeArray(int *ptr) { *ptr = 5; }` - the argument array, passed to this function, will have its first element changed to 5. This thing also works with pointers to non-array values as well.
- The arrays that are part of structs or classes do not decay when the whole struct or class is passed to a function.

## Pointer arithmetics
- If `ptr` points to an integer, `ptr + 1` returns the address of the next integer in memory after `ptr`, `ptr - ` - of the previous. Note that `ptr + ` returns not the memory address after `ptr`, but the *memory address of the next object of the type* that `ptr` points to. If `ptr` points to an integer (assuming 4 bytes), `ptr + 3` means 3 integers (12 bytes) after `ptr`.
- When calculating the result of a pointer arithmetic expression, the compiler always multiplis the integer operand by the size of the object being pointed to. This is called **scaling**
- Arrays are laid out sequentially in memory
- `array[n]` <=> `*(array + n)`. The subscript operator ([]) is identical to an addition and indirection. That's why, `arr[2]` is the same as `*(arr + 2)` same as `*(2 + arr)` same as `2[arr]` (this only works for the build-in subscript operator)
- To count, for example, vowels in a word (`char name[]{ "Vasya" };`), we can use `std::count_if(std::begin(name), std::end(name), isVowel);`. std::begin/end only work on arrays with known size. If the array decayed to a pointer, we can calculate begin and end manually: `std::count_if(name, name + nameLength, isVowel)`

## Pointers and C-style strings
- C++ deals with the memory allocation for the next examples differently: `char myName[]{ "Nik" }; // fixed array` and `const char *myName{ "Alex" }; // pointer to symbolic constant`
    - For the first one, the program allocates memory for fixed array of length 4 and initializes it with "Nik\0". We can alter the contents freely, because the memory has specifically been allocated for the array. Also, it dies when goes out of scope, and the memory is freed.
    - For the second one, it is compiler-implementation defined. But usually, compiler places "Nik\0" into read-only memory somewhere and then sets the pointer to point to it.
        - Because the memory may be read-only, best practise is to make sure the string is const.
        - `const char *name1{ "Nik" }; const char *name2{ "Nik" };` For optimization purposes, compiler may opt to combine multiple string literals into single shared string literal, with both name1 and name2 pointed at the same address. Thus, if name1 wasn't const, making a change to it could also impact name2.
        - As a result of string literals being stored in a fixed location in memory, they have static duration (they die at the end of the program). That means, the following is okay: `const char* getName() { return "Nik"; }`. In this code, `getName()` will return a pointer to C-style string "Nik". If the function was returning any other local variable by address, the variable would be destroyed at the end of *getName()* and we'd return a dangling pointer back to the caller. However, because string literals have static duration, the caller can still successfully access "Nik".
- `int nArray[5]{ 9, 7, 5, 3, 1 }; char cArray[]{ "Hello!" }; const char *name{ "Nik" };`. If we `std::cout` each of them, nArray will decay to type `int*` and print out something like *0x7ffeeb5487d0*; cArray will decay to type `char*` and print out *Hello!*; name is already `char*` and prints out *Nik*. This is because std::cout prints the contents of non-char pointer, but if you pass `char*` or `const char*`, it will print the string.
- The above point can be a problem when: `char c{ 'Q' }; std::cout << &c;`. Because &c has type char*, cout tries to print it as a string, so it will print Q, then some nonesence, until it runs into 0, which will be interpreted as a null-terminator (THOUGH I didn't experience such thing on my MacBook when compiling by gcc)

## Void pointers
- **Void pointer** (also *generic pointer*) is a special type of pointer that can be pointed at objects of any data type:

`Something sValue; int nValue;`

`void *ptr; ptr = &sValue; ptr = &nValue;`
- Direct indirection through void pointer is not possible, it must first be explicitly case to another pointer type:

`int *intPtr{ static_cast<int*>(ptr) }; std::cout << *intPtr;`
- Can be set to a null value: `void *ptr{ nullptr };`
- Although some compilers allow deleting a void pointer that points to dynamically allocated memory, this should be avoided, because it leads to undefined behaviour.
- Pointer arithmetic can't be done on void pointer (it doesn't know the size of the object it is pointing to)
- There is no such thing as void reference
- It's better to avoid void pointers unless absolutely necessary (many places where they would be once used are done through things like *function overloading*, *templates*)

## Pointers to pointers
- `int **ptrptr;`
- Indirection to get int value: `std::cout << **ptrptr;` (two consecutive indirections)
- You can't set a pointer to a poinert directly to a value: `int **ptrptr = &&value;` - not valid, because *operator&* requires an lvalue, but `&value` is an rvalue.
- Can be set to nullptr.
- Usage:
    - The most common - dynamically allocate an array of pointers: `int **array = new int*[10];` - allocate an array of 10 int pointers
    - Another common - to facilitate dynamically allocated multidimensional arrays. Two possible solutions:
        1. Works if all non-leftmost array dimensions are compile-time constants: `int (*array)[5] = new int[10][5];` (from C++11: `auto array = new int[10][5];`)
        2. See `conspect/src/arrays/pointer-two-dimensional-array.cpp`
- We can pass a pointer to a pointer to a function and use that pointer to change the value of the pointer it points to. However, it's better to use a reference to a pointer instead.
- We can do `int ***ptrx3;` and so on (but why?)
- It's recommended to avoid pointers to pointers unless there are no other options available

# Dynamic memory allocation
Three types of memory allocations:
1. **Static** - happens for static and global variables. Memory for these types of vars is allocated once when the program is run and persists throughout the life of the program.
2. **Automatic** - for function parameters and local variables. Memory for these types of vars is allocated when the relevant block is entered, and freed when the block is exited, as many times as necessary.

*Static* and *automatic* allocation have two things in common:
- The size of the var / array must be known at compile-time.
- Memory alloc and deallocation happens automatically when the variable is instantiated / destroyed.

3. **Dynamic** - running programs are responsible for requesting the memory from the OS when needed, and also for freeing it.

- If we have to declare the size of everything at compile time, the best we can do is try to make a guess the maximum size of vars we'll need. But that's bad for such reasons:
    1. It leads to wasted memory, which is not being used
    2. It's hard to tell which bits of memory are actually used
    3. Most normal variables (including fixed arrays) are allocated in the portion of memory called **stack**. The amount of stack memory is generally quite small - e.g., Visual Studio defaults the stack size to 1MB. If you exceed it - stack overflow.
    4. It can lead to artificial limitations or array overflows.
- The memory for dynamic allocation is allocated from a much larger pool of memory managed by the OS called the **heap**. On modern machines, heap can be gigabytes in size.
- To allocate a single variable dynamically, we use the scalar (non-array) form of the **new** operator: `new int; // dynamically allocate an int (and discard the result)`. We're requesting an integer's worth of memory from the OS. The new operator creates the object using that memory, and then returns a pointer containing the *address* of the memory that has been allocated.
- Most ofter, we'll assign the return value to out own pointer variable so we can access the allocated memory later: `int *ptr{ new int }; *ptr = 7;`
- Init a dynamically allocated var: `int *ptr1{ new int(5) }; int *ptr2{ new int{ 6 } };`
- To delete a single dynamically alloced var, use the scalar (non-array) form of the **delete** operator: `delete ptr; // return the memory pointer to by ptr to the OS, so it could give it to some other application`, then `prt = 0; // set ptr to be a null pointer (nullptr instead of 0 from C++11)`
- There are no guarantees about what will happen to the contents of deallocated memory. In most cases, the memory returned to the OS will contain some values it had before it was returned, and the pointer will be left pointing to the now deallocated memory. Such pointer is called a **dangling pointer**. Indirection through such pointer (or deleting it) will result in undefined behaviour.
- Deallocating memory may create multiple dangling pointers. Best practises regarding this:
    1. Try to avoid having multiple pointers point at the same piece of dynamic memory. If it's not possible, be clear about which pointer "owns" the memory (and is responsible for deleting it) and which are just accessing it.
    2. When you delete a pointer, if that pointer is not going out of scope immediately afterward, set the pointer to 0 (or nullptr since C++11)
- Operator *new* can fail rarely, when the OS doesn't have any memory to grant the request with. By default, if *new* fails, a bad_alloc exception is thrown. If this exception isn't properly handled, the program will terminate with an unhandled exception error.
- There's the alternate form of *new* that can be used to tell new to return a null pointer if memory can't be allocated instead. This is done by adding the constant *std::nothrow* between the new keyword and the allocation type: `int *value = new (std::nothrow) int;`. The best practise is then to check all memory requests to ensure they actually succeeded before using the allocated memory (`if (!value) {...}`)
- As null pointer means that "no memory has been allocated to this pointer", we can conditionally allocate memory: `if (!ptr) { ptr = new int; }`
- **Memory leak** occurs when the program loses the address of some bit of dynamically allocated memory before giving it back to the OS (we can't *delete* it). E.g.:
    - The pointer to the dynamically allocated memory goes out of scope before that memory is deallocated.
    - The pointer is assigned the new variable address before the previous one was deallocated

## Dynamically allocating arrays
- To allocate an array dynamically, we use the array from of the new and delete (also called *new[]* and *delete[]*)
- The length of dynamically allocated arrays has to be a type that's convertible to `std::size_t`
- Allocate the array: `std::size_t length{}; std::cin >> length; int *array{ new int[length]{} };`
- When deleting memory allocated for arrays, don't forget to use `delete[]`. The array `new[]` keeps track of how much memory was allocated to a variable, so that array `delete[]` can delete the proper amount
- Dynamic array functions identically to a decayed fixed array, with the exception that the programmer is responsible for memory deallocation
- Prior to C++11, you couldn't initialize a dynamic array to a non-zero value easily (initializer lists only worked for fixed arrays)
- The author or learncpp tells that it's better to not resize dynamically alloced array yourself, and instead use `std::vector` (? is it always true ?)

## Const pointers
- We can't set non-const pointers to a const var.

`const int value = 5; int *ptr = &value;` - compile error.
- A **pointer to a const value** is a (non-const) pointer that points to a constant value.

`const int value = 5; const int *ptr = &value;` - O.K., ptr is a non-const pointer that is pointing to a "const int".

`int value = 5; const int *ptr = &value;` - this is still O.K., a pointer to a constant variable treats the variable as constant when it is accessed through the pointer, regardless of whether variable was or wasn't defined as const. Thus, we can do `value = 6;`, but not `*ptr = 6;`.

Because a pointer to a const value isn't const itself, it can be redirected to point at other values: `ptr = &value2;`
- A **const pointer** is a pointer whose value can not be changed after initialization.

`int value = 5; int *const ptr = &value;`. Acts like a normal const variable: `ptr = &value2;` is not allowed. However, because the *value* itself isn't const, it's possible to change the value through an indirection: `*ptr = 6;` - this is O.K.
- It is possible to declare a **const pointer to a const value**: `int value = 5; const int *const ptr = &value;`

# Reference variables
- **Reference** is a type of C++ variable (third basic type of variable C++ supports) that acts as an alias to another object or value
- 3 kinds of references:
    1. References to non-const values ("references", "non-const references")
    2. References to const values ("const references")
    3. r-value references (from C++11)
- Reference is declared by using an ampersand (&) between the reference type and the var name: `int value{ 5 }; int &ref{ value };`. In this context, ampersand doesn't mean "address of", but means "reference to"
- References generally act identically to the values they're referencing: from previous point, `ref = 6;` - now `value` is also 6.
- The address-of operator on references returns the address of the value being referenced: `cout << &value;` prints equal address as `cout << &ref;`

## l-values and r-values
- In C++, vars are a type of l-value. **l-value** is a value that has an address (in memory). Since all vars have addressed, they are l-values.
- l-values are the only values that can be on the left side of an assignment statement. `5 = 6;` causes a compile error as 5 is not l-value
- **r-value** is an expression that's not an l-value. Examples are literals (like *5*, which evaluates to 5) and non-l-value expressions (such as 2 + x)
- *const* variables are considereed non-modifiable l-values

## Back to references
- References must be initialized when created: `int &invalidRef;` - compile error. There is no such thing as null reference
- References to non-const vars can only be initialized with non-const l-values
- Refs can't be reassigned: `int value1{ 5 }; int value2{ 6 }; int &ref{ value1 }; ref = value2;` - assigns 6 to value1 - doesn't change the reference
- References, when used as function parameters, act as an alias for the argument, so no copy of the argument is made into the parameter. A function that uses a reference parameter is able to modify the argument passed in: `void changeN(int &ref){ ref = 6 };`. Now we can call `changeN(n);` and the variable n will be changed to 6 through the reference *ref*. The primary downside of this is that the argument must be a non-const l-value
- C-style arrays do not decay when passed by reference: see `conspect/src/arrays/c-style-array-reference.cpp`
- References can also be used as shortcuts: `int &ref{ other.something.value1 };`

## References vs pointers
- A reference acts like a pointer that implicitly performs indirection through it when accessed (references are usually implemented internally by the compiler using pointers)

`int value{ 5 }; int *const ptr{ &value }; int &ref{ value };` - `*ptr` and `ref` evaluate identically, thus `*ptr = 5;` <=> `ref = 5;`
- Because references must be initialized to valid objects (can't be null) and can not be changed once set, refs are generally much safer to use than pointers (no risk of indirection through a null pointer). However, they are also a bit more limited in functionality
- If task can be solved with either reference or pointer, reference should generally be preferred
- Pointers should only be used in situations where refs are not sufficient (such as dynamically allocating memory)

## References and const
- **Const reference** (reference to a const value): `const int value{ 5 }; const int &ref{ value };`
- They can be initialized with const l-values, r-values (`const int& ref2{ 6 };`), non-const l-values:

`int x{ 5 }; const int& ref3{ x };`. Much like a pointer to a const value, when accessed through a reference to a const value, the value is considered const even if the original variable is not: `x = 6;` is O.K., `ref = 7;` is not.
- Reference to r-values extend their lifetime to match the lifetime of the ref (normally, r-values have expression scope)
- Const references in function parameters allow us to access the argument without making the copy of it, while guaranteeing the function won't change it's value

`void printIt(const int &x) { std::cout << x; }`
- The last point is also useful because of it's versatility. We can pass in non-const l-value argument, const l-value, literal, or result of the expression:

`int a{ 1 }; printIt(a); const int b{ 2 }; printIt(b); printIt(3); printIt(2 + b);`
- Some rules about passing to functions:
    - To avoid making potentially exprensive unnecessary copies, vars that are not pointers or fundamental data types should be passed by (const) reference
    - Fundamental data types should be passed by value, unless the function needs to change them
    - There are few exceptions, namely types that are so small that it's faster for the CPU to copy them than having to perform an extra indirection for a reference (e.g., `std::string_view`)

## Member selection with pointers and refs
- Normal variables: `person.age`; refs: `ref.age` (the same); pointers: `ptr->age` or `(*ptr).age` (the `->` variant is preferred)

# For-each loops
- Simpler and safer type of loops - **for-each loop** (also **range-based for-loop**) for cases where we want to iterate through every element in an array (or other list-type structure): `for (element_declaration : array) { statement; }`
- This is an ideal case to use `auto` keyword:

`constexpr int fibonacci[]{ 0, 1, 1, 2, 3, 5, 8, 13, 21 };`

`for (auto number : fibonacci) { std::cout << number << ' '; }`
- We can use references (and const references) in for-each loops. It's better to do it for non-fundamental type elements to avoid expensive copying:

`std::string array[]{ "nik", "likes", "frozen", "cock" };`

`for (const auto &element : array) { std::cout << element; }`

- For-each loops also works with `std::vectors` and other list-like structures

- For-each loops don't work with decayed and dynamic arrays, because arrays that have decayed into a pointer don't know their size, and for-each loops need it

- From C++20, for-each loops can have *init-statement*: `for (int i{ 0 }; auto score : scores) { ...; ++i; }` (be careful when using `continue`, so that `++i` doesn't get skipped)

# std::array
- `std::array<int, 3> myArray{ 3, 2, 4 };`. Like fixed arrays, the length must be known at compile time
- From C++17, we can ommit the type and size: `std::array myArray{ 2, 1, 4 };`
- From C++20, we can specify the element type, but omit the array length:

`auto myArray1{ std::to_array<int, 3>({ 3, 2, 4 }) }; // specify type and size`

`auto myArray1{ std::to_array<int>({ 3, 2, 4 }) }; // deduce size`

`auto myArray1{ std::to_array({ 3, 2, 4 }) }; // deduce type and size`
- However, *std::to_array* is more exprensive than creating *std::array* directly, because it copies all elems from C-style array to std::array. So, std::to_array should be avoided when the array is created many times, e.g. in a loop.
- To access std::array elem, we can use subscript operator as usual ([]), or `myArray.at(index)`. *.at()* is safer (because it does bounds checking, trying to *.at()* out of bounds index will throw an exception), but slower.
- std::array will clean up after itself when it goes out of scope
- `myArray.size()` can be used to retrieve the length
- We should always pass *std::array* by reference/const reference
- For-each works with std::array, also std::sort: `std::sort(myArray.begin(), myArray.end());`
- The `myArray.size()` and index in *operator[]* of *std::array* both are of type `size_type` which is defined by the C++ standard as an unsigned integral type. It isn't a global type, it's defined inside the definition of std::array (C++ allows nested types). If we want to use *size_type*, we have to prefix it with full array type. For *myArray*:

`for (std::array<int, 3>::size_type i{ 0 }; i < myArray.size(); ++i) { std::cout << myArray[i] << ' '; }`

Fortunately, that's just an alias for *std::size_t*, so we can use that instead: `std::array<int, 3>::size_type` <=> `std::size_t`. But it might be best to avoid manual indexing of std::array in the first place.
- The working reverse for-loop for unsigned integers looks like this: see `conspect/src/arrays/unsigned-reverse-for-loop.cpp`
- To initialize array of struct with brace initialization, there are some nuances, see [Array of struct](https://www.learncpp.com/cpp-tutorial/6-15-an-introduction-to-stdarray/)
- Prefer using `std::array` over build-in fixed arrays

# std::vector
- `std::vector` provides dynamic array functionality that handles its own memory management. Lives if `<vector>` header. Declaration: `std::vector<int> array{ 1, 3, 5 };`
- Since C++17, we can omit type: `std::vector array{ 1, 3 ,5 };`
- Accessing array elements is just like `std::array`
- As of C++11, we can assign values to `std::vector` using initializer list: `array = { 0, 1, 5, 3, 6 };` In this case, the vector will self-resize to match the number of elements provided
- Prevents memory leaks, as the memory will be deallocated as soon as `std::vector` instance goes out of scope
- Unlike build-in dynamic arrays, keeps track of length (`size()`). Returns `size_type`, as in std::array
- Resize a vector: `array.resize(7)`. Existing elements are preserved, new elements are initialized to default value for the type (for *int* it's 0). Can be resized to be smaller too.
- Resizing vector is computationally expensive, so if I need a vector with specific num of elems but don't know the values of the elems at the point of declaration, I can create a vector with default elements like so: `std::vector<int> array(5);`. Using direct initialization, we can create a vector with 5 elems and init them to 0. If we use brace initialization here, the vector would have 1 elem, which would be the integer 5. *A rule of thumb:* if a type is some kind of list and I don't want to init it with a list, use direct initialization
- Using `std::vector`, we can compact 8 booleans into a single byte: `std::vector<bool> array{ true, false, false, true, true };`
- Prefer using `std::vector` over build-in dynamic arrays

# Iterators
- **Iterator** is an object designed to traverse through a container (e.g. values in array, chars in a string), providing access to each element along the way
- Container may provide different kinds of iterators - e.g., array container might offer a forwards iterator, and reverse iterator (walks through array in reverse order)
- C++ iterators typically use the same interface for traversal (`operator++` to move to the next element) and access (`operator*` to access the current element), we can iterate through a wide variety of different container types using a consistent method
- Simplest kind of iterator - pointer iterator (using pointer arithmetics): see `conspect/src/iterators/pointer-iterator.cpp`
- All types that have `begin()` and `end()` member functions or can be used with `std::begin` and `std::end` are usable in range-based for-loops (for-each loops). Including user-defined types
- If the elements being iterated over change address or are destroyed, the iterator becomes **invalidated** (*dangling*, like pointers and references can be)
- Some operatuons that modify containers (such as adding elem to *std::vector*) can cause elems in the container to change addresses. When this happens, existing iterators will be invalidated. Good C++ reference documentation should note which container operations may or will invalidate iterators

# Standard library algorithms
- The functionality provided in algorithms library generally fall into one of three categories:
    1. **Inspectors** - used to view (but not modify) data in container (e.g. searching, counting)
    2. **Mutators** - used to modify data in container (e.g. sorting, shuffling)
    3. **Facilitators** - used to generate a result based on values of the data members (e.g. objects that multiply values, objects that determine what order pairs of elements should be sorted in)
- Some examples:
    - `std::find` searches for the first occurence of a value in a container. Takes in 3 params: iterator to the starting elem in the sequence, iterator to the ending elem in the sequence, value to search for. Returns an iterator pointing to the element (if it is found) or the end of container (if not found). See `conspect/src/standard-algorithms/find.cpp`
    - `std::find_if` searches for value in container that matches some condition. Similar to *std::find*, but instead of passing a value to search for, we pass in a callable object, such as function pointer or a lambda, that checks to see if a match is found. See `conspect/src/standard-algorithms/find-if.cpp`
    - `std::count` and `std::count_if` to search for all occurrences of an elem or an elem fulfilling a condition. See `conspect/src/standard-algorithms/count.cpp`
    - `std::sort` to sort an array in ascending order, but also there is a *std::sort* version which takes a **comparison function** as 3rd param that allows us to sort by our own conditions. That function takes two params to compare and returns true if the first argument should be ordered before the second. See `conspect/src/standard-algorithms/sort.cpp`
        - Because sorting in descending order is popular, C++ provides a custom type `std::greater` (part of `<functional>` header) for that. So we can `std::sort(arr.begin(), arr.end(), std::greater{});` (before C++17, we'd have to specify the type `std::greater<int>{}`)
        - See how `std::sort` uses the comparison function in `conspect/src/standard-algorithms/sort-with-comparison.cpp` using the example of selection sort
    - `std::for_each` takes a list as input and applies a custom function to every element. See `conspect/src/standard-algorithms/for-each.cpp` (there's also why it might be better to use `std::for_each` rather than *range-based for-loops*)
- Many standard algorithms can be parallelized to achieve faster processing
- Most standard algorithms don't guarantee a particular order of execution. For such algos, ensure any functions you pass in do not assume a particular ordering. Some algorithms do guarantee sequential execution: `std::for_each`, `std::copy`, `std::copy_backward`, `std::move`, and `std::move_backward`
- C++20 adds *ranges*, which allow us to simply pass *arr*, without having to pass *arr.begin()* and *arr.end()*

# Functions (detailed)
- **Function parameter** (or **formal parameter**) is a var declared in the function declaration
- **Argument** (or **actual parameter**) is the value passed to the function
- 3 ways of passing arguments:
    1. **Pass by value** - the argument's value is copied into the value of the corresponding function parameter
    - Advantages:
        - Arguments can be just about anything
        - Arguments are never changed by the function (prevents side effects)
    - Disadvantages:
        - Copying structs and classes can incur significant performance penalty
    - When to use:
        - When passing fundamental data types and enumerators, and the function doesn't need to change the arguments
    - When not to use:
        - When passing structs or classes
    2. **Pass by reference** - we declare function parameters as references, and they become references to the arguments
    - We can use this to imitate multiple return values. Parameters that are only used for returning values back to the caller - **out parameters**: `void getSinCos(double degrees, double &sinOut, double &cosOut) { ... }`
    - However, out parameters should be avoided:
        - We must pass in arguments to hold the updated outputs even if we don't use them
        - The syntax is unnatural with both input and output params together
        - It's not obvious from caller's side that some params are out params and will be changed (if we still want out params, it'd be more explicit (though we then need to do the check for nullptr value in function) to use pass by address for them). See `conspect/src/functions/out-params.cpp`
        - The best recommendation is to avoid modifiable parameters altogether
    - Non-const refs can only reference non-const l-values
    - **Rule**: when passing argument by reference, always use a const reference unless you need to change the value of the argument
    - Advantages:
        - Refs allow the function to change the argument, if we need this. Otherwise, const refs can be used
        - Pass by ref is fast, because no copy of the argument is made. **Rule**: use pass by const ref for structs and classes and other expensive-to-copy types (if they don't need to be modified)
        - Refs can be used to return multiple values from functions (out params)
        - Refs must be initialized, so no worry about null values
    - Disadvantages:
        - Arguments to non-const ref parameters can only be normal variables
        - If using non-const ref, it's hard to tell whether parameter is an input, output or both
        - It's impossible to tell from the function call whether the argument may change - arg passed by value and by ref looks the same
    - When to use:
        - When passing structs or classes (use const if read-only)
        - When I need the function to modify the arg
        - When function needs access to the type information of a fixed array
    - When not to use:
        - When passing fundamental types that don't need to be modified
    3. **Pass by address** - passing the address of the argument variable rather than the arg var itself. Function param must be a pointer
    - Typically used with built-in arrays (which decay into pointers)
    - It is good idea to check if params passed by address are not null pointers before dereferencing them (so the program doesn't crash)
    - To ensure function doesn't modify the argument passed in, we make the parameter to be a pointer to const var: `void printArray(const int *array, int length) { ... }`
    - When you pass pointer to a function, the pointer's value (the address it points to) is copied to func's param. So it's passed by value (ofc, if we dereference it, we can still change the value at that address)
    - We can pass address by reference: `void setToNull(int *&ptr) { ptr = nullptr; }`
    - Because pass by address is actually a pass by value (the value happens to be an address), and references are implemented via pointers (they implicitly are dereferenced), we can say that *everything is actually a pass by value*
    - Advantages:
        - The same as refs (excluding the *must be initialized* one)
    - Disadvantages:
        - Because literals (excepting C-style strings) and expressions don't have addresses, pointer args can only be normal variables
        - Values must be checked whether they are null
        - Because dereferencing a ptr is slower than accessing a value directly, accessing args passed by address is slower than accessing args passed by value
    - When to use:
        - When passing built-in arrays (if decaying is fine)
        - When passing a pointer and nullptr is a valid argument logically
    - When not to use:
        - When passing a pointer and nullptr is not a valid argument logically (use pass by ref)
        - When passing structs or classes (use pass by ref)
        - When passing fundamental types (use pass by value)
    - **Rule**: prefer pass by ref to pass by address when applicable, because it's safer

## Returning values
- Returning values works similar to passing them, just the direction of data flow is reversed. Though we also need to consider the fact that local vars of a function go out of scope
    1. **Return by value**
    - When to use:
        - When returning vars that were declared inside the func
        - When returning function args passed by value
    - When not to use:
        - When returning a built-in array or poiner (use return by address)
        - When returning a large struct or class (use return by ref)
    2. **Return by address**
    - Can return only the address, not literal or expression (they don't have addresses)
    - Fast, because just copies an address from the function to the caller
    - If you try to return the address of variable local to the function, it'll result in undefined behaviour: `int* doubleValue(int x) { int value{ x * 2}; return &value; }`. The caller will end up with the address of non-allocated memory (dangling pointer)
    - Return by address was often used to return dynamically allocated memory to the caller: `int* allocateArray(int size) { return new int[size]; }`, though it's hard to track who's responsible for deleting the resource. Better to use smart pointers and types that clean up after themselves
    - When to use:
        - When returning dynamically allocated memory and you can't use a type that handles allocation for you
        - When returning function arguments that were passed by address
    - When not to use:
        - When returning vars that were declared inside the function, or params passed by value (use return by value)
        - When returning a large struct or class that was passed by ref (use return by ref)
    3. **Return by reference**
    - Can return only variable (should not return a ref to a literal or expression that resolves to a temporary value, those will go out of scope at the end of the function and the dangling reference will be returned)
    - Fast, useful when returning structs and classes
    - If you return local variable, it'll be destroyed at the end of the scope, and caller will receive garbage
    - Simple example of when return by ref is useful (it'll be more useful when using classes): `conspect/src/functions/return-by-reference.cpp`
    - When to use:
        - When returning a reference parameter
        - When returning a member of an object that was passed into the function by ref or address
        - When returning a large struct or class that will not be destroyed at the end of the func (e.g. that was passed by ref)
    - When not to use:
        - When returning vars that were declared inside the func or params that were passed by value (use return by value)
        - When returning a built-in array or pointer value (use return by address)
- What happens if the caller mixes the value and reference types: see `conspect/src/functions/return-ref-type-mix.cpp` (also for returned ref lifetime nuances)
- Methods to return multiple values:
    1. Out params (not recommended)
    2. Data-only structs:

    `struct S{ int x; double y; }; S returnStruct(){ S s; s.x = 5; s.y = 6.9; }`

    3. Use `std::tuple` (`#include <tuple>`) (from C++11). **Tuple** is a sequence of elems that may be different types, where the type of each elem must be explicitly specified

    `std::tuple<int, double> returnTuple(){ return { 5, 6.9 }; }`

    Then we can `std::get<n>(someTuple)` to get the nth element of the tuple

    Can also use `std::tie` to unpack the tuple into predefined variables:

    `int a; double b; std::tie(a, b) = returnTuple();`

    From C++17: `auto [a, b]{ returnTuple() };`

    Using struct is better option if using in multiple places. If just packaging up these values to return and there would be no reuse, it's cleaner to use tuple, since we don't introduce new user-defined data type

## Inline functions
- Code written in-place is significantly faster, because it doesn't have performace overhead of calling a function (CPU must store address of the current instruction (to know where to return) along with other registers, function params must be created and assigned values, program has to branch to new location)
- For small, commonly used functions, the overhead is a lot more than the time to actually run their code
- **inline** keyword requests the compiler to treat a function as inline function - when compiler compiler code, the function call is replaced with a copy of the contents of the function itself
- The downside - compiled code becomes quite large
- Inlining a function is best suited to short functions (no more than a few lines) that are typically called inside loops and do not branch. Also, *inline* keyword is just a recommendation - the compiler is free to ignore the request
- Modern compilers are very good at inlining functions automatically
- Inline functions are exempt (исключение) from the one-definition per program rule. But you still generally shouldn't define global functions in header files

## Function overloading
- **Overloaded functions** are functions with the same name, but different parameters (either different types of params or different amount)
- Function return type isn't considered for uniqueness: `int getRandom(); double getRandom();` results in the mistake
- Typedefs are not distinct: `typedef char* string; void print(string value); void print(char *value);` - two declarations are considered identical
- When an overloaded function is called, C++ goes through this process:
    1. Tries to find an exact match:
    
    `void print(int value); void print(char *value); print(0);`

    0 could technically match char* (nullptr), but matches int exactly, so that func is called

    2. C++ tries to find a match through *promotion* (see `Implicit type conversion` in this conspect)

    `print('a');` (considering declarations above). There is no *print(char)*, so char 'a' is promoted to int

    3. If no promotion is possible, tries through standard *conversion* (see `Implicit type conversion`)

    `struct Employee; void print(float value); void print(Employee value); print('a');`

    No exact match, no promotion match, so 'a' is converted to float and matched with print(float). All standard conversions are considered equal

    4. Finally, C++ tries user-defined conversion. Classes can define conversions to other types that can be implicitly applied to objects of that class.

    `class X; // with user-defined conversion to int`

    `void print(float value); void print(int value); X value; print(value);`

    Will resolve to print(int). User-defined conversions are all considered equal
- Ambiguous matches occur when the parameters match equally good (as conversions - standard and user-defined are considered equal)

`void print(unsigned int value); void print(float value);`

`print('a'); print(0); print(3.14159);` Ambiguous matches, result in compile-time error.

Three ways to resolve:
1. Define a new overloaded function that takes parameters of exactly the type called
2. Explicitly cast ambiguous argument: `print(static_cast<unsigned int>(x));`
3. If argument is a literal, we can use literal suffix: `print(0u);` - matches unsigned int

- For multiple arguments, the function with a better match for at least one parameter and no worse for the other parameters will be chosen

## Default arguments
- Function parameter with default value is called an **optional parameter**:

`void printValues(int x, int y=10){ ... }`

`int main(){ printValues(1); // y will use default argument 10`

`printValues(3, 4); // y will use user-supplied argument 4 }`

- The following is NOT allowed: `void printValue(int x=10, int y);`, as well as function call syntax `printValues(,,3);`

- Default argument can only be declared once - either in function definition or a forward declaration - but not in both. Best practise - in forward declaration

- Functions with default args can be overloaded: `void print(std::string string); void print(char ch=' ');`. *print()* would resolve to *print(' ')*

- Optional params do NOT count towards the parameters that make function unique:

`void printValues(int x); void printValues(int x, int y=20);` - this is not allowed

# Function pointers
- Functions have their own l-value function type - e.g. below function has a func type that returns an int and takes no params
- Much like vars, funcs live at an assigned address in memory. When a func is called, execution jumps to the address of the function being called:

`int foo(){ return 5 } // code for foo starts at memory address 0x002717f0`

`int main() { foo(); // jump to address 0x002717f0`

`return 0; }`

- If we pass the identifier of func w/o calling it to cout, it may print it's address: `std::cout << foo;`. If my machine doesn't print the func's address, I may be able to force it by converting the func to a void pointer and printing that: `std::cout << reinterpret_cast<void*>(foo);`
- Just like we can declare non-const pointer to a normal variable, it's possible to declare a non-const pointer to function:

`int (*fcnPtr)();` - fcnPtr is a pointer to a function that takes no arguments and returns an integer. fcnPtr can point to any function that matches this type
- To make a const function pointer, the const goes after the asterisk:

`int (*const fcnPtr)();`. If const is put before the int, what would indicate the function being pointer to would return a const int
- Function pointers can be initialized with a function (and non-const function pointers can be assigned a function). In the above *foo* example, we used foo directly, and it has been converted to a function pointer. Like with pointers to variables, we can also use `&foo` to get a function pointer to foo

`int goo(){ return 6 }; int (*fcnPtr)(){ &foo }; fcnPtr = &goo;`
- The type (parameters and return type) of func pointer must match the type of the func

`int hoo(int x); double kek(); int (*fcnPtr2)(){ &kek };` - wrong, return type doesn't match. `fcnPtr2 = &hoo;` - wrong, parameters don't match
- Unlike fundamental types, C++ *will* implicilty convert a func into a func pointer if needed (so operator& is not necessary). However, it won't implicilty convert func ptrs to void ptrs, or vice-versa.
- Two ways to call a func via func ptr (function - `int foo(int x);`):
    1. Explicit dereference: `int (*fcnPtr)(int){ &foo }; (*fcnPtr)(5);`
    2. Implicit dereference: `fcnPtr(5);`. Some older compilers don't support this
- Default params won't work for funcs called through function ptrs. That's because default params are resolved at compile-time, and func pointers are resolved at run-time.
- Functions used as arguments to another function are sometimes called **callback functions**
- For example, we want to add own comparator function to selection sort. Comparator funcs:

`bool ascending(int x, int y) { return x > y; }`

`bool descending(int x, int y) { return x < y; }`

A pointer to such function would look like (3rd parameter):

`void selectionSort(int *array, int size, bool (*compasionFcn)(int, int))`

Inside selection sort, the comparison is now done like this:

`if (comparisonFcn(array[bestIndex], array[currentIndex])) { bestIndex = currentIndex; }`

And we use it like this:

`selectionSort(array, 9, descending);`

We can provide default function:

`void selectionSort(int *array, int size, bool (*compasionFcn)(int, int) = ascending);`

And call it:

`selectionSort(array, 9);`
- If a function parameter is of a function type, it will be converted to a pointer to the function type. That means, we can write the above sort function declaration as

`void selectionSort(int *array, int size, bool compasionFcn(int, int));`
- We can make type aliases for pointers to functions:

`using CompareFunction = bool(*)(int, int);`

`void selectionSort(int *array, int size, CompareFunction compasionFcn);`
- We can use *std::function* from `#include <functional>`:

`void selectionSort(int *array, int size, std::function<bool(int, int)> fcn);`

If there are no parameters, parentheses can be left empty `()`. Another example:

`int foo() { return 5; }`

`std::function<int()> fcnPtr{ &foo }; fcnPtr = &goo; std::cout << fcnPtr();`

For *std::function**, you can do the alias too.
- We can infer the type of func pointer using *auto*, just like we infer the type of normal variables:

`int goo(int x) { return x; }`

`auto fcnPtr{ &goo }; std::cout << fcnPtr(6);`
- Also function pointers are useful when you want to store functions in array or other structure
- Recommendation is to use `std::function`. And in places where a func pointer type is used multiple times, make a type alias to your *std::function*

# Memory
- Memory that program uses is typically divided into areas, called **segments**:
    - **Code segment** (also *text segment*), where the compiled program sits in memory. Is typically read-only
    - **Bss segment** (also *unitialized data segment*), where zero-initialized global and static variables are stored
    - **Data segment** (also *initialized data segment*), where initialized global and static vars are stored
    - **Heap** (also *free store*), where dynamically allocated vars are allocated from
    - **Call stack** (also *stack*), where function params, local vars, and other function-related information are stored
- Sequential memory requests (e.g., via *new*) may not result in sequential memory addresses being allocated
- Advantages and disadvantages of heap:
    - Allocing memory is comparatively slow
    - Allocated memory stays alloced until specifically dealloces or the app ends (then OS should clean it up)
    - Dynamically alloced memory must be accessed via pointer. Dereferencing pointer is slower than accessing a var directly
    - Heap is a big pool of memory, so large arrays, structures, or classes can be alloced here
- Call stack keeps track of all active funcs (those that were called but not terminated) from the start of the program to the current point of execution, and handles allocation of all function params and local vars
- Call stack is implemented as **stack** data structure
- **Data structure** is a programming mechanism for organizing data so that it can be used efficiently (e.g. array, struct). They provide mechanisms for storing and accessing data in an efficient way.
- Array lets you access and modify elems in any order (called **random access**)
- How call stack works, stack overflow, and adv/disadv of the stack: see `conspect/text/call-stack.md`

## std::vector capacity and stack behaviour
- In `std::vector`, **length** is how many elems are being used in the array; **capacity** is how many elems were alloced in memory.
- `array.resize(n)` causes to change both length and capacity if resized to bigger, and only length (capacity stays the same) if resized downwards. It works similarly if you do it using initializer's lists (`vect = { 1, 2, 3 };`).
- The range for `[]` and `at()` are based on vector's length, not capacity
- Can be used as a stack using functions `push_back()`, `back()` (returns the value of the top elem), `pop_back()`. `push_back()` will resize vector.
- Because resizing is expensive, we can tell vector to alloc a certain amount of capacity using `reserve()`:

`std::vector<int> stack{}; stack.reserve(5);`
- When vector is resized, it may allocate more capacity than is needed.

# Recursion
- **Recursive termination** is a condition that, when met, will cause the recursive function to stop calling itself
- Inputs for which an algorithm trivially produces an output is called a **base case**. Base cases act as termination conditions for the algorithm. Base cases can often be identified by considering the output for an input of 0, 1, "", '', or null

Example:

`int sumTo(int sumto) {`

`if (sumto <= 0) return 0; // base case (termination condition) when user passed in unexpected param (<=0)`

`else if (sumto == 1) return 1; // normal base case (termination condition)`

`else return sumTo(sumto - 1) + sumto; // recursive function call`

`}`

Note, that `sumto - ` is used instead of `--sumto`. That's because `operator--` has a side effect, and we use var `sumto` one more time in the whole expression

- Fibonacci numbers is a typical function that uses recursive algorithm for its implementation
- **Memoization** is a technique that caches the results of expensive function calls so thee result can be returned if the same input occurs again. Example with memoized fibonacci recursion: `conspect/src/fibonacci-recursion.cpp`
- Recursion is good choice when most of these are true:
    - Recursive code is much simpler to implement
    - Recursion depth can be limited
    - Iterative version of the algorithm requires managing a stack of data
    - This isn't a performance-critical section of code
- But almost always should favor iteration over recursion

# Handling errors
- **Semantic error** occurs when statement is syntactically valid, but doesn't do what it is intended to do. Some types:
    - **Logic error**: `if(x >= 5) std::cout << "x is greater than 5";
    - **Violated assumption** - the programmer assumes that something will be either true or false, and it isn’t
- **Defensive programming** - form of program design that involves trying to identify areas where assumptions may be violated, and writing code that detects and handles any violation of those assumptions so that program reacts in a predictable way when those violations do occur. Almost all assumptions can be checked in:
    1. When a function has been called, function arguments are incorrect or semantically meaningless
    2. When function returns, return value may indicate that error occured
    3. Program receives input (from user/file), it may not be in correct format

Consequently, following rules should be used when programming defensively:
1. At the top of each function, check to make sure any parameters have appropriate values
2. After a function has returned, check the return value (if any), and any other error reporting mechanisms, to see if an error occurred
3. Validate any user input to make sure it meets the expected formatting or range criteria

Methods to handle errors:
1. Skip the code if the assumption is wrong (bad, because user has no way to see if something went wrong): `void printString(const char *cstring) { if (cstring) std::cout << cstring; }`
2. Return error code from function and let caller deal with it
3. `#include <cstdlib>`, then `std::exit(2);` - terminate app and return error code 2 to OS
4. Ask the user to enter input again
5. `std::cerr` (like *cout*) - e.g., add the `else` clause to the first method to print the error message if `cstring` is null
6. If working in graphical environment (e.g. MFC, SDL, QT, etc) - pop up a message box with an error code and then terminate the app

## Assert
- **Assert statement** is a preprocessor macro that evaluates a conditional expression at runtime. If the conditional expression is true, the assert statement does nothing. If the conditional expression evaluates to false, an error message is displayed and the program is terminated. This error message contains the conditional expression that failed, along with the name of the code file and the line number of the assert
- From `<cassert>`
- Trick to make asserts more descriptive: `assert(found && "Car could not be found in database");`
- To turn off asserts in production code, we need to define `NDEBUG` macro (e.g., in Visual Studio, the following preprocessor definitions are set at the project level: WIN32;NDEBUG;_CONSOLE - so asserts are stripped out of release code by default)
- **Note**: `exit()` and `assert()` functions terminate the app immediately, without a chance to cleanup (e.g. close a file or database), so be careful to not cause any corruptions
- `static_assert` is a compile-time assert. Because it's evaluated at compile time, 1. we can place it anywhere in the code file; 2. conditional part must be evaluated at compile time too. Example: `static_assert(sizeof(int) == 4, "int must be 4 bytes");`. In C++11, the diagnostic message must be passed as 2nd parameter, since C++17 it is optional

# Command line arguments
- **Command line arguments** are optional string arguments that are passed by the operating system to the program when it is launched: `C:\>WordCount Myfile.txt Myotherfile.txt`
- `int main(int argc, char *argv[])` is equal to `int main(int argc, char** argv)`
    - **argc** contains a number of args passed to the program (`arg`ument `c`ount). Will always be at least 1, because the first argument is always the name of the program itself
    - **argv** is where the actual arguments are stored (`arg`ument `v`alues, though the proper name is `arg`ument `v`ectors). It is an array of C-style strings
- To deal with numeric args, they must first be converted. To see example: `conspect/src/numeric-program-arguments.cpp`
- The OS parses command line args first. Typically, OSs have special rules about how special characters like double quotes and backslashes are treated. E.g.: `Hello world` are 2 arguments, but if we write `"Hello world"`, it will be treated as a single string argument. We could also escape double quotes `\"Hello world\"`, and now it's again counted as 2 arguments (`"Hello` and `world"`)

# Ellipsis
- We can pass variable number of parameters to a function using **ellipsis**: `return_type function_name(argument_list, ...)`. Ellipsis must always be the last parameter in the func. It captures additional arguments (if there are any).
- To see implementation of `findAverage()` using ellipsis (and 3 methods to track parameters count): see `conspect/src/ellipsis.cpp`
- Using ellipsis is discouraged, as it is dangerous:
    - There is no type checking. The following is possible (will produce garbage result): `findAverage(6, 1.0, 2, "Hello, world!", 'G', &value, &findAverage);`
    - Ellipsis don't know how many params were passed - we have to do the tracking ourselves:
        1. Method 1: Pass a length parameter
        2. Method 2: Use a sentinel value - **sentinel** is a special value that is used to terminate a loop when it is encountered
        3. Method 3: Use a decoder string
- Recommendations if still decided to use ellipsis:
    - Do not mix expected argument types if possible
    - Using a count parameter or decoder string is generally safer than using a sentinel. This ensures the ellipsis loop will terminate after a reasonable number of iternations even if it produces garbage value

# Lambdas
- **Lambda expression** (also **lambda** or **closure**) allows us to define anonymous function inside another function. Nesting is important, as it allows us both to avoid namespace pollution and to define the function as close to where it is used as possible (providing additional context)
- Syntax:

`[ captureClause ] ( parameters ) -> returnType`

`{`

&ensp;&ensp;&ensp;`statements;`

`}`

The *capture clause* and *parameters* can both be empty if they are not needed. The *return type* is optional, and if omitted, *auto* will be assumed (thus using type inference used to determine the return type). Though type inference for return types should be avoided, in this context, it's fine (because these functions are typically trivial)

`[]() {}; // defines a lambda with no captures, no parameters, and no return type`
- Prefer regular functions over lambdas for non-trivial and reusable cases

## Lambdas type
- The use of a lambda in `conspect/src/lambdas/rewrite-function-to-lambda.cpp` is correct. This use is sometimes called **function literal**
- We can initialize a lambda variable with a lambda definition and use it later. Instead of:

`return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); });`

We could do it much clearer:

`auto isEven{`

`[](int i)`

`{`

`return ((i % 2) == 0);`

`}`

`};`

`return std::all_of(array.begin(), array.end(), isEven);`
- Lambdas don't have a type that we can explicitly use. When we write a lambda, the compiler generates a unique type just for the lambda that is not exposed to us.
- In actuality, lambdas aren’t functions (which is part of how they avoid the limitation of C++ not supporting nested functions). They’re a special kind of object called a *functor*. Functors are objects that contain an overloaded `operator()` that make them callable like a function.
- There are several ways of storing lambda to use post-definition. See `conspect/src.lambdas/storing-lambda.cpp`
- **Rule**: Use `auto` when initializing variables with lambdas, and `std::function` if you can’t initialize the variable with the lambda.

## Generic lambdas
- Lambda parameters work by the same rules as regular function parametes. Since C++14, we are allowed to use *auto* for parameters in lambdas (from C++20, in regular functions too). The compiler will infer the types from the calls. Because lambdas with one or more *auto* parameter can potentially work with a wide variety of types, they are called **generic lambdas**
- When used in context of lambda, *auto* is just a shorthand for a template parameter
- To see when we can and can't use generic lambdas: `conspect/src/lambdas/generic-lambda.cpp`

### Generic lambdas and static variables
- One thing to be aware of is that a unique lambda will be generated for each different type that auto resolves to. The example how one generic lambda turns into two distinct lambdas: see `conspect/src/lambdas/generic-lambda-static-variable.cpp`

## Return type deduction and trailing return types
- If we use return type inference, all return statements must return the same type (e.g. can't `return x / y;` in if-clause and `return static_cast<double>(x) / y;` in else-clause)
- If we want to return different types, we can:
    1. Do explicit casts to make all the return types match
    2. Explicitly specify a return type for the lambda (trailing type), and let the compiler do implicit conversions

## Standard library function objects
- For common operations (e.g. addition, negation or comparison) we don't need own lambdas, as there are many basic callable objects defined in `<functional>` header. E.g.: `std::sort(arr.begin(), arr.end(), std::greater{});` using `std::greater`

## Lambda captures
- Unlike nested blocks, where any identifier defined in outer block is accessible in the scope of nested block, lambdas can only access specific kinds of identifiers: global identifiers, entities that are known at compile time, entities with static storage duration
- **Capture clause** is used to (indirectly) give a lambda access to variables available in surrounding scope that it normally would not have access to:

`std::cin >> search;`

`auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) { return (str.find(search) != std::string_view::npos); }) };` - capture *search*
- When a lambda definition is executed, for each var that lambda captures, clone of that var is made (with identical name) inside lambda. Cloned vars are initialized from the outer scope vars of the same name at this point. While cloned vars have the same name, they don't necessarily have the same type as original vars
- When compiler encounteres lambda definition, it creates a custom object definition for the lambda. Each captured var becomes a data member of the object. At runtime, when lambda definition is encountered, lambda object is instantiated, and the members of the lambda are initialized.
- Captures default to const value
- To allow modifications of vars that were captured by value, we can mark the lambda as *mutable*. `mutable` keyword in this context removes the *const* qualification from all vairables captured by value (note: only the captured copy will be modified, not the variable defined outside of the lambda). See: `conspect/src/lambdas/mutable-lambda.cpp`

### Capture by reference
- We can also capture variables by reference to allow out lambda to affect the value of the original variable: `auto shoot{ [&ammo]() { --ammo; }};`. Unlike variables captured by value, variables that are captured by reference are non-const, unless the variable they're capturing is const.
- Capture by ref should be preferred over capture by value just like for passing arguments to functions (e.g. for non-fundamental types)
- We can capture multiple variables: `[health, armor, &enemies](){};`

### Default captures
- **Default capture** (or *capture-default*) captures all vars that are mentioned in the lambda. To capture all used vars by value, use a capture value of `=`. To capture all used vars by ref, use capture value of `&`. We can mix default captures with normal captures. We can capture some by value, some by ref, but each variable can only be captured once. See `conspect/src/lambdas/default-capture.cpp`

### Defining new variables in lambda-capture
- If we want to capture a var with slight modification or declare a new var that's only visible in scope of lambda, we can define a var in lambda-capture without specifying its type:

`int width{}; int height{}; std::cin << width << height;`

`auto found{ std::find_if(areas.begin(), areas.end(), [userArea{ width * height }](int knownArea) { return (userArea == knownArea); }) };`

*userArea* type will be deduced to be int. *userArea* will only be calculated once lambda is defined. The calculated area is stored in the lambda object.
- Best practise is to only initialize vars in the capture if their value is short and their type is obvious. Otherwise it's best to define the var outside of the lambda and capture it

### Dangling captured variables
- Variables are captured at the point where the lambda is defined. If a variable captured by reference dies before the lambda, lambda will be left holding a dangling reference.
- See `conspect/src/lambdas/dangling-captured-variables.cpp`

### Unintended copies of mutable lambdas
- Because lambdas are object, they can be copied. This can cause problems in some cases. See `conspect/src/lambdas/unintended-lambda-copy.cpp` and `conspect/text/unintended-lambda-copy.md` for comment