#include "quest2.h"

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

namespace quest2 {

    bool compareStudents(const StudentInfo &st1, const StudentInfo &st2)
    {
        return st1.grade > st2.grade;
    }

    void ignoreInput()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int askForNumber()
    {
        int studentsNum{};
        while (true)
        {
            std::cout << "Enter number: ";
            std::cin >> studentsNum;

            if (std::cin.fail())
            {
                std::cin.clear();
                ignoreInput();

                std::cout << "Try again.\n";
            }
            else
            {
                ignoreInput();

                return studentsNum;
            }
        }
    }
    
    int askForGrade()
    {
        do
        {
            std::cout << "Enter student's grade (0 to 100)\n";
            int grade{ askForNumber() };

            if (grade >= 0 && grade <= 100)
            {
                return grade;
            }

            std::cout << "Try again.\n";
        }
        while (true);
    }

    std::string askForName()
    {
        std::cout << "Enter student's name: \n";
        std::string name{};
        std::getline(std::cin, name);

        return name;
    }

    int executeQuest2()
    {
        using vector_type = std::vector<StudentInfo>;

        std::cout << "Enter the students' number\n";
        int studentsNum{ askForNumber() };

        vector_type students(static_cast<vector_type::size_type>(studentsNum));
        for (auto &student : students)
        {
            student.name = askForName();
            student.grade = askForGrade();
        }

        std::sort(students.begin(), students.end(), compareStudents);

        for (const auto &student : students)
        {
            std::cout << student.name << " got a grade of " << student.grade << '\n';
        }

        return 0;
    }

}