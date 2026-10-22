#pragma once

#include "../headers/animal.h"

class Cat : public Animal
{
private:
    bool indoor = true;
public:
    Cat();
    Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, bool indoorTemp);

    void setIndoor(bool indoorTemp);
    bool isIndoor() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};
