#include "../headers/animal.h"
#include "../headers/dog.h"
#include "../headers/cat.h"
#include "../headers/bird.h"
#include "../headers/rodent.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"
#include "../exception/duplicateException.h"
#include "../exception/incompatibleVetException.h"
#include "../exception/inputFormatException.h"
#include "../exception/invalidDataException.h"
#include "../exception/notFoundException.h"
#include "../exception/outOfRangeException.h"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

#define MIN_MENU_OPTION int(0)
#define MAX_MENU_OPTION int(9)

void clearInput()
{
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void printMenu()
{
    std::cout << "=============== Menu ================" << std::endl;
    std::cout << "1. Add a veterinarian" << std::endl;
    std::cout << "2. Add an animal" << std::endl;
    std::cout << "3. Schedule an appointment" << std::endl;
    std::cout << "4. Show all doctors" << std::endl;
    std::cout << "5. Show all animals" << std::endl;
    std::cout << "6. Show appointment history" << std::endl;
    std::cout << "7. Remove veterinarian" << std::endl;
    std::cout << "8. Remove the animal" << std::endl;
    std::cout << "9. Create a report" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=====================================" << std::endl;
}

int readMenuOption()
{
    int option = -1;
    std::cout << "Select the item number: ";
    std::cin >> option;

    if (std::cin.fail())
    {
        if (std::cin.eof())
            return MIN_MENU_OPTION;     // input stream ended (Ctrl+Z / Ctrl+D): behave like "Exit"

        clearInput();
        throw InputFormatException("Menu items must be a number");
    }

    clearInput();
    if (option < MIN_MENU_OPTION || option > MAX_MENU_OPTION)
    {
        throw InputFormatException("The menu items cannot be negative or more menu items");
    }

    return option;
}

void addVeterinarian(VetClinic& clinic)
{
    Vet vet;
    std::cout << "Enter vet data (full name / specialization, each on its own line):" << std::endl;

    try
    {
        std::cin >> vet;
        clinic += vet;
        std::cout << "\nVet added successfully" << std::endl;
    }
    catch (const InvalidDataException& e)
    {
        std::cerr << "\n!!!Invalid data: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Invalid data: " + std::string(e.what()));
    }
    catch (const DuplicateException& e)
    {
        std::cerr << "\n!!!Duplicate exception: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Duplicate exception: " + std::string(e.what()));
    }

    std::cout << std::endl;
}

std::shared_ptr<Animal> readAnimalType()
{
    int type = 0;
    std::cout << "Animal type: 1. Dog  2. Cat  3. Bird  4. Rodent" << std::endl;
    std::cout << "Select the type: ";
    std::cin >> type;

    if (std::cin.fail())
    {
        clearInput();
        throw InputFormatException("Animal type must be a number");
    }

    clearInput();
    if (type < 1 || type > 4)
    {
        throw InputFormatException("The animal type cannot be negative or more menu items");
    }

    switch (type)
    {
    case 1: return std::make_shared<Dog>();
    case 2: return std::make_shared<Cat>();
    case 3: return std::make_shared<Bird>();
    case 4: return std::make_shared<Rodent>();
    default: throw InputFormatException("Unknown animal type");
    }
}

void addAnimal(VetClinic& clinic)
{
    std::shared_ptr<Animal> animal = readAnimalType();
    std::cout << "Enter animal data (" << animal->inputHint() << ", each on its own line):" << std::endl;

    try
    {
        std::cin >> *animal;
        clinic += animal;
        std::cout << "\nAnimal added successfully" << std::endl;
    }
    catch (const InputFormatException& e)
    {
        std::cerr << "\n!!!Input format: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Input format: " + std::string(e.what()));
    }
    catch (const InvalidDataException& e)
    {
        std::cerr << "\n!!!Invalid data: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Invalid data: " + std::string(e.what()));
    }
    catch (const DuplicateException& e)
    {
        std::cerr << "\n!!!Duplicate exception: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Duplicate exception: " + std::string(e.what()));
    }

    std::cout << std::endl;
}

void scheduleAppointment(VetClinic& clinic)
{
    std::string vetName;
    std::string nameAnimal;
    std::string ownerAnimal;
    std::string date;
    std::string diagnosis;
    std::string treatment;

    std::cout << "Enter the vet's name: ";
    std::getline(std::cin, vetName);
    std::cout << "Enter the animal's name: ";
    std::getline(std::cin, nameAnimal);
    std::cout << "Enter the animal's owner: ";
    std::getline(std::cin, ownerAnimal);
    std::cout << "Enter the date: ";
    std::getline(std::cin, date);
    std::cout << "Enter the diagnosis: ";
    std::getline(std::cin, diagnosis);
    std::cout << "Enter the prescribed treatment: ";
    std::getline(std::cin, treatment);

    try
    {
        clinic.setAppeals(vetName, nameAnimal, ownerAnimal, date, diagnosis, treatment);
        std::cout << "\nAppeals added successfully" << std::endl;
    }
    catch (const NotFoundException& e)
    {
        std::cerr << "\n!!!Not found: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Not found: " + std::string(e.what()));
    }
    catch (const IncompatibleVetException& e)
    {
        std::cerr << "\n!!!Incompatible vet: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Incompatible vet: " + std::string(e.what()));
    }
    catch (const InvalidDataException& e)
    {
        std::cerr << "\n!!!Invalid data: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Invalid data: " + std::string(e.what()));
    }

    std::cout << std::endl;
}

void removeVeterinarian(VetClinic& clinic)
{
    std::string name;
    std::cout << "Enter the vet's full name to remove: ";
    std::getline(std::cin, name);

    try
    {
        clinic -= Vet(name, "");
        std::cout << "\nVet removed successfully" << std::endl;
    }
    catch (const NotFoundException& e)
    {
        std::cerr << "\n!!!Not found: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Not found: " + std::string(e.what()));
    }

    std::cout << std::endl;
}

void removeAnimal(VetClinic& clinic)
{
    std::string name;
    std::string owner;

    std::cout << "Enter the animal's name to remove: ";
    std::getline(std::cin, name);
    std::cout << "Enter the owner's name: ";
    std::getline(std::cin, owner);
    std::cout << std::endl;

    try
    {
        clinic.removeAnimal(name, owner);
        std::cout << "Animal removed successfully" << std::endl;
    }
    catch (const NotFoundException& e)
    {
        std::cerr << "\n!!!Not found: " << e.what() << std::endl;
        clinic.logEvent("ERROR: Not found: " + std::string(e.what()));
    }

    std::cout << std::endl;
}

void createReport(const VetClinic& clinic)
{
    if (clinic.repEvent())
        std::cout << "\nReport successfully created\n" << std::endl;
    else
        std::cout << "\nReport was not created\n" << std::endl;
}

void menu(VetClinic& clinic, bool& end)
{
    printMenu();

    switch (readMenuOption())
    {
    case 1:
        addVeterinarian(clinic);
        break;
    case 2:
        addAnimal(clinic);
        break;
    case 3:
        scheduleAppointment(clinic);
        break;
    case 4:
        clinic.infoVet();
        std::cout << std::endl;
        break;
    case 5:
        clinic.infoAnimal();
        std::cout << std::endl;
        break;
    case 6:
        clinic.infoAppeals();
        std::cout << std::endl;
        break;
    case 7:
        removeVeterinarian(clinic);
        break;
    case 8:
        removeAnimal(clinic);
        break;
    case 9:
        createReport(clinic);
        break;
    case 0:
        end = true;
        break;
    default:
        break;
    }
}
