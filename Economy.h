#ifndef ECONOMY_H
#define ECONOMY_H

#include <string>
#include <map>
#include <vector>

struct Transaction {
    enum class Type { Sponsor, Loan, Repay, Interest } type;
    double amount;
    std::string team;
    std::string timestamp;
};

class Economy {
public:
    void addSponsor(const std::string& team, double amount);
    void takeLoan(const std::string& team, double amount);
    bool repayLoan(const std::string& team, double amount);
    double getBalance(const std::string& team) const;
    void applyInterest(double rate);
    const std::vector<Transaction>& getHistory() const;

private:
    std::map<std::string, double> balance_;
    std::map<std::string, double> debt_;
    std::vector<Transaction> history_;
    std::string makeTimestamp() const;
};

#endif // ECONOMY_H
