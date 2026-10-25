#include "../headers/cat.h"

Cat::Cat() : Animal("", "Cat", "", 0, "") {
}
Cat::Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, std::string_view furTemp)
    : Animal(nameTemp, "Cat", breedTemp, ageTemp, ownerTemp), fur(furTemp) {
}

void Cat::setFur(std::string_view furTemp) { fur = furTemp; }
std::string Cat::getFur() const { return fur; }

// Simplified model: 15 human years for the 1st year, 24 for the 2nd, +4 for every next year
unsigned int Cat::humanAge() const
{
    unsigned int years = getAge();

    if (years == 0) return 0;
    if (years == 1) return 15;

    return 24 + (years - 2) * 4;
}

std::string Cat::makeSound() const
{
    return "Meow!";
}

std::string Cat::careAdvice() const
{
    if (fur == "long") return Animal::careAdvice() + " Long fur should be brushed once a week.";

    return Animal::careAdvice();
}

void Cat::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Fur: " << fur << std::endl;
}

void Cat::read(std::istream& is)
{
    Animal::read(is);
    std::getline(is, fur);
}

std::string Cat::inputHint() const
{
    return Animal::inputHint() + " / fur length (short/long)";
}
