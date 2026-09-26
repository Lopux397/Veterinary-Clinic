#include "vet.h"

Vet::Vet() = default;
Vet::Vet(std::string_view nameTemp, std::string_view specialityTemp)
    : name(nameTemp), speciality(specialityTemp) {
}

void Vet::setName(std::string_view nameTemp) { name = nameTemp; }
void Vet::setSpeciality(std::string_view specialityTemp) { speciality = specialityTemp; }

std::string Vet::getName() const { return name; }
std::string Vet::getSpeciality() const { return speciality; }

std::ostream& operator<< (std::ostream& os, const Vet& v) 
{
    os << v.name << std::endl;
    os << v.speciality << std::endl;

    return os;
}

std::istream& operator>> (std::istream& is, Vet& v) 
{
    std::getline(is, v.name);
    std::getline(is, v.speciality);

    return is;
}

bool Vet::operator== (const Vet& v) const 
{
    return name == v.name;
}