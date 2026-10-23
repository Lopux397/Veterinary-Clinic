#include "../headers/bird.h"

Bird::Bird() : Animal("", "Bird", "", 0, "") {
}
Bird::Bird(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int wingspanTemp)
    : Animal(nameTemp, "Bird", breedTemp, ageTemp, ownerTemp), wingspan(wingspanTemp) {
}

void Bird::setWingspan(unsigned int wingspanTemp) { wingspan = wingspanTemp; }
unsigned int Bird::getWingspan() const { return wingspan; }

std::string Bird::makeSound() const
{
    return "Tweet!";
}

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
    Animal::read(is);
    is >> wingspan;
    skipLine(is);
}

std::string Bird::inputHint() const
{
    return Animal::inputHint() + " / wingspan in cm";
}
