#include "../headers/clinicStorage.h"
#include "../exception/fileException.h"
#include "../exception/inputFormatException.h"
#include "../headers/bird.h"
#include "../headers/cat.h"
#include "../headers/dog.h"
#include "../headers/rodent.h"

#include <fstream>
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
			if (fields.size() != 2)
				throw InputFormatException("Line " + std::to_string(lineNumber) + ": VET needs 2 fields");

			clinic.setVet(Vet(fields[0], fields[1]));

		}
		else if (type == "BIRD") 
		{
			if (fields.size() != 5)
				throw InputFormatException("Line " + std::to_string(lineNumber) + ": BIRD needs 5 fields");

			clinic.setAnimal(std::make_shared<Bird>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stoul(fields[4])));
		}
		else if (type == "CAT")
		{
			if (fields.size() != 5)
				throw InputFormatException("Line " + std::to_string(lineNumber) + ": CAT needs 5 fields");

			clinic.setAnimal(std::make_shared<Cat>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stoul(fields[4])));
		}
		else if (type == "DOG")
		{
			if (fields.size() != 5)
				throw InputFormatException("Line " + std::to_string(lineNumber) + ": DOG needs 5 fields");

			clinic.setAnimal(std::make_shared<Dog>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stoul(fields[4])));
		}
		else if (type == "RODENT")
		{
			if (fields.size() != 5)
				throw InputFormatException("Line " + std::to_string(lineNumber) + ": RODENT needs 5 fields");

			clinic.setAnimal(std::make_shared<Rodent>(fields[0], fields[1], std::stoul(fields[2]), fields[3], std::stod(fields[4])));
		}
		else if (type == "APPEALS")
		{
			if (fields.size() != 6)
				throw InputFormatException("Line " + std::to_string(lineNumber) + ": APPEALS needs 6 fields");

			clinic.setAppeals(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5]);
		}
		else
		{
			throw InputFormatException("Line " + std::to_string(lineNumber) + ": unknown record type '" + type + "'");
		}
	}

	if (in.bad())
		throw FileException("Read error in file '" + filePath + "'");

	in.close();
	clinic.logEvent("INFO: State loaded from '" + filePath + "'");
}

