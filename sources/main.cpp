#include "../headers/animal.h"
#include "../headers/dog.h"
#include "../headers/cat.h"
#include "../headers/bird.h"
#include "../headers/rodent.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"

#include <memory>
#include <vector>

#include <Windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    bool end = false;
    VetClinic clinic;
    
    clinic.setVet(Vet("Ivan Ivanov", "Therapist"));
    clinic.setVet(Vet("Anna Petrova", "Ornithologist"));
    clinic.setVet(Vet("Alexey Sidorov", "Rodentologist"));

    clinic.setAnimal(std::make_shared<Dog>("Rex", "German Shepherd", 5, "Maria", true));
    clinic.setAnimal(std::make_shared<Cat>("Barsik", "British Shorthair", 3, "Alexey", "short"));
    clinic.setAnimal(std::make_shared<Bird>("Kesha", "Budgerigar", 2, "Elena", 20));
    clinic.setAnimal(std::make_shared<Rodent>("Homa", "Djungarian hamster", 1, "Dmitry", 35.5));
    clinic.setAnimal(std::make_shared<Animal>("Kaa", "Reptile", "Boa", 4, "Pavel"));

    clinic.setAppeals("Therapist", "Rex", "13.09.2026", "Routine checkup", "Vitamin course");
    clinic.setAppeals("Therapist", "Barsik", "14.09.2026", "Vaccination", "Observation for 2 days");
    clinic.setAppeals("Ornithologist", "Kesha", "14.09.2026", "Feather problems", "Vitamin B12 supplement");
    clinic.setAppeals("Rodentologist", "Homa", "15.09.2026", "Paw dislocation", "Fixing bandage");
    clinic.setAppeals("Therapist", "Kaa", "16.09.2026", "Molting", "Increase terrarium humidity");

    Animal animal1("Rex", "Dog", "German Shepherd", 5, "Maria");
    Animal animal2("Barsik", "Cat", "British Shorthair", 3, "Alexey");
    Animal animal3("Rex", "Dog", "German Shepherd", 5, "Maria");

    std::cout << std::boolalpha;

    std::cout << "Is animal1 equal to animal2: " << (animal1 == animal2) << std::endl;
    std::cout << "Is animal1 equal to animal3: " << (animal1 == animal3) << std::endl;
    std::cout << "Is animal1 older than animal2: " << (animal1 > animal2) << std::endl;
    std::cout << "Is animal1 younger than animal2: " << (animal1 < animal2) << std::endl;

    std::cout << std::noboolalpha << std::endl;

    std::cout << "=== Animal hierarchy demo ===" << std::endl;

    Dog dog("Sharik", "Mongrel", 4, "Igor", false);
    Cat cat("Murka", "Siamese", 6, "Olga", "long");
    Bird bird("Gosha", "Macaw", 8, "Viktor", 90);
    Rodent rodent("Pushok", "Syrian hamster", 2, "Anna", 120.5);

    std::cout << "Inherited methods: " << dog.getName() << ", " << dog.getView() << ", owner " << dog.getOwner() << std::endl;
    std::cout << "Own properties: dog vaccinated - " << (dog.isVaccinated() ? "yes" : "no")
              << ", cat fur - " << cat.getFur()
              << ", bird wingspan - " << bird.getWingspan() << " cm"
              << ", rodent weight - " << rodent.getWeight() << " g" << std::endl << std::endl;

    std::vector<std::shared_ptr<Animal>> pets = {
        std::make_shared<Animal>("Kaa", "Reptile", "Boa", 4, "Pavel"),
        std::make_shared<Dog>(dog),
        std::make_shared<Cat>(cat),
        std::make_shared<Bird>(bird),
        std::make_shared<Rodent>(rodent)
    };

    for (const auto& pet : pets)
    {
        std::cout << pet->getView() << " " << pet->getName() << ": " << pet->makeSound() << std::endl;
        std::cout << "  Care advice: " << pet->careAdvice() << std::endl;
        std::cout << "  Can a therapist treat it: " << (pet->canBeTreatedBy("Therapist") ? "yes" : "no") << std::endl;
    }

    std::cout << std::endl << "Output via operator<< (the overridden print is called):" << std::endl;
    std::cout << dog << std::endl;
    std::cout << rodent << std::endl;

    while(!end) menu(clinic, end);       
    return 0;
}