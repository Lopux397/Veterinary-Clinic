#include "../headers/bird.h"
#include "../exception/invalidDataException.h"
#include "../exception/inputFormatException.h"

Bird::Bird() : Animal() {}
Bird::Bird(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int wingspanTemp)
    : Animal(nameTemp, breedTemp, ageTemp, ownerTemp), wingspan(wingspanTemp) 
{}

void Bird::setWingspan(unsigned int wingspanTemp) 
{
    if (wingspanTemp > 350)
        throw InvalidDataException("The wingspan cannot be too large");

    wingspan = wingspanTemp;
}
unsigned int Bird::getWingspan() const { return wingspan; }

unsigned int Bird::minCageWidth() const
{
    return wingspan * 2;
}

std::string Bird::makeSound() const
{
    return "Tweet!";
}

double Bird::checkupPrice() const 
{
    return 67 + wingspan * 0.5 + ((getWingspan() > 50) ? 25 : 0);
}

std::string Bird::getType() const { return "Bird"; }

std::string Bird::careAdvice() const
{
    if (wingspan > 50) return Animal::careAdvice() + " A large bird needs a spacious aviary.";

    return Animal::careAdvice();
}

bool Bird::canBeTreatedBy(std::string_view vetSpeciality) const
{
    return vetSpeciality != "Therapist" && vetSpeciality != "Rodentologist";
}

void Bird::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Wingspan (cm): " << wingspan << std::endl;
}

void Bird::read(std::istream& is)
{
    unsigned int wingspanTemp{};

    Animal::read(is);

    is >> wingspanTemp;
    if (is.fail()) 
    {
        skipLine(is);
        throw InputFormatException("Wingspan must be a number");
    }
    skipLine(is);
    setWingspan(wingspanTemp);
}

std::string Bird::inputHint() const
{
    return Animal::inputHint() + " / wingspan in cm";
}

void Bird::save(std::ostream& os) const 
{
    os << "BIRD" << "#";
    Animal::save(os);
    os << wingspan;
}
