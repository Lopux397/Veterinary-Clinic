#pragma once

#include "../headers/animal.h"

class Cat : public Animal
{
private:
    unsigned int outdoorHours = 0; //Часы вне дома
public:
    Cat();
    Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int outdoorHoursTemp);

    void setOutdoorHours(unsigned int outdoorHoursTemp);
    unsigned int getOutdoorHours() const;
    
    unsigned int parasiteTreatmentsPerYear() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::string inputHint() const override;
};
