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

std::ostream& operator<< (std::ostream& os, const Appeals& app) 
{
    os << app.vet.getSpeciality() << " " << app.vet.getName() << std::endl;
    os << app.animal.getView() << " " << app.animal.getName() << std::endl;
    os << app.date << std::endl;
    os << app.diagnosis << std::endl;
    os << app.treatment << std::endl;

    return os;
}