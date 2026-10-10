#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <limits>
#include <algorithm>
#include <compare>

class Animal
{
private:
    std::string name;
    std::string view;
    std::string breed;
    unsigned int age;
    std::string owner;
public:
    Animal();
    Animal(std::string_view nameTemp, std::string_view viewTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp);
    
    void setName(std::string_view nameTemp);
    void setView(std::string_view viewTemp);
    void setBreed(std::string_view breedTemp);
    void setAge(const unsigned int ageTemp);
    void setOwner(std::string_view ownerTemp);

    std::string getName() const;
    std::string getView() const;
    std::string getBreed() const;
    unsigned int getAge() const;
    std::string getOwner() const;

    friend std::ostream& operator<< (std::ostream& os, const Animal& ani)
    {
        os << ani.name << std::endl;
        os << ani.view << std::endl;
        os << ani.breed << std::endl;
        os << ani.age << std::endl;
        os << ani.owner << std::endl;

        return os;
    }
    friend std::istream& operator>> (std::istream& is, Animal& ani)
    {
        std::getline(is, ani.name);
        std::getline(is, ani.view);
        std::getline(is, ani.breed);
        is >> ani.age;

        is.clear();
        is.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        std::getline(is, ani.owner);

        return is;
    }

    bool operator== (const Animal& ani) const;
    std::strong_ordering operator<=> (const Animal& ani) const;
};
