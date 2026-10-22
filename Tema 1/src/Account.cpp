#include "Account.h"

#include <algorithm>
#include <iostream>
#include <utility>

#define TRANSACTION_HISTORY_INITIAL_CAPACITY 10

int Account::nextId = 1; //incepem id-ul de la 1
int Account::liveHistoryCount = 0;

// 3. Initializarea membrilor in lista de initializare a constructorului.
//    - 'id' este const, deci NU poate primi valoare in corpul constructorului

Account::Account(const std::string& ownerName, double initialDeposit)
    : id(nextId++),
      owner(ownerName),
      balance(0.0),
      transactions(new double[TRANSACTION_HISTORY_INITIAL_CAPACITY]),
      count(0),
      capacity(TRANSACTION_HISTORY_INITIAL_CAPACITY) {
        ++liveHistoryCount;
        std::cout << "[Constructor] cont #" << id << " (" << owner<< "), istoric alocat la " << transactions << "\n";
        if (initialDeposit > 0) {
            deposit(initialDeposit);
        }
    }


// 5. Copy constructor, cu deep copy
Account::Account(const Account& other)
    : id(nextId++),
      owner(other.owner + " (copie)"),
      balance(other.balance),
      transactions(new double[other.capacity]),
      count(other.count),
      capacity(other.capacity) {
        std::copy(other.transactions, other.transactions + other.count, transactions); // aici se face copia efectiva a tabloului de tranzactii
        ++liveHistoryCount;
        std::cout << "[Copy constructor] cont #" << id << " copiat din #"<< other.id << ", istoric NOU la " << transactions<< " (originalul are " << other.transactions << ")\n";
    }

// 6. Move constructor.
Account::Account(Account&& other) noexcept
    : id(other.id),
      owner(std::move(other.owner)),
      balance(other.balance),
      transactions(other.transactions),
      count(other.count),
      capacity(other.capacity) {
    other.transactions = nullptr;  //punem pe null tabloul de tranzactii al obiectului mutat, ca sa nu fie sters la destructor
    other.balance = 0.0;
    other.count = 0;
    other.capacity = 0;
    std::cout << "[Move constructor] cont #" << id<< " mutat, istoricul ramane la " << transactions << "\n";
}


// 4. Destructor
Account::~Account() {
    if (transactions != nullptr) {
        --liveHistoryCount;
        std::cout << "  [Destructor] cont #" << id << " elibereaza istoricul de la "<< transactions << "\n";
    } else {
        std::cout << "  [Destructor] cont #" << id<< " (gol dupa move, nu are ce elibera)\n";
    }
    delete[] transactions;
}

void Account::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "  Suma invalida pentru depunere: " << amount << "\n";
        return;
    }
    balance += amount;
    addTransaction(amount);
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        std::cout << "  Retragere refuzata: " << amount<< " (sold " << balance << ")\n";
        return false;
    }
    balance -= amount;
    addTransaction(-amount);
    return true;
}

int Account::getId() const { return id; }
const std::string& Account::getOwner() const { return owner; }
double Account::getBalance() const { return balance; }
std::size_t Account::getTransactionCount() const { return count; }
const double* Account::historyAddress() const { return transactions; }

void Account::printHistory() const {
    std::cout << "  Cont #" << id << " (" << owner << "), sold " << balance
              << ", " << count << " tranzactii:";
    for (std::size_t i = 0; i < count && i < 10; ++i) {
        std::cout << " " << (transactions[i] > 0 ? "+" : "") << transactions[i];
    }
    if (count > 10) {
        std::cout << " ...";
    }
    std::cout << "\n";
}

int Account::liveHistories() { return liveHistoryCount; }

void Account::addTransaction(double amount) {
    if (count == capacity) {
        grow();
    }
    transactions[count++] = amount;
}
//mareste numarul de tranzactii alocate pe heap (dublare capacitate)
void Account::grow() {
    bool hadBuffer = transactions != nullptr;  // false pentru un cont golit prin move
    std::size_t newCapacity = 0;
    if (capacity == 0) {
        newCapacity = TRANSACTION_HISTORY_INITIAL_CAPACITY;
    }
    else{
        newCapacity = capacity * 2;
    }
    double* bigger = new double[newCapacity];
    std::copy(transactions, transactions + count, bigger);
    delete[] transactions;
    transactions = bigger;
    capacity = newCapacity;
    if (!hadBuffer) {
        ++liveHistoryCount;
    }
}
