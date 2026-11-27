#pragma once

#include "../headers/vetClinic.h"

#include <string>
#include <string_view>

class ClinicStorage
{
private:
	std::string filePath;
	void checkFields(const std::vector<std::string>& fields, size_t expected, int lineNumber, std::string_view type);
public:
	explicit ClinicStorage(std::string_view filePathTemp);

	void save(const VetClinic& clinic) const;
	void load(VetClinic& clinic);
};