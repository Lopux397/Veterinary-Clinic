#include "../headers/animal.h"
#include "../headers/dog.h"
#include "../headers/cat.h"
#include "../headers/bird.h"
#include "../headers/rodent.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"

#include <iterator>

namespace
{
    using Factory = std::shared_ptr<Animal> (*)();

    template <typename T>
    std::shared_ptr<Animal> create()
    {
        return std::make_shared<T>();
    }

    const Factory factories[] = { create<Dog>, create<Cat>, create<Bird>, create<Rodent>, create<Animal> };

    std::string ask(const char* question)
    {
        std::string answer;

        std::cout << question;
        std::getline(std::cin, answer);

        return answer;
    }
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void menu(VetClinic& clinic, bool& end)
{
    int option = -1;
    bool repeat;
    const char* const items[] = {
        "1. Add a veterinarian",
        "2. Add an animal",
        "3. Schedule an appointment",
        "4. Show all doctors",
        "5. Show all animals",
        "6. Show appointment history",
        "7. Remove veterinarian",
        "8. Remove the animal",
        "0. Exit"
    };

    std::cout << "=============== Menu ================" << std::endl;
    for (const char* item : items) std::cout << item << std::endl;
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

            std::cout << "Animal type: 1. Dog  2. Cat  3. Bird  4. Rodent  5. Other" << std::endl;
            std::cout << "Select the type: ";
            std::cin >> type;
            clearInput();

            if (type < 1 || type > static_cast<int>(std::size(factories)))
            {
                std::cout << "Unknown animal type" << std::endl << std::endl;
                break;
            }

            std::shared_ptr<Animal> animal = factories[type - 1]();

            std::cout << "Enter animal data (" << animal->inputHint() << ", each on its own line):" << std::endl;
            std::cin >> *animal;

            clinic += animal;
            std::cout << std::endl;
            break;
        }
        case 3:
        {
            std::string vetSpeciality = ask("Enter the vet's specialization: ");
            std::string nameAnimal = ask("Enter the animal's name: ");
            std::string date = ask("Enter the date: ");
            std::string diagnosis = ask("Enter the diagnosis: ");
            std::string treatment = ask("Enter the prescribed treatment: ");

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
            clinic -= Vet(ask("Enter the vet's full name to remove: "), "");

            std::cout << std::endl;
            break;
        }
        case 8:
        {
            std::string name = ask("Enter the animal's name to remove: ");
            std::string owner = ask("Enter the owner's name: ");

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