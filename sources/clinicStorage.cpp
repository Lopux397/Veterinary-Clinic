#include "../headers/clinicStorage.h"
#include "../exception/fileException.h"
#include "../exception/inputFormatException.h"
#include "../headers/bird.h"
#include "../headers/cat.h"
#include "../headers/dog.h"
#include "../headers/rodent.h"

#include <fstream>
#include <format>
#include <sstream>
#include <memory>
#include <vector>

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

void ClinicStorage::load(VetClinic& clinic)
{
	std::ifstream in(filePath, std::ios::in);

	if (!in.is_open())
		throw FileException("The file at the path '" + filePath + "' could not be opened");

	std::string line;
	int lineNumber = 0;

	while (std::getline(in, line))
	{
		++lineNumber;

		if (line.empty()) continue;               

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
			clinic.setVet(Vet(fields[0], fields[1]));

		}
		else if (type == "BIRD") 
		{
			checkFields(fields, 5, lineNumber, type);
			clinic.setAnimal(std::make_shared<Bird>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stoul(fields[4])));
		}
		else if (type == "CAT")
		{
			checkFields(fields, 5, lineNumber, type);
			clinic.setAnimal(std::make_shared<Cat>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stoul(fields[4])));
		}
		else if (type == "DOG")
		{
			checkFields(fields, 5, lineNumber, type);
			clinic.setAnimal(std::make_shared<Dog>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stoul(fields[4])));
		}
		else if (type == "RODENT")
		{
			checkFields(fields, 5, lineNumber, type);
			clinic.setAnimal(std::make_shared<Rodent>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stod(fields[4])));
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

	if (in.bad())
		throw FileException("Read error in file '" + filePath + "'");

	in.close();
	clinic.logEvent("INFO: State loaded from '" + filePath + "'");
}

void ClinicStorage::checkFields(const std::vector<std::string>& fields, size_t expected, int lineNumber, std::string_view type)
{
	if (fields.size() != expected)
		throw InputFormatException(std::format("Line {}: {} needs {} fields", lineNumber, type, expected));
}