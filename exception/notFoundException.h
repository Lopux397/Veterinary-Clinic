#pragma once

#include <stdexcept>
#include <string>

class NotFoundException : public std::runtime_error //Исключение «Не найдено»
{
public:
	explicit NotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};