#pragma once

#include "../headers/animal.h"

class Rodent : public Animal
{
private:
    unsigned int weight = 0;
public:
    Rodent();
    Rodent(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int weightTemp);

    void setWeight(unsigned int weightTemp);
    unsigned int getWeight() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;
    bool canBeTreatedBy(std::string_view vetSpeciality) const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};
