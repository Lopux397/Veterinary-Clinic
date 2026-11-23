#pragma once

#include <stdexcept>
#include <string>

class InputFormatException : public std::runtime_error //Исключение при форматировании входных данных
{
public:
	InputFormatException(const std::string& msg) : std::runtime_error(msg) {}
};