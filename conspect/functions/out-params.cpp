int foo1(int x); // pass by value
int foo2(int &x); // pass by reference
int foo3(int *x); // pass by address
 
int i {};
 
foo1(i);  // can't modify i
foo2(i);  // can modify i
foo3(&i); // can modify i