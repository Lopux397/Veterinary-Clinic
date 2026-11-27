#include "../headers/report.h"
#include "../exception/fileException.h"

#include <fstream>
#include <iomanip>
#include <map>
#include <string>

Report::Report(std::string_view filePathTemp) : filePath(filePathTemp)
{

}

void Report::create(const VetClinic& clinic) const
{
	std::ofstream out(filePath, std::ios::out);

	if (!out.is_open())
		throw FileException("The file at the path '" + filePath + "' could not be opened");

	out << "========== VETERINARY CLINIC REPORT ==========\n\n";

	// 1. Врачи
	out << "--- Veterinarians (" << clinic.getVet().size() << ") ---\n";

	if (clinic.getVet().empty())
		out << "No veterinarians.\n";

	int number = 1;
	for (const auto& v : clinic.getVet())
	{
		out << number++ << ". " << v.getName() << " - " << v.getSpeciality() << '\n';
	}
	out << '\n';

	// 2. Животные
	out << "--- Animals (" << clinic.getAnimal().size() << ") ---\n";

	if (clinic.getAnimal().empty())
		out << "No animals.\n";

	number = 1;
	double totalPrice = 0;
	std::map<std::string, int> countByType;

	for (const auto& a : clinic.getAnimal())
	{
		out << number++ << ". "
			<< std::left << std::setw(8) << a->getType()
			<< std::setw(14) << a->getName()
			<< std::setw(20) << a->getBreed()
			<< "age " << std::setw(3) << a->getAge()
			<< "owner: " << std::setw(12) << a->getOwner()
			<< "checkup: " << std::fixed << std::setprecision(2) << a->checkupPrice() << '\n';

		totalPrice += a->checkupPrice();
		++countByType[a->getType()];
	}
	out << '\n';

	// 3. Обращения
	out << "--- Appeals (" << clinic.getAppeals().size() << ") ---\n";

	if (clinic.getAppeals().empty())
		out << "No appeals.\n";

	number = 1;
	for (const auto& ap : clinic.getAppeals())
	{
		out << number++ << ". " << ap.getDate() << '\n';
		out << "   Vet:       " << ap.getVet().getName() << " (" << ap.getVet().getSpeciality() << ")\n";

		if (ap.getAnimal())
			out << "   Animal:    " << ap.getAnimal()->getType() << " '" << ap.getAnimal()->getName()
			<< "', owner: " << ap.getAnimal()->getOwner() << '\n';
		else
			out << "   Animal:    -\n";

		out << "   Diagnosis: " << ap.getDiagnosis() << '\n';
		out << "   Treatment: " << ap.getTreatment() << '\n';
	}
	out << '\n';

	// 4. Итоги
	out << "--- Summary ---\n";
	out << "Veterinarians: " << clinic.getVet().size() << '\n';
	out << "Animals:       " << clinic.getAnimal().size() << '\n';

	for (const auto& [type, count] : countByType)
		out << "  " << type << ": " << count << '\n';

	out << "Appeals:       " << clinic.getAppeals().size() << '\n';
	out << "Total checkup price of all animals: " << std::fixed << std::setprecision(2) << totalPrice << '\n';

	if (!out)
		throw FileException("The file at the path '" + filePath + "' could not record");

	out.close();

	clinic.logEvent("INFO: Report written to '" + filePath + "'");
}