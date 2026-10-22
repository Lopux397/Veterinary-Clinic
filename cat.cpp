#include "../headers/cat.h"

Cat::Cat() : Cat("", "", 0, "", true) {
}
Cat::Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, bool indoorTemp)
    : Animal(nameTemp, "Кошка", breedTemp, ageTemp, ownerTemp), indoor(indoorTemp) {
}

void Cat::setIndoor(bool indoorTemp) { indoor = indoorTemp; }
bool Cat::isIndoor() const { return indoor; }

std::string Cat::makeSound() const
{
    return "Мяу!";
}

std::string Cat::careAdvice() const
{
    std::string advice = Animal::careAdvice();
    if (!indoor) advice += " Уличной кошке нужна регулярная обработка от клещей и блох.";

    return advice;
}

void Cat::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Indoor: " << (indoor ? "yes" : "no") << std::endl;
}

void Cat::read(std::istream& is)
{
    Animal::read(is);
    indoor = readFlag(is);
}
