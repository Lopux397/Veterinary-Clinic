#pragma once

#include "../headers/vetClinic.h"

#include <string>
#include <string_view>

class ClinicStorage
{
private:
	std::string filePath;

	void loadLine(VetClinic& clinic, const std::string& line, int lineNumber) const;
	void checkFields(const std::vector<std::string>& fields, size_t expected, int lineNumber, std::string_view type) const;

	unsigned int parseUnsigned(const std::string& text, int lineNumber, std::string_view fieldName) const;
	double parseDouble(const std::string& text, int lineNumber, std::string_view fieldName) const;
public:
	explicit ClinicStorage(std::string_view filePathTemp);

	void save(const VetClinic& clinic) const;
	void load(VetClinic& clinic) const;
};