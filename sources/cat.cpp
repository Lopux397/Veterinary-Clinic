#include "../headers/cat.h"

Cat::Cat() : Animal("", "Cat", "", 0, "") {
}
Cat::Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int outdoorHoursTemp)
    : Animal(nameTemp, "Cat", breedTemp, ageTemp, ownerTemp), outdoorHours(outdoorHoursTemp) {
}

void Cat::setOutdoorHours(unsigned int outdoorHoursTemp) { outdoorHours = outdoorHoursTemp; }
unsigned int Cat::getOutdoorHours() const { return outdoorHours; }

unsigned int Cat::parasiteTreatmentsPerYear() const 
{
    return (2 + (outdoorHours / 2));
}

std::string Cat::makeSound() const
{
    return "Meow!";
}

std::string Cat::careAdvice() const
{
    return Animal::careAdvice() + " Keep track of the number of parasite treatments per year.";
}

void Cat::print(std::ostream& os) const
{
    Animal::print(os);
    os << "OutdoorHours: " << outdoorHours << std::endl;
}

void Cat::read(std::istream& is)
{
    Animal::read(is);
    is >> outdoorHours;
    skipLine(is);
}

std::string Cat::inputHint() const
{
    return Animal::inputHint() + " / Number of hours spent away from home";
}
