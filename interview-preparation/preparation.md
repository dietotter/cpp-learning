- [Some nice FAQ site](https://isocpp.org/wiki/faq/exceptions)
- [Why there is no virtual constructor](https://stackoverflow.com/questions/733360/why-do-we-not-have-a-virtual-constructor-in-c)
- [How does deleting destructor prevents stack allocation](https://stackoverflow.com/questions/18847739/how-does-delete-on-destructor-prevent-stack-allocation)
- [Object lifetime and storage duration](https://linuxhint.com/object-lifetime-and-storage-duration-in-c/) - here, a nice explanation for initialization is also provided: *While creating an object, its location in memory has to be established, before it is initialized. Initialization means putting value into the location.*
- [Indirect function call](https://softwareengineering.stackexchange.com/questions/401110/difference-between-direct-and-indirect-function-calls)
- [Size of an object](https://stackoverflow.com/questions/937773/how-do-you-determine-the-size-of-an-object-in-c)
- [Difference between copy and direct initialization](https://stackoverflow.com/questions/1051379/is-there-a-difference-between-copy-initialization-and-direct-initialization)
- [2D arrays in memory](https://cse.engineering.nyu.edu/~mleung/CS1114/f03/ch10/MDmemory.htm)
- [Compilation steps](https://www.freelancer.com/community/articles/how-c-works-understanding-compilation)
- [Database normalization principles](https://www.guru99.com/database-normalization.html#1)
- [What is POD (plain old data)](https://stackoverflow.com/questions/146452/what-are-pod-types-in-c)
- [Page fault](https://www.geeksforgeeks.org/page-fault-handling-in-operating-system/)
- [Shared ptr](https://shaharmike.com/cpp/shared-ptr/#std-shared-ptr)
- [Data alignment and paddings](https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/)
- [Game programming patterns](https://gameprogrammingpatterns.com/)
- [Quick linear algebra usage for game dev](https://habr.com/ru/post/131931/)

## Copy elision

## RVO and NRVO
- Read here:
    - http://alenacpp.blogspot.com/2008/02/rvo-nrvo.html
    - http://msdn2.microsoft.com/en-us/library/ms364057(vs.80).aspx
- **RVO** - return value optimisation.
- **NRVO** - named return value optimisation.

## What are expressions
- https://en.cppreference.com/w/cpp/language/expressions

## prvalues, lvalues, glvalues, xvalues, rvalues
- Read here:
    - https://en.cppreference.com/w/cpp/language/value_category
    - https://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues
    - https://habr.com/ru/post/441742/
- Basically, the following schema:

               Expression
              /          \
           glvalue     rvalue
          /       \   /      \
        lvalue   xvalue     prvalue

## Storage class specifiers
- Read:
    - https://en.cppreference.com/w/cpp/language/storage_duration

## Type qualifiers
- [Const and volatile](https://en.cppreference.com/w/cpp/language/cv)
- [Volatile explained](https://habr.com/ru/sandbox/114114/)

## Conversion constructor
- **Conversion constructor** is a single-parameter constructor with no `explicit` specifier.
    
        Foo(int a);
        ...

        Foo f{ 5 };

- **Conversion operator**:

        ...
            double value;
        public:
            operator double() { return value; }
        ...
        
        Foo fooThing;
        double i = fooThing;

## MyObject obj; vs MyObject obj();
- [Explanations for user-defined and built-in types](https://www.programmersought.com/article/21556677929/)
- [Most vexing parse](https://en.wikipedia.org/wiki/Most_vexing_parse)

## Derived class inherits/doesn't inherit
- Inherits:
    - All member variables (even w/o access to them)
    - All member functions (even w/o access to them)
    - Initial data layout
- Doesn't:
    - Base class's constructor/destructor
    - Base class's assignment operator
    - Base class's friends

## delete this;
- Q: What happens when you make call "delete this;"?

A: The code has two built-in pitfalls. First, if it executes in a member function for an extern, static, or automatic object, the program will probably crash as soon as the delete statement executes. There is no portable way for an object to tell that it was instantiated on the heap, so the class cannot assert that its object is properly instantiated. Second, when an object commits suicide this way, the using program might not know about its demise. As far as the instantiating program is concerned, the object remains in scope and continues to exist even though the object
did itself in. Subsequent dereferencing of the pointer can and usually does lead to disaster.
You should never do this. Since compiler does not know whether the object was allocated on the stack or on the heap, "delete this" could cause a disaster.

## Implicit member functions (generated for us)
1. default ctor
2. copy ctor
3. assignment operator
4. default destructor
5. address-of operator (&)

## Solid links
- https://www.baeldung.com/solid-principles
- http://butunclebob.com/ArticleS.UncleBob.PrinciplesOfOod
- https://medium.com/backticks-tildes/the-s-o-l-i-d-principles-in-pictures-b34ce2f1e898 (in pictures)

## Patterns
- https://refactoring.guru/design-patterns/catalog

## erase-remove idiom (see links)
- https://stackoverflow.com/questions/22729906/stdremove-if-not-working-properly
- https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
- https://ps-group.github.io/cxx/cxx_remove_if

## STL containers
- https://embeddedartistry.com/blog/2017/08/02/an-overview-of-c-stl-containers/
- https://cs.helsinki.fi/u/tpkarkka/alglib/k06/lectures/containers.html
- https://embeddedartistry.com/blog/2017/08/23/choosing-the-right-stl-container-general-rules-of-thumb/

## Concurrency
- Critical operations and atomicity (page 303-304 in game engines book)
- Deadlock and how to solve it (page 322)
- Primitives - mutexes, critical ops, conditional vars, semaphors (page 308+)

## Game engine structure
- Page 62 of game engines book

## Static-dynamic libraries
- https://www.learncpp.com/cpp-tutorial/a1-static-and-dynamic-libraries/
- https://medium.com/swlh/linux-basics-static-libraries-vs-dynamic-libraries-a7bcf8157779

## Balanced binary trees
- https://xlinux.nist.gov/dads/HTML/balancedtree.html#:~:text=(data%20structure),work%20to%20keep%20them%20balanced.
- https://www.programiz.com/dsa/balanced-binary-tree

## Multiple inheritance and vtables (a bit advanced)
- https://shaharmike.com/cpp/vtable-part2/
- https://habr.com/ru/company/otus/blog/479802/
- https://www.codeproject.com/Questions/878838/How-many-vptrs-will-be-created