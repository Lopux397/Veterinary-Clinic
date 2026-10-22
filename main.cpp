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
    
    clinic.setVet(Vet("Иванов Иван", "Терапевт"));
    clinic.setVet(Vet("Петрова Анна", "Орнитолог"));
    clinic.setVet(Vet("Сидоров Алексей", "Ратолог"));

    clinic.setAnimal(std::make_shared<Dog>("Рекс", "Овчарка", 5, "Мария", true));
    clinic.setAnimal(std::make_shared<Cat>("Барсик", "Британская", 3, "Алексей", true));
    clinic.setAnimal(std::make_shared<Bird>("Кеша", "Волнистый попугай", 2, "Елена", true));
    clinic.setAnimal(std::make_shared<Rodent>("Хома", "Джунгарский хомяк", 1, "Дмитрий", 35));
    clinic.setAnimal(std::make_shared<Animal>("Каа", "Рептилия", "Удав", 4, "Павел"));

    clinic.setAppeals("Терапевт", "Рекс", "13.09.2026", "Плановый осмотр", "Курс витаминов");
    clinic.setAppeals("Терапевт", "Барсик", "14.09.2026", "Вакцинация", "Наблюдение 2 дня");
    clinic.setAppeals("Орнитолог", "Кеша", "14.09.2026", "Проблемы с оперением", "Кормовая добавка B12");
    clinic.setAppeals("Ратолог", "Хома", "15.09.2026", "Вывих лапы", "Наложение фиксирующей повязки");
    clinic.setAppeals("Терапевт", "Каа", "16.09.2026", "Линька", "Повышение влажности в террариуме");

    Animal animal1("Рекс", "Собака", "Овчарка", 5, "Мария");
    Animal animal2("Барсик", "Кошка", "Британская", 3, "Алексей");
    Animal animal3("Рекс", "Собака", "Овчарка", 5, "Мария");

    std::cout << std::boolalpha;

    std::cout << "Равны ли animal1 и animal2: " << (animal1 == animal2) << std::endl;
    std::cout << "Равны ли animal1 и animal3: " << (animal1 == animal3) << std::endl;
    std::cout << "Старше ли animal1, чем animal2: " << (animal1 > animal2) << std::endl;
    std::cout << "Младше ли animal1, чем animal2: " << (animal1 < animal2) << std::endl;

    std::cout << std::noboolalpha << std::endl;

    std::cout << "=== Демонстрация иерархии Animal ===" << std::endl;

    Animal reptile("Каа", "Рептилия", "Удав", 4, "Павел");
    Dog dog("Шарик", "Дворняга", 4, "Игорь", false);
    Cat cat("Мурка", "Сиамская", 6, "Ольга", false);
    Bird bird("Гоша", "Ара", 8, "Виктор", false);
    Rodent rodent("Пушок", "Сирийский хомяк", 2, "Анна", 120);

    std::cout << "Унаследованные методы: " << dog.getName() << ", " << dog.getView() << ", владелец " << dog.getOwner() << std::endl;
    std::cout << "Собственные свойства: привита - " << (dog.isVaccinated() ? "да" : "нет")
              << ", кошка живёт дома - " << (cat.isIndoor() ? "да" : "нет")
              << ", птица летает - " << (bird.getCanFly() ? "да" : "нет")
              << ", вес грызуна - " << rodent.getWeight() << " г" << std::endl << std::endl;

    std::vector<std::shared_ptr<Animal>> pets = {
        std::make_shared<Animal>(reptile),
        std::make_shared<Dog>(dog),
        std::make_shared<Cat>(cat),
        std::make_shared<Bird>(bird),
        std::make_shared<Rodent>(rodent)
    };

    for (const auto& pet : pets)
    {
        std::cout << pet->getView() << " " << pet->getName() << ": " << pet->makeSound() << std::endl;
        std::cout << "  Рекомендации: " << pet->careAdvice() << std::endl;
        std::cout << "  Примет терапевт: " << (pet->canBeTreatedBy("Терапевт") ? "да" : "нет") << std::endl;
    }

    std::cout << std::endl << "Вывод через оператор << (вызывается переопределённый print):" << std::endl;
    std::cout << dog << std::endl;
    std::cout << rodent << std::endl;

    while(!end) menu(clinic, end);       
    return 0;
}