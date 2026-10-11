#include "../headers/animal.h"
#include "../headers/vet.h"
#include "../headers/appeals.h"
#include "../headers/vetClinic.h"
#include "../headers/functions.h"

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

    clinic.setAnimal(Animal("Рекс", "Собака", "Овчарка", 5, "Мария"));
    clinic.setAnimal(Animal("Барсик", "Кошка", "Британская", 3, "Алексей"));
    clinic.setAnimal(Animal("Кеша", "Птица", "Волнистый попугай", 2, "Елена"));
    clinic.setAnimal(Animal("Хома", "Грызун", "Джунгарский хомяк", 1, "Дмитрий"));

    clinic.setAppeals("Терапевт", "Рекс", "13.09.2026", "Плановый осмотр", "Курс витаминов");
    clinic.setAppeals("Терапевт", "Барсик", "14.09.2026", "Вакцинация", "Наблюдение 2 дня");
    clinic.setAppeals("Орнитолог", "Кеша", "14.09.2026", "Проблемы с оперением", "Кормовая добавка B12");
    clinic.setAppeals("Ратолог", "Хома", "15.09.2026", "Вывих лапы", "Наложение фиксирующей повязки");

    Animal animal1("Рекс", "Собака", "Овчарка", 5, "Мария");
    Animal animal2("Барсик", "Кошка", "Британская", 3, "Алексей");
    Animal animal3("Рекс", "Собака", "Овчарка", 5, "Мария");

    std::cout << std::boolalpha;

    std::cout << "Равны ли animal1 и animal2: " << (animal1 == animal2) << std::endl;
    std::cout << "Равны ли animal1 и animal3: " << (animal1 == animal3) << std::endl;
    std::cout << "Старше ли animal1, чем animal2: " << (animal1 > animal2) << std::endl;
    std::cout << "Младше ли animal1, чем animal2: " << (animal1 < animal2) << std::endl;

    std::cout << std::noboolalpha << std::endl;

    while(!end) menu(clinic, end);       
    return 0;
}