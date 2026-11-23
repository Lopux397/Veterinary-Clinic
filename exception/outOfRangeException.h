#pragma once

#include <stdexcept>

class OutOfRangeException : public std::out_of_range //Исключение выхода за пределы диапазона
{
public:
    using std::out_of_range::out_of_range;
};
