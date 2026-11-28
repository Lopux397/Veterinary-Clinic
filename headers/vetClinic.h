#pragma once

#include "../headers/animal.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/collection.h"
#include "../headers/logger.h"

#include <iostream>
#include <memory>
#include <string_view>
#include <string>
#include <vector>

class Report;
class ClinicStorage;

class VetClinic
{
private:
    Collection<std::shared_ptr<Animal>> animal;
    Collection<Vet> vet;
    Collection<Appeals> appeals;
    Logger* logger = nullptr;
    Report* report = nullptr;
    ClinicStorage* storage = nullptr;

    void removeAppealsOfAnimal(std::string_view name, std::string_view owner);
    void removeAppealsOfVet(std::string_view name);
public:
    explicit VetClinic(Logger* loggerTemp, Report* reportTemp, ClinicStorage* storageTemp);

    VetClinic(const VetClinic&) = delete;
    VetClinic& operator=(const VetClinic&) = delete;

    Collection<std::shared_ptr<Animal>>& getAnimal();
    Collection<Vet>& getVet();
    Collection<Appeals>& getAppeals();

    const Collection<std::shared_ptr<Animal>>& getAnimal() const;
    const Collection<Vet>& getVet() const;
    const Collection<Appeals>& getAppeals() const;

    void setAnimal(std::shared_ptr<Animal> animalTemp);
    void setVet(const Vet& vetTemp);
    bool setAppeals(std::string_view vetName, std::string_view animalName, std::string_view animalOwner, std::string_view date, std::string_view diagnosis, std::string_view treatment);
    void setLogger(Logger& loggerTemp);
    void setReport(Report& reportTemp);
    void setStorage(ClinicStorage& storageTemp);

    void logEvent(const std::string& message) const;
    bool repEvent() const;
    bool load();
    void save() const;

    bool appointmentCheck(std::string_view vetSpeciality, const Animal& patient) const;

    bool removeAnimal(std::string_view name, std::string_view owner);

    void infoAnimal() const;
    void infoVet() const;
    void infoAppeals() const;

    VetClinic& operator+=(std::shared_ptr<Animal> ani);
    VetClinic& operator+=(const Vet& v);

    VetClinic& operator-=(const Animal& ani);
    VetClinic& operator-=(const Vet& v);
};