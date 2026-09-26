#include "vetClinic.h"

VetClinic::VetClinic() = default;

bool VetClinic::appointmentCheck(std::string_view vetSpeciality, std::string_view viewAnimal) const
{
    if (vetSpeciality == "Орнитолог" && viewAnimal != "Птица") return false;
    if (vetSpeciality == "Ратолог" && viewAnimal != "Грызун") return false;
    if (vetSpeciality == "Терапевт" && (viewAnimal == "Птица" || viewAnimal == "Грызун")) return false;

    return true;
}

void VetClinic::setAnimal(const Animal& animalTemp)
{
    animal.push_back(animalTemp);
}

void VetClinic::setVet(const Vet& vetTemp)
{
    vet.push_back(vetTemp);
}

bool VetClinic::setAppeals(std::string_view vetSpeciality, std::string_view nameAnimal, std::string_view date, const std::string_view diagnosis, std::string_view treatment)
{
    const Vet* addsDoc = nullptr;
    for (const auto& currentVet : vet)
    {
        if (currentVet.getSpeciality() == vetSpeciality)
        {
            addsDoc = &currentVet;
            break;
        }
    }
        
    if (!addsDoc)
    {
        std::cout<< "Vet not found" << std::endl;
        return false;
    }

    const Animal* addsAnimal = nullptr;
    for (const auto& currentAnimal : animal) 
    {
        if (currentAnimal.getName() == nameAnimal) {
            addsAnimal = &currentAnimal;
            break;
        }
    }

    if (!addsAnimal) 
    {
        std::cout << "Animal not found" << std::endl;
        return false;
    }

    if (!appointmentCheck(vetSpeciality, addsAnimal->getView())) 
    {
        std::cout << "A "<< vetSpeciality << " cannot treat a" << addsAnimal->getView() << std::endl;
        return false;
    }

    appeals.emplace_back(*addsDoc, *addsAnimal, date, diagnosis, treatment);
    
    return true;
}

void VetClinic::infoAnimal() const
{
    for (int i = 0; i < animal.size(); i++) 
    {
        std::cout << "========= Animal[" << i + 1 << "] =========" << std::endl;
        animal[i].info();
        std::cout << "=============================\n" << std::endl;
    }
}

void VetClinic::infoVet() const 
{
    for (int i = 0; i < vet.size(); i++)
    {
        std::cout << "========= Vet[" << i + 1 << "] =========" << std::endl;
        vet[i].info();
        std::cout << "==========================\n" << std::endl;
    }
}

void VetClinic::infoAppeals() const 
{
    for (int i = 0; i < appeals.size(); i++)
    {
        std::cout << "========= Appeals[" << i + 1 << "] =========" << std::endl;
        appeals[i].info();
        std::cout << "==============================\n" << std::endl;
    }
}