#pragma once

#include "../headers/vetClinic.h"

#include <string>
#include <string_view>

class Report 
{
private:
	std::string filePath;
public:
	explicit Report(std::string_view filePathTemp);

	void create(const VetClinic& clinic) const;
};