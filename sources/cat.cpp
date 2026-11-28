#include "../headers/cat.h"
#include "../exception/invalidDataException.h"
#include "../exception/inputFormatException.h"

Cat::Cat() : Animal() {}
Cat::Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int hairballsPerMonthTemp)
    : Animal(nameTemp, breedTemp, ageTemp, ownerTemp)
{
    setHairballsPerMonth(hairballsPerMonthTemp);
}

void Cat::setHairballsPerMonth(unsigned int hairballsPerMonthTemp)
{
    if (hairballsPerMonthTemp > 30)
        throw InvalidDataException("The hairballsPerMonth cannot be too large");

    hairballsPerMonth = hairballsPerMonthTemp;
}
unsigned int Cat::getHairballsPerMonth() const { return hairballsPerMonth; }

unsigned int Cat::groomingsPerWeek() const 
{
    return std::min((unsigned int)7, 1 + hairballsPerMonth / 2);
}

double Cat::checkupPrice() const 
{
    return 67 + groomingsPerWeek() * 4;
}

std::string Cat::getType() const { return "Cat"; }

std::string Cat::makeSound() const
{
    return "Meow!";
}

std::string Cat::careAdvice() const
{
    return std::format("{} Brush the cat {} times a week.", Animal::careAdvice(), groomingsPerWeek());
}

void Cat::print(std::ostream& os) const
{
    Animal::print(os);
    os << "HairballsPerMonth: " << hairballsPerMonth << std::endl;
}

void Cat::read(std::istream& is)
{
    unsigned int hairballsPerMonthTemp{};

    Animal::read(is);

    is >> hairballsPerMonthTemp;
    if (is.fail())
    {
        skipLine(is);
        throw InputFormatException("Hairballs Per Month must be a number");
    }
    skipLine(is);
    setHairballsPerMonth(hairballsPerMonthTemp);
}

std::string Cat::inputHint() const
{
    return Animal::inputHint() + " / Number of hairballs per month";
}

void Cat::save(std::ostream& os) const
{
    os << "CAT" << "#";
    Animal::save(os);
    os << hairballsPerMonth;
}