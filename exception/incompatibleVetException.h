#pragma once

#include <stdexcept>
#include <string>

class IncompatibleVetException : public std::logic_error //Исключение: несовместимый ветеринар
{
public:
	IncompatibleVetException(const std::string& msg) : std::logic_error(msg) {}
};