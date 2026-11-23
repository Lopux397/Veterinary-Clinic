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
#include "../exception/duplicateException.h"
#include "../exception/incompatibleVetException.h"
#include "../exception/inputFormatException.h"
#include "../exception/invalidDataException.h"
#include "../exception/notFoundException.h"
#include "../exception/outOfRangeException.h"

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
    
    while (!end)
    {
        try
        {
            menu(clinic, end);
        }
        catch (const InputFormatException& e)
        {
            std::cout << "\n!!!Input format: " << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "\n!!!Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
