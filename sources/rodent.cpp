#include "../headers/rodent.h"
#include "../exception/invalidDataException.h"
#include "../exception/inputFormatException.h"

Rodent::Rodent() : Animal() {}
Rodent::Rodent(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, double incisorLengthTemp)
    : Animal(nameTemp, breedTemp, ageTemp, ownerTemp), incisorLength(incisorLengthTemp) 
{}

void Rodent::setIncisorLength(double incisorLengthTemp)
{ 
    if (incisorLengthTemp < 0)
        throw InvalidDataException("The incisorLength cannot be negative");
    if (incisorLengthTemp > 1000)
        throw InvalidDataException("The incisorLength cannot be too large");

    incisorLength = incisorLengthTemp;
}
double Rodent::getIncisorLength() const { return incisorLength; }

unsigned int Rodent::daysUntilDentalTrim() const
{
    if (incisorLength > 35) return 0;

    return (unsigned int)((35 - incisorLength) / 0.275);
}

double Rodent::checkupPrice() const 
{
    return 67 + ((daysUntilDentalTrim() == 0) ? 20 : 0);
}

std::string Rodent::getType() const { return "Rodent"; }

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
    double incisorLengthTemp{};

    Animal::read(is);

    is >> incisorLengthTemp;
    if (is.fail())
    {
        skipLine(is);
        throw InputFormatException("Incisor length must be a number");
    }
    skipLine(is);
    setIncisorLength(incisorLengthTemp);
}

std::string Rodent::inputHint() const
{
    return Animal::inputHint() + " / Incisor Length in mm";
}

bool Rodent::canBeTreatedBy(std::string_view vetSpeciality) const
{
    return vetSpeciality != "Therapist" && vetSpeciality != "Ornithologist";
}

void Rodent::save(std::ostream& os) const
{
    os << "RODENT" << "#";
    Animal::save(os);
    os << incisorLength;
}