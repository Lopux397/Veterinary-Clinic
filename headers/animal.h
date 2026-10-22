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
    unsigned int age = 0;
    std::string owner;
protected:
    static bool readFlag(std::istream& is);
    static void skipLine(std::istream& is);

    template <typename T>
    static void readNumber(std::istream& is, T& value)
    {
        is >> value;
        skipLine(is);
    }
public:
    Animal();
    Animal(std::string_view nameTemp, std::string_view viewTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp);

    Animal(const Animal&) = default;
    Animal& operator=(const Animal&) = default;
    Animal(Animal&&) = default;
    Animal& operator=(Animal&&) = default;
    virtual ~Animal() = default;
    
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

    virtual std::string makeSound() const;
    virtual std::string careAdvice() const;
    virtual bool canBeTreatedBy(std::string_view vetSpeciality) const;

    virtual void print(std::ostream& os) const;
    virtual void read(std::istream& is);
    virtual std::string inputHint() const;

    friend std::ostream& operator<< (std::ostream& os, const Animal& ani)
    {
        ani.print(os);

        return os;
    }
    friend std::istream& operator>> (std::istream& is, Animal& ani)
    {
        ani.read(is);

        return is;
    }

    bool operator== (const Animal& ani) const;
    std::strong_ordering operator<=> (const Animal& ani) const;
};
