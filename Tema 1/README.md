# Tema: Cont bancar cu istoric

Clasa `Account` tine istoricul tranzactiilor intr-un tablou alocat dinamic
(`double*`). Pentru ca detine memorie pe heap, are nevoie de destructor,
copy constructor si move constructor scrise de mana.

## Structura

```
tema-cont-bancar/
├── CMakeLists.txt
├── include/
│   ├── Account.h          clasa principala
│   └── ShallowCopyAccount.h   exemplu fara copy constructor
└── src/
    ├── Account.cpp
    └── main.cpp           
```

## Build si rulare

```
cmake -S . -B build
cmake --build build
./build/tema           # demonstratia completa
./build/tema --crash   # arata double free-ul copiei superficiale
```