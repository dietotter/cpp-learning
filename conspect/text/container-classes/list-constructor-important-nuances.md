# Class assignment using std::initializer_list

If implementing a constructor that takes a std::initializer_list, you should ensure you do at least one of the following:

1. Provide an overloaded list assignment operator
2. Provide a proper deep-copying copy assignment operator

Here’s why: consider the above class (which doesn’t have an overloaded list assignment or a copy assignment), along with following statement:

`array = { 1, 3, 5, 7, 9, 11 }; // overwrite the elements of array with the elements from the list`

First, the compiler will note that an assignment function taking a `std::initializer_list` doesn’t exist. Next it will look for other assignment functions it could use, and discover the implicitly provided copy assignment operator. However, this function can only be used if it can convert the initializer list into an `IntArray`. Because `{ 1, 3, 5, 7, 9, 11 }` is a *std::initializer_list*, the compiler will use the list constructor to convert the initializer list into a temporary *IntArray*. Then it will call the implicit assignment operator, which will shallow copy the temporary *IntArray* into our array object.

At this point, both the temporary *IntArray*’s `m_data` and `array->m_data` point to the same address (due to the shallow copy).

At the end of the assignment statement, the temporary *IntArray* is destroyed. That calls the destructor, which deletes the temporary *IntArray*’s `m_data`. This leaves our array variable with a hanging `m_data` pointer. When you try to use `array->m_data` for any purpose (including when array goes out of scope and the destructor goes to delete `m_data`), you’ll get undefined results (and probably a crash).

**Rule**: If you provide list construction, it’s a good idea to provide list assignment as well.