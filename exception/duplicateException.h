#pragma once

#include <stdexcept>
#include <string>

class DuplicateException : public std::runtime_error //Исключение: дубликат
{
public:
	explicit DuplicateException(const std::string& msg) : std::runtime_error(msg) {}
};