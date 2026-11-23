#pragma once

#include <stdexcept>

class IncompatibleVetException : public std::logic_error //Исключение: несовместимый ветеринар
{
public:
    using std::logic_error::logic_error;
};
