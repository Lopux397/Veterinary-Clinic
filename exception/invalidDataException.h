#pragma once

#include <stdexcept>

class InvalidDataException : public std::invalid_argument //Исключение: недопустимые данные
{
public:
    using std::invalid_argument::invalid_argument;
};
