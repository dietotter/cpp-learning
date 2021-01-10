# Some terminology
- Yield - отдавать/выдавать. Пример: Taking the address of a pointer yields the memory address of the pointer variable - Если мы возьмем адрес у указателя (имеется ввиду с помощью &), нам выдас адрес переменной, которая хранит этот указатель.
- Ambiguity - двусмысленность
- Contrived - надуманный
- Leverage - использовать
- Inherently - по своей сути
- Incur - нести за собой
- Inadvertently - нечаянно
- Retroactively - задним числом
- Ubiquitous - вездесущий
- Waive - отказаться
- Compelling - убедительный, веский

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
- **Fallthrough** - when execution flows from a statement underneath some case to statements of some other cases (because of abscence of *break* or *return*). Because it is rarely wanted, compiler may flag it as warning. From C++17, we can use `[[fallthrough]]` with null statement to let compiler know that overflow (fallthrough) is intentional:

`case 1:`

`std::cout << 1 << '\n';`

`[[fallthrough]];`

`case 2: ...`

## Goto
- *Goto statements* have **function scope** - they and the corresponding *statement labels* should appear in the same function
- To see how goto statements and statement labels are used, see `conspect/src/goto.cpp`
- Gotos should be avoided

## While loops
- For performance reasons, it's better to define non-fundamental variables (such as structs and classes) before the loop

## For loops
- Variables in for loops have **loop scope** - they exist only within the loop

## Halts
- **Halt** is a flow control statement that terminates the program. In C++, they are implemented as functions (not keywords), so halt statements = function calls.
- **Normal termination** - the program has exited in an *expected* way (doesn't imply that the program was *successful* - status code is used for that).
- `std::exit()` is a function that causes the program to terminate normally. It performs some cleanups: First, objects with statuc storage duration are destroyed. Then some other miscellaneous file cleanup is done if any files were used. Finally, controll is returned to the OS, with the argument passed to *std::exit()* used as status code.
- `std::exit()` is called implicitly when `main()` function ends. We can call it explicitly too, including it from `<cstdlib>` header.
- `std::exit()` function does not clean up local variables in the current function or up the call stack. Because of this, we should avoid calling `std::exit()` explicitly. Because it exits immediately, we need to do some cleanup ourselves (for example, in some `cleanup()` function). To assist with this, C++ offers `std::atexit(cleanup_function_name)` function, which allows to specify which function will be called on program termination via `std::exit()`. The function being registered must take no parameters and have no return value. We can register multiple cleanup functions, they will be called in reverse order of registration.
- In multithreaded programs `std::exit()` can cause the app to crash, because it cleans up static objects, which may be used by other threads. For this reason, C++ offers another functions: `std::quick_exit()` and `std::at_quick_exit()`. *quick_exit* does not clean up static objects, and may or may not do other types of clean up.
- **Abnormal termination** means the program had some kind of unusual runtime error and it couldn't continue to run (e.g., trying to divide by 0)
- `std::abort()` causes program to terminate abnormally
- `std::terminate()` is typically used with exceptions. It's most often called implicitly when an exception isn't handled (and in some other exception-related cases). By default, *std::terminate()* calls *std::abort()*.
- **Rule**: Only use a *halt* when there is no safe way to return nrmally from the main function. If exceptions aren't disabled, use them.

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

# Classes
- Functions defined inside of a class - **member functions** (or **methods**). They can be defined inside or outside of the class definition
- **The implicit object** - the associated object that is implicitly passed to a member function (`today.print()` - *today*)
- With member functions, you can call a function that's defined below it without a forward declaration
- Classes can have **member types** or **nested types** (including type aliases):

`class Calculator {`

`public:`

`using number_t = int; // nested type alias`

`...`

`};`

From outside the class, we can access the type via `Calculator::number_t`
- Nested types cannot be forward declared, and generally should only be used when the nested type is used exclusively within that class.
- Since classes are types, it's possible to nest classes inside other classes
- Structs have the ability to have member functions too, but we shouldn't do it. **Rule**: Use the `struct` keyword for data-only structures. Use the `class` keyword for objects that have both data and functions.
- Members are **private** by default
- **Access specifiers**: `private`, `protected`, `public`
- The group of public members of a class are often referred to as **public interface** - it defines how programs using the class will interact with it.
- Access control works on a **per-class** basis, not a **per-object** basis. This means that when a function has access to the private members of a class, it can access the private members of *any* object of that class type. E.g. (`copyFrom` is public member function of *DateClass*; `m_month` and other are private members):

`void copyFrom(const DateClass &d) { m_month = d.m_month; m_day = d.m_day; m_year = d.m_year; }`
- Struct defaults its members to **public**

## Encapsulation
- **Encapsulation** (also called **information hiding**) is the process of keeping the details about how an object is implemented hidden away from users of the object. Instead, users of the object access the object through a public interface. In this way, users are able to use the object without having to understand how it is implemented. *Note*: The word encapsulation is also sometimes used to refer to the packaging of data and functions that work on that data together. We prefer to just call that object-oriented programming.
    - *Benefit*: encapsulated classes are easier to use and reduce the complexity of your programs - we can use a class without having to know how it was implemented
    - *Benefit*: encapsulated classes help protect your data and prevent misuse:

`class MyString { char *m_string; int m_length; };` - *m_length* should always equal the length of the string held by *m_string* (this connection is called **invariant**). If they were public, anybody could chang ethe length of the string without changing m_string (or vice-versa). This would put the class into inconsistent state
- (continuing)
    - *Benefit*: encapsulated classes are easier to change
    - *Benefit*: encapsulated classes are easier to debug: we can set breakpoints in **access functions** - a short public function whose job is to retrieve or change the value of private member variable. These are **getters** (or **accessors**) and **setters** (or **mutators**)
        - **Best practise**: getters should return by value or const reference
- For access functions, *whether to provide them*, we should consider the following:
    - If nobody outside your class needs to access a member, don’t provide access functions for that member.
    - If someone outside your class needs to access a member, think about whether you can expose a behavior or action instead (e.g. rather than a setAlive(bool) setter, implement a kill() function instead).
    - If you can’t, consider whether you can provide only a getter.

## Constructors
- When all members of a class (or struct) are public, we can use **aggregate initialization** to initialize the class (or struct) directly using an initialization list or uniform initialization:

`class Foo { public: int m_x; int m_y; };`

`Foo foo1 = { 4, 5 }; // initialization list`

`Foo foo2 { 6, 7 }; // uniform initialization`
- A constructor that takes no parameters (or has parameters that all have default values) is called a **default constructor**: `Foo() { m_x = 0; m_y = 1; }`

then `int main(){ Foo foo; return 0; }`

Because we’re instantiating an object of type Foo with no arguments, the default constructor will be called immediately after memory is allocated for the object, and our object will be initialized. Without a default constructor, m_x and m_y would have garbage values (fundamental variables aren't initialized by default)
- Favor brace initialization to initialize class objects: `Foo(int x, int y=1) { m_x = x; m_y = y; }`

`Foo oneFoo{ 1, 2 }; Foo twoFoo{ 5 };`

over direct initialization:

`Foo threeFoo(3, 4);`

- It's also possible to initialize using copy initialization (relevant before C++11):

`Foo six = Foo{ 6 }; // will call Foo(6, 1)`

`Foo seven = 7; // also copy initialize, will invoke Foo(7, 1)`

but we should avoid it, because copy-initialization does not work the same with classes as uniform or direct initializations
- We could reduce the number of constructors, for example, by doing this: `Foo(int x=0, int y=1) { ... }`

then we can: `Foo zero; Foo one{}; Foo two{ 2 }; Foo three{ 3, 5 };`
- For implicit constructors, see `conspect/text/classes/implicit-constructor.md`
- We can explicitly tell the compiler to create a default constructor, even if there are other user-provided constructors: `Foo() = default;`. It's almost the same as adding a default constructor with empty body, the difference is that *= default* allows us to safely initialize member variables even if they don't have an initializer: see `conspect/src/classes/default-constructor.cpp`. **Rule**: If you have constructors in your class and need a default constructor that does nothing, use *= default*.
- Classes may contain other classes as member variables. If a `class B` has a private member of `class A` - `A m_a;`, and we have `int main() { B b; return 0; }`. When variable `b` is constructed, the `B()` constructor is called. Before the body of the constructor executes, `m_a` is initialized, calling the `class A` default constructor. Then control returns back to the `B` constructor, and the body of the `B` constructor executes.
- `class`-type members get initialized even if we don’t explicitly initialize them.
- Constructor does not create an object - the compiler sets up the memory allocation for the object prior to the constructor call.
- Constructor is for:
    - Determining who is allowed to create an object (an object of class can only be created if a matching constructor is found)
    - Can be used to initialize objects
- **Best practise** - initialize all member variables, whether via constructor, or via other means
- Constructors are only intended to be used for initialization when the object is created. You should not try to call a constructor to re-initialize an existing object. While it may compile, the results will not be what you intended (instead, the compiler will create a temporary object and then discard it).

### Member initializer lists
- The version with assignment in constructor might be less efficient than using members initialization (and doesn't work with references or const variables). So to initialize member variables, we use **member initializer lists**:

`Something(int value1, double value2, char value3 = 'c')`

`: m_value1{ value1 }, m_value2 { value2 }, m_value3 { value3 }`

`{ /* no need for assignment here */ }`
- If we have array member: `const int m_array[5];`, since C++11 we can initialize it using uniform initialization: `Something(): m_array{ 1, 2, 3, 4, 5 } { }`

Before C++11, we could only zero initialize it: `Something(): m_array {} { }`
- We can also initialize members that are classes: `class B` has member `A m_a;`. `class A` has constructor `A(int x) { ... }`. Class B constructor: `B(int y): m_a{ y - 1 } { ... }` - call *A(int)* constructor to initialize member *m_a*
- Formatting recommendations:
    - If initializer list fits on the same line as function name, put everything in one line
    - If init list doesn't fit on the same line as function name, then it should go indented on the next line
    - If all of the initializers don't fit on a single line (or the initializers are non-trivial), then we can space them out, one per line
- Variables in the initializer list are initialized in the order in which they are declared in class
- Recommendations:
    1. Don’t initialize member variables in such a way that they are dependent upon other member variables being initialized first
    2. Initialize variables in the initializer list in the same order in which they are declared in your class

### Non-static member initialization
- Since C++11, it's possible to give normal (without `static` keyword) class member variables a default initialization value directly:

`class Circle { private: double m_radius{ 1.0 }; };`

Now if we call default constructor (if it is provided by user or implicitly by compiler) - `Circle x{};`, - *x* initializes with the radius of `1.0`.
- **Rule**: Favor use of non-static member initialization to give default values for your member variables.

### Delegating constructors
- Constructors are allowed to call other constructors. This process is called **delegating constructors** (or **constructor chaining**). To delegate a constructor, simply call the constructor in the member initializer list. See `conspect/src/classes/delegating-constructors.cpp`
- Some notes:
    - Constructor that delegates to another constructor is not allowed to do any member initialization itself. So your constructors can delegate or initialize, but not both.
    - It’s possible for one constructor to delegate to another constructor, which delegates back to the first constructor. This forms an infinite loop.
- **Best practise**: If you have multiple constructors that have the same functionality, use delegating constructors to avoid duplicate code.
- Another way to deal with overlapping functionality is to move it to a separate function, and then call it in constructors which need this functionality. E.g. something like `void init() {}`
- Be careful when using functions like `init()` with dynamically allocated memory
- Btw: by the time the constructor starts executing statements in its body, members already exist and have been default initialized or are unitialized. Then we can only assign values to the members

## Destructors
- **Destructor** is another special kind of class member function that is executed when an object of that class is destroyed. Whereas constructors are designed to initialize a class, destructors are designed to help clean up. When an object goes out of scope normally, or a dynamically allocated object is explicitly deleted using the delete keyword, the class destructor is automatically called (if it exists)
- If your class object is holding any resources (e.g. dynamic memory, or a file or database handle), or if you need to do any kind of maintenance before the object is destroyed, the destructor is the perfect place to do so
- `~Circle() { ... }`
- As destructor can't take arguments, only one destructor may exist per class
- Destructors may safely call other member functions since the object isn’t destroyed until after the destructor executes
- For class using destructor example, **RAII** (**Resource Acquisition Is Initialization**) example and `-Weffc++` "*class has pointer data members ... but does not override ...*" error, see `conspect/src/classes/destructor-and-raii.cpp`
- If using `exit()` function, program will terminate and no destructors will be called

## Hidden *this* pointer
- `simple.setID(2);`. Although the call to function setID() looks like it only has one argument, it actually has two. When compiled, the compiler converts it into:

`setID(&simple, 2);`

Consequently, member function `void setID(int id) { m_id = id; }` is converted into:

`void setID(Simple* const this, int id) { this->m_id = id; }`
- **this pointer** is a hidden const pointer that holds the address of the object the member function was called on
- The recommendation is to use the *m_* prefix rather than *this->* on member variables for solving the duplicate name problem (`m_x = x;` rather than `this->x = x;`)
- We may need to return `*this` from function when we want to enable chaining member functions. See `conspect/src/classes/chaining-member-functions.cpp`

## Class code and header files
- Types (which include classes) are exempt from the part of the one-definition rule that says you can only have one definition per program, so there isn't an issue #including class definitions into multiple code files
- Member functions defined inside class definition are considered implicitly inline, so there is no problem defining trivial member functions (such as access functions) inside the class definition itself
- Member functions defined outside the class definition are treated like normal functions, so those functions should be defined in a code file. The one exception for this is for template functions
- Recommendations:
    - For classes used in only one file that aren’t generally reusable, define them directly in the single .cpp file they’re used in
    - For classes used in multiple files, or intended for general reuse, define them in a .h file that has the same name as the class
    - Trivial member functions (trivial constructors or destructors, access functions, etc…) can be defined inside the class
    - Non-trivial member functions should be defined in a .cpp file that has the same name as the class
- Default parameters for member functions should be declared in the class definition (in the header file), where they can be seen by whomever #includes the header
- Outside of some open source software (where both .h and .cpp files are provided), most 3rd party libraries provide only header files, along with a precompiled library file. There are several reasons for this:
    1. It’s faster to link a precompiled library than to recompile it every time you need it
    2. A single copy of a precompiled library can be shared by many applications, whereas compiled code gets compiled into every executable that uses it (inflating file sizes)
    3. Intellectual property reasons (you don’t want people stealing your code)

## Const classes
- Classes can also be made const by using const keyword. Initialization is done via class constructors. After that, the members can't be changed, even with member functions
- Const class objects can only explicitly call *const** member functions
- **const member function** is a member function that guarantees it will not modify the object or call any non-const member functions (as they may modify the object)
- To make a member function const: `int getValue() const { return m_value; }` For member functions defined outside the class definition, we need to use `const` keyword both on function prototype in class definition and function definition:

`int getValue() const;` (inside `class Something`)

`int Something::getValue() const { return m_value; }`
- Constructor can't be const as they need to be able to initialize member vars
- **Rule**: Make any member function that does not modify the state of the class object *const*, so that it can be called by const objects
- A more common way to use const class objects is by passing an object to a function by const reference `void printDate(const Date &date) { ... }`
- It's possible to overload a function to have a const and non-const version:

`const std::string& getValue() const { return m_value; }`

`std::string& getValue() { return m_value; }`

The first one will be called on any const objects, the second one - on non-const objects. Such overloading is typically done when the return value needs to differ in constness - the non-const version of getValue() is more flexible because we can use it to both read and write m_value.

## Static member variables and functions
- Static member variables are shared by all objects of the class: `static int s_value;`. They can be accessed directly using the class name (this is the preferred method for accessing static members): `Something::s_value = 2;`
- When we declare a static member var inside a class, we're telling the compiler about its existence, but not actually defining it (much like forward declaration). Because static member vars are not part of the individual class objects (they are treated similarly to global vars and are initialized when the program starts), we must explicitly define the static member outside of the class, in the global scope: `int Something::s_value{ 1 };`. This line serves 2 purposes - instantiates the static member var (just like global var), and optionally initializes it (if no initializer is provided, C++ will init it to 0)
- The above static member definition can be done even if the member is declared as private or protected
- If the class is defined in a .h file, define static member in the associated .cpp file. If class is defined in .cpp, define it directly underneath the class. Few shortcuts:
    1. When the static member is a const integral type (which includes char and bool) or a const enum, the static member can be initialized inside the class definition: `static const int s_value{ 4 };`
    2. Static constexpr members can be initialized inside the class definition:

    `static constexpr std::array<int, 3> s_array{ 1, 2, 3 }; // this even works for classes that support constexpr initialization`
- Static member vars can be useful when implementing unique id system, or internal lookup table
- For private static members we can write static access functions
- Static member functions have no `*this` pointer
- Static member functions can directly access other static members, but not non-static members
- **pure static classes** (or **monostates**) - classes with all static members. Although they can be useful, some warnings:
    - There is no way to have multiple copies of a pure static class (e.g. if I needed 2 independent IDGenerator objects, this would not be possible with a single pure static class)
    - The problems of global vars (such as that any piece of code can change the value of the global variable) hold the same for pure static classes
- C++ does not have static constructors. If initializing static member vars requires executing code (e.g. a loop) there are many different ways of doing that. E.g., one way that works with all vars, static or not, is to use a lambda and call it immediately: `std::vector<char> MyClass::s_mychars{ []{ ... }() };`
- There is one way to init static members kinda like a constructor. See `conspect/src/classes/interesting-static-member-init.cpp`. Though probably I'll never need it

## Friend functions and classes
- **Friend function** is a function that can access the private members of a class as though it were a member of that class. Friend function may be either a normal function, or a member function of another class. To declare it - simply use the `friend` keyword in front of the prototype of the func I wish to be a friend of the class (e.g., in `class Accumulator`):

`friend void reset(Accumulator &accumulator);`. It doesn't matter where to declare it - in the private or public section of the class. Then, outside the class:

`void reset(Accumulator &accumulator) { accumulator.m_value = 0; }` - considering that `m_value` is private member, *reset* (while not being a member function) has access to it, because it is a friend function. We have to pass an Accumulator object to it, because it doesn't have a `*this` pointer.
- Another example - `class Value` with private `int m_value;`. Friend function: `friend bool isEqual(const Value &value1, const Value &value2);` It will have access to the private members of all Value objects, so it can do the comparison on two objects.
- A function can be a friend of more than one class at the same time. Consider two classes: `Temperature` and `Humidity` and a function, that is a friend of both of them:

`friend void printWeather(const Temperature &temperature, const Humidity &humidity);`, which prints the temperature and humidity by accessing the private members of both classes.

**Note**: If these are all defined in the same class, and, for example, `Temperature` is defined first, we need to put a class prototype of Humidity above the definition of Temperature class: `class Humidity;`
- It is possible to make an entire class a friend of another class. This gives all the members of the friend class access to the private members of the other class. Inside *class Storage*: `friend class Display;`. Then, inside *class Display*:

`void displayItem(const Storage &storage) { std::cout << storage.m_value; }`

And use it in *main()*: `display.displayItem(storage);`
- Instead of making an entire class a friend, we can make a single member function a friend. This is a little trickier, because in order to make a member function a friend, the compiler has to have seen the full definition for the class of the friend member function (not just a forward declaration). How its made when everything is defined in a single file: see `conspect/src/classes/friend-member-function.cpp`
- **Usage**: Friending is uncommonly used when two or more classes need to work together in an intimate way, or much more commonly, when defining overloading operators
- **Best practise**: Limit the use of friend functions and classes to a minimum, because their usage violates encapsulation.

## Anonymous objects
- **Anonymous object** is essentially a value that has no name. Because they have no name, there's no way to refer to them beyond the point where they are created. Consequently, they have *expression scope*. E.g.:

`return x + y; // an anonymous object is created to hold and return the result of x + y`

A copy of the anon object is then returned to the caller by value, and the anon object is destroyed.

This also works with function params: `printValue(5 + 3);`
- It's also possible with classes: (consider *class Cents*) `Cents{ 7 }`. Full example of this: see `conspect/src/classes/anonymous-objects.cpp`
- In C++, anonymous objects are primarily used to pass or return values without having to create lots of temporary variables. Memory allocated dynamically is also done so anonymously (which is why its address must be assigned to a pointer)
- Anonymous objects are treated as *rvalues*
- **Note**: Some compilers, such as Visual Studio, will let you set non-const references to anonymous objects. This is non-standard behaviour

## Nested types in classes
- We can define (nest) other types in classes under the appropriate access specifier
- If we move `enum FruitType { APPLE, BANANA, CHERRY };` inside `class Fruit`, we can now refer to enum values from outside the class as `Fruit::APPLE` (considering its under the `public` access specifier)
- Classes essentially act as a namespace for any nested types. Note that because *enum classes* also act like namespaces, if we'd nested *FruitType* inside *Fruit* as `enum class` instead of `enum`, we'd access the APPLE enumerator via `Fruit::FruitType::APPLE`
- Typedefs, type aliases and other classes can also be nested into classes. Nested classes have the same access to members of the enclosing class that the enclosing class does. Though the nested class does not have nay special access to the `this` pointer of the enclosing class.
- Nested types can't be forward declared (though this may change in future C++)
- The example of nested class: an iterator class

## Timing my code (using timer)
- From C++11, we can use `<chrono>` library. Though as using it is a bit *arcane* (as learncpp author called it), we can encapsulate chrono's timing functionality we need into a class. See `conspect/src/timer.cpp` (there's also how to use it)
- Make sure to use release build when timing, not debug
- Results of timing can be significantly impacted by a lot of things (e.g. system doing cpu/memory/hard drive intensive stuff)

# Operator overloading
- **Operator overloading** - using function overloading to overload operators
- We can think of `x + y` as `operator+(x, y)`
- When evaluating expression containing an operator, compiler uses these rules:
    - If *all* of the operands are fundamental data types, compiler will call built-in routine if one exists. If it doesn't exist, compiler will produce a compiler error
    - If *any* of the operands are user data types (e.g. class or enum), the compiler looks to see whether the type has a matching overloaded operator function. If it can't find one, it will try to convert one or more user-def type operands into fundamental data types (via an *overloaded typecast*). If that fails, then - compiler error
- Limitations on operator overloading:
    1. Almost any existing C++ operator can be overloaded. Exceptions: conditional (`?:`), `sizeof`, scope (`::`), member selector (`.`), member pointer selector (`.*`), `typeid`, and the casting operators
    2. I can only overload operators that exist. Can't create new operators or rename existing.
    3. At least one of the operands of overloaded operator must be a user-defined type
    4. It is not possible to change the number of operands an operator supports
    5. All operators keep their default precedence and associativity, this can't be changed (e.g. if we try to overload bitwise XOR (`^`) to do exponentiation, this won't work, as `^` has lower precedence than basic arithmetic operators. So we'd need to always use parentheses, and it's counter-intuitive: e.g. `4 + (3 ^ 2)` (also, we can't overload it like this, because 3 and 2 are both fundamental data types))
- **Rule**: *When overloading operators, it’s best to keep the function of the operators as close to the original intent of the operators as possible.*
- **Rule**: *If the meaning of an operator when applied to a custom class is not clear and intuitive, use a named function instead.*
- We can overload operators in three ways:
    1. Member function way
    2. Friend function way
    3. Normal function way

## Operator overloading via friend function
- See `conspect/src/overloading-operators/using-friend-function.cpp`. This will be similar for all arithmetic operations (+, -, *, /)
- Despite being not considered a member of the class, we can still define friend functions inside class, but it's not recommended, as non-trivial function definitions are better kept in a separate .cpp file
- If we want to overload operator for operands of different types, we need to do it for all positioning cases. E.g.: `Cents(4) + 6` would call `operator+(Cents, int)`, while `6 + Cents(4)` would call `operator+(int, Cents)`. So we need two functions for this case
- We can implement overloaded operators using other overloaded operators. E.g. `Cents operator+(int value, const Cents &c) ...` can be implemented by calling the already implemented *operator+(Cents, int)*: `... { return c + value; }`. This should be done to reduce code, so if the implementation is trivial (e.g. one line of code), then it's probably not worth it

## Operator overloading via normal function
- If we don't need access to private members, we can use normal functions instead of friend functions. The usage is almost identical, but we work with private variables via access functions, and we need to forward declare them in headers outside of the class: `class Cents{ ... }; Cents operator+(const Cents &c1, const Cents &c2);`
- **Rule**: Prefer overloading operators as normal functions instead of friends if it’s possible to do so without adding additional functions. (e.g. don't add additional access functions just to overload an operator as a normal function)

## Overloading io operators
- To overload `<<` operator for output:

`std::ostream& operator<<(std::ostream &out, const Cents &c) { out << "Cents(" << c.m_cents << ')'; return out; }`

Now we can `std::cout << Cents{ 5 } << '\n';`
- To overload `>>` operator for input:
 
`std::istream& operator>>(std::istream &in, Cents &c) { in >> c.m_cents; return in; }`

Now we can `Cents cents{}; std::cin >> cents;`

## Operator overloading via member function
- When overloading using a member function:
    - The overloaded operator must be added as member function of the left operand
    - The left operand becomes the implicit `*this` object
    - All other operands become function parameters
- See `conspect/src/overloading-operators/using-member-function.cpp`
- **Rules of thumb** for which type of function to use:
    - If overloading assignment (`=`), subscript (`[]`), function call (`()`), or member selection (`->`), do so as a *member function* (the language requires so)
    - If overloading unary operator, use *member function*
    - If overloading binary operator that does not modify its left operand (e.g. `operator+`), use *normal* (preferred) or *friend function*
    - If overloading binary operator that modifies its left operand, but you can’t modify the definition of the left operand (e.g. `operator<<`, which has a left operand of type `ostream`), use *normal* (preferred) or *friend function*
    - If overloading binary operator that modifies its left operand (e.g. `operator+=`), and you can modify the definition of the left operand, use *member function*

## Overloading unary operators
- Typically overloaded using member functions:

`Cents Cents::operator-() const { return Cents(-m_cents); }` - because the original Cents is not modified, we make this const, so it could be called on const Cents objects too
- Overload unary `!` to see if point is set at the origin:

`bool Point::operator!() const { return (m_x == 0.0 && m_y == 0.0); }`
- If we overloading unary `+`, we can just do

`Cents Cents::operator+() const { return *this; }`, because we are returning the exact copy of the object

## Overloading comparison operators
- Because comparison operators are binary operators that don't modify their left operand, use normal/friend functions:

`bool operator== (const Car &c1, const Car &c2) { return c1.m_model == c2.m_model && c1.m_make == c2.m_make; }`

`bool operator!= (const Car &c1, const Car &c2) { return !(c1 == c2); }`
- **Recommendation**: Don’t define overloaded operators that don’t make sense for your class (e.g. for class Car, operators `<` or `>` wouldn't make sense)
- There is an exception to the above recommendation - we might want to overload the comparison operators for comparing when sorting purposes (e.g. Car could be sorted based on make and model alphabetically). Some of the container classes in the standard library (classes that hold sets of other classes) require an overloaded `operator<` so they can keep the elements sorted
- Because `operator>` is the logical oposite of `operator<=` (the same is true for `operator<` and `operator>=`), we can use one to define the other

## Overloading increment and decrement operators
- Unary ops => overload as members
- To distinguish between prefix incr/decr and postfix incr/decr, we use the **dummy variable** (or **dummy argument**) for the postfix ones:

`Digit& operator++(); // prefix`

`Digit operator++(int); // postfix`
- For implementation, see `conspect/src/overloading-operators/overloading-increment-decrement.cpp`. Notes:
    - Because the dummy parameter isn't used in implementation, we haven't given it a name. This tells the compiler to treat this variable as a placeholder, which means it won't warn us that we declared a var that is never used
    - The prefix and postfix operators do the same job. The difference is that prefix ops return the object after it has been incremented/decremented (so we do the operation and return `*this`). For postfix, we need to return the state of the object before the incr/decr. So we create *temp* variable, then do operation on the original object, and then return *temp* by value. That's why the prefix operator is usually preferred - because postfix has the overhead of creating temporary variable and returning by value
    - Post-incr/decr definitions use pre-incr/decr to avoid duplicate code

## Overloading subscript operator
- Must be overloaded as member
- Will take one parameter - the subscript that user places between the hard braces `[..]`
- E.g. for `class IntList`, which has an int array inside:

`int& IntList::operator[] (int index) { return m_list[index]; }`
- We're returning reference, because we might need to use the result on the left side of expression (e.g. `intList[4] = 5;`), so we need to return an l-value
- We can set default value for overloaded `operator[]`, but there is no point, because using `[]` without a subscript inside is not a valid syntax
- For const `IntList` objects, we can define a const version of `operator[]` separately:

`const int& IntList::operator[] (int index) const { return m_list[index]; }`
- We can do the error checking in overloaded `operator[]`:

`int& IntList::operator[] (int index) { assert(index >= 0 && index < 10); return m_list[index]; }` (assuming m_list has a fixed length of 10)
- Pointers to objects and overloaded `operator[]` don't mix: `IntList *intList{ new IntList{} }; list[2] = 3; delete list;` - error: this will assume we're accessing index 2 of an array of IntLists
- The proper syntax for the above would be to dereference the pointer first: `(*list)[2] = 3;` (though still don't set pointers to objects if there is no need)
- The parameter doesn't have to be `int` - we can use `std::string&`, for example. It would be useful if we're writing classes that use words as indices. Also, some (bad) example to use `operator[]` for printing:

`void Stupid::operator[] (const std::string& index) { std::cout << index; }`

`Stupid stupid{}; stupid["Hello, cocksuckers!"]`
- I wondered how to overload double subscript operator `[][]`: [The accepted answer and Bo Perrson's one](https://stackoverflow.com/questions/6969881/operator-overload)

## Overloading parenthesis operator
- Must be overloaded as member
- Can have any number of parameters
- `Operator()` is sometimes overloaded with two params to index multidimensional arrays, or to retrieve a subset of one-dimensional array. E.g., we can implement taking element of a matrix:

`double& Matrix::operator()(int row, int col) { return m_data[row][col]; }` - we couldn't do this with `operator[]` because it can only take one index. Use it: `matrix(1, 2) = 4.5;`
- It may be tempting to use `operator()` for many different purposes, but it's strongly discouraged because the *()* symbol doesn't give any indication of what the operator is doing.
- `Operator()` is also commonly overloaded to implement **functors** (or **function objects**), which are classes that operate like functions. The advantage of a functor over normal functions is that functors can store data in member variables. E.g.: see `conspect/src/overloading-operators/functors.cpp`

## Overloading typecasts
- **User-defined conversions** allow us to convert our class into another data type
- Providing user-defined conversion for `Cents` by overloading the int typecast:

`operator int() const { return m_cents; }` (public member function)
- User-defined conversions do not take parameters, as there is no way to pass arguments to them
- User-defined conversions do not have return type
- Now if we have some function that takes int parameter: `void printInt(int value) { std::cout << value; }`, we can call `printInt(cents);` and cents will be implicitly converted to int by calling our overloaded operator function (or we can just do `std::cout << cents;` instead of *printInt* and it'll work). We can also now explicitly cast Cents: `Cents cents{ 7 }; int c{ static_cast<int>(cents) };`
- We can provide user-defined conversions for user-defined data types. E.g., in `class Dollar`:

`operator Cents() const { return Cents(m_dollars * 100); } // Allow us to convert Dollars into Cents`

## Copy constructor
- **Copy constructor** is a special type of constructor used to create a new object as a copy of an existing object. Like default constructor, if we don't provide copy constructor for class, C++ will create a public copy constructor for us
- By default, the created copy constructor utlizes memberwise initialization. **Memberwise initialization** means that each member of the copy is initialized directly from the member of the class being copied
- We can provide out own copy constructor (e.g. for Fraction):

`Fraction(const Fraction &fr): m_numerator(fr.m_numerator), m_denominator(fr.m_denominator) { /* no need to check for a denominator of 0, as fr must already be a valid Fraction */ }`

Then we use can use, for example, direct initialization with copy constructor:

`Fraction fiveThirds(5, 3); Fraction fCopy(fiveThirds);`
- It's fine to use default copy constructor if it meets our needs
- **Note**: Member functions of a class can access the private members of parameters of the same class type (example - the above copy constructor)
- **Elision** - case, when the compiler is allowed to opt out of calling the copy constructor and just do a direct initialization. E.g.: `Fraction fiveThirds(Fraction(5, 3));` This takes two steps - 1. create anonymous object, 2. call the copy constructor. The compiler may (or may not) simply do `Fraction fiveThirds(5, 3);`, which only requires one constructor call (to `Fraction(int, int)`).

Note: Since C++17, some cases of copy elision (including the example above) have been made mandatory.
- We can prevent making copies of our class by making the copy constructor private. Then, any initialization that would use the copy constructor will cause a compile error, even if the copy constructor is elided

## Copy initialization
- For classes, `Fraction six = Fraction(6);` is evaluated the same way as `Fraction six(Fraction(6));`. So copy constructor may (from C++17 - will) be elided. **Rule**: *Avoid using copy initialization, use uniform initialization instead.*
- Copy initialization is used in a few other places. One of them - when passing or returning a class by value. Usually, the copy constructor can not be elided in these cases.

It may be elided in such situation, even though `s` is returned by value:

`class Something{}; Something foo() { Something s; return s; }`

then `Something s = foo();`

## Converting constructors, explicit, delete
- By default, C++ will treat any constructor as an implicit conversion operator. E.g. we have `Fraction(int num = 0, int denom = 1): m_num(num), m_denom(denom) { assert(denom != 0) }` constructor and `void printFraction(const Fraction &f) { std::cout << f; }` function (not Fraction member). We call `printFraction(6);`, compiler will implicitly conver literal 6 to Fraction object when initializing parameter `f` using the `Fraction(int, int)` constructor. This implicit conversion works for all kinds of initialization (direct, uniform, copy)
- Constructors eligible to be used for implicit conversions are called **converting constructors**. Prior to C++11 only constructors with one parameter could be converting. With new uniform initialization in C++11, all constructors can be
- Unlike the Fraction case, implicit conversion may be undesirable or lead to unexpected behaviour. See `conspect/src/overloading-operators/undesirable-implicit-conversion.cpp`
- For the example in file, there are several ways to address the issue:
    1. Make constructors (and conversion functions) *explicit* via `explicit` keyword. Constructors and conversion functions made explicit will not be used for *implicit* conversions or copy initialization:
    
        `explicit MyString(int x) { m_string.resize(x); }`
        
        Note, that this only prevents *implicit* conversions. Explicit conversions (via casting) are still allowed: `std::cout << static_cast<MyString>(5);`

        Direct and uniform initialization will also still convert parameters to match (uniform initialization won't do narrowing conversions, but will do other types of conversions): `MyString str{ 'x' };` is allowed

    2. We can partially disallow `'x'` from being converted to `MyString` (both implicit and explicit) by adding `MyString(char)` constructor and making it private: `MyString(char){}`. However, this constructor can still be used inside the class.
    3. We can completely disallow this conversion by using the `delete` keyword (from C++11) to delete a function: `public: ... MyString(char) = delete;`. Now any use of this constructor is a compile error. Copy constructor and overloaded operators may also be deleted

## Overloading assignment operator
- **Assignment operator** (`operator=`) is used to copy values from one object to another *already existing object*
- Copy constructor initializes new objects, whereas assignment operator  replaces the contents of existing objects. Their usage:
    - If new object has to be created before the copying can occur, the copy constructor is used (note: this includes passing or returning objects by value)
    - If new object does not have to be created before the copying can occur, the assignment operator is used
- Must be overloaded as member
- Simple implementation:

`Fraction& Fraction::operator= (const Fraction &fr) { m_num = fr.m_num; m_denom = fr.m_denom; return *this; /* for chaining assignment */ }`
- Issues can occur due to self assignment (`Fraction f1(5, 3); f1 = f1;`). In the above form, it is safe (and useless). It can be dangerous though, if an assignment operator needs to dynamically assign memory. See `conspect/src/overloading-operators/dangerous-assignment-overloading.cpp`
- The problem of example in a file can be solved by doing a *self-assignment check*. Before anything else in `MyString::operator=`, we could write: 

`if (this == &str) { return *this; }` We are checking if the address of our implicit object is the same as the address of the object being passed. Because this is just address comparison, it should be fast and doesn't need `operator==` to be overloaded
- When not to handle self-assignment:
    1. No need to check for self-assignment in a copy constructor, because it is only called when new objects are being constructed
    2. The check may be omitted in classes that can naturally handle self-assignment (like the `Fraction` example above). Though we still might include the self-assignment guard just so the function doesn't do the unnecessary work
- Unlike other operators, compiler will provide a default public assignment operator if you don't provide one. It does memberwise assignment (like default copy constructor)
- Like other ops and constructors, we can prevent assignments from being made by making assignment operator private or by using `delete` keyword

## Shallow vs deep copying
- Memberwise copy is also known as **shallow copy**. It means that C++ copies each member of the class individually (using the assignment op for overloaded operator=, and direct initialization for the copy constructor). This works well when classes are simple (e.g. do not contain dynamically allocated memory)
- If class has dynamically allocated memory, shallow copy can lead to problems. See `conspect/src/overloading-operators/shallow-copy-problems.cpp`
- One answer to above problem is to do deep copy on any non-null pointers being copied. **Deep copy** allocates memory for the copy and then copies the actual value, so that the copy lives in distinct memory from the source. Example: `conspect/src/overloading-operators/deep-copy.cpp`
- Differences of assignment operator comparing to copy constructor for deep copy:
    - A self-assignment check
    - Returning `*this` so we can chain assignment operator
    - We need to explicitly dealocate any value that the string is already holding to avoid memory leaks
- The better solution is to use standard library classes, such as std::string and std::vector, because they hangle all of their memory management, and have overloaded copy constructors and assignment ops with proper deep copying

# Object relations
## Object Composition
- **Object composition** - process of building complex objects from simpler ones. "*Has-a*" type relationship (A car "has-a" steering wheel. I "have-a" heart). The complex object is sometimes called the *whole* (or *parent*). The simpler object is called the *part*, *child*, or *component*
- Structs and classes are sometimes referred to as **composite types**, because when we build them with data members, we're constructing a complex object from simpler parts (object composition)
- Two subtypes of object composition: *composition* and *aggregation*

### Composition
- To qualify as **composition**, an object and part must have the following relationship:
    - The part (member) is part of the object (class)
    - The part can only belong to one object at a time
    - The part has its existence managed by the object
    - The part doesn't know about the existence of the object
- Example: person's body and a heart:
    1. Heart is part of the body
    2. Heart can only be in one body at a time. *Note*: composition has nothing to say about the transferability of parts. We can transplant heart from one body to another, and after that it still meets composition requirements
    3. When person's body is created, heart is created. When it dies, heart dies with it (composition is sometimes called "*death relationship*")
    4. Heart operates unaware that it is part of a body (**unidirectional** relationship - body knows about heart, but not the other way around)
- Composition models "*part-of*" relationships (heart is part-of body, numerator is part-of fraction). Is often used to model physical relationships, where one object is physically contained inside another
- The parts can be singular of multiplicative (could be modeled as array)
- Typically implemented as structs or classes with normal data members. If composition needs to do dynamic alloc/dealloc, it may be implemented using pointer data members. The class should be responsible for doing memory management itself (not the user of the class)
- If you *can* design a class using composition, you *should*
- Composition example of creature class that uses a point class to hold the creature's location: see `conspect/src/object-relations/composition`
- Although most compositions directly create their parts when the composition is created and directly destroy them when composition is destroyed, there are some variations of composition that bend these rules a bit:
    - A composition may defer creation of some parts until they are needed (e.g. string class may not create a dynamic array of chars until user assigns the string some data to hold)
    - A composition may opt to use a part that has been given to it as input rather than create the part itself
    - A composition may delegate destruction of its parts to some other object (e.g. to garbage collection routine)

The key point is that composition should manage its parts without the user of the composition need to manage anything.
- Using a subclass instead of implementing a feature directly into composition (like `Point2D` in example from src) has a number of benefits:
    1. Each individual class can be kept relatively simple and straightforward, focused on performing one task well. Makes those easier to write and understand (Point2D only worries about point-related stuff)
    2. Each subclass can be self-contained, which makes them reusable  (Point2D can be used multiple times in `Creature`, or in completely different class)
    3. The parent class can have subclasses do the hard work, and instead focus on coordinating the data flow between the subclasses. Lowers the overall complexity of the parent object, because it can delegate tasks to children, who already know how to do those tasks (when we move Creature, it delegates the task to Point2D, which already understands how to set a point. Thus, Creature doesn't have to worry about how such things whould be implemented)

A good rule of thumb is that each class should be built to accomplish a single task. The task should either be the storage and manipulation of data (Point2D, std::string), OR the coordination of subclasses (Creature). Ideally not both. Creature's job is to worry about how to coordinate the data flow and ensure that each of the subclasses knows *what* it is supposed to do. It's up to the individual subclasses to worry about *how* they will do it.

### Aggregation
- To qualift as **aggregation**, a whole object and its parts must have the following relationship:
    - The part (member) is part of the object (class)
    - The part can belong to more than one object at a time
    - The part does not have its existence managed by the object
    - The part does not know about the existence of the object
- Example of aggregate relationship: relationship between a person and their home address. Person has an address, however, that address can belong to more than one person at a time (e.g. for your family members). The address isn't managed by the person - it existed before the person got there, and will exist after person is gone. Also, person knows their address, addresses don't know what people live there.
- Another example: a car engine is part of the car. Though it belongs to the car, it can belong to other things (for example, person owning the car). The car is not responsible for creation or destruction of the engine. The car knows it has an engine, the engine doesn't know it's part of the car
- Aggregation models "*has-a*" relationships (department has teachers, car has an engine)
- Parts can be singular of multiplicative
- Implemented similar to composition: we add parts as member variables, but they are typically either references or pointers that are used to point at objects that have been created outside of the class scope. Consequently, aggregation usually either takes the objects it is going to point to as constructor parameters, or it begins empty and the subobjects are added later via access functions or operators. When the class is destroyed, the pointer or reference member variables will be destroyed, but not deleted - the parts themselves will still exist.
- Example of aggregation: see `conspect/src/object-relations/aggregation.cpp`. It hase a couple simplifications: the department will only hold one teacher; the teacher will be unaware of what department they're part of. Though it may seem silly that `Teacher` doesn't know what `Department` they're working for, it's fine in the context of a given program
- **Rule**: Implement the simplest relationship type that meets the needs of your program, not what seems right in real-life.
- For example, if writing car body shop simulator, we may want to implement a car and engine as an aggregation. However, if writing a racing simulation, we may want to implement a car and engine as a composition, since the engine will never exist outside of the car in that context.
- The concepts of composition and aggregation are not mutually exclusive and can be mixed within the same class. We can write a class responsible for destroying some parts, but not the other. For out Teacher-Department example, we could add a Department name, which would utilize composition, but Teacher would still be added by aggregation, and created/destroyed separately.
- Aggregations are useful, but more dangerous, because they don't handle deallocation of their parts. For this reason, compositions should be preferred over aggregations.
- Historically, unlike composition, definitions of aggregation may differ.
- *Note*: Don't confuse aggregation with aggregates (such as structs or classes)
- Summing up:
    - Composition:
        - Typically use normal member variables
        - Can use pointer members if the class handles object allocation/deallocation itself
        - Responsible for creation/destruction of parts
    - Aggregation:
        - Typically use pointer or reference members that point to or reference objects that live outside the scope of the aggregate class
        - Not responsible for creating/destroying parts

### std::reference_wrapper
- In the above Teacher/Department example, if we wanted a list of Teacher references, it would be illegal, because refs have to be initialized and cannot be reassigned. E.g.:

`std::vector<const Teacher&> m_teachers{}; // Illegal`

Instead of refs, we could use pointers, but that would open the possibility to store or pass null pointers. To solve this, there is `std::reference_wrapper`
- `std::reference_wrapper` is a class that acts like a reference, but also allows assignment and copying, so it’s compatible with lists like `std::vector`
    1. Lives in `<functional>` header
    2. When creating object wrapped by `std::reference_wrapper`, it can't be anonymous object (because then reference would be left dangling)
    3. If we want to get object back from `std::reference_wrapper`, we use `get()` member function
- Example usage: see `conspect/src/reference-wrapper.cpp`

## Association
- Weaker type of object relationship than composition or association
- To qualify as an **association**, object must have the following relationship:
    - The associated object (member) is otherwise unrelated to the object (class)
    - The associated object (member) can belong to more than one object (class) at a time
    - The associated object (member) does not have its existence managed by the object (class)
    - The associated object (member) may or may not know about the existence of the object (class) - the relationship can bi uni- or bidirectional
- Association models as "*uses-a*" relationship (the doctor "uses" the patient (to earn income). The patient uses doctor (for health purposes))
- Can be implemented in different ways, most often - using pointers, where the object points at the associated object. See `conspect/src/object-relations/association.cpp`
- In general, we should avoid bidirectional associations if a unidirectional one will do.
- **Reflexive association** - when objects have a relationship with other objects of the same type. E.g.: a university course and its prerequisites. The simplified case when Course can have only one prerequisite:

`class Course {`

`private: std::string m_name; const Course *m_prerequisite;`

`public: `

`Course(const std::string &name, const Course *prerequisite = nullptr): m_name{ name }, m_prerequisite{ prerequisite } {}` 

`};`

This can lead to a chain of associations (where Course's prerequisite also needs a prerequisite etc)
- Associations can be indirect - instead of using pointers or references to directly link objects together, we could, for example, use ids. E.g.: see `conspect/src/object-relations/indirect-association.cpp`

## Summary table for object composition and association
- See `conspect/text/object-relations/object-relations-table.md`

## Dependencies
- **Dependency** occurs when one object invokes another object's functionality in order to accomplish some specific task (e.g. flowers are dependent upon bees to pollinate them, in order to grow fruit; person who broke their foot is dependent upon crutches to get around (but not otherwise))
- Weaker relationship than association, but still, change to object being depended upon may break functionality in the dependent caller
- Unidirectional relationship
- Example of dependency: class that uses `std::cout` uses it for printing something to console, but not otherwise. E.g. `class Average` from `tests/overloading-operators/quiz/Average.h` isn't directly related to `std::cout`, but it has dependency on *std::cout* since `operator<<` uses *std::cout* to print the Average to console

### Dependencies vs Association
- Associations are a relationship between two classes at the class level - one class keeps a direct or indirect "link" to the associated class as a member. So, for example, we can always ask the Doctor who his Patients are
- Dependencies typically are not represented at the class level - the object being depended on is not linked as a member. Rather, the object being depended on is typically instantiated as needed (opening a file to write data to), or passed into a function as a parameter (like *std::ostream* for *operator<<*)

# Container classes
- **Container class** is a class designed to hold and organize multiple instances of another type (either another class, or fundamental type)
- Most well-defined containers will include (though some might omit) functions that:
    - Create an empty container (via a constructor)
    - Insert a new object into the container
    - Remove an object from the container
    - Report the number of objects currently in the container
    - Empty the container of all objects
    - Provide access to the stored objects
    - Sort the elements (optional)
- Container classes implement a "*member-of*" relationship (e.g. elements of an array are members-of (belong to) the array) - not the C++ class member sense, but conventional sense
- Two varieties of containers:
    - **Value containers** are compositions that store copies of the objects that they are holding (and thus are responsible for creating and destroying those copies)
    - **Reference containers** are aggregations that store pointers or references to other objects (and thus are not responsible for creation or destruction of those objects)
- One container can hold one type of data, unless we use templates
- E.g. of writing an integer array container class, similar to `std::vector<int>`, from scratch: see `conspect/src/container-classes/IntArray.h`. It's going to be a *value container*

## std::initializer_list
- Is used for providing ability to initialize objects using initializer list syntax (e.g., like arrays: `int array[] { 5, 4, 3, 2, 1 };`)
- Lives in `<initializer_list>` header
- We need to specify the type for it to hold in angled brackets (e.g., `<int>`)
- Has a (misnamed) size() function which returns the number of elements in the list
- Updating `IntArray` from previous example with `std::initializer_list`: see `conspect/src/container-classes/initializer-list-int-array.cpp`
- Much like `std::string_view`, it is very lightweight, so we pass the list by value instead of const reference (as seen in example)
- Initializer lists will always favor a matching initializer_list constructor over other potentially matching constructors. Thus, the definition `IntArray array { 5 };` would match to `IntArray(std::initializer_list<int>)`, not `IntArray(int)`. So if we want to match `IntArray(int)` (when list constructor has been defined), we need to use copy or direct initialization. Example for `std::vector`:

`std::vector<int> array(5); // Calls std::vector::vector(std::vector::size_type), initializes to [0 0 0 0 0]`

`std::vector<int> array{ 5 }; // Calls std::vector::vector(std::initializer_list<int>), initializes to [5]`

- We can also use `std::initializer_list` to assign new values by overloading the assignment operator to take `std::initializer_list` parameter. Note that if implementing a constructor that takes a `std::initializer_list`, we should ensure we do at least one of the following:
    1. Provide an overloaded list assignment operator
    2. Provide a proper deep-copying copy assignment operator

For reasoning, see `conspect/text/container-classes/list-constructor-important-nuances.md`
- **Rule**: If you provide list construction, it’s a good idea to provide list assignment as well.

# Inheritance
- Models "*is-a*" relationship between two objects
- **Hierarchy** is a diagram that shows how various objects are related
- Class being inherited from - **parent class**, **base class**, or **superclass**
- Class doing the inheriting - **child class**, **derived class**, or **subclass**
- A child class inherits both behaviors (member functions) and properties (member variables) from the parent (subject to some access restrictions). These variables and functions become members of the derived class
- To have one class inherit the other: `class Employee : public Person { ... };` - public inheritance
- We can chain inheritance: `class Supervisor : public Employee { ... };`
- C++ constructs derived classes in phases, starting with the most-base class (e.g. `Person`) and finishing with the most-child class (e.g. `Supervisor`) - that's all if we are creating a `Supervisor` object
- Considering we have two classes: `Base` and `Derived` (which inherits from `Base`). We can consider `Derived` as a two part class: one part Derived, one part Base
- What happens when `Derived` is instantiated (`Derived derived{ 1.3 };`):
    1. Memory for derived is set aside (enough for both the Base and Derived portions)
    2. The appropriate Derived constructor is called
    3. The Base object is constructed first using the appropriate Base constructor. If no base constructor is specified, the default constructor will be used.
    4. The initialization list initializes variables
    5. The body of the constructor executes
    6. Control is returned to the caller
- You can't initialize inherited member vars in initialization list of a constructor. It works like that to restrict potential initialization of const and ref vars of base class in derived class (their value must be set when they are created - in the base class)
- We can choose which `Base` class constructor will be called from the `Derived` class:

`Derived(double cost = 0.0, int id = 0): Base{ id }, m_cost{ cost } {}` - call `Base(int)` constructor with value *id*

Now if we call `Derived derived{ 1.3, 5 };`, the following will happen:
1. Memory for derived is allocated.
2. The Derived(double, int) constructor is called, where cost = 1.3, and id = 5
3. The compiler looks to see if we’ve asked for a particular Base class constructor. We have! So it calls Base(int) with id = 5.
4. The base class constructor initialization list sets m_id to 5
5. The base class constructor body executes, which does nothing
6. The base class constructor returns
7. The derived class constructor initialization list sets m_cost to 1.3
8. The derived class constructor body executes, which does nothing
9. The derived class constructor returns
- Destructors are called in *reverse* order of construction

## Inheritance and access specifiers
- **Private** members: can be accessed by members of the same class or friends
- **Protected** members: can be accessed by members of the same class, friends and derived classes
- **Public** members: can be accessed by anybody
- When to use `protected`: when I am going to be the one deriving from my own classes, and the number of derived classes is reasonable. That way, if I make a change to the implementation of the base class, the updated to the derived classes can be made by myself and quickly
- We can inherit from classes in three ways:
    1. Publicly - `class Pub: public Base`
    2. Protectedly - `class Pro: protected Base`
    3. Privately - `class Pri: private Base` or `class Def: Base` (defaults to private)
- When members are inherited, the access specifier for an inherited member may be changed (in the derived class only) depending on the type of inheritance used (members that were `public` or `protected` in base class may change access specifiers in derived class)
- See inheritance access table: `conspect/text/inheritance/inheritance-access-table.md`. Keep in mind the following rules:
    - A class can always access its own (non-inherited) members
    - The public accesses the members of a class based on the access specifiers of the class it is accessing
    - A derived class accesses inherited members based on the access specifier inherited from the parent class. This varies depending on the access specifier and type of inheritance used
- Public inheritance is the most commonly used
- Private inheritance can be useful when the derived class has no obvious relationship to the base class, but uses the base class for implementation internally. In such case, we probably don't want the public interface of the base class to be exposed through objects of the derived class
- Example of how access specifiers work in inheritance: see `conspect/src/inheritance/access-specifiers.cpp`

## New functionality in derived classes
- When member function is called with a derived class object, compiler first looks to see if that member exists in the derived class. If not - it walks up the inheritance chain to the base class. It uses the first one it finds
- We can redefine the function in derived classes. We can also change the access specifier when redefining (e.g. in `Base` function is `private`, but in `Derived` we can make it `public`)
- We can use the base function (from `class Base`) in the redefined one: (in `class Derived`)

`void identify() { Base::identify(); std::cout << "I am Derived"; }`
- If we want to use the base friend functions, we need to use `static_cast`. E.g.:

`friend std::ostream& operator<< (std::ostream &out, const Derived &d) { out << "In Derived"; out << static_cast<Base>(d); return out; }`
- We can just change the access specifier of base member in derived class (without redefining). This won't work though if the base class member is `private`. This is done through *using declaration*:

`class Base { protected: void printValue() { ... } };`

`class Derived : public Base { public: using Base::printValue; };`
- We can hide the functionality of Base class in Derived by:
    1. Making something `public` from Base `private` in Derived:

        `class Base { public: int m_value; };`

        `class Derived { private: using Base::m_value; };`
    2. Marking member functions as deleted in the derived class:

        `class Base { public: int getValue() { return m_value } };`
        
        `class Derived { public: int getValue() = delete; }`

        *Note*: Derived object can still access the Base version of *getValue()* by upcasting to a Base first:

        `std::cout << static_cast<Base>(derived).getValue();`

## Multiple inheritance
- **Multiple inheritance** enables a derived class to inherit members from more than one parent. E.g.:

`class Teacher: public Person, public Employee { ... };`
- Problems with multiple inheritance:
    1. Multiple base classes can contain a function with the same name, which result in ambiguity. E.g.: `class USBDevice` and `class NetworkDevice` both have `getId()` function. `class WirelessAdapter` derives from both of them. If we create a WirelessAdapter object and try to call *getId()*, it will result in compile error:

        `WirelessAdapter c54G(123, 456); std::cout << c54G.getId();`

        We can work around this by specifying the version we want to call:

        `std::cout << c54G.USBDevice::getId();`

        But it still leads to complex code.
    2. The diamond problem. It's when a class multiply inherits from two classes which each inherit from a single base class. E.g.:

        `class PoweredDevice {};`

        `class Scanner: public PoweredDevice {};`

        `class Printer: public PoweredDevice {};`
        
        `class Copier: public Scanner, public Printer {};`

        Many issues with this, like whether `Copier` should have one or two copies of `PoweredDevice`, and how to resolve certain types of ambigous references. While most of these issues can be addressed through explicit scoping, the maintenance overhead is huge.
- **Rule**: Avoid multiple inheritance unless alternatives lead to more complexity.

# Virtual functions
## Pointers and references to the base class of derived objects
- Since `Derived` has a `Base` part in it, we can set a `Base` pointer or reference to a `Derived` object:

`Derived derived{ 5 }; Base &rBase{ derived }; Base *pBase{ &derived };`

- However, because *rBase* and *pBase* can obly see members of Base (or any classes that Base inherited). So even though `Derived::printName() { std::cout << "derived"; }` may shadow (hide) `Base::printName() { std::cout << "base"; }`, if we call *printName()* on *rBase* or *pBase*, `Base::printName()` will be called, printing out "base".

## Virtual functions
- **Virtual function** is a special type of function that, when called, resolves to the most-derived version of the function that exists between the base and derived class. This capability is known as **polymorphism**.
- A derived function is considered a match if it has the same signature (name, parameter types, and whether it is const) and return type as the base version of the function. Such functions are called **overrides**.
- To make a function *virtual*, we use `virtual` keyword:

`virtual std::string_view getName() const { return "Base"; }`

`virtual std::string_view getName() const { return "Derived"; }`

Now if we call `rBase.getName()` or `pBase->getName()`, they will return "Derived".
- If a function is marked as virtual, all matching overrides are also considered virtual, even if they are not explicitly marked as such. But it's a good idea to use the virtual keyword for them still - just as a reminder that they are virtualized. One example: see `conspect/src/virtual-functions/virtualized-derived-functions.cpp`
- We shouldn't call virtual functions from constructors or destructors because of the order in which inherited/inheriting classes are created/destroyed.
- Downsides:
    - Virtual functions are inefficient - resolving a virtual function call takes longer than resolving a regular one.
    - The compiler has to allocate an extra pointer for each class object that has one or more virtual functions

## The override and final specifiers, and covariant return types
- For cases when function was meant to be an override, but isn't (example 1 below), C++11 introduces `override` specifier (not keyword) (example 2 below):

Example 1:

`class A { public: virtual const char* getName1(int x) { return "A"; } };`

`class B : public A { public: virtual const char* getName1(int x) const { return "B"; } };` - isn't an override because the constness is different

Example 2 (in class B):

`virtual const char* getName1(int x) const override { return "B"; }` - compile error, function is not an override

`virtual const char* getName3(int x) override { return "B"; }` - okay, function is an override of `A::getName1(int)`

If the function does not override a base class function (or is applied to a non-virtual function), the compiler will flag the function as an error. This is useful in complex programs, where such things as mismatched virtual functions are difficult to debug.
- There is no performance penalty for using the *override* specifier
- **Rule**: Apply the override specifier to every intended override function I write
- If we want to restrict user from overriding a function, or inherit from a class, we can use `final` specifier (not keyword). If the user tries to override a function or inherit from a class that has been specified as final - compile error. Example:

`class A { public: virtual const char* getName() { return "A"; } };`

`class B : public A { public: virtual const char* getName() override final { return "B"; } };`

`class C : public B { public: virtual const char* getName() override { return "C"; } };` - compile error; overrides `B:getName()`, which is *final*

- In case where we want to prevent inheriting from a class:

`class A { ... };`

`class B final : public A { ... };`

`class C : public B { ... };` - compile error, cannot inherit from final class
- Special case when a derived class virtual function can have a different return type than the base class and still be an override: If the return type of a virtual functions is a pointer or a reference to a class, override functions can return a pointer or a reference to a derived class. These are called **covariant return types**. Example:

`virtual Base* getThis() { return this; }` (in class `Base`)

`Derived* getThis() override { return this; }` (in class `Derived`) - overrides the Base's `getThis()`

`int main() { Derived d{}; Base *b{ &d }; d.getThis();` - returns a `Derived*`

`b->getThis();` - returns a `Base*`

` return 0; }`

One interesting note about covariant return types: C++ can’t dynamically select types, so you’ll always get the type that matches the base version of the function being called. In other words, in the above example, you only get a Derived* if you call getThis() with an object that is typed as a Derived object in the first place.
- Some older compilers (e.g. Visual Studio 6) do not support covariant return types

## Virtual destructors, virtual assignment, and overriding virtualization
- **Rule**: If providing own destructor, we should **always** make it virtual if dealing with inheritance. E.g. our derived class has some memory allocation, and it gets deallocated in destructor.

`Derived *derived{ new Derived(5) }; Base *base{ derived }; delete base;` - if destructor isn't virtual, only Base destructor will be called, thus some memory inside `base` object won't be deallocated. (full example: see `conspect/src/virtual-functions/virtual-destructor.cpp`)
- It is possible to make the assignment operator virtual. However, virtualizing the ass op opens up some advanced stuff - so maybe should read up on this later, if needed.
- We can ignore virtualization using scope resolution operator:

`Derived derived; const Base &base{ derived }; std::cout << base.Base::getName();`
- Recommendations about virtual destructors and inheritance:
    - If you intend your class to be inherited from, make sure your destructor is virtual.
    - If you do not intend your class to be inherited from, mark your class as final. This will prevent other classes from inheriting from it in the first place, without imposing any other use restrictions on the class itself.

(more detailed on the above recommendations: see `conspect/text/virtual-functions/making-destructors-virtual.md`)

## Early and late binding
- **Binding** refers to the process that is used to convert identifiers (such as variable and function names) into addresses
- **Early binding** (or *static binding*) means the compiler (or linker) is able to directly associate the identifier name (function or variable name) with a machine address. Direct function calls are resolved as early binding. When compiler/linker encounters a function call, it replaces it with machine language instruction that tells CPU to jump to that function's address
- **Late binding** (or *dynamic binding*) is when it's not possible to know which function will be called until runtime (e.g., function pointers, which then are called via indirect function calls)
- Late binding is slightly less efficient, because the program has to read the address held in pointer first and then jump to that address, but also more flexible

### The virtual table
- **Virtual table** (*vtable*) is a lookup table of functions used to resolve function calls in a dynamic/late binding manner
- [Full explanation](https://www.learncpp.com/cpp-tutorial/the-virtual-table/) on how virtual functions are implemented
- Performance costs:
    - Any class that uses virtual functions has a `*__vptr`, and thus each object of that class will be bigger by one pointer
    - For virtual functions, we have to do 3 operations to find the function to call, as opposed to 2 operations for a normal indirect function call, or one operation for a direct function call

## Pure virtual functions, abstract base classes, interface classes
- **Pure virtual function** (or **abstract function**) - has no body at all, acts as placeholder that is meant to be redefined by derived classes. Example:

`class Base { public: virtual int getValue() const = 0; };`
- Consequences of using pure virtual function:
    - Any class with one or more pure virtual functions becomes an **abstract base class**, which means that it can not be instantiated
    - Any derived class must define a body for this function, or that derived class will be considered an abstract base class as well
- For example, see `conspect/src/virtual-functions/pure-virtual-functions.cpp`
- Pure virtual function can have a body:

`class Animal { public: virtual const char* speak() const = 0; };`

`const char* Animal::speak() const { return "buzz"; }`

The function is still pure virtual, even though it has a body. This can be useful if the derived class is fine with default implementation, so we can override the function by simply calling the base class implementation directly:

`class Dragonfly : public Animal { public: const char* speak() const override { return Animal::speak(); } };`
- **Interface class** is a class that has no member variables, and where all of the functions are pure virtual. Useful when we want to define the functionality that derived classes must implement, but leave the implementation details entirely up to derived class.
- Are often named beginning with an I: `class IErrorLog`. See full example: `conspect/src/virtual-functions/interfaces.cpp`
- Abstract classes still have virtual tables. The virtual table entry for a pure virtual function will generally either contain a null pointer, or point to a generic function that prints an error (sometimes this function is named `__purecall`) if no override is provided.

## Virtual base classes
- If we have a diamond problem (see `conspect/images/diamond-problem.gif`):

        class PoweredDevice{};
        class Scanner: public PoweredDevice {};
        class Printer: public PoweredDevice {};
        class Copier: public Scanner, public Printer {};

    We end up with two copies of the PoweredDevice class - one from `Printer`, one from `Scanner` (structure: see `conspect/images/diamond-problem-structure.gif`). While this is often desired, some times we may want to have only one copy of `PoweredDevice` to be shared by `Scanner` and `Printer`
- To share a base class, simply insert the `virtual` keyword in the inheritance list of the derived class. This creates a **virtual base class**, which means there is only one base object. The base object is shared between all objects in the inheritance tree and it is only constructed once. Example: see `conspect/src/virtual-functions/virtual-base-class.cpp`. Because *Scanner* and *Printer* share a *PoweredDevice* base class, *Copier* constructor is responsible for creating *PoweredDevice*.
- Notes on virtual base classes:
    1. Virtual base classes are always created before non-virtual base classes
    2. **Note for example**: *Scanner* and *Printer* constructors still have calls to the *PoweredDevice* constructor. When creating an instance of *Copier*, these constructor calls are simply ignored because *Copier* is responsible for creating the *PoweredDevice*. However, if we were to create an instance of *Scanner* or *Printer*, those constructor calls would be used, and normal inheritance rules apply.
    3. If a class inherits one or more classes that have virtual parents, the most derived class is responsible for constructing the virtual base class. This is true even in a single inheritance case.
    4. All classes inheriting a virtual base class will have a virtual table, even if they would normally not have one otherwise, and thus be larger by a pointer
    5. **Another note for example**: Because *Scanner* and *Printer* derive virtually from *PoweredDevice*, *Copier* will only be one *PoweredDevice* subobject. *Scanner* and *Printer* both need to know how to find that single *PoweredDevice* subobject, so they can access its members (because after all, they are derived from it). This is typically done through some virtual table magic (which essentially stores the offset from each subclass to the PoweredDevice subobject)

## Object slicing
- (for `Base`/`Derived` example) - instead of setting a Base reference or pointer to a Derived object (like in **Pointers and references to the base class of derived objects** section above), we can simply assign a Derived object to a Base object:

`Derived derived{ 5 }; Base base{ derived };`
- When we do it, only the Base portion of the Derived object is copied, the Derived portion is not. This is called **object slicing** (or *slicing*)
- Slicing can be dangerous in some cases:
    - Used accidentally with functions:
    
            void printName(const Base base) { std::cout << base.getName(); }
            int main() { Derived d{ 5 }; printName(d); }

        The Derived part of `d` is sliced off, so printName will always print 'Base' (even if `getName()` is virtual)

        Fix: `void printName(const Base &base) { ... }`
    - Slicing vectors. The same problem will occur in the following code:
    
            std::vector<Base> v{};
            v.push_back(Base{ 5 });
            v.push_back(Derived{ 6 });

        Fix:

            std::vector<Base*> v{};
	
            Base b{ 5 };
            Derived d{ 6 };
        
            v.push_back(&b);
            v.push_back(&d);

        Also, in this fix, `nullptr` becomes a valid option (desired or not)

        *? using reference wrappers is also a fix ?*
        
    - The Frankenobject

            Derived d1{ 5 };
            Derived d2{ 6 };
            Base &b{ d2 };
            b = d1; // this line is problematic
        
        Because `b` is a Base, and the *operator=* provided to class by default isn't virtual, only the Base portion of `d1` is copied into `d2`. So `d2` now has the Base portion of `d1` and Derived portion of `d2`.

        Also, see `tests/virtual-functions/without-using-virtual-functions.cpp` - there is some code to prevent object slicing
- We should try to avoid slicing and use references (or pointers) wherever we can

## Dynamic casting
- It's possible to implicitly convert Derived pointer into a Base pointer (process is called **upcasting**)
- C++ provides casting operator `dynamic_cast`. Dynamic casts have a few different capabilities, but the most common use is for converting base-class pointers into derived-class pointers (process is called **downcasting**)
- Using `dynamic_cast` example: see `conspect/src/virtual-functions/dynamic-casting.cpp`
- **Rule**: Always ensure your dynamic casts actually succeeded by checking for a null pointer result. (explanation - in previous line's example)
- Because `dynamic_cast` does some consistency checking at runtime (to ensure the conversion can be made), use of dynamic_cast incurs a performance penalty
- Cases where downcasting using dynamic_cast will not work:
    1. With protected or private inheritance
    2. For classes that do not declare or inherit any virtual functions (and thus don't have a virtual table)
    3. In certain cases involving virtual base classes (see [this page](https://docs.microsoft.com/en-us/cpp/cpp/dynamic-cast-operator?redirectedfrom=MSDN&view=msvc-160) for some examples and how to resolve them)
- We can downcast using `static_cast`. Because `static_cast` does no runtime type checking, it's faster, but more dangerous, because a conversion of Base* to Derived* will succeed. This will result in undefined behaviour when trying to acces the resulting Derived pointer (that is actually pointing to a Base object)
- `dynamic_cast` can be used with references: see `conspect/src/virtual-functions/dynamic-casting-references.cpp`. Because there is no such thing as "null reference" in C++, if dynamic_cast of a reference fails, an exception of type `std::bad_cast` is thrown.
- Use `static_cast` unless downcasting, in which case it's better to use `dynamic_cast`. In general, it's better to avoid casting and just use virtual functions
- Downcasting may be preferred over virtual functions in some cases:
    - When you can not modify the base class to add a virtual function (e.g. because the base class is part of the standard library)
    - When you need access to something that is derived-class specific (e.g. an access function that only exists in the derived class)
    - When adding a virtual function to your base class doesn’t make sense (e.g. there is no appropriate value for the base class to return). Using a pure virtual function may be an option here if you don’t need to instantiate the base class

### dynamic_cast and RTTI
- **Run-time type information** (**RTTI**) is a feature of C++ that exposes information about an object’s data type at runtime. This capability is leveraged by dynamic_cast. Because RTTI has a pretty significant space performance cost, some compilers allow to turn RTTI off as an optimization. If we do this, dynamic_cast won’t function correctly.

## Printing inherited classes using operator<<
- See how to print: `conspect/src/virtual-functions/printing-inherited-classes.cpp` ([explanation](https://www.learncpp.com/cpp-tutorial/printing-inherited-classes-using-operator/))

# Templates
## Function templates
- **Function templates** are functions that serve as a pattern for creating other similar functions. We define the function using placeholder types, called **template type parameters**. When you call a template function, the compiler “stencils” out a copy of the template, replacing the placeholder types with the actual variable types from the parameters in your function call
- The usual name for placeholder type - `T`
- To say that this is template definition, and that `T` is a placeholder type, we use a **template parameter declaration**:

        template <typename T> // this is the template parameter declaration
        T max(T x, T y)
        {
            return (x > y) ? x : y;
        }
- We can use both keywords `class` and `typename` for template parameter declaration - in this case, they mean the same
- For multiple placeholder types: `template <typename T1, typename T2>`
- Because the function argument passed in for type T could be a class type, and it’s generally not a good idea to pass classes by value, it would be better to make the parameters and return types of our templated function const references: `const T& max(const T &x, const T &y)`
- Drawbacks:
    - Some older compilers don't have very good template support
    - Template functions produce hard-to-read error messages
    - Template functions can increase compile time and code size, as single template mught be "realized" and recompiled in many files (there are ways to work arount this one)

## Function template instances
- C++ doesn't compile template functions directly, instead, at compile time, when compiler encounters a call to template function, it replicates the template function and replaces the template type params with actual types. That function is called **function template instance**
- Compiler creates only one instance per unique set of params (per file). Also, if we create template function but do not call it, no template instances will be created.
- When template instance is compiled, it is compiled like a normal function, so types used in these instances should have all the necessary operators or functions defined (e.g. user-defined class should have `operator>` overloaded for the above `max` function to work)

## Template classes
- Template classes are instanced the same way template functions are
- Ideal for container classes. See `conspect/src/templates/Array.h`
- If we decide to split member function definitions from template class definition (e.g. move `getLength()` from `conspect/src/templates/Array.h` to `Array.cpp`), then we'll get a linker error. Why this happens and how to work around it: see `conspect/text/templates/splitting-template-classes.md`

## Template non-type parameters
- **Template non-type parameter** is a special type of parameter that does not substitute for a type, but is instead replaced by a value. A non-type parameter can be any of the following:
    - Value that has an integral type or enumeration
    - Pointer or reference to a class object
    - Ptr or ref to a function
    - Ptr or ref to a class member function
    - `std::nullptr_t`
- E.g., usage in non-dynamic (static) array class: see `conspect/src/templates/StaticArray.h`

## Function template specialization
- We can implement a templated function slightly different for a specific data type. E.g., in `conspect/src/templates/function-template-specialization.cpp`, we use a **function template specialization** (sometimes called a *full* or *explicit func templ spec*) to create a specialized version of `print()` for type `double`, and specialized version of constructor and destructor for type `char*`
- In the above example, we can see, that we would need to create specialized versions of constructor and destructor for all pointer types (e.g. for deep copy). See how to handle this using partial template specialization in the corresponding part of `conspect/text/templates/partial-template-specialization.md`

## Class template specialization
- **Class template specialization** allows us to specialize a template class for a particular data type (or data types, if there are multiple template parameters). E.g., we can make some storage class more efficient for booleans: see `conspect/src/templates/class-template-specialization.cpp`
- Class template specializations are treated as completely independent classes, even though they are allocated in the same way as the templated class. This means that we can change anything and everything about our specialization class, including the way it’s implemented and even the functions it makes public, just as if it were an independent class. **Note**: Keeping the public interface between your template class and all of the specializations identical is generally a good idea, as it makes them easier to use

## Partial template specialization
- See `conspect/text/templates/partial-template-specialization.md`

# Exceptions
- Exception handling provides a mechanism to decouple handling of errors or other exceptional circumstances from the typical control flow of our code
- Exceptions are implemented using 3 keywords: `throw`, `try`, `catch`
- **Throw statement** is used to signal that an exception or error case has occurred (**raising** an exception). Usage: `throw` keyword, followed by a value of any data type you wish to use to signal that an error has occurred. Typically, this value will be an error code, a description of the problem, or a custom exception class:

        throw -1; // throw a literal integer value
        throw ENUM_INVALID_INDEX; // throw an enum value
        throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
        throw dX; // throw a double variable that was previously defined
        throw MyException("Fatal Error"); // Throw an object of class MyException

- Use `try` keyword to define a block of statements (**try block**) that acts as an observer, looking for any exceptions that are thrown by any of the statements within the try block:

        try
        {
            // Statements that may throw exceptions you want to handle go here
            throw -1; // here's a trivial throw statement
        }

- Use `catch` keyword to define a block of code (`catch block`) that handles exceptions for a single data type:

        catch (int x)
        {
            // Handle an exception of type int here
            std::cerr << "We caught an int exception with value" << x << '\n';
        }

- *Try block* must have at least one *catch block* immediately following it, but may have multiple *catch blocks* listed in sequence
- Exceptions of fundamental types can be caught by value, but exceptions of non-fundamental types should be caught by const reference to avoid making an unnecessary copy
- If the parameter is not going to be used in the catch block, the variable name can be omitted (this can help prevent compiler warnings about unused variables):

        catch (double) // note: no variable name since we don't use it in the catch block below
        {
            // Handle exception of type double here
            std::cerr << "We caught an exception of type double" << '\n';
        }

- **Recap**: When an exception is raised (using `throw`), execution of the program immediately jumps to the nearest enclosing `try` block (propagating up the stack if necessary to find an enclosing try block). If any of the `catch` handlers attached to the try block handle that type of exception, that handler is executed and the exception is considered handled.

If no appropriate catch handlers exist, execution of the program propagates to the next enclosing try block. If no appropriate catch handlers can be found before the end of the program, the program will fail with an exception error
- **Note**: The compiler will not perform implicit conversions or promotions when matching exceptions with catch blocks! For example, a char exception will not match with an int catch block. An int exception will not match a float catch block. However, casts from a derived class to one of its parent classes will be performed
- What catch blocks typically do:
    1. May print an error (either to the console, or a log file)
    2. May return a value or error code back to the caller
    3. May throw another exception. Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block
- Example of exception usage: see `conspect/src/exceptions/example-exception.cpp`

## Stack unwinding
- If exception is thrown in a function, and that function doesn't handle it, the function is terminated, and the program checks to see if the function's caller will handle the exception. If not, it terminates the caller and checks the caller's caller. And so on, until the handler is found, or until `main()` is terminated without exception being handled. This process is called **unwinding the stack**
- Throw can be used outside of try/catch block (then the function will terminate and stack unwinding will begin, as described above)
- Why it may be a good idea to pass errors back to the caller: see `conspect/text/exceptions/modularity-of-exceptions.md`
- Example of stack unwinding: see `conspect/src/exceptions/stack-unwinding.cpp`

## Unhandled exceptions and catch-all handlers
- When `main()` terminates with an unhandled exception, the OS generally notifies you that there is unhandled exception error (how - depends on the OS). Generally, we want to avoid this
- Mechanism to catch all types of exceptions - **catch-all handler**. Works like a normal catch block, but uses the ellipsis operator (`...`) as a type to catch. Example:

        int main()
        {
            try
            {
                throw 5; // throw an int exception
            }
            catch (double x)
            {
                std::cout << "We caught an exception of type double: " << x << '\n';
            }
            catch (...) // catch-all handler
            {
                std::cout << "We caught an exception of an undetermined type\n";
            }
        }

- Catch-all handler should be placed last in the catch block chain
- Often, the catch-all handler block is left empty:

`catch(...) {} // ignore any unanticipated exceptions`
- One use of catch-all handler is to wrap the contents of `main()`:

        int main()
        {
        
            try
            {
                runGame();
            }
            catch(...)
            {
                std::cerr << "Abnormal termination\n";
            }
        
            saveState(); // Save user's game
            return 1;
        }

## Exceptions, classes, inheritance
### In members, overloaded operators, and constructors
- Exceptions in overloaded operators:

        int& IntArray::operator[](const int index)
        {
            if (index < 0 || index >= getLength())
                throw index;
        
            return m_data[index];
        }

- Exceptions can be used in constructors if something goes wrong during object creation. In such case, the object's construction is aborted, and all class members (which have already been created and initialized) are destructed as per usual. However, because class's destructor is never called, we need to clean up prior to throwing the exception. Even better, because the members of the class are destructed as per usual, if we do resource allocations in the members themselves, then those members can clean up after themselves when destructed. This is part of the reason that RAII is advocated so highly. Example: see `conspect/src/exceptions/exceptions-in-constructor.cpp`

### Exception classes
- Throwing basic data types as exception types is vague
- **Exception class** is just a normal class that is designed specifically to be thrown as an exception. Example of such class:

        class ArrayException
        {
        private:
            std::string m_error;
        
        public:
            ArrayException(std::string error)
                : m_error{error}
            {
            }
        
            const char* getError() const { return m_error.c_str(); }
        };

Now we can throw it:

`throw ArrayException("Invalid index");`,

and catch it: 

`catch (const ArrayException &exception) { std::cerr << "An array exception occurred (" << exception.getError() << ")\n"; }`

### Exceptions and inheritance
- Exception handlers will not only match classes of a specific type, they’ll also match classes derived from that specific type. Example: see `conspect/src/exceptions/exceptions-inheritance.cpp`
- **Rule**: Handlers for derived exception classes should be listed before those for base classes.

### std::exception
- Many of the classes and operators in the standard library throw exception classes on failure (e.g. `operator new` can throw `std::bad_alloc` if it is unable to allocate enough memory. Failed `dynamic_cast` will throw `std::bad_cast`). As of C++17, there are 25 different exception classes that can be thrown. They are all derived from `std::exception`
- `std::exception` (from `#include <exception>`) has a virtual function `what()`, which provides a C-style string description of the exception
- Some example of usage:

        try
        {
            // code using standard library goes here
        }
        // This handler will catch std::length_error (and any exceptions derived from it) here
        catch (const std::length_error &exception)
        {
            std::cerr << "You ran out of memory!" << '\n';
        }
        // This handler will catch std::exception (and any exception derived from it) that fall
        // through here
        catch (const std::exception &exception)
        {
            std::cerr << "Standard exception: " << exception.what() << '\n';
        }
- Nothing throws a `std::exception` directly, and neither should we. But we can throw other standard exception classes. `std::runtime_error` from `#include <stdexcept>` is a popular generic choice, with its constructor taking a customizable message:

`throw std::runtime_error("Bad things happened");`
- We can derive our own exception classes from `std::exception`:

        class ArrayException : public std::exception
        {
        private:
            std::string m_error{};
        
        public:
            ArrayException(std::string_view error)
                : m_error{error}
            {
            }
        
            // return the std::string as a const C-style string
            const char* what() const noexcept override { return m_error.c_str(); }
        };

- In C++11, `what()` was updated to have specifier `noexcept` (which means the function promises not to throw exceptions itself). Therefore, in C++11 and beyond, our override should also have specifier `noexcept`

## Rethrowing exceptions
- There may be cases where we can handle the exception and return reasonable value:

        Database* createDatabase(std::string filename)
        {
            try
            {
                Database *d = new Database(filename);
                d->open(); // assume this throws an int exception on failure
                return d;
            }
            catch (int exception)
            {
                // Database creation failed
                // Write an error to some global logfile
                g_log.logError("Creation of Database failed");
            }
        
            return nullptr;
        }

- If we can't handle exception reasonably in current function, we can throw another exception and it will be propagated up the stack:

        int getIntValueFromDatabase(Database *d, std::string table, std::string key)
        {
            assert(d);
        
            try
            {
                return d->getIntValue(table, key); // throws int exception on failure
            }
            catch (int exception)
            {
                // Write an error to some global logfile
                g_log.logError("doSomethingImportant failed");
        
                throw 'q'; // throw char exception 'q' up the stack to be handled by caller of getIntValueFromDatabase()
            }
        }

- We can rethrow the same exception in wrong way:

        int getIntValueFromDatabase(Database *d, std::string table, std::string key)
        {
            assert(d);
        
            try
            {
                return d->getIntValue(table, key); // throws Derived exception on failure
            }
            catch (Base &exception)
            {
                // Write an error to some global logfile
                g_log.logError("doSomethingImportant failed");
        
                throw exception; // Danger: this throws a Base object, not a Derived object
            }
        }

This can be bad in 2 ways:
1. This throws a copy-initialized copy of the exception, not the exception itself. Compiler may elide the copy, but also it may not, so this could be less performant.
2. (in the above example) `getIntValue()` throws `Derived` exception, but caught exception has type `Base`, so the thrown copy will also be `Base` - so `Derived` object has been sliced

- We can rethrow the same exception in right way by just using the keyword `throw`:

        catch (Base &exception)
        {
            g_log.logError("doSomethingImportant failed");

            throw; // This won't slice Derived object
        }

**Rule**: When rethrowing the same exception, use the throw keyword by itself.

## Function try blocks
- **Function try blocks** are designed to allow you to establish an exception handler around the body of an entire function, rather than around a block of code. Example: see `conspect/src/exceptions/function-try-block.cpp`
- Unlike normal catch blocks (where you can resolve the exception), with function-level try blocks, you must throw or rethrow an exception. If we don't explicitly do any of this, exception will be implicitly rethrown
- Function try blocks can also be used with non-member functions, but they're almost exclusively used with constructors
- Primarily are used for logging failures before passing exception up the stack, or for changing the type of exception thrown
- Function try blocks can't be used to clean up resources of a class that failed to construct, but already allocated resources, because the object is "dead" before the catch block executes

## Exception dangers and downsides
- Cleaning up resources
    1. We shouldn't forget to close files (and similar)

            try
            {
                openFile(filename);
                writeFile(filename, data);
                closeFile(filename);
            }
            catch (const FileException &exception)
            {
                // Make sure file is closed
                closeFile(filename);
                // Then write error
                std::cerr << "Failed to write to file: " << exception.what() << '\n';
            }
    
    2. Working with dynamically allocated memory:

            try
            {
                auto *john { new Person{ "John", 18, PERSON_MALE } };
                processPerson(john);
                delete john;
            }
            catch (const PersonException &exception)
            {
                std::cerr << "Failed to process person: " << exception.what() << '\n';
            }

        Here, we have two relatively easy ways to fix this:

        1. Declare `john` outside the try block

                Person *john{ nullptr };
                try
                {
                    john = new Person("John", 18, PERSON_MALE);
                    processPerson(john);
                    delete john;
                }
                catch (const PersonException &exception)
                {
                    delete john;
                    std::cerr << "Failed to process person: " << exception.what() << '\n';
                }

        2. Use local var of class that knows how to cleanup after itself when it goes out of scope ("smart pointer"). `std::unique_ptr` is a template class that holds a ptr, and deallocs it when it goes out of scope:

                #include <memory> // for std::unique_ptr
 
                try
                {
                    auto *john { new Person("John", 18, PERSON_MALE) };
                    std::unique_ptr<Person> upJohn { john }; // upJohn now owns john
                
                    ProcessPerson(john);
                
                    // when upJohn goes out of scope, it will delete john
                }
                catch (const PersonException &exception)
                {
                    std::cerr << "Failed to process person: " << exception.what() << '\n';
                }

- Exception should never be thrown in destructors (explanation [here](https://www.learncpp.com/cpp-tutorial/exception-dangers-and-downsides/)). Write message to a log file instead
- Exceptions have a small performance price. They increase the size of your executable, and they may also cause it to run slower due to additional checking that has to be performed. The main performance penalty is when exception is actually thrown (the stack must be unwound and appropriate handler found, which is relatively expensive)
- Some modern computer architectures support zero-cost exceptions. They have no additional runtime cost in the non-error case (which is the case we most care about performance). However, they incur even larger penalty when an exception is found
- We should use exceptions when all of the following is true:
    1. The error being handled is likely to occur only infrequently.
    2. The error is serious and execution could not continue otherwise.
    3. The error cannot be handled at the place where it occurs.
    4. There isn’t a good alternative way to return an error code back to the caller.

## Exception specifications and noexcept
- In C++, all functions are classified as either **non-throwing** (do not throw exceptions) or **potentially throwing** (may throw an exception)
- Looking at a typical function declaration, it is not possible to determine whether a function might throw an exception or not. **Exception specifications** are a language mechanism that was originally designed to document what kind of exceptions a function might throw as part of a function specification. Most of them are now deprecated or removed
- The **noexcept specifier** defines a function as non-throwing:

`void doSomething() noexcept;`

`noexcept` doesn’t actually prevent the function from throwing exceptions or calling other functions that are potentially throwing. Rather, when an exception is thrown, if an exception exits a noexcept function, `std::terminate` will be called. **Note**: if `std::terminate` is called from inside a `noexcept` function, stack unwinding may or may not occur (depending on implementation and optimizations), which means your objects may or may not be destructed properly prior to termination
- Much like functions that differ only in their return values can not be overloaded, functions differing only in their exception specification can not be overloaded
- `noexcept` specifier has an optional `Boolean` parameter. `noexcept(true)` is equivalent to `noexcept`, meaning the function is non-throwing. `noexcept(false)` means the function is potentially throwing. These parameters are typically only used in template functions, so that a template function can be dynamically created as non-throwing or potentially throwing based on some parameterized value
- Functions that are *non-throwing* by default:
    - default constructors
    - copy constructors
    - move constructors
    - destructors
    - copy assignment operators
    - move assignment operators
- If any of the listed functions call (explicitly or implicitly) another function which is *potentially throwing*, then the listed function will be treated as *potentially throwing* as well. For example, if a class has a data member with a *potentially throwing* constructor, then the class’s constructors will be treated as *potentially throwing* as well
- **Best practise**: If you want any of the above listed functions to be non-throwing, explicitly tag them as `noexcept` (even though they are defaulted that way), to ensure they don’t inadvertently become *potentially throwing*
- Functions that are *potentially throwing* by default:
    - Normal functions
    - User-defined constructors
    - Some operators, such as new
- `noexcept operator` can be used inside functions. It takes an expression as an argument, and returns true or false if the compiler thinks it will throw an exception or not. The noexcept operator is checked statically at compile-time, and doesn’t actually evaluate the input expression:

        void foo() {throw -1;}
        void boo() {};
        void goo() noexcept {};
        struct S{};
        
        constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
        constexpr bool b2{ noexcept(foo()) }; // false; foo() throws an exception
        constexpr bool b3{ noexcept(boo()) }; // false; boo() is implicitly noexcept(false)
        constexpr bool b4{ noexcept(goo()) }; // true; goo() is explicitly noexcept(true)
        constexpr bool b5{ noexcept(S{}) };   // true; a struct's default constructor is noexcept by default
- `noexcept operator` can be used to conditionally execute code depending on whether it is potentially throwing or not. This is required to fulfill certain *exception safety guarantees*
- **Exception safety guarantee** is a contractual guideline about how functions or classes will behave in the event an exception occurs. There are four levels of exception safety:

    - *No guarantee* -- There are no guarantees about what will happen if an exception is thrown (e.g. a class may be left in an unusable state)
    - *Basic guarantee* -- If an exception is thrown, no memory will be leaked and the object is still usable, but the program may be left in a modified state.
    - *Strong guarantee* -- If an exception is thrown, no memory will be leaked and the program state will not be changed. This means the function must either completely succeed or have no side effects if it fails. This is easy if the failure happens before anything is modified in the first place, but can also be achieved by rolling back any changes so the program is returned to the pre-failure state.
    - *No throw / No fail* -- The function will always succeed (no-fail) or fail without throwing an exception (no-throw).

More detailed about the last point:

- The *no-throw guarantee*: if a function fails, then it won’t throw an exception. Instead, it will return an error code or ignore the problem. No-throw guarantees are required during stack unwinding when an exception is already being handled; for example, all destructors should have a no-throw guarantee (as should any functions those destructors call). Examples of code that should be no-throw:

    - destructors and memory deallocation/cleanup functions
    - functions that higher-level no-throw functions need to call

- The *no-fail guarantee*: a function will always succeed in what it tries to do (and thus never has a need to throw an exception, thus, no-fail is a slightly stronger form of no-throw). Examples of code that should be no-fail:

    - move constructors and move assignment
    - swap functions
    - clear/erase/reset functions on containers
    - operations on std::unique_ptr
    - functions that higher-level no-fail functions need to call

- **Best practise**: Use the noexcept specifier in specific cases where you want to express a *no-fail* or *no-throw guarantee* (only on functions that *must not* throw or fail). If you are uncertain whether a function should have a no-fail/no-throw guarantee, error on the side of caution and do not mark it with `noexcept`
- There are a few good reasons to mark functions a non-throwing:
    - Non-throwing functions can be safely called from functions that are not exception-safe, such as destructors
    - Functions that are `noexcept` can enable the compiler to perform some optimizations that would not otherwise be available. Because a noexcept function cannot throw an exception, the compiler doesn’t have to worry about keeping the runtime stack in an unwindable state, which can allow it to produce faster code.
    - There are also a few cases where knowing a function is `noexcept` allows us to produce more efficient implementations in our own code: the standard library containers (such as `std::vector`) are noexcept aware and will use the `noexcept operator` to determine whether to use *move semantics* (faster) or *copy semantics* (slower) in some places
- Before C++11, **dynamic exception specifications** were used in place of noexcept. The *dynamic exception specifications* syntax uses the `throw` keyword to list which exception types a function might directly or indirectly throw:

        int doSomething() throw(); // does not throw exceptions
        int doSomething() throw(std::out_of_range, int*); // may throw either std::out_of_range or a pointer to an integer
        int doSomething() throw(...); // may throw anything

Were removed in C++17.

# Move semantics and smart pointers
- **Smart pointer** is a composition class that is designed to manage dynamically allocated memory and ensure that memory gets deleted when the smart pointer object goes out of scope:

`Auto_ptr1<Resource> ptr(new Resource()); // ptr now owns the Resource`
- The problem might occur if we do the following:

        Auto_ptr1<Resource> res1(new Resource());
	    Auto_ptr1<Resource> res2(res1); // Alternatively, don't initialize res2 and then assign res2 = res1;

(also, on pass and return by value)

C++ automatically provides shallow copy constructor and `operator=` to `Auto_ptr1`, so `Resource` pointer will be duplicated. Deep copy also doesn't work, because it might be expensive (or undesirable/impossible). So, instead of copying, we move the ownership of the pointer from source to destination object
- **Move semantics** means the class will transfer ownership of the object rather than making a copy. See implementation of `Auto_ptr2`: `conspect/src/move-semantics/Auto_ptr2.cpp`
- Why to avoid `std::auto_ptr`:
    1. Because `std::auto_ptr` implements move semantics through the copy constructor and assignment operator, passing a `std::auto_ptr` by value to a function will cause your resource to get moved to the function parameter (and be destroyed at the end of the function)
    2. `std::auto_ptr` always deletes its contents using non-array `delete`. This means auto_ptr won’t work correctly with dynamically allocated arrays. Worse, it won’t prevent you from passing it a dynamic array, which it will then mismanage, leading to memory leaks
    3. `auto_ptr` doesn’t play nice with a lot of the other classes in the standard library, including most of the containers and algorithms. This occurs because those standard library classes assume that when they copy an item, it actually makes a copy, not a move
- **Rule**: `std::auto_ptr` is deprecated and should not be used.
- In C++11, move semantics were officially added, to properly differentiate copying from moving, and `std::auto_ptr` was replaced with "move-aware" smart ptrs: `std::unique_ptr`, `std::weak_ptr`, and `std::shared_ptr`

## r-value references
- In addition to l-values and r-values, in order to support move semantics, C++11 introduces 3 new value categories: **pr-values**, **x-values**, and **gl-values** ([see for more](https://en.cppreference.com/w/cpp/language/value_category))
- C++11 adds a new type of reference called an **r-value reference**. An r-value reference is a reference that is designed to be initialized with an r-value (only): `int &&rref{ 5 };`
- R-value ref properties:
    1. r-value refs extend the lifespan of the object they are initialized with to the lifespan of the r-value reference (l-value refs to const objects can do this too)
    2. Non-const r-value refs allow you to modify the r-value
- R-value refs can be useful for function overloads as function parameters, to have different behaviour for l-value and r-value arguments:

        void fun(const int &lref) // l-value arguments will select this function
        {
            std::cout << "l-value reference to const\n";
        }
        
        void fun(int &&rref) // r-value arguments will select this function
        {
            std::cout << "r-value reference\n";
        }
    
**Note**: r-value reference itself is a l-value, as all named objects are. So `int &&ref{ 5 }; fun(ref);` will call the l-value version of `fun()`
- We can think this way: named objects are *l-values*, anonymous objects are *r-values*
- We should almost never return r-value refs, for the same reason as we almost never return l-value refs

## Move constructors and move assignment
- The goal of the move constructor and move assignment is to move ownership of the resources from one object to another (which is typically much less expensive than making a copy)
- We define move constructor and move assignment analogously to their copy counterparts, but when copy flavors of these functions take in const l-value reference parameter, the move flavors use non-const r-value reference parameters. Example: see `conspect/src/move-semantics/move-constructor-assignment.cpp`
- **Rule**: If you want a move constructor and move assignment that do moves, you’ll need to write them yourself
- Key insight behind move semantics:
    - If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b”, we wouldn’t reasonably expect b to be changed in any way.
    - If we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway.
- Move functions should always leave both objects in a well-defined state: see EXPLANATION TO LINE 31 in `conspect/src/move-semantics/move-constructor-assignment.cpp`
- Automatic l-values (created on the stack, not dynamically) returned by value may be moved instead of copied: see EXPLANATION TO generateResource() in `conspect/src/move-semantics/move-constructor-assignment.cpp`
- In move-enabled classes, it's sometimes desirable to delete the copy constructor and copy assignment functions to ensure copies aren't made. In `Auto_ptr4` class of `conspect/src/move-semantics/move-constructor-assignment.cpp`, we don't want to copy templated object `T`, because it's expensive, and whatever class T is, it may not even support copying. So we can disable support of copy semantics:

        Auto_ptr4(const Auto_ptr5& a) = delete;
        Auto_ptr4& operator=(const Auto_ptr5& a) = delete;

If we try to pass an `Auto_ptr4` l-value by value, the compiler will complain that the copy constructor has been deleted. This is good, because we should probably be passing `Auto_ptr4` by const l-value reference anyway.

With that, `Auto_ptr4` becomes a good smart pointer class. It is now similar to `std::unique_ptr`

## std::move
- There are cases, where we want to invoke move semantics, but the objects we work with are l-values (e.g., swap function, where we want to make our code more performant by doing 3 moves instead of 3 copies). `std::move` from `#include <utility>` converts its arguments to r-values. Example of swap function with move semantics:

        template<class T>
        void myswap(T& a, T& b) 
        { 
            T tmp { std::move(a) }; // invokes move constructor
            a = std::move(b); // invokes move assignment
            b = std::move(tmp); // invokes move assignment
        }

- `std::move()` gives a hint to the compiler that the programmer doesn’t need this object any more (at least, not in its current state). Consequently, you should not use `std::move()` on any persistent object you don’t want to modify, and you should not expect the state of any objects that have had `std::move()` applied to be the same after they are moved
- It’s a good idea to always leave the objects being stolen from in some well-defined (deterministic) state. Ideally, this should be a “null state”, where the object is set back to its uninitiatized or zero state. Why: with `std::move`, the object being stolen from may not be a temporary after all. The user may want to reuse this (now empty) object again, or test it in some way. Example: see `conspect/src/move-semantics/std-move-example.cpp`
- Some usages of `std::move`:
    - Many sorting algorithms (such as selection sort and bubble sort) work by swapping pairs of elements. Move semantics is more efficient in this case, than copying
    - Moving the contents managed by one smart pointer to another
- **Conclusion**: `std::move` can be used whenever we want to treat an l-value like an r-value for the purpose of invoking move semantics instead of copy semantics.

## std::move_if_noexcept
- Copy semantics hold *strong exception guarantee* (we can just discard the failed copy, the original object is not harmed), while move semantics don't (if source object is non-temporary and has already transferred the ownership, when the exception occurs, then it's left in a modified state). It is simple enough to avoid throwing exceptions in the body of a move constructor, but a move constructor may invoke other constructors that are potentially throwing.

Example: see `conspect/src/move-semantics/std-move-if-noexcept.cpp`
- `std::move_if_noexcept` will return a movable r-value if the object has a `noexcept` move constructor, otherwise it will return a copyable l-value. We can use the `noexcept` specifier in conjunction with `std::move_if_noexcept` to use move semantics only when a strong exception guarantee exists (and use copy semantics otherwise) (move constructors are `noexcept` by default, unless they call a function that is `noexcept(false)`)
- **Warning**: If a type has both potentially throwing move semantics and deleted copy semantics (the copy constructor and copy assignment operator are unavailable), then `std::move_if_noexcept` will waive the strong guarantee and invoke move semantics. This conditional waiving of the strong guarantee is ubiquitous in the standard library container classes, since they use `std::move_if_noexcept` often

## std::unique_ptr
- Smart pointers should always be allocated on the stack - so they are always automatically destroyed, and thus will always clean up the dynamic resources they manage
- `std::unique_ptr` should be used to manage any dynamically allocated object that is not shared by multiple objects. Lives in `<memory>` header
- Implements move semantics, so copy is disabled:

        std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
        std::unique_ptr<Resource> res2{}; // Start as nullptr
    
        // res2 = res1; // Won't compile: copy assignment is disabled
        res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

- `std::unique_ptr` has overloaded `operator*`, which returns a reference to the managed resource, and `operator->`, which returns a pointer. Because `std::unique_ptr` may not always manage a resource, before we use any of these operators, we should check whether unique_ptr actually has a resource. This is easy: unique_ptr has a cast to bool that returns true if unique_ptr is managing a resource:

        std::unique_ptr<Resource> res{ new Resource{} };
 
	    if (res) { std::cout << *res << '\n'; }

- Unlike auto_ptr, unique_ptr knows when to use scalar or array `delete`. Still, **Rule**: Favor `std::array`, `std::vector`, or `std::string` over a smart pointer managing a fixed array, dynamic array, or C-style string
- **Rule**: use `std::make_unique()` instead of creating `std::unique_ptr` and using `new` yourself:

        auto f1{ std::make_unique<Fraction>(3, 5) };
    
        // Create a dynamically allocated array of Fractions of length 4
        auto f2{ std::make_unique<Fraction[]>(4) };

It makes the code simpler, also it resolves an exception safety issue that can result from C++ leaving the order of evaluation for function arguments unspecified. Example:

        some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());

The above may be called in such order: `new T` => `function_that_can_throw_exception()` => create`std::unique_ptr<T>`. So `T` will be leaked, if `function_that_can_...` throws an exception
- In general, we should not return std::unique_ptr by pointer (ever) or reference (unless we have a specific compelling reason to).
- If we want to pass unique_ptr to a function, that will take ownership of the contents, pass by value (using `move` because copy is disabled):

        void takeOwnership(std::unique_ptr<Resource> res) {...}

        int main()
        {
            auto ptr{ std::make_unique<Resource>() };
    
            takeOwnership(std::move(ptr));

            return 0;
        }
- We can pass a unique_ptr by reference (which will allow the function to use the object without assuming ownership), we should only do so when the called function might alter or change the object being managed
- It’s better to just pass the resource itself (by pointer or reference, depending on whether null is a valid argument). This allows the function to remain agnostic of how the caller is managing its resources. To get raw resource ptr, use `get()` member function:

        auto ptr{ std::make_unique<Resource>() };
	    useResource(ptr.get());

- We can use `std::unique_ptr` as a composition member of your class, so that our class destructor doesn't have to worry about deleting dynamic memory. **Note**: if class object itself is dynamically allocated, it's at risk of not being properly deallocated itself
- Ways to misuse `std::unique_ptr`:
    - Don’t let multiple classes manage the same resource, because they both will try to delete it, which will lead to undefined behaviour:

            Resource *res{ new Resource() };
            std::unique_ptr<Resource> res1{ res };
            std::unique_ptr<Resource> res2{ res };
    
    - Don't manually delete the resource out from underneath the unique_ptr:

            Resource *res{ new Resource() };
            std::unique_ptr<Resource> res1{ res };
            delete res;

**Note**: `std::make_unique()` prevents both of the above cases from happening inadvertently

## std::shared_ptr
- `std::shared_ptr` is meant to solve the case where you need multiple smart pointers co-owning a resource. Internally, std::shared_ptr keeps track of how many std::shared_ptr are sharing the resource. As long as at least one std::shared_ptr is pointing to the resource, the resource will not be deallocated, even if individual std::shared_ptr are destroyed. As soon as the last std::shared_ptr managing the resource goes out of scope (or is reassigned to point at something else), the resource will be deallocated. Lives in `<memory>` header
- For explicit example (of this and `std::make_shared`): see `conspect/src/move-semantics/shared-and-make-shared.cpp`
- **Rule**: Always make a copy of an existing `std::shared_ptr` if you need more than one `std::shared_ptr` pointing to the same resource.
- The reasons for using `std::make_shared()` are the same as `std::make_unique()` - `std::make_shared()` is simpler and safer (there’s no way to directly create two shared_ptr pointing to the same resource using this method). However, make_shared is also more performant than not using it, because of the way that `std::shared_ptr` keeps track of how many pointers are pointing at a given resource
- Details of how `std::shared_ptr` works: see `conspect/text/move-semantics/shared-ptr-details.md`
- `std::unique_ptr` can be converted into a `std::shared_ptr` via a special `std::shared_ptr` constructor that accepts a `std::unique_ptr` r-value. However, shared_ptr can not be safely converted to a unique_ptr