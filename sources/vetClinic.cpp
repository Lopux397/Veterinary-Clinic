#include "../headers/vetClinic.h"

VetClinic::VetClinic() = default;

bool VetClinic::appointmentCheck(std::string_view vetSpeciality, const Animal& patient) const
{
    return patient.canBeTreatedBy(vetSpeciality);
}

bool VetClinic::removeAnimal(std::string_view name, std::string_view owner)
{
    bool removed = animal.removeIf(
        [&name, &owner](const std::shared_ptr<Animal>& current)
        {
            return current->getName() == name && current->getOwner() == owner;
        });

    if (!removed)
        std::cout << "Animal not found!" << std::endl;

    return removed;
}

void VetClinic::setAnimal(std::shared_ptr<Animal> animalTemp)
{
    if (!animalTemp) return;

    animal.add(animalTemp);
    std::sort(animal.begin(), animal.end(), [](const std::shared_ptr<Animal>& a, const std::shared_ptr<Animal>& b) { return *a < *b; });
}

void VetClinic::setVet(const Vet& vetTemp)
{
    vet.add(vetTemp);
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

    std::shared_ptr<Animal> addsAnimal;
    for (const auto& currentAnimal : animal) 
    {
        if (currentAnimal->getName() == nameAnimal) {
            addsAnimal = currentAnimal;
            break;
        }
    }

    if (!addsAnimal) 
    {
        std::cout << "Animal not found" << std::endl;
        return false;
    }

    if (!appointmentCheck(vetSpeciality, *addsAnimal)) 
    {
        std::cout << "A "<< vetSpeciality << " cannot treat a " << addsAnimal->getType() << std::endl;
        return false;
    }

    appeals.add(Appeals(*addsDoc, addsAnimal, date, diagnosis, treatment));
    
    return true;
}

void VetClinic::infoAnimal() const
{
    for (int i = 0; i < animal.size(); i++) 
    {
        std::cout << "========= Animal[" << i + 1 << "] =========" << std::endl;
        std::cout << *animal[i];
        std::cout << "=============================\n" << std::endl;
    }
}

void VetClinic::infoVet() const 
{
    for (int i = 0; i < vet.size(); i++)
    {
        std::cout << "========= Vet[" << i + 1 << "] =========" << std::endl;
        std::cout << vet[i];
        std::cout << "==========================\n" << std::endl;
    }
}

void VetClinic::infoAppeals() const 
{
    for (int i = 0; i < appeals.size(); i++)
    {
        std::cout << "========= Appeals[" << i + 1 << "] =========" << std::endl;
        std::cout << appeals[i];
        std::cout << "==============================\n" << std::endl;
    }
}

VetClinic& VetClinic::operator+=(std::shared_ptr<Animal> ani)
{
    setAnimal(std::move(ani));

    return *this;
}

VetClinic& VetClinic::operator+=(const Vet& v)
{
    setVet(v);

    return *this;
}

VetClinic& VetClinic::operator-=(const Animal& ani)
{
    if (!animal.removeIf([&ani](const std::shared_ptr<Animal>& current) { return *current == ani; }))
        std::cout << "Animal not found!" << std::endl;

    return *this;
}

VetClinic& VetClinic::operator-=(const Vet& v)
{
    if (!vet.removeIf([&v](const Vet& current) { return current == v; }))
        std::cout << "Vet not found!" << std::endl;

    return *this;
}