#pragma once

#include "../headers/animal.h"

class Bird : public Animal
{
private:
    bool canFly = true;
public:
    Bird();
    Bird(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, bool canFlyTemp);

    void setCanFly(bool canFlyTemp);
    bool getCanFly() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;
    bool canBeTreatedBy(std::string_view vetSpeciality) const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};
