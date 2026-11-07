#pragma once

#include "../headers/animal.h"

class Dog : public Animal
{
private:
    unsigned int walksPerDay = 0; //количество прогулок в день
public:
    Dog();
    Dog(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, unsigned int walksPerDayTemp);

    void setWalksPerDay(unsigned int walksPerDayTemp);
    unsigned int getWalksPerDay() const;

    unsigned int weeklyWalkHours() const;

    double checkupPrice() const override;
    std::string getType() const override;

    std::string makeSound() const override;
    std::string careAdvice() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::string inputHint() const override;
};
