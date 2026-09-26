#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <limits>
#include <algorithm>

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

    friend std::ostream& operator<< (std::ostream& os, const Animal& ani);
    friend std::istream& operator>> (std::istream& is, Animal& ani);

    bool operator== (const Animal& ani) const;
    bool operator< (const Animal& ani) const;
};
