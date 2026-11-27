#pragma once

#include "../headers/vetClinic.h"
#include "../headers/animal.h"

#include <limits>

void clearInput();
void menu(VetClinic& clinic, bool& end);

void printMenu();
int readMenuOption();
void addVeterinarian(VetClinic& clinic);
std::shared_ptr<Animal> readAnimalType();
void addAnimal(VetClinic& clinic);
void scheduleAppointment(VetClinic& clinic);
void removeVeterinarian(VetClinic& clinic);
void removeAnimal(VetClinic& clinic);
void createReport(VetClinic& clinic);
