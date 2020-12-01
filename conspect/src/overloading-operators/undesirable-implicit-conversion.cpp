#include <string>
#include <iostream>
 
class MyString
{
private:
	std::string m_string;
public:
	MyString(int x) // allocate string of size x
	{
		m_string.resize(x);
	}
 
	MyString(const char *string) // allocate string to hold string value
	{
		m_string = string;
	}
 
	friend std::ostream& operator<<(std::ostream& out, const MyString &s);
 
};
 
std::ostream& operator<<(std::ostream& out, const MyString &s)
{
	out << s.m_string;
	return out;
}
 
void printString(const MyString &s)
{
	std::cout << s;
}
 
int main()
{
	MyString mine = 'x'; // Will compile and use MyString(int)
	std::cout << mine << '\n';
 
	printString('x'); // Will compile and use MyString(int)
	return 0;
}