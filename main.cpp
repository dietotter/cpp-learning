#include "helper.h"

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <string_view>

struct Student
{
    std::string name;
    int points;
};

struct Season
{
    std::string_view name{};
    double averageTemperature{};
};

int main()
{
    std::array<Student, 6> students{ 
        {
            { "Kek", 80 },
            { "Lol", 69 },
            { "Asd", 91 },
            { "Loh", 5 },
            { "Chel", 75 },
            { "Shestoy", 69 }
        } 
    };

    Student *bestStudent{
        std::max_element(students.begin(), students.end(),
            [](const auto &currentBest, const auto &student) {
                return currentBest.points < student.points;
            })
    };

    std::cout << bestStudent->name << " is the biggest zadrot\n";
    
    std::array<Season, 4> seasons{
        {
            { "Spring", 285.0 },
            { "Summer", 296.0 },
            { "Fall", 288.0 },
            { "Winter", 263.0 }
        }
    };

    std::sort(seasons.begin(), seasons.end(), [](const auto &a, const auto &b) {
        return a.averageTemperature < b.averageTemperature;
    });

    for (const auto& season : seasons)
    {
        std::cout << season.name << '\n';
    }

    return 0;
}
