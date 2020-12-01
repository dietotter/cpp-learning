#include <iostream>
#include <string>
#include <cassert>

class MyString
{
private:
    std::string m_str{};

public:
    MyString(const std::string &str = "");

    std::string operator()(size_t startIndex, size_t returningLength) const;
};

MyString::MyString(const std::string &str): m_str(str)
{
}

std::string MyString::operator()(size_t startIndex, size_t returningLength) const
{
    assert(startIndex < m_str.size() && "Out of bounds");

    std::string result{};

    for (size_t i{ startIndex }, count{ 0 } ; i < m_str.size() && count < returningLength; ++i, ++count)
    {
        result += m_str[i];
    }

    return result;
}

int main()
{
    MyString string{ "Hello, world!" };
    std::cout << string(7, 5) << '\n'; // start at index 7 and return 5 characters

    return 0;
} // can use std::string::substr for substring