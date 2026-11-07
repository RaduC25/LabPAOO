#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// =====================================================================
//  Clasa Student - demonstreaza ITEM 4 si ITEM 5
// =====================================================================
class Student {
public:
    static const int MAX_NOTE = 10;

    // ITEM 4: ambii constructori initializeaza TOTI membrii
    // folosind lista de initializare (vezi Student.cpp).
    Student();
    Student(const std::string& nume, int varsta);

    bool adaugaNota(int nota);
    double medie() const;
    void afiseaza() const;

    const std::string& getNume() const { return nume; }
    int getVarsta() const { return varsta; }

    // ITEM 5: NU declaram constructor de copiere, operator= si destructor.
    // Compilatorul le genereaza automat, atunci cand sunt folosite:
    //   Student(const Student&)            -> copiaza membru cu membru
    //   Student& operator=(const Student&) -> atribuie membru cu membru
    //   ~Student()                         -> apeleaza destructorii membrilor
    // Array-ul note[] este copiat element cu element, iar std::string
    // se copiaza singur corect, deci versiunile generate sunt suficiente.

private:
    // ITEM 4: membrii se initializeaza in ORDINEA DECLARARII de aici,
    // nu in ordinea din lista de initializare. De aceea, in constructori
    // pastram exact aceeasi ordine: nume, varsta, note, nrNote.
    std::string nume;
    int varsta;
    int note[MAX_NOTE];
    int nrNote;
};

#endif
