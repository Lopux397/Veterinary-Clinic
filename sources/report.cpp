#include "../headers/report.h"
#include "../exception/fileException.h"

#include <fstream>

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
    int i = 1;
    for (const auto& v : clinic.getVet())
        out << i++ << ". " << v.getName() << " - " << v.getSpeciality() << '\n';
    out << '\n';
    // 2. Животные: цикл по clinic.getAnimal(), у каждого it->getType(), it->getName() и т.д.

    out << "--- Animals (" << clinic.getAnimal().size() << ") ---\n";
    i = 1;
    for (const auto& ani : clinic.getAnimal())
        out << i++ << ". " << ani->getType() << ": " << ani->getName() << " - " << ani->getOwner() << '\n';
    out << '\n';
    // 3. Обращения: цикл по clinic.getAppeals(), у каждого a.getDate(), a.getVet().getName(),
    //    a.getAnimal()->getName() (animal может быть nullptr, поэтому проверь)

    // 4. Итоги

    if (!out)
        throw FileException("The file at the path '" + filePath + "' could not record");

	out.close();
}