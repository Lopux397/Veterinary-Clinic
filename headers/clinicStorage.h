#pragma once

#include "../headers/vetClinic.h"

#include <string>
#include <string_view>

class ClinicStorage
{
private:
	std::string filePath;
public:
	explicit ClinicStorage(std::string_view filePathTemp);

	void save(const VetClinic& clinic) const;
	void load(VetClinic& clinic);
};