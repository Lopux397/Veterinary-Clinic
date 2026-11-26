#pragma once

#include <string>
#include <format>
#include <string_view>
#include <chrono>

class Logger 
{
private:
	std::string filePath;

	inline std::string curTimeStr() const
	{
		using namespace std::chrono;
		return std::format("{:%Y-%m-%d %H:%M:%S}", zoned_time{
				current_zone(), floor<seconds>(system_clock::now())});
	}

public:
	explicit Logger(std::string_view filePathTemp);

	void log(std::string_view message) const;
};