#pragma once

#include "../exception/invalidDataException.h"

#include <algorithm>
#include <format>
#include <string_view>

inline void checkNoSeparator(std::string_view value, std::string_view fieldName)
{
    if (std::ranges::find(value, '#') != value.end())
        throw InvalidDataException(std::format("The {} cannot contain '#'", fieldName));
}
