#pragma once

#include "../headers/animal.h"

class Dog : public Animal
{
private:
    bool vaccinated = false;
public:
    Dog();
    Dog(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, bool vaccinatedTemp);

    void setVaccinated(bool vaccinatedTemp);
    bool isVaccinated() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};
