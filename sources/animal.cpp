#include "../headers/animal.h"

Animal::Animal(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp)
    : name(nameTemp), breed(breedTemp), age(ageTemp), owner(ownerTemp) {
}

void Animal::setName(std::string_view nameTemp) { name = nameTemp; }
void Animal::setBreed(std::string_view breedTemp) { breed = breedTemp; }
void Animal::setAge(unsigned int ageTemp) { age = ageTemp; }
void Animal::setOwner(std::string_view ownerTemp) { owner = ownerTemp; }

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
    std::getline(is, name);
    
    std::getline(is, breed);
    is >> age;
    skipLine(is);

    std::getline(is, owner);
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
