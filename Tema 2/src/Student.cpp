#include "Student.h"
#include <iostream>

// ITEM 4: initializare prin lista de initializare, nu prin atribuire in corp.
//
// Varianta GRESITA (de evitat):
//   Student::Student() {
//       nume = "Necunoscut";  // nume e construit gol, apoi i se atribuie
//       varsta = 0;
//       // note[] si nrNote raman cu valori aleatoare daca uitam de ele!
//   }
//
// Varianta CORECTA: fiecare membru e construit direct cu valoarea dorita.
// note() initializeaza toate elementele array-ului cu 0.
Student::Student()
    : nume("Necunoscut"), varsta(0), note(), nrNote(0)
{
}

Student::Student(const std::string& nume, int varsta)
    : nume(nume), varsta(varsta), note(), nrNote(0)
{
}

bool Student::adaugaNota(int nota)
{
    if (nrNote >= MAX_NOTE || nota < 1 || nota > 10)
        return false;
    note[nrNote++] = nota;
    return true;
}

double Student::medie() const
{
    if (nrNote == 0)
        return 0.0;
    int suma = 0;  // variabila locala initializata explicit
    for (int i = 0; i < nrNote; ++i)
        suma += note[i];
    return static_cast<double>(suma) / nrNote;
}

void Student::afiseaza() const
{
    std::cout << "Student: " << nume << ", varsta " << varsta << ", note: ";
    if (nrNote == 0)
        std::cout << "-";
    for (int i = 0; i < nrNote; ++i)
        std::cout << note[i] << " ";
    std::cout << "| medie: " << medie() << "\n";
}
