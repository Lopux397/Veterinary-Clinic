#include "../exception/incompatibleVetException.h"
#include "../exception/inputFormatException.h"
#include "../exception/invalidDataException.h"
#include "../exception/outOfRangeException.h"
#include "../exception/duplicateException.h"
#include "../exception/notFoundException.h"
#include "../headers/clinicStorage.h"
#include "../headers/collection.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"
#include "../headers/appeals.h"
#include "../headers/findAll.h"
#include "../headers/animal.h"
#include "../headers/rodent.h"
#include "../headers/logger.h"
#include "../headers/report.h"
#include "../headers/bird.h"
#include "../headers/dog.h"
#include "../headers/cat.h"
#include "../headers/vet.h"


#include <iostream>
#include <memory>
#include <vector>

int main()
{
    bool end = false;

    Logger logger("D:/Veterinary-Clinic/clinicLog.log");
    ClinicStorage file("D:/Veterinary-Clinic/clinic.txt");
    Report report("D:/Veterinary-Clinic/report.txt");

    VetClinic clinic(&logger, &report, &file);

    clinic.logEvent("INFO: Program started");

    /*clinic.setVet(Vet("Ivan Ivanov", "Therapist"));
    clinic.setVet(Vet("Anna Petrova", "Ornithologist"));
    clinic.setVet(Vet("Alexey Sidorov", "Rodentologist"));

    clinic.setAnimal(std::make_shared<Dog>("Rex", "German Shepherd", 5, "Maria", 2));
    clinic.setAnimal(std::make_shared<Cat>("Barsik", "British Shorthair", 3, "Alexey", 4));
    clinic.setAnimal(std::make_shared<Bird>("Kesha", "Budgerigar", 2, "Elena", 20));
    clinic.setAnimal(std::make_shared<Rodent>("Homa", "Djungarian hamster", 1, "Dmitry", 15.5));

    clinic.setAppeals("Ivan Ivanov", "Rex", "Maria", "13.09.2026", "Routine checkup", "Vitamin course");
    clinic.setAppeals("Anna Petrova", "Kesha", "Elena", "14.09.2026", "Feather problems", "Vitamin B12");
    clinic.setAppeals("Alexey Sidorov", "Homa", "Dmitry", "15.09.2026", "Paw dislocation", "Fixing bandage");*/

    clinic.load();

    while (!end)
    {
        try
        {
            menu(clinic, end);
        }
        catch (const InputFormatException& e)
        {
            std::cerr << "\n!!!Input format: " << e.what() << '\n' << std::endl;
            logger.log("ERROR: Input format: " + std::string(e.what()));
        }
    }

    clinic.save();

    clinic.logEvent("INFO: Program finished");
    return 0;
}
