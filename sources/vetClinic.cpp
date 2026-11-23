#include "../headers/vetClinic.h"
#include "../exception/notFoundException.h"
#include "../exception/invalidDataException.h"
#include "../exception/incompatibleVetException.h"
#include "../exception/duplicateException.h"

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
        throw NotFoundException("Animal '" + std::string(name) + "', owner '" + std::string(owner) + "': not found!");

    return removed;
}

void VetClinic::setAnimal(std::shared_ptr<Animal> animalTemp)
{
    if (!animalTemp)
        throw InvalidDataException("Animal - null pointer");

    if (animal.findIf([&animalTemp](const auto& item) { return *item == *animalTemp; }))
        throw DuplicateException("Animal '" + std::string(animalTemp->getName()) + "' of owner '" + std::string(animalTemp->getOwner()) + "' already exists");

    animal.add(animalTemp);
    std::sort(animal.begin(), animal.end(), [](const std::shared_ptr<Animal>& a, const std::shared_ptr<Animal>& b) { return *a < *b; });
}

void VetClinic::setVet(const Vet& vetTemp)
{
    if (vet.findIf([&vetTemp](const auto& item) { return item == vetTemp; })) 
        throw DuplicateException("Vet '" + std::string(vetTemp.getName()) + "' already exists");

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
        throw NotFoundException("Vet not found");

    std::shared_ptr<Animal> addsAnimal;
    for (const auto& currentAnimal : animal) 
    {
        if (currentAnimal->getName() == nameAnimal) {
            addsAnimal = currentAnimal;
            break;
        }
    }

    if (!addsAnimal) 
        throw NotFoundException("Animal not found");

    if (!appointmentCheck(vetSpeciality, *addsAnimal))
        throw IncompatibleVetException("A " + std::string(vetSpeciality) + " cannot treat a " + addsAnimal->getType());

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
        throw NotFoundException("Animal not found!");
    
    return *this;
}

VetClinic& VetClinic::operator-=(const Vet& v)
{
    if (!vet.removeIf([&v](const Vet& current) { return current == v; }))
        throw NotFoundException("Vet '" + v.getName() + "' not found!");

    return *this;
}