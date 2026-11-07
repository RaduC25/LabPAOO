#include "StudentUnic.h"
#include <iostream>

// contorul de id-uri este un "static local".

int StudentUnic::genereazaId()
{
    static int urmatorulId = 1000;
    return urmatorulId++;
}

StudentUnic::StudentUnic(const std::string& nume, int varsta)
    : Student(nume, varsta), id(genereazaId())
{
}

void StudentUnic::afiseaza() const
{
    std::cout << "[ID " << id << "] ";
    Student::afiseaza();
}
