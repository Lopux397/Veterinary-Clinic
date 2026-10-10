#pragma once

#include "../headers/animal.h"
#include "../headers/vet.h"

#include <iostream>
#include <string>
#include <string_view>

class Appeals
{
private:
    Vet vet;
    Animal animal;
    std::string date;
    std::string diagnosis;
    std::string treatment;
public:
    Appeals();
    Appeals(const Vet& vetTemp, const Animal& animalTemp, std::string_view dateTemp, std::string_view diagnosisTemp, std::string_view treatmentTemp);

    void setVet(const Vet& vetTemp);
    void setAnimal(const Animal& animalTemp);
    void setDate(std::string_view dateTemp);
    void setDiagnosis(std::string_view diagnosisTemp);
    void setTreatment(std::string_view treatmentTemp);

    Vet getVet() const;
    Animal getAnimal() const;
    std::string getDate() const;
    std::string getDiagnosis() const;
    std::string getTreatment() const;

    friend std::ostream& operator<< (std::ostream& os, const Appeals& app)
    {
        os << app.vet.getSpeciality() << " " << app.vet.getName() << std::endl;
        os << app.animal.getView() << " " << app.animal.getName() << std::endl;
        os << app.date << std::endl;
        os << app.diagnosis << std::endl;
        os << app.treatment << std::endl;

        return os;
    }
};
