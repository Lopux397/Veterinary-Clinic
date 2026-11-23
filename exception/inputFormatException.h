#pragma once

#include <stdexcept>

class InputFormatException : public std::runtime_error //Исключение при форматировании входных данных
{
public:
    using std::runtime_error::runtime_error;
};
