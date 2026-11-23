#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

class Vet
{
private:
    std::string name;
    std::string speciality;
public:
    Vet();
    Vet(std::string_view nameTemp, std::string_view specialityTemp);

    void setName(std::string_view nameTemp);
    void setSpeciality(std::string_view specialityTemp);

    std::string getName() const;
    std::string getSpeciality() const;

    friend std::ostream& operator<< (std::ostream& os, const Vet& v)
    {
        os << v.name << std::endl;
        os << v.speciality << std::endl;

        return os;
    }
    friend std::istream& operator>> (std::istream& is, Vet& v)
    {
        std::string nameTemp, specialityTemp;

        std::getline(is, nameTemp);
        v.setName(nameTemp);
        std::getline(is, specialityTemp);
        v.setSpeciality(specialityTemp);

        return is;
    }

    bool operator== (const Vet& v) const;
};

