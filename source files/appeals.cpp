#include "appeals.h"

Appeals::Appeals() = default;
Appeals::Appeals(const Vet& vetTemp, const Animal& animalTemp, std::string_view dateTemp, std::string_view diagnosisTemp, std::string_view treatmentTemp)
    : vet(vetTemp), animal(animalTemp), date(dateTemp), diagnosis(diagnosisTemp), treatment(treatmentTemp) {
}

void Appeals::setVet(const Vet& vetTemp) { vet = vetTemp; }
void Appeals::setAnimal(const Animal& animalTemp) { animal = animalTemp; }
void Appeals::setDate(std::string_view dateTemp) { date = dateTemp; }
void Appeals::setDiagnosis(std::string_view diagnosisTemp) { diagnosis = diagnosisTemp; }
void Appeals::setTreatment(std::string_view treatmentTemp) { treatment = treatmentTemp; }

Vet Appeals::getVet() const { return vet; }
Animal Appeals::getAnimal() const { return animal; }
std::string Appeals::getDate() const { return date; }
std::string Appeals::getDiagnosis() const { return diagnosis; }
std::string Appeals::getTreatment() const { return treatment; }

void Appeals::info() const
{
    std::cout << "Vet: " << vet.getName() << "(" << vet.getSpeciality() << ")" << std::endl;
    std::cout << "Animal: " << animal.getName() << "(" << animal.getView() << ")" << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Diagnosis: " << diagnosis << std::endl;
    std::cout << "Treatment: " << treatment << std::endl;
}