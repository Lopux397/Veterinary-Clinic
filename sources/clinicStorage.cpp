#include "../headers/clinicStorage.h"
#include "../exception/fileException.h"
#include "../exception/inputFormatException.h"
#include "../headers/bird.h"
#include "../headers/cat.h"
#include "../headers/dog.h"
#include "../headers/rodent.h"

#include <filesystem>
#include <system_error>
#include <fstream>
#include <format>
#include <sstream>
#include <memory>
#include <vector>
#include <stdexcept>
#include  <cmath>
#include <limits> 

ClinicStorage::ClinicStorage(std::string_view filePathTemp) : filePath(filePathTemp)
{
	
}

void ClinicStorage::save(const VetClinic& clinic) const 
{
	std::ofstream out(filePath, std::ios::out);

	if (!out.is_open())
		throw FileException("The file at the path '" + filePath + "' could not be opened");

	for (const auto& it : clinic.getVet()) 
	{
		it.save(out);
		out << std::endl;
	}

	for (const auto& it : clinic.getAnimal())
	{
		it->save(out);
		out << std::endl;
	}

	for (const auto& it : clinic.getAppeals()) 
	{
		it.save(out);
		out << std::endl;
	}

	if (!out)
		throw FileException("The file at the path '" + filePath + "' could not record");

	out.close();

	clinic.logEvent("INFO: State saved to '" + filePath + "'");
}

void ClinicStorage::load(VetClinic& clinic) const
{
	if (std::error_code ec; !std::filesystem::exists(filePath, ec))
	{
		// first run: there is no saved state yet, this is not an error
		clinic.logEvent("INFO: No saved state found at '" + filePath + "', starting empty");
		return;
	}

	std::ifstream in(filePath, std::ios::in);

	if (!in.is_open())
		throw FileException("The file at the path '" + filePath + "' could not be opened");

	std::string line;
	int lineNumber = 0;

	while (std::getline(in, line))
	{
		++lineNumber;

		if (!line.empty() && line.back() == '\r')
			line.pop_back();

		if (line.empty()) continue;

		try
		{
			loadLine(clinic, line, lineNumber);
		}
		catch (const InputFormatException&)
		{
			throw;
		}
		catch (const std::exception& e)
		{
			// any other problem (duplicate, invalid value, missing vet/animal, ...) gets its line number
			throw InputFormatException(std::format("Line {}: {}", lineNumber, e.what()));
		}
	}

	if (in.bad())
		throw FileException("Read error in file '" + filePath + "'");

	in.close();
	clinic.logEvent("INFO: State loaded from '" + filePath + "'");
}

void ClinicStorage::loadLine(VetClinic& clinic, const std::string& line, int lineNumber) const
{
	std::istringstream ss(line);
	std::string type;
	std::getline(ss, type, '#');

	std::vector<std::string> fields;
	std::string field;
	while (std::getline(ss, field, '#'))
		fields.push_back(field);

	if (type == "VET")
	{
		checkFields(fields, 2, lineNumber, type);

		Vet v;
		v.setName(fields[0]);
		v.setSpeciality(fields[1]);
		clinic.setVet(v);
	}
	else if (type == "BIRD")
	{
		checkFields(fields, 5, lineNumber, type);
		clinic.setAnimal(std::make_shared<Bird>(fields[0], fields[1], parseUnsigned(fields[2], lineNumber, "age"),
			fields[3], parseUnsigned(fields[4], lineNumber, "wingspan")));
	}
	else if (type == "CAT")
	{
		checkFields(fields, 5, lineNumber, type);
		clinic.setAnimal(std::make_shared<Cat>(fields[0], fields[1], parseUnsigned(fields[2], lineNumber, "age"),
			fields[3], parseUnsigned(fields[4], lineNumber, "hairballs per month")));
	}
	else if (type == "DOG")
	{
		checkFields(fields, 5, lineNumber, type);
		clinic.setAnimal(std::make_shared<Dog>(fields[0], fields[1], parseUnsigned(fields[2], lineNumber, "age"),
			fields[3], parseUnsigned(fields[4], lineNumber, "walks per day")));
	}
	else if (type == "RODENT")
	{
		checkFields(fields, 5, lineNumber, type);
		clinic.setAnimal(std::make_shared<Rodent>(fields[0], fields[1], parseUnsigned(fields[2], lineNumber, "age"),
			fields[3], parseDouble(fields[4], lineNumber, "incisor length")));
	}
	else if (type == "APPEALS")
	{
		checkFields(fields, 6, lineNumber, type);
		clinic.setAppeals(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5]);
	}
	else
	{
		throw InputFormatException(std::format("Line {}: unknown record type '{}'", lineNumber, type));
	}
}

void ClinicStorage::checkFields(const std::vector<std::string>& fields, size_t expected, int lineNumber, std::string_view type) const
{
	if (fields.size() != expected)
		throw InputFormatException(std::format("Line {}: {} needs {} fields", lineNumber, type, expected));
}

unsigned int ClinicStorage::parseUnsigned(const std::string& text, int lineNumber, std::string_view fieldName) const
{
	try
	{
		size_t pos = 0;
		if (text.empty() || text[0] == '-')
			throw std::invalid_argument("bad number");

		unsigned long value = std::stoul(text, &pos);
		if (pos != text.size() || value > std::numeric_limits<unsigned int>::max())
			throw std::invalid_argument("bad number");

		return static_cast<unsigned int>(value);
	}
	catch (const std::logic_error&)
	{
		throw InputFormatException(std::format("Line {}: {} must be a non-negative number, got '{}'", lineNumber, fieldName, text));
	}
}

double ClinicStorage::parseDouble(const std::string& text, int lineNumber, std::string_view fieldName) const
{
	try
	{
		size_t pos = 0;
		double value = std::stod(text, &pos);
		if (pos != text.size() || !std::isfinite(value))
			throw std::invalid_argument("bad number");

		return value;
	}
	catch (const std::logic_error&)
	{
		throw InputFormatException(std::format("Line {}: {} must be a number, got '{}'", lineNumber, fieldName, text));
	}
}