# Lucrarea 4 – Effective C++ (Item 4, 5, 6)

Proiect C++ care demonstrează trei reguli din *Effective C++* (Scott Meyers):

- **Item 4:** inițializează obiectele înainte să fie folosite.
- **Item 5:** cunoaște funcțiile pe care C++ le scrie și le apelează automat.
- **Item 6:** interzice explicit funcțiile generate de compilator pe care nu le vrei.

## Structura proiectului

```
tema2/
├── CMakeLists.txt
├── include/
│   ├── Student.h
│   └── StudentUnic.h
└── src/
    ├── main.cpp
    ├── Student.cpp
    └── StudentUnic.cpp
```

## Clase

### `Student` (Item 4 și Item 5)
Conține un nume, o vârstă și un array de până la 10 note.

- **Item 4:** toți membrii sunt inițializați în lista de inițializare a constructorilor. Array-ul de note pornește cu zero, iar membrii sunt inițializați în ordinea în care sunt declarați.
- **Item 5:** clasa nu declară constructor de copiere, `operator=` sau destructor. Compilatorul le generează automat, iar în `main` se arată că o copie este independentă de original.

### `StudentUnic` (Item 6)
Moștenește `Student` și adaugă un `id` unic (`const int`), generat automat începând de la 1000.

- **Item 6:** copierea este interzisă cu `= delete`, ca să nu existe doi studenți cu același ID. Varianta din carte (C++98, declarat `private` și nedefinit) apare comentată în header.
- Generatorul de ID-uri folosește un `static` local. Acesta se inițializează garantat la primul apel, ceea ce ține tot de Item 4.

## Compilare și rulare

Cu CMake (din folderul proiectului):

```
mkdir -p build && cd build
cmake ..
make
./tema2
```

Fără CMake:

```
clang++ -std=c++11 -Wall -Iinclude src/*.cpp -o tema2
./tema2
```

## Ce afișează programul

Programul are trei secțiuni, câte una pentru fiecare item:

1. **Item 4:** un student creat cu constructorul implicit și unul creat cu date, ambii complet inițializați.
2. **Item 5:** copii făcute cu constructorul de copiere și cu `operator=` generate de compilator.
3. **Item 6:** doi studenți cu ID-uri diferite. În `main.cpp` sunt comentate liniile de copiere care nu compilează, împreună cu eroarea primită.
