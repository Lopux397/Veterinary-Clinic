#include "../headers/animal.h"
#include "../headers/dog.h"
#include "../headers/cat.h"
#include "../headers/bird.h"
#include "../headers/rodent.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"

#include <iostream>
#include <memory>
#include <vector>

#include <Windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    VetClinic clinic;
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
    {
        std::cout << pet->getType() << " " << pet->getName() << ": " << pet->makeSound() << " | " << pet->checkupPrice() << " | " << pet->careAdvice() << std::endl;
    }
        
    std::cout << std::endl;

    while (!end) menu(clinic, end);
    return 0;
}
