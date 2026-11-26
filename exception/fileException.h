#pragma once

#include <stdexcept>

class FileException : public std::runtime_error //Исключение: всё что связано с файлами
{
public:
    using std::runtime_error::runtime_error;
};
