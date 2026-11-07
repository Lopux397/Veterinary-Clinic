#pragma once

#include "../headers/animal.h"
#include <algorithm>

class Cat : public Animal
{
private:
    unsigned int hairballsPerMonth = 0; //волосяные комки в месяц
public:
    Cat();
    Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int hairballsPerMonthTemp);

    void setHairballsPerMonth(unsigned int hairballsPerMonthTemp);
    unsigned int getHairballsPerMonth() const;
    
    unsigned int groomingsPerWeek() const;

    double checkupPrice() const override;

    std::string makeSound() const override;
    std::string careAdvice() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::string inputHint() const override;
};
