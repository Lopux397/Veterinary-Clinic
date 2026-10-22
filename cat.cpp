#include "../headers/cat.h"

Cat::Cat() : Animal("", "Кошка", "", 0, "") {
}
Cat::Cat(std::string_view nameTemp, std::string_view breedTemp, unsigned int ageTemp, std::string_view ownerTemp, std::string_view furTemp)
    : Animal(nameTemp, "Кошка", breedTemp, ageTemp, ownerTemp), fur(furTemp) {
}

void Cat::setFur(std::string_view furTemp) { fur = furTemp; }
std::string Cat::getFur() const { return fur; }

std::string Cat::makeSound() const
{
    return "Мяу!";
}

std::string Cat::careAdvice() const
{
    if (fur == "длинная") return Animal::careAdvice() + " Расчёсывать шерсть раз в неделю.";

    return Animal::careAdvice();
}

void Cat::print(std::ostream& os) const
{
    Animal::print(os);
    os << "Fur: " << fur << std::endl;
}

void Cat::read(std::istream& is)
{
    Animal::read(is);
    std::getline(is, fur);
}

std::string Cat::inputHint() const
{
    return Animal::inputHint() + " / fur length (короткая/длинная)";
}
