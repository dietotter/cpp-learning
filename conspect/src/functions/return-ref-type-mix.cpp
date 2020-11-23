int returnByValue()
{
    return 5;
}
 
int& returnByReference()
{
     static int x{ 5 }; // static ensures x isn't destroyed when the function ends
     return x;
}

const int& returnByReference2()
{
     return 5;
}
 
int main()
{
    int giana{ returnByReference() }; // case A -- ok, treated as return by value. Since giana isn't a ref, the return value is copied into giana
    int& ref{ returnByValue() }; // case B -- compile error since the value is an r-value, and an r-value can't bind to a non-const reference
    const int& cref{ returnByValue() }; // case C -- ok, the lifetime of the return value is extended to the lifetime of cref

    // Lifetime extension doesn't save dangling references
    const int &ref { returnByReference() }; // runtime error
    // 5 goes out of scope first, then the reference to 5 is copied back to the caller,
    // and then ref extends the lifetime of the now-dangling reference
    // The case above this case works as expected, because the literal value 5 is copied back into the scope of the caller
    // to then have its lifetime be extended by the ref
 
    return 0;
}