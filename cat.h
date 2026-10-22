#pragma once

#include "../headers/animal.h"

class Cat : public Animal
{
private:
    std::string fur;
public:
    Cat();
    Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, std::string_view furTemp);

    void setFur(std::string_view furTemp);
    std::string getFur() const;

    std::string makeSound() const override;
    std::string careAdvice() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::string inputHint() const override;
};
