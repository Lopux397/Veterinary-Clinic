#include "vet.h"

Vet::Vet() = default;
Vet::Vet(std::string_view nameTemp, std::string_view specialityTemp)
    : name(nameTemp), speciality(specialityTemp) {
}

void Vet::setName(std::string_view nameTemp) { name = nameTemp; }
void Vet::setSpeciality(std::string_view specialityTemp) { speciality = specialityTemp; }

std::string Vet::getName() const { return name; }
std::string Vet::getSpeciality() const { return speciality; }

void Vet::info() const
{
    std::cout << "Name: " << name << "\nSpeciality: " << speciality << std::endl;
}