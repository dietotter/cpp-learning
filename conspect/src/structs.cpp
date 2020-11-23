struct Employee
{
    short id;
    int age;
    double wage;
};

// Since C++11, we can give non-static struct members a default value
struct Rectangle
{
    double length{ 1.0 };
    double width{ 1.0 };
};

struct Company
{
    Employee CEO; // Employee is a nested struct
    int numberOfEmployees;
};

struct SomeStruct
{
    int arr[3]{};
    int i{};
};

int main()
{
    // like normal vars, struct member variables which are not initialized will contain junk
    Employee hoe;
    hoe.id = 14;
    hoe.age = 32;
    hoe.wage = 20.0;

    Employee lol;
    lol = { 3, 40, 12.5 }; // C++11

    // can use initializer list
    Employee chel{ 1, 20 };
    // if the list does not contain an initializer for some elements,
    // those elems are initialized to a default value
    // (chel.wage will initialize to 0.0)

    // in C++11, though, non-static member initialization is incompatible with the uniform initialization
    // This works from C++14
    Rectangle x{ 2.0, 2.0 };

    // using nested initializer list
    Company myCompany{ { 4, 42, 60000.0 }, 5 };

    // Braces can be omitted during aggregate initialization:
    // These two do the same
    SomeStruct s1{ { 1, 2, 3 }, 4 };
    SomeStruct s2{ 1, 2, 3, 4 };
}

struct Point3d
{
    double x;
    double y;
    double z;
};
 
Point3d getZeroPoint()
{
    // We can create a variable and return the variable.
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}
 
Point3d getZeroPoint2()
{
    // We can return directly. We already specified the type
    // at the function declaration (Point3d), so we don't need
    // it again here.
    return { 0.0, 0.0, 0.0 };
}
 
Point3d getZeroPoint3()
{
    // We can use empty curly braces to zero-initialize all
    // members of `Point3d`.
    return {};
}