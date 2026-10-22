#pragma once

#include <cstddef>
#include <iostream>

//acelasi principiu ca la clasa Account, dar fara deep copy si move constructor
class ShallowAccount {
public:
    explicit ShallowAccount(int id) : id(id), transactions(new double[8]), count(0) {
        std::cout << "  [Shallow constructor] #" << id << ", istoric la "
                  << transactions << "\n";
    }

    ~ShallowAccount() {
        std::cout << "  [Shallow destructor] #" << id << " face delete[] pe "
                  << transactions << "\n";
        delete[] transactions;
    }

    void addTransaction(double amount) {
        if (count < 8) {
            transactions[count++] = amount;
        }
    }

    void setId(int newId) { id = newId; }
    const double* historyAddress() const { return transactions; }

    void printHistory() const {
        std::cout << "  #" << id << " (istoric la " << transactions << "):";
        for (std::size_t i = 0; i < count; ++i) {
            std::cout << " " << transactions[i];
        }
        std::cout << "\n";
    }

private:
    int id;
    double* transactions;
    std::size_t count;
};