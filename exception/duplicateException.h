#pragma once

#include <stdexcept>

class DuplicateException : public std::runtime_error //Исключение: дубликат
{
public:
    using std::runtime_error::runtime_error;
};
