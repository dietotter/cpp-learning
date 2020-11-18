#pragma once

#include <string>

namespace quest2 {

    struct StudentInfo
    {
        std::string name{};
        int grade{};
    };
    
    int executeQuest2();
}