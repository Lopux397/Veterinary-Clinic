#include "../headers/vet.h"
#include "../exception/invalidDataException.h"

Vet::Vet() = default;
Vet::Vet(std::string_view nameTemp, std::string_view specialityTemp)
    : name(nameTemp), speciality(specialityTemp)
{}

void Vet::setName(std::string_view nameTemp)
{
    if (nameTemp.empty())
        throw InvalidDataException("The name cannot be empty");

    name = nameTemp;
}
void Vet::setSpeciality(std::string_view specialityTemp)
{ 
    if (specialityTemp.empty())
        throw InvalidDataException("The speciality cannot be empty");

    speciality = specialityTemp;
}

std::string Vet::getName() const { return name; }
std::string Vet::getSpeciality() const { return speciality; }

bool Vet::operator== (const Vet& v) const 
{
    return name == v.name;
}