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
