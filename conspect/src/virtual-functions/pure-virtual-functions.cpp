#include <string>
#include <utility>
 
class Animal
{
protected:
    std::string m_name;
 
    // We're making this constructor protected because
    // we don't want people creating Animal objects directly,
    // but we still want derived classes to be able to use it.
    Animal(const std::string& name)
        : m_name{ name }
    {
    }
 
public:
    std::string getName() const { return m_name; }
    virtual const char* speak() const { return "???"; }
    
    virtual ~Animal() = default;
};
 
class Cat: public Animal
{
public:
    Cat(const std::string& name)
        : Animal{ name }
    {
    }
 
    const char* speak() const override { return "Meow"; }
};
 
class Dog: public Animal
{
public:
    Dog(const std::string& name)
        : Animal{ name }
    {
    }
 
    const char* speak() const override { return "Woof"; }
};

// We’ve prevented people from allocating objects of type Animal by making the constructor protected. However, there are two problems with this:
// 1) The constructor is still accessible from within derived classes, making it possible to instantiate an Animal object.
// 2) It is still possible to create derived classes that do not redefine function speak().
// A better solution to this problem is to use a pure virtual function:

class Animal2 // This Animal is an abstract base class
{
protected:
    std::string m_name;
 
public:
    Animal2(const std::string& name)
        : m_name{ name }
    {
    }
 
    const std::string& getName() const { return m_name; }
    virtual const char* speak() const = 0; // note that speak is now a pure virtual function
    
    virtual ~Animal2() = default;
};

// Animal is now an abstract base class, and can not be instantiated. Consequently,
// we do not need to make the constructor protected any longer (though it doesn’t hurt).
// Because our Cow class was derived from Animal, but we did not define Cow::speak(),
// Cow is also an abstract base class. If we try to instantiate cow,
// it will give a compile error and warning that pure virtual function was not defined