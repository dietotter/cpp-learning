#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct StudentGrade
{
    std::string studentName{};
    char grade{};
};

// Note: there is std::map
// Optimization: keep m_map sorted and use binary search on operator[]
class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};

public:
    char& operator[](const std::string &index);
};

char& GradeMap::operator[](const std::string &name)
{
    auto nameExists{ [&name](StudentGrade elem) { return elem.studentName == name; } };

    auto found{ std::find_if(m_map.begin(), m_map.end(), nameExists) };
    
    if (found != m_map.end())
    {
        return found->grade;
    }

    m_map.push_back({ name });

    return m_map.back().grade;
}

int main()
{
    GradeMap grades{};
 
	grades["Joe"] = 'A';
	grades["Frank"] = 'B';
 
	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

	grades["Frank"] = 'C';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

    return 0;
}

// int main()
// {
// 	GradeMap grades{};
 
// 	char& gradeJoe{ grades["Joe"] }; // does a push_back
// 	gradeJoe = 'A';
 
// 	char& gradeFrank{ grades["Frank"] }; // does a push_back
// 	gradeFrank = 'B';
 
// 	std::cout << "Joe has a grade of " << gradeJoe << '\n';
// 	std::cout << "Frank has a grade of " << gradeFrank << '\n';
 
// 	return 0;
// }
//
// The commented example above won't work, because std::vector needs to be resized when
// new elements are added, and so it dynamically allocates a new block of memory,
// copying the elements to that block and deleting the old one.
// So, whe "Frank" is pushed into array, gradeJoe is left as a dangling ref to deleted memory.