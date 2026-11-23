#include "../headers/animal.h"
#include "../exception/invalidDataException.h"
#include "../exception/inputFormatException.h"

Animal::Animal(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp)
    : name(nameTemp), breed(breedTemp), age(ageTemp), owner(ownerTemp)
{}

void Animal::setName(std::string_view nameTemp)
{
    if (nameTemp.empty())
        throw InvalidDataException("The name cannot be empty");

    name = nameTemp;
}
void Animal::setBreed(std::string_view breedTemp)
{
    if (breedTemp.empty())
        throw InvalidDataException("The breed cannot be empty");

    breed = breedTemp;
}
void Animal::setAge(unsigned int ageTemp)
{ 
    if (ageTemp < 0)
        throw InvalidDataException("The age cannot be negative");
    if (ageTemp > 30)
        throw InvalidDataException("The age cannot be too large");

    age = ageTemp;
}
void Animal::setOwner(std::string_view ownerTemp)
{ 
    if (ownerTemp.empty())
        throw InvalidDataException("The owner cannot be empty");

    owner = ownerTemp;
}

std::string Animal::getName() const { return name; }
std::string Animal::getBreed() const { return breed; }
unsigned int Animal::getAge() const { return age; }
std::string Animal::getOwner() const { return owner; }

void Animal::skipLine(std::istream& is)
{
    is.clear();
    is.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

std::string Animal::careAdvice() const
{
    return "Routine checkup once a year.";
}

bool Animal::canBeTreatedBy(std::string_view vetSpeciality) const
{
    return vetSpeciality != "Ornithologist" && vetSpeciality != "Rodentologist";
}

void Animal::print(std::ostream& os) const
{
    os << name << std::endl;
    os << getType() << std::endl;
    os << breed << std::endl;
    os << age << std::endl;
    os << owner << std::endl;
}

void Animal::read(std::istream& is)
{
    std::string nameTemp, breedTemp, ownerTemp;
    unsigned int ageTemp{};

    std::getline(is, nameTemp);
    setName(nameTemp);

    std::getline(is, breedTemp);
    setBreed(breedTemp);

    is >> ageTemp;
    if (is.fail()) 
    {
        skipLine(is);
        throw InputFormatException("Age must be a number");
    }
    skipLine(is);
    setAge(ageTemp);

    std::getline(is, ownerTemp);
    setOwner(ownerTemp);
}

std::string Animal::inputHint() const
{
    return "name / breed / age / owner";
}

bool Animal::operator== (const Animal& ani) const
{
    return name == ani.name && owner == ani.owner;
}

std::strong_ordering Animal::operator<=> (const Animal& ani) const
{
    return age <=> ani.age;
}
