#pragma once

#include <stdexcept>
#include <string>

class OutOfRangeException : public std::out_of_range //Исключение выхода за пределы диапазона
{
public:
	explicit OutOfRangeException(const std::string& msg) : std::out_of_range(msg) {}
};