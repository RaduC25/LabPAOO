#ifndef STUDENT_UNIC_H
#define STUDENT_UNIC_H

#include "Student.h"

// =====================================================================
//  Clasa StudentUnic - demonstreaza ITEM 6
//  Are toate campurile din Student + un id unic.
//  Doi studenti cu acelasi id nu au voie sa existe, deci copierea
//  trebuie interzisa explicit.
// =====================================================================
class StudentUnic : public Student {
public:
    StudentUnic(const std::string& nume, int varsta);

    // ITEM 6: interzicem explicit functiile pe care compilatorul
    // le-ar genera altfel automat (vezi ITEM 5).
    StudentUnic(const StudentUnic&) = delete;
    StudentUnic& operator=(const StudentUnic&) = delete;

    // Varianta din carte (C++98), echivalenta, dar cu eroare mai tarzie (la link):
    // private:
    //     StudentUnic(const StudentUnic&);             // declarat, nedefinit
    //     StudentUnic& operator=(const StudentUnic&);  // declarat, nedefinit

    int getId() const { return id; }
    void afiseaza() const;

private:
    const int id;  // ITEM 4: un membru const POATE fi initializat
                   // DOAR in lista de initializare

    static int genereazaId();
};

#endif
