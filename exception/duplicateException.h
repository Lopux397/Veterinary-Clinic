#pragma once

#include <stdexcept>
#include <string>

class DuplicateException : public std::runtime_error //Исключение: дубликат
{
public:
	DuplicateException(const std::string& msg) : std::runtime_error(msg) {}
};