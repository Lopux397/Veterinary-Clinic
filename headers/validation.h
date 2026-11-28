#pragma once

#include "../exception/invalidDataException.h"

#include <format>
#include <string_view>

inline void checkNoSeparator(std::string_view value, std::string_view fieldName)
{
    if (value.find('#') != std::string_view::npos)
        throw InvalidDataException(std::format("The {} cannot contain '#'", fieldName));
}
