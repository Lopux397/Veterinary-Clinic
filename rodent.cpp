#include "../headers/rodent.h"

Rodent::Rodent() : Rodent("", "", 0, "", 0) {
}
Rodent::Rodent(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int weightTemp)
    : Animal(nameTemp, "Грызун", breedTemp, ageTemp, ownerTemp), weight(weightTemp) {
}

void Rodent::setWeight(unsigned int weightTemp) { weight = weightTemp; }
unsigned int Rodent::getWeight() const { return weight; }

std::string Rodent::makeSound() const
{
    return "Пи-пи!";
}

std::string Rodent::careAdvice() const
{
    return Animal::careAdvice() + " Взвешивать при каждом осмотре, текущий вес: " + std::to_string(weight) + " г.";
}

bool Rodent::canBeTreatedBy(std::string_view vetSpeciality) const
{
    return vetSpeciality != "Терапевт" && vetSpeciality != "Орнитолог";
}

void Rodent::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Weight (g): " << weight << std::endl;
}

void Rodent::read(std::istream& is)
{
    Animal::read(is);
    is >> weight;
    skipLine(is);
}
