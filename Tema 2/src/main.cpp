#include <iostream>
#include "Student.h"
#include "StudentUnic.h"

int main()
{
    std::cout << "========== ITEM 4: initializarea obiectelor ==========\n";

    // int x;          // gresit pentru ca este initializat cu o valoare aleatorie
    int x = 0;         // corect
    std::cout << "x = " << x << "\n";

    Student s0;        // constructorul implicit initializeaza toti membrii
    s0.afiseaza();

    Student s1("Ana Popescu", 20);
    s1.adaugaNota(9);
    s1.adaugaNota(10);
    s1.adaugaNota(8);
    s1.afiseaza();

    std::cout << "\n========== ITEM 5: functii generate de compilator ==========\n";

    //constructor de copiere generat automat
    Student s2 = s1;
    std::cout << "s2 = copie a lui s1 (copy constructor generat):\n";
    s2.adaugaNota(5);  // modificam doar copia
    s1.afiseaza();
    s2.afiseaza();
    std::cout << "-> copia e independenta: array-ul note[] a fost copiat element cu element\n";

    // Student nu are operator= scris de noi -> e generat automat
    Student s3;
    s3 = s1;
    std::cout << "s3 = s1 (operator= generat):\n";
    s3.afiseaza();

    // Destructorul generat va fi apelat automat la finalul lui main
    // pentru s0, s1, s2, s3 (si pentru u1, u2 de mai jos).

    std::cout << "\n========== ITEM 6: interzicerea copierii ==========\n";

    StudentUnic u1("Ion Ionescu", 21);
    u1.adaugaNota(10);
    u1.adaugaNota(9);

    StudentUnic u2("Maria Georgescu", 22);
    u2.adaugaNota(7);

    u1.afiseaza();
    u2.afiseaza();

    // Daca decomentam liniile de mai jos, programul NU se compileaza:
    //
    // StudentUnic u3 = u1;
    //   error: use of deleted function 'StudentUnic::StudentUnic(const StudentUnic&)'
    //
    // u2 = u1;
    //   error: use of deleted function 'StudentUnic& StudentUnic::operator=(const StudentUnic&)'
    //
    // Astfel nu pot exista doi studenti cu acelasi ID.

    std::cout << "-> StudentUnic nu poate fi copiat, fiecare ID ramane unic\n";

    return 0;
}
