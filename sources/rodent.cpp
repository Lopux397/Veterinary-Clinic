#include "../headers/rodent.h"

Rodent::Rodent() : Animal("", "Rodent", "", 0, "") {
}
Rodent::Rodent(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, double weightTemp)
    : Animal(nameTemp, "Rodent", breedTemp, ageTemp, ownerTemp), weight(weightTemp) {
}

void Rodent::setWeight(double weightTemp) { weight = weightTemp; }
double Rodent::getWeight() const { return weight; }

std::string Rodent::makeSound() const
{
    return "Squeak!";
}

std::string Rodent::careAdvice() const
{
    return Animal::careAdvice() + " Weigh at every checkup and monitor the teeth.";
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

std::string Rodent::inputHint() const
{
    return Animal::inputHint() + " / weight in grams";
}

bool Rodent::canBeTreatedBy(std::string_view vetSpeciality) const
{
    return vetSpeciality != "Therapist" && vetSpeciality != "Ornithologist";
}
