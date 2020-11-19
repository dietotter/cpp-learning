#include <utility>
#include <vector>
#include <string>

struct Employee{};

int sumTo(const int value);

void printEmployeeName(const Employee &employee);

std::pair<int, int> minmax(const int a, const int b);

int getIndexOfLargestValue(const std::vector<int> &intArray);

const std::string& getElement(const std::vector<std::string> &stringArray, const int index);

int main()
{
    return 0;
}