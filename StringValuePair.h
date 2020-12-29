#pragma once

#include "Pair.h"

#include <string>

template <class S>
class StringValuePair : public Pair<std::string, S>
{
public:
    StringValuePair(const std::string &key, const S &value)
        : Pair<std::string, S>{ key, value }
    {
    }
};