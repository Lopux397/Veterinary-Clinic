#include "../headers/dog.h"

Dog::Dog() : Animal("", "Dog", "", 0, "") {
}
Dog::Dog(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, bool vaccinatedTemp)
    : Animal(nameTemp, "Dog", breedTemp, ageTemp, ownerTemp), vaccinated(vaccinatedTemp) {
}

void Dog::setVaccinated(bool vaccinatedTemp) { vaccinated = vaccinatedTemp; }
bool Dog::isVaccinated() const { return vaccinated; }

// Simplified model: 15 human years for the 1st year, 24 for the 2nd, +5 for every next year
unsigned int Dog::humanAge() const
{
    unsigned int years = getAge();

    if (years == 0) return 0;
    if (years == 1) return 15;

    return 24 + (years - 2) * 5;
}

std::string Dog::makeSound() const
{
    return "Woof!";
}

std::string Dog::careAdvice() const
{
    std::string advice = Animal::careAdvice();
    if (!vaccinated) advice += " A rabies vaccination is needed.";

    return advice;
}

void Dog::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Rabies vaccinated: " << (vaccinated ? "yes" : "no") << std::endl;
}

void Dog::read(std::istream& is)
{
    Animal::read(is);
    vaccinated = readFlag(is);
}

std::string Dog::inputHint() const
{
    return Animal::inputHint() + " / rabies vaccinated (yes/no)";
}
