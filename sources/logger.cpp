#include "../headers/logger.h"
#include "../exception/fileException.h"

#include <fstream>

Logger::Logger(std::string_view filePathTemp) : filePath(filePathTemp)
{
	
}

void Logger::log(std::string_view message) const
{
	std::ofstream out(filePath, std::ios::app);

	if (!out.is_open())
		throw FileException("The file at the path '" + filePath + "' could not be opened");

	out << "[" << curTimeStr() << "] " << std::string(message) << std::endl;

	if (!out)
		throw FileException("The file at the path '" + filePath + "' could not record");

	out.close();
}