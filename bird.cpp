#include "../headers/bird.h"

Bird::Bird() : Bird("", "", 0, "", true) {
}
Bird::Bird(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, bool canFlyTemp)
    : Animal(nameTemp, "Птица", breedTemp, ageTemp, ownerTemp), canFly(canFlyTemp) {
}

void Bird::setCanFly(bool canFlyTemp) { canFly = canFlyTemp; }
bool Bird::getCanFly() const { return canFly; }

std::string Bird::makeSound() const
{
    return "Чирик!";
}

std::string Bird::careAdvice() const
{
    std::string advice = Animal::careAdvice();
    if (!canFly) advice += " Птица не летает: проверить крылья и лапы.";

    return advice;
}

bool Bird::canBeTreatedBy(std::string_view vetSpeciality) const
{
    return vetSpeciality != "Терапевт" && vetSpeciality != "Ратолог";
}

void Bird::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Can fly: " << (canFly ? "yes" : "no") << std::endl;
}

void Bird::read(std::istream& is)
{
    Animal::read(is);
    canFly = readFlag(is);
}
