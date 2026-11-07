#include "../headers/cat.h"

Cat::Cat() : Animal("", "Cat", "", 0, "") {
}
Cat::Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int hairballsPerMonthTemp)
    : Animal(nameTemp, "Cat", breedTemp, ageTemp, ownerTemp), hairballsPerMonth(hairballsPerMonthTemp) {
}

void Cat::setHairballsPerMonth(unsigned int hairballsPerMonthTemp) { hairballsPerMonth = hairballsPerMonthTemp; }
unsigned int Cat::getHairballsPerMonth() const { return hairballsPerMonth; }

unsigned int Cat::groomingsPerWeek() const 
{
    return std::min((unsigned int)7, 1 + hairballsPerMonth / 2);
}

std::string Cat::makeSound() const
{
    return "Meow!";
}

std::string Cat::careAdvice() const
{
    return Animal::careAdvice() + " Monitor the condition of the coat.";
}

void Cat::print(std::ostream& os) const
{
    Animal::print(os);
    os << "HairballsPerMonth: " << hairballsPerMonth << std::endl;
}

void Cat::read(std::istream& is)
{
    Animal::read(is);
    is >> hairballsPerMonth;
    skipLine(is);
}

std::string Cat::inputHint() const
{
    return Animal::inputHint() + " / Number of hairballs per month";
}
