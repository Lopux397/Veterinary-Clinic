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

void Animal::info() const
{
    std::cout << "Name: " << name << "\nView: " << view << "\nBreed: " << breed << "\nAge: " << age << "\nOwner: " << owner << std::endl;
}