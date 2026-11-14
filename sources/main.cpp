#include "../headers/animal.h"
#include "../headers/dog.h"
#include "../headers/cat.h"
#include "../headers/bird.h"
#include "../headers/rodent.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"
#include "../headers/collection.h"
#include "../headers/findAll.h"

#include <iostream>
#include <memory>
#include <vector>

#include <Windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    /*VetClinic clinic;
    bool end = false;

    clinic.setVet(Vet("Ivan Ivanov", "Therapist"));
    clinic.setVet(Vet("Anna Petrova", "Ornithologist"));
    clinic.setVet(Vet("Alexey Sidorov", "Rodentologist"));

    clinic.setAnimal(std::make_shared<Dog>("Rex", "German Shepherd", 5, "Maria", 2));
    clinic.setAnimal(std::make_shared<Cat>("Barsik", "British Shorthair", 3, "Alexey", 4));
    clinic.setAnimal(std::make_shared<Bird>("Kesha", "Budgerigar", 2, "Elena", 20));
    clinic.setAnimal(std::make_shared<Rodent>("Homa", "Djungarian hamster", 1, "Dmitry", 15.5));

    clinic.setAppeals("Therapist", "Rex", "13.09.2026", "Routine checkup", "Vitamin course");
    clinic.setAppeals("Ornithologist", "Kesha", "14.09.2026", "Feather problems", "Vitamin B12");
    clinic.setAppeals("Rodentologist", "Homa", "15.09.2026", "Paw dislocation", "Fixing bandage");
 
    std::vector<std::shared_ptr<Animal>> pets = {
        std::make_shared<Dog>("Sharik", "Mongrel", 4, "Igor", 3),
        std::make_shared<Bird>("Gosha", "Macaw", 8, "Viktor", 90),
        std::make_shared<Cat>("Barsik", "British Shorthair", 3, "Alexey", 4),
        std::make_shared<Rodent>("Homa", "Djungarian hamster", 1, "Dmitry", 15.5)
    };

    for (const auto& pet : pets) 
        std::cout << pet->getType() << " " << pet->getName() << ": " << pet->makeSound() << " | " << pet->checkupPrice() << " | " << pet->careAdvice() << std::endl;
        
    std::cout << std::endl;

    while (!end) menu(clinic, end);*/


    Collection<std::shared_ptr<Animal>> animal;
    std::cout << "==============================Animal====================================" << std::endl;
    animal.add(std::make_shared<Dog>("Sharik", "Mongrel", 4, "Igor", 3));
    animal.add(std::make_shared<Cat>("Barsik", "British Shorthair", 3, "Alexey", 4));
    animal.add(std::make_shared<Rodent>("Homa", "Djungarian hamster", 1, "Dmitry", 15.5));
    animal.add(std::make_shared<Cat>("Kitty", "Maine Coon", 2, "Magamed", 2));
    animal.print(std::cout);
    std::cout << "------------------------------Size--------------------------------------" << std::endl;
    std::cout << "Collection size - " << animal.size() << std::endl;
    std::cout << "------------------------------Index-------------------------------------" << std::endl;
    std::cout << animal[1];
    std::cout << "-------------------------------Search-----------------------------------" << std::endl;
    std::string type{ "Rodent" };
    auto check = animal.findIf([&type](const auto& item) { return item->getType() == type;});
    if (check)
        std::cout << *(check);
    else
        std::cout << "No result" << std::endl;
    std::cout << "-------------------------------Remove-----------------------------------" << std::endl;
    std::string name{ "Barsik" };
    std::string owner{ "Alexey" };
    bool successful = animal.removeIf([&name, &owner](const auto& item) { return item->getName() == name && item->getOwner() == owner; });
    std::cout << "Was the removal successful? - " << std::boolalpha << successful << std::endl;
    std::cout << "Collection size - " << animal.size() << std::endl;
    std::cout << std::endl;
    animal.print(std::cout);
    std::cout << "--------------------------------Template function-----------------------" << std::endl;
    type = { "Cat" };
    auto noCat = findAll(animal, [&type](const auto& item) { return item->getType() != type; });
    for (const auto& it : noCat)
        std::cout << it << std::endl;
    std::cout << "----------------------------------Hollow?-------------------------------" << std::endl;
    animal.clear();
    std::cout << "Is the collection empty? - " << animal.empty() << std::endl;


    std::cout << std::endl << std::endl;
    Collection<Vet> vet;
    std::cout << "==================================Vet====================================" << std::endl;
    vet.add(Vet("Ivan Ivanov", "Therapist"));
    vet.add(Vet("Anna Petrova", "Ornithologist"));
    vet.add(Vet("Alexey Sidorov", "Rodentologist"));
    vet.add(Vet("Dima Bilan", "Ornithologist"));
    vet.print(std::cout);
    std::cout << "------------------------------Size--------------------------------------" << std::endl;
    std::cout << "Collection size - " << vet.size() << std::endl;
    std::cout << "------------------------------Index-------------------------------------" << std::endl;
    std::cout << vet[2];
    std::cout << "-------------------------------Search-----------------------------------" << std::endl;
    std::string speciality{ "Rodentologist" };
    auto checkV2 = vet.findIf([&speciality](const auto& item) { return item.getSpeciality() == speciality;});
    if (checkV2)
        std::cout << *(checkV2);
    else
        std::cout << "No result" << std::endl;
    std::cout << "--------------------------------Template function-----------------------" << std::endl;
    speciality = { "Ornithologist" };
    auto Ornithologists = findAll(vet, [&speciality](const auto& item) { return item.getSpeciality() == speciality; });
    for (const auto& it : Ornithologists)
        std::cout << it << std::endl;
    std::cout << "-------------------------------Remove-----------------------------------" << std::endl;
    name = { "Alexey Sidorov" };
    speciality = { "Rodentologist" };
    successful = vet.removeIf([&name, &speciality](const auto& item) { return item.getName() == name && item.getSpeciality() == speciality; });
    std::cout << "Was the removal successful? - " << std::boolalpha << successful << std::endl;
    std::cout << "Collection size - " << vet.size() << std::endl;
    std::cout << std::endl;
    vet.print(std::cout);
    std::cout << "----------------------------------Hollow?-------------------------------" << std::endl;
    vet.clear();
    std::cout << "Is the collection empty? - " << vet.empty() << std::endl;


    std::cout << std::endl << std::endl;
    Collection<int> integer;
    std::cout << "==================================int====================================" << std::endl;
    integer.add(15);
    integer.add(0);
    integer.add(-8);
    integer.add(4);
    integer.print(std::cout);
    std::cout << "------------------------------Size--------------------------------------" << std::endl;
    std::cout << "Collection size - " << integer.size() << std::endl;
    std::cout << "------------------------------Index-------------------------------------" << std::endl;
    std::cout << integer[0] << std::endl;
    std::cout << "-------------------------------Search-----------------------------------" << std::endl;
    auto checkV3 = integer.findIf([](const auto& item) { return item < 0;});
    if (checkV3)
        std::cout << *(checkV3) << std::endl;
    else
        std::cout << "No result" << std::endl;
    std::cout << "--------------------------------Template function-----------------------" << std::endl;
    auto even = findAll(integer, [](const auto& item) { return item % 2 == 0; });
    for (const auto& it : even)
        std::cout << it << std::endl;
    std::cout << "-------------------------------Remove-----------------------------------" << std::endl;
    int i = 0;
    successful = integer.removeIf([i](const auto& item) { return item == i; });
    std::cout << "Was the removal successful? - " << std::boolalpha << successful << std::endl;
    std::cout << "Collection size - " << integer.size() << std::endl;
    std::cout << std::endl;
    integer.print(std::cout);
    std::cout << "----------------------------------Hollow?-------------------------------" << std::endl;
    integer.clear();
    std::cout << "Is the collection empty? - " << integer.empty() << std::endl;

    return 0;
}
