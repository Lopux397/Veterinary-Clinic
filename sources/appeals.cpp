#include "../headers/appeals.h"
#include "../exception/invalidDataException.h"

Appeals::Appeals() = default;
Appeals::Appeals(const Vet& vetTemp, std::shared_ptr<Animal> animalTemp, std::string_view dateTemp, std::string_view diagnosisTemp, std::string_view treatmentTemp)
    : vet(vetTemp), animal(std::move(animalTemp)), date(dateTemp), diagnosis(diagnosisTemp), treatment(treatmentTemp)
{}

void Appeals::setVet(const Vet& vetTemp) { vet = vetTemp; }
void Appeals::setAnimal(std::shared_ptr<Animal> animalTemp)
{ 
    if (!animalTemp)
        throw InvalidDataException("Animal - null pointer");
    animal = std::move(animalTemp); 
}
void Appeals::setDate(std::string_view dateTemp)
{
    if (dateTemp.empty())
        throw InvalidDataException("The date cannot be empty");

    date = dateTemp; 
}
void Appeals::setDiagnosis(std::string_view diagnosisTemp)
{ 
    if (diagnosisTemp.empty())
        throw InvalidDataException("The diagnosis cannot be empty");

    diagnosis = diagnosisTemp;
}
void Appeals::setTreatment(std::string_view treatmentTemp)
{ 
    if (treatmentTemp.empty())
        throw InvalidDataException("The treatment cannot be empty");

    treatment = treatmentTemp;
}

Vet Appeals::getVet() const { return vet; }
std::shared_ptr<Animal> Appeals::getAnimal() const { return animal; }
std::string Appeals::getDate() const { return date; }
std::string Appeals::getDiagnosis() const { return diagnosis; }
std::string Appeals::getTreatment() const { return treatment; }

void Appeals::save(std::ostream& os) const
{
    os << "APPEALS#";
    os << vet.getName() << "#";
    os << animal->getName() << "#";
    os << animal->getOwner() << "#";
    os << date << "#";
    os << diagnosis << "#";
    os << treatment;
}
