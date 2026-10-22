#pragma once

#include <cstddef>
#include <string>

// Cont bancar 
// istoricul tranzactiilor intr-un tablou alocat dinamic (double*)
class Account {
public:
    Account(const std::string& ownerName, double initialDeposit = 0.0);
    Account(const Account& other);      // deep copy
    Account(Account&& other) noexcept;  // move 
    ~Account();                         // destructor

    void deposit(double amount);
    bool withdraw(double amount);

    int getId() const;
    const std::string& getOwner() const;
    double getBalance() const;
    std::size_t getTransactionCount() const;
    const double* historyAddress() const;  // doar pentru demonstratie

    void printHistory() const;

    // Cate tablouri de istoric sunt inca alocate pe heap (pentru demonstratie).
    static int liveHistories();

private:
    void addTransaction(double amount);
    void grow();

    // campuri
    const int id;               // se seteaza o singura data in constructor
    std::string owner;
    double balance;
    double* transactions;       // resursa de pe heap
    std::size_t count;
    std::size_t capacity;

    static int nextId;
    static int liveHistoryCount;
};
