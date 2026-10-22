#pragma once

#include "../headers/animal.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"

#include <iostream>
#include <memory>
#include <string_view>
#include <string>
#include <vector>

class VetClinic
{
private:
    std::vector<std::shared_ptr<Animal>> animal;
    std::vector<Vet> vet;
    std::vector<Appeals> appeals;
public:
    VetClinic();

    VetClinic(const VetClinic&) = delete;
    VetClinic& operator=(const VetClinic&) = delete;

    void setAnimal(std::shared_ptr<Animal> animalTemp);
    void setVet(const Vet& vetTemp);
    bool setAppeals(std::string_view vetSpeciality, std::string_view nameAnimal, std::string_view date, std::string_view diagnosis, std::string_view treatment);

    bool appointmentCheck(std::string_view vetSpeciality, const Animal& patient) const;

    void infoAnimal() const;
    void infoVet() const;
    void infoAppeals() const;

    VetClinic& operator+=(std::shared_ptr<Animal> ani);
    VetClinic& operator+=(const Vet& v);

    VetClinic& operator-=(const Animal& ani);
    VetClinic& operator-=(const Vet& v);
};