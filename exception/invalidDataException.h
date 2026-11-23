#pragma once

#include <stdexcept>
#include <string>

class InvalidDataException : public std::invalid_argument //Исключение: недопустимые данные
{
public:
	explicit InvalidDataException(const std::string& msg) : std::invalid_argument(msg) {}
};