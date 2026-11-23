#include "../headers/dog.h"
#include "../exception/invalidDataException.h"
#include "../exception/inputFormatException.h"

Dog::Dog() : Animal() {}
Dog::Dog(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int walksPerDayTemp)
    : Animal(nameTemp, breedTemp, ageTemp, ownerTemp), walksPerDay(walksPerDayTemp) 
{}

void Dog::setWalksPerDay(unsigned int walksPerDayTemp)
{ 
    if (walksPerDayTemp > 50)
        throw InvalidDataException("The walksPerDay cannot be too large");

    walksPerDay = walksPerDayTemp;
}
unsigned int Dog::getWalksPerDay() const { return walksPerDay; }

unsigned int Dog::weeklyWalkHours() const 
{
    return ((walksPerDay * 30 * 7) / 60);
}

double Dog::checkupPrice() const
{
    return 67 + weeklyWalkHours() * 2 + ((getAge() > 8) ? 15 : 0);
}

std::string Dog::getType() const { return "Dog"; }

std::string Dog::makeSound() const
{
    return "Woof!";
}

std::string Dog::careAdvice() const
{
    return Animal::careAdvice() + " Need to take out for a walk.";
}

void Dog::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Number of walks per day: " << walksPerDay << std::endl;
}

void Dog::read(std::istream& is)
{
    unsigned int walksPerDayTemp{};

    Animal::read(is);

    is >> walksPerDayTemp;
    if (is.fail())
    {
        skipLine(is);
        throw InputFormatException("Walks Per Day must be a number");
    }
    skipLine(is);
    setWalksPerDay(walksPerDayTemp);
}

std::string Dog::inputHint() const
{
    return Animal::inputHint() + " / number of walks per day";
}
