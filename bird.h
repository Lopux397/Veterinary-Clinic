#pragma once

#include "../headers/animal.h"

class Bird : public Animal
{
private:
    unsigned int wingspan = 0;
public:
    Bird();
    Bird(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int wingspanTemp);

    void setWingspan(unsigned int wingspanTemp);
    unsigned int getWingspan() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;
    bool canBeTreatedBy(std::string_view vetSpeciality) const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::string inputHint() const override;
};
