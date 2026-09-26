#include "animal.h"

Animal::Animal() = default;
Animal::Animal(std::string_view nameTemp, std::string_view viewTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp)
    : name(nameTemp), view(viewTemp), breed(breedTemp), age(ageTemp), owner(ownerTemp) {
}

void Animal::setName(std::string_view nameTemp) { name = nameTemp; }
void Animal::setView(std::string_view viewTemp) { view = viewTemp; }
void Animal::setBreed(std::string_view breedTemp) { breed = breedTemp; }
void Animal::setAge(unsigned int ageTemp) { age = ageTemp; }
void Animal::setOwner(std::string_view ownerTemp) { owner = ownerTemp; }

std::string Animal::getName() const { return name; }
std::string Animal::getView() const { return view; }
std::string Animal::getBreed() const { return breed; }
unsigned int Animal::getAge() const { return age; }
std::string Animal::getOwner() const { return owner; }

std::ostream& operator<< (std::ostream& os, const Animal& ani)
{
    os << ani.name << std::endl;
    os << ani.view << std::endl;
    os << ani.breed << std::endl;
    os << ani.age << std::endl;
    os << ani.owner << std::endl;

    return os;
}

std::istream& operator>> (std::istream& is, Animal& ani) 
{
    std::getline(is, ani.name);
    std::getline(is, ani.view);
    std::getline(is, ani.breed);
    is >> ani.age;

    is.clear();
    is.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
      
    std::getline(is, ani.owner);

    return is;
}

bool Animal::operator== (const Animal& ani) const
{
    return name == ani.name && owner == ani.owner;
}

bool Animal::operator< (const Animal& ani) const 
{
    return age < ani.age;
}