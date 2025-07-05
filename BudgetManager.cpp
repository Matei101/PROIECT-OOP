#include "BudgetManager.h"
#include "Exception.h"

BudgetManager::BudgetManager(double initialBalance)
  : balance(initialBalance)
{}

void BudgetManager::purchase(double cost) {
    if (cost > balance) {
        throw BudgetException(cost, balance);
    }
    balance -= cost;
}

double BudgetManager::getBalance() const {
    return balance;
}
