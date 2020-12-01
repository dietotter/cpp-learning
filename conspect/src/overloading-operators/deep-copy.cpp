#include <iostream>
 
class MyString
{
private:
    char *m_data;
    int m_length;
    
    void MyString::deepCopy(const MyString &source);
 
public:
    MyString(const char *data="", int length=0);

    MyString::MyString(const MyString &source);
 
    // Overloaded assignment
    MyString& operator= (const MyString &str);
};

// assumes m_data is initialized
void MyString::deepCopy(const MyString &source)
{
    // first we need to deallocate any value that this string is holding!
    delete[] m_data;
 
    // because m_length is not a pointer, we can shallow copy it
    m_length = source.m_length;
 
    // m_data is a pointer, so we need to deep copy it if it is non-null
    if (source.m_data)
    {
        // allocate memory for our copy
        m_data = new char[m_length];
 
        // do the copy
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

MyString::MyString(const char *data="", int length=0) :
    m_length(length)
{
    if (!length)
        m_data = nullptr;
    else 
        m_data = new char[length];
 
    for (int i=0; i < length; ++i)
        m_data[i] = data[i];
}
 
// Copy constructor
MyString::MyString(const MyString &source)
{
    deepCopy(source);
}

// Assignment operator
MyString& MyString::operator=(const MyString & source)
{
    // check for self-assignment
    if (this != &source)
    {
        // now do the deep copy
        deepCopy(source);
    }
 
    return *this;
}