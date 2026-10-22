#include <chrono>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

#include "Account.h"
#include "ShallowCopyAccount.h"

static void title(const char* text) {
    std::cout << "\n==================================================\n"
              << text
              << "\n==================================================\n";
}

static void showLive() {
    std::cout << "  -> tablouri de istoric alocate acum pe heap: "
              << Account::liveHistories() << "\n";
}

// Creeaza un cont mare. Folosita in demonstratia de move.
static Account makeBigAccount(const std::string& owner, int transactions) {
    Account acc(owner);
    for (int i = 0; i < transactions; ++i) {
        acc.deposit(1.0);
    }
    return acc;
}

int main(int argc, char* argv[]) {
    bool crashMode = argc > 1 && std::strcmp(argv[1], "--crash") == 0;
    showLive();
    {
        std::cout << "  Intram intr-un bloc si cream doua conturi..." << "\n";
        Account ana("Ana", 500);
        ana.withdraw(200);
        ana.withdraw(10000);  // refuzata: regula e verificata in clasa
        ana.deposit(-50);     // refuzata: suma invalida
        ana.deposit(50);
        ana.printHistory();

        Account bogdan("Bogdan", 100);
        bogdan.printHistory();
        
        std::cout << "  Iesim din bloc...\n";
    }
    showLive();

    std::cout << "\n  Demonstratie shallow copy (copie superficiala):\n";
    if (!crashMode) {
        ShallowAccount original(1);
        original.addTransaction(100);
        original.addTransaction(200);

        // Copy constructorul generat de compilator copiaza doar ADRESA.
        // Copia e creata cu new si nu o stergem intentionat: delete pe ea ar
        // elibera a doua oara acelasi tablou (vezi rularea cu --crash).
        ShallowAccount* copy = new ShallowAccount(original);
        copy->setId(2);
        std::cout << "  (Nu apare niciun mesaj de copiere: copy constructorul\n"
                  << "  generat de compilator nu afiseaza nimic.)\n";

        std::cout << "  Adresa istoricului: original " << original.historyAddress()
                  << ", copie " << copy->historyAddress() << "  <- ACEEASI!\n";

        std::cout << "  Depunem 50 in contul original:\n";
        original.addTransaction(50);
        original.printHistory();
        std::cout << "  Retragem 999 DOAR din copie...\n";
        copy->addTransaction(-999);
        std::cout << "  ...si tranzactia originalului a fost suprascrisa:\n";
        original.printHistory();

        std::cout << "  La final ambele obiecte ar face delete[] pe aceeasi adresa\n"
                  << "  (double free) si programul s-ar opri brusc. Ruleaza\n"
                  << "  './tema --crash' ca sa vezi asta.\n";
    } else {
        std::cout << "  Mod --crash: copia este pe stiva, deci la iesirea din bloc\n"
                  << "  se apeleaza ambii destructori.\n";
        {
            ShallowAccount original(1);
            original.addTransaction(100);
            ShallowAccount copy = original;  // copie superficiala
            copy.setId(2);
            std::cout << "  Iesim din bloc...\n";
        }
        std::cout << "  (Daca vezi acest mesaj, ai avut noroc: comportament nedefinit.)\n";
        return 1;
    }

    std::cout << "\n  Demonstratie deep copy (copie profunda):\n";
    {
        Account elena("Elena", 300);
        elena.withdraw(100);

        std::cout << "  Facem o copie a contului ca sa simulam o retragere mare:\n";
        Account simulation = elena;  // apeleaza copy constructorul nostru
        simulation.withdraw(150);
        simulation.deposit(1000);

        std::cout << "  Originalul a ramas neschimbat:\n";
        elena.printHistory();
        std::cout << "  Copia are propriul istoric:\n";
        simulation.printHistory();
        std::cout << "  La iesire, fiecare destructor elibereaza alt tablou:\n";
    }

   std::cout << "\n  Demonstratie move constructor:\n";
    {
        std::cout << "  a) std::move: transferam contul fara sa copiem istoricul\n";
        Account florin("Florin", 70);
        const double* before = florin.historyAddress();
        Account newOwner = std::move(florin);
        std::cout << "  Istoricul era la " << before << " si acum e la "
                  << newOwner.historyAddress() << " (acelasi tablou, nicio alocare)\n";
        std::cout << "  Obiectul din care am mutat a ramas gol: sold "
                  << florin.getBalance() << ", " << florin.getTransactionCount()
                  << " tranzactii\n";
        newOwner.printHistory();
    }

    {
        std::cout << "\n  b) std::vector: la marire, elementele sunt MUTATE, nu copiate\n"
                  << "     (pentru ca move constructorul este noexcept)\n";
        std::vector<Account> bank;
        bank.push_back(Account("Gabi", 10));
        bank.push_back(Account("Horia", 20));
        bank.push_back(Account("Ioana", 30));
        std::cout << "  Vectorul are " << bank.size() << " conturi. Se distruge:\n";
    }

    {
        std::cout << "\n  c) Cost: copie vs. mutare pentru un cont cu 1.000.000 tranzactii\n";
        std::streambuf* old = std::cout.rdbuf(nullptr);
        Account big = makeBigAccount("Mare", 1000000);
        std::cout.rdbuf(old);

        auto t0 = std::chrono::steady_clock::now();
        Account copied = big;
        auto t1 = std::chrono::steady_clock::now();
        Account moved = std::move(big);
        auto t2 = std::chrono::steady_clock::now();

        auto us = [](auto d) {
            return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
        };
        std::cout << "  Copiere: " << us(t1 - t0) << " us (aloca si copiaza 1.000.000 valori)\n"
                  << "  Mutare:  " << us(t2 - t1) << " us (copiaza doar un pointer)\n";
    }

    title("FINAL");
    showLive();
    return 0;
}
