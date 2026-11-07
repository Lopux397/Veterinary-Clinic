#include "../headers/rodent.h"

Rodent::Rodent() : Animal("", "Rodent", "", 0, "") {
}
Rodent::Rodent(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, double incisorLengthTemp)
    : Animal(nameTemp, "Rodent", breedTemp, ageTemp, ownerTemp), incisorLength(incisorLengthTemp) {
}

void Rodent::setIncisorLength(double incisorLengthTemp) { incisorLength = incisorLengthTemp; }
double Rodent::getIncisorLength() const { return incisorLength; }

unsigned int Rodent::daysUntilDentalTrim() const
{
    if (incisorLength > 35) return 0;

    return (unsigned int)((35 - incisorLength) / 0.275);
}

double Rodent::checkupPrice() const 
{
    return 67 + (daysUntilDentalTrim() == 0) ? 20 : 0;
}

std::string Rodent::makeSound() const
{
    return "Squeak!";
}

std::string Rodent::careAdvice() const
{
    return Animal::careAdvice() + " Monitor the condition and length of the teeth.";
}

void Rodent::print(std::ostream& os) const
{
    Animal::print(os);
    os << "IncisorLength (mm): " << incisorLength << std::endl;
}

void Rodent::read(std::istream& is)
{
    Animal::read(is);
    is >> incisorLength;
    skipLine(is);
}

std::string Rodent::inputHint() const
{
    return Animal::inputHint() + " / Incisor Length in mm";
}

bool Rodent::canBeTreatedBy(std::string_view vetSpeciality) const
{
    return vetSpeciality != "Therapist" && vetSpeciality != "Ornithologist";
}
