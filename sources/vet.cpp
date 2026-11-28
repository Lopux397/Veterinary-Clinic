#include "../headers/vet.h"
#include "../exception/invalidDataException.h"
#include "../headers/validation.h"

Vet::Vet() = default;
Vet::Vet(std::string_view nameTemp, std::string_view specialityTemp)
    : name(nameTemp), speciality(specialityTemp)
{}

void Vet::setName(std::string_view nameTemp)
{
    if (nameTemp.empty())
        throw InvalidDataException("The name cannot be empty");

    checkNoSeparator(nameTemp, "name");
    name = nameTemp;
}
void Vet::setSpeciality(std::string_view specialityTemp)
{ 
    if (specialityTemp.empty())
        throw InvalidDataException("The speciality cannot be empty");

    checkNoSeparator(specialityTemp, "speciality");
    speciality = specialityTemp;
}

std::string Vet::getName() const { return name; }
std::string Vet::getSpeciality() const { return speciality; }

void Vet::save(std::ostream& os) const
{
    os << "VET#" << name << "#" << speciality;
}

bool Vet::operator== (const Vet& v) const 
{
    return name == v.name;
}