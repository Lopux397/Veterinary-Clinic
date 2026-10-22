#include "../headers/animal.h"
#include "../headers/dog.h"
#include "../headers/cat.h"
#include "../headers/bird.h"
#include "../headers/rodent.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void menu(VetClinic& clinic, bool& end)
{
    int option = -1;
    bool repeat;

    std::cout << "=============== Menu ================" << std::endl;
    std::cout << "1. Add a veterinarian" << std::endl;
    std::cout << "2. Add an animal" << std::endl;
    std::cout << "3. Schedule an appointment" << std::endl;
    std::cout << "4. Show all doctors" << std::endl;
    std::cout << "5. Show all animals" << std::endl;
    std::cout << "6. Show appointment history" << std::endl;
    std::cout << "7. Remove veterinarian" << std::endl;
    std::cout << "8. Remove the animal" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=====================================" << std::endl;
    do
    {
        repeat = false;
        std::cout << "Select the item number: ";
        std::cin >> option;
        clearInput();
        std::cout << std::endl;
        switch (option) {
        case 1:
        {
            Vet vet;

            std::cout << "Enter vet data (full name / specialization, each on its own line):" << std::endl;
            std::cin >> vet;

            clinic += vet;
            std::cout << std::endl;
            break;
        }
        case 2:
        {
            int type = 0;
            std::shared_ptr<Animal> animal;

            std::cout << "Animal type: 1. Dog  2. Cat  3. Bird  4. Rodent  5. Other" << std::endl;
            std::cout << "Select the type: ";
            std::cin >> type;
            clearInput();

            if (type == 1) animal = std::make_shared<Dog>();
            else if (type == 2) animal = std::make_shared<Cat>();
            else if (type == 3) animal = std::make_shared<Bird>();
            else if (type == 4) animal = std::make_shared<Rodent>();
            else if (type == 5) animal = std::make_shared<Animal>();
            else
            {
                std::cout << "Unknown animal type" << std::endl << std::endl;
                break;
            }

            std::cout << "Enter animal data (" << animal->inputHint() << ", each on its own line):" << std::endl;
            std::cin >> *animal;

            clinic += animal;
            std::cout << std::endl;
            break;
        }
        case 3:
        {
            std::string vetSpeciality;
            std::string nameAnimal;
            std::string date;
            std::string diagnosis;
            std::string treatment;

            std::cout << "Enter the vet's specialization: ";
            std::getline(std::cin, vetSpeciality);

            std::cout << "Enter the animal's name: ";
            std::getline(std::cin, nameAnimal);

            std::cout << "Enter the date: ";
            std::getline(std::cin, date);

            std::cout << "Enter the diagnosis: ";
            std::getline(std::cin, diagnosis);

            std::cout << "Enter the prescribed treatment: ";
            std::getline(std::cin, treatment);

            clinic.setAppeals(vetSpeciality, nameAnimal, date, diagnosis, treatment);
            std::cout << std::endl;
            break;
        }
        case 4:
        {
            clinic.infoVet();
            std::cout << std::endl;
            break;
        }
        case 5:
        {
            clinic.infoAnimal();
            std::cout << std::endl;
            break;
        }
        case 6:
        {
            clinic.infoAppeals();
            std::cout << std::endl;
            break;
        }
        case 7: 
        {
            std::string name;

            std::cout << "Enter the vet's full name to remove: ";
            std::getline(std::cin, name);

            clinic -= Vet(name, "");

            std::cout << std::endl;
            break;
        }
        case 8:
        {
            std::string name;
            std::string owner;

            std::cout << "Enter the animal's name to remove: ";
            std::getline(std::cin, name);

            std::cout << "Enter the owner's name: ";
            std::getline(std::cin, owner);

            clinic -= Animal(name, "", "", 0, owner);

            std::cout << std::endl;
            break;
        }
        case 0:
        {
            end = true;
            break;
        }
        default:
        {
            repeat = true;
            break;
        }
        }
    } while (repeat);
}