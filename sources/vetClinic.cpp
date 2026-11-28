#include "../headers/vetClinic.h"
#include "../exception/notFoundException.h"
#include "../exception/invalidDataException.h"
#include "../exception/incompatibleVetException.h"
#include "../exception/duplicateException.h"
#include "../exception/fileException.h"
#include "../headers/report.h"
#include "../headers/clinicStorage.h"
#include "../exception/inputFormatException.h"

#include <ranges>

VetClinic::VetClinic(Logger* loggerTemp, Report* reportTemp, ClinicStorage* storageTemp)
    : logger(loggerTemp), report(reportTemp),storage(storageTemp){}

Collection<std::shared_ptr<Animal>>& VetClinic::getAnimal()  { return animal; }
Collection<Vet>& VetClinic::getVet() { return vet; }
Collection<Appeals>& VetClinic::getAppeals() { return appeals; }

const Collection<std::shared_ptr<Animal>>& VetClinic::getAnimal() const { return animal; }
const Collection<Vet>& VetClinic::getVet() const { return vet; }
const Collection<Appeals>& VetClinic::getAppeals() const { return appeals; }

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

    logEvent("INFO: Animal removed: " + std::string(name) + " - " + std::string(owner));
    return removed;
}

void VetClinic::setAnimal(std::shared_ptr<Animal> animalTemp)
{
    if (!animalTemp)
        throw InvalidDataException("Animal - null pointer");

    if (animal.findIf([&animalTemp](const auto& item) { return *item == *animalTemp; }))
        throw DuplicateException("Animal '" + std::string(animalTemp->getName()) + "' of owner '" + std::string(animalTemp->getOwner()) + "' already exists");

    animal.add(animalTemp);

    std::ranges::sort(animal, [](const std::shared_ptr<Animal>& a, const std::shared_ptr<Animal>& b) { return *a < *b; });
    logEvent("INFO: Animal added: " + animalTemp->getType() + ": " + animalTemp->getName() + " - " + animalTemp->getOwner());
}

void VetClinic::setVet(const Vet& vetTemp)
{
    if (vet.findIf([&vetTemp](const auto& item) { return item == vetTemp; })) 
        throw DuplicateException("Vet '" + std::string(vetTemp.getName()) + "' already exists");

    vet.add(vetTemp);
    logEvent("INFO: Vet added: " + vetTemp.getSpeciality() + ": " + vetTemp.getName());
}

bool VetClinic::setAppeals(std::string_view vetName, std::string_view animalName, std::string_view animalOwner, std::string_view date, std::string_view diagnosis, std::string_view treatment)
{
    const Vet* addsDoc = nullptr;
    for (const auto& currentVet : vet)
    {
        if (currentVet.getName() == vetName)
        {
            addsDoc = &currentVet;
            break;
        }
    }

    if (!addsDoc)
        throw NotFoundException("Vet '" + std::string(vetName) + "' not found");

    std::shared_ptr<Animal> addsAnimal;
    for (const auto& currentAnimal : animal)
    {
        if (currentAnimal->getName() == animalName && currentAnimal->getOwner() == animalOwner)
        {
            addsAnimal = currentAnimal;
            break;
        }
    }

    if (!addsAnimal)
        throw NotFoundException("Animal '" + std::string(animalName) + "', owner '" + std::string(animalOwner) + "' not found");

    if (!appointmentCheck(addsDoc->getSpeciality(), *addsAnimal))
        throw IncompatibleVetException("A " + addsDoc->getSpeciality() + " cannot treat a " + addsAnimal->getType());

    appeals.add(Appeals(*addsDoc, addsAnimal, date, diagnosis, treatment));

    logEvent("INFO: Appeals added: " + std::string(vetName) + " - " + std::string(animalName) + " : " + std::string(animalOwner));
    return true;
}

void VetClinic::setLogger(Logger& loggerTemp)
{
    logger = &loggerTemp;
}

void VetClinic::setReport(Report& reportTemp)
{
    report = &reportTemp;
}

void VetClinic::setStorage(ClinicStorage& storageTemp) 
{
    storage = &storageTemp;
}

void VetClinic::logEvent(const std::string& message) const
{
    if (!logger) return;

    try
    {
        logger->log(message);
    }
    catch (const FileException& e)
    {
        std::cerr << "\nLog error: " << e.what() << std::endl;
    }
}

bool VetClinic::repEvent() const 
{
    if (!report) return false;

    try 
    {
        report->create(*this);
        return true;
    }
    catch (const FileException& e)
    {
        std::cerr << "\nFile error: " << e.what() << std::endl;
        logEvent("ERROR: File error: " + std::string(e.what()));
    }

    return false;
}

bool VetClinic::load()
{
    if (!storage) return true;

    try
    {
        storage->load(*this);
        return true;
    }
    catch (const FileException& e)
    {
        std::cerr << "\nFile error: " << e.what() << std::endl;
        logEvent("ERROR: File error: " + std::string(e.what()));
    }
    catch (const InputFormatException& e)
    {
        std::cerr << "\n!!!Input format: " << e.what() << std::endl;
        logEvent("ERROR: Input format: " + std::string(e.what()));
    }
    catch (const DuplicateException& e)
    {
        std::cerr << "\n!!!Duplicate exception: " << e.what() << std::endl;
        logEvent("ERROR: Duplicate exception: " + std::string(e.what()));
    }
    catch (const InvalidDataException& e)
    {
        std::cerr << "\n!!!Invalid data: " << e.what() << std::endl;
        logEvent("ERROR: Invalid data: " + std::string(e.what()));
    }
    catch (const NotFoundException& e)
    {
        std::cerr << "\n!!!Not found: " << e.what() << std::endl;
        logEvent("ERROR: Not found: " + std::string(e.what()));
    }
    catch (const IncompatibleVetException& e)
    {
        std::cerr << "\n!!!Incompatible vet: " << e.what() << std::endl;
        logEvent("ERROR: Incompatible vet: " + std::string(e.what()));
    }

    animal.clear();
    vet.clear();
    appeals.clear();
    return false;
}

void VetClinic::save() const
{
    if (!storage) return;

    try
    {
        storage->save(*this);
    }
    catch (const FileException& e)
    {
        std::cerr << "\nFile error: " << e.what() << std::endl;
        logEvent("ERROR: File error: " + std::string(e.what()));
    }
}

void VetClinic::infoAnimal() const
{
    for (int i = 0; i < animal.size(); i++) 
    {
        std::cout << "========= Animal[" << i + 1 << "] =========" << std::endl;
        std::cout << *animal[i];
        std::cout << "=============================\n" << std::endl;
    }
    logEvent("INFO: Information about the 'Animal' has been displayed");
}

void VetClinic::infoVet() const 
{
    for (int i = 0; i < vet.size(); i++)
    {
        std::cout << "========= Vet[" << i + 1 << "] =========" << std::endl;
        std::cout << vet[i];
        std::cout << "==========================\n" << std::endl;
    }
    logEvent("INFO: Information about the 'Vet' has been displayed");
}

void VetClinic::infoAppeals() const 
{
    for (int i = 0; i < appeals.size(); i++)
    {
        std::cout << "========= Appeals[" << i + 1 << "] =========" << std::endl;
        std::cout << appeals[i];
        std::cout << "==============================\n" << std::endl;
    }
    logEvent("INFO: Information about the 'Appeals' has been displayed");
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
    
    logEvent("INFO: Animal removed: " + std::string(ani.getName()) + " - " + std::string(ani.getOwner()));
    return *this;
}

VetClinic& VetClinic::operator-=(const Vet& v)
{
    std::string name(v.getName());
    std::string speciality(v.getSpeciality());

    if (!vet.removeIf([&v](const Vet& current) { return current == v; }))
        throw NotFoundException("Vet '" + v.getName() + "' not found!");

    logEvent("INFO: Vet removed: " + speciality + ": " + name);
    return *this;
}