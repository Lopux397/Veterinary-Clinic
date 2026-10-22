#include "../headers/appeals.h"

Appeals::Appeals() = default;
Appeals::Appeals(const Vet& vetTemp, std::shared_ptr<Animal> animalTemp, std::string_view dateTemp, std::string_view diagnosisTemp, std::string_view treatmentTemp)
    : vet(vetTemp), animal(std::move(animalTemp)), date(dateTemp), diagnosis(diagnosisTemp), treatment(treatmentTemp) {
}

void Appeals::setVet(const Vet& vetTemp) { vet = vetTemp; }
void Appeals::setAnimal(std::shared_ptr<Animal> animalTemp) { animal = std::move(animalTemp); }
void Appeals::setDate(std::string_view dateTemp) { date = dateTemp; }
void Appeals::setDiagnosis(std::string_view diagnosisTemp) { diagnosis = diagnosisTemp; }
void Appeals::setTreatment(std::string_view treatmentTemp) { treatment = treatmentTemp; }

Vet Appeals::getVet() const { return vet; }
std::shared_ptr<Animal> Appeals::getAnimal() const { return animal; }
std::string Appeals::getDate() const { return date; }
std::string Appeals::getDiagnosis() const { return diagnosis; }
std::string Appeals::getTreatment() const { return treatment; }