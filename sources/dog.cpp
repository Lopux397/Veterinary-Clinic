#include "../headers/dog.h"

Dog::Dog() : Animal("", "Dog", "", 0, "") {
}
Dog::Dog(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, bool vaccinatedTemp)
    : Animal(nameTemp, "Dog", breedTemp, ageTemp, ownerTemp), vaccinated(vaccinatedTemp) {
}

void Dog::setVaccinated(bool vaccinatedTemp) { vaccinated = vaccinatedTemp; }
bool Dog::isVaccinated() const { return vaccinated; }

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
