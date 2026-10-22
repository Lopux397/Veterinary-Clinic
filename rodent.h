#pragma once

#include "../headers/animal.h"

class Rodent : public Animal
{
private:
    double weight = 0.0;
public:
    Rodent();
    Rodent(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, double weightTemp);

    void setWeight(double weightTemp);
    double getWeight() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;
    bool canBeTreatedBy(std::string_view vetSpeciality) const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::string inputHint() const override;
};
