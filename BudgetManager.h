#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

class BudgetManager {
public:
    explicit BudgetManager(double initialBalance);
    void purchase(double cost);      // throws BudgetException
    double getBalance() const;
private:
    double balance;
};

#endif // BUDGETMANAGER_H
