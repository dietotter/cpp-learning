#include <string>
#include <iostream>
 
class Employee
{
private:
    int m_id{};
    std::string m_name{};
 
public:
    Employee(int id=0, const std::string &name=""):
        m_id{ id }, m_name{ name }
    {
        std::cout << "Employee " << m_name << " created.\n";
    }
 
    // Use a delegating constructor to minimize redundant code
    Employee(const std::string &name) : Employee{ 0, name }
    { }

    // Note that if we tried to call a constructor inside the body of another constructor,
    // it wouldn't work as expected (because that way a new object would be instantiated,
    // and then immediately discarded)
};