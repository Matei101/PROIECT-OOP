#include "Economy.h"
#include "TimeUtils.h"

void Economy::addSponsor(const std::string& team, double amount) {
    balance_[team] += amount;
    history_.push_back({Transaction::Type::Sponsor, amount, team, makeTimestamp()});
}

void Economy::takeLoan(const std::string& team, double amount) {
    debt_[team] += amount;
    balance_[team] += amount;
    history_.push_back({Transaction::Type::Loan, amount, team, makeTimestamp()});
}

bool Economy::repayLoan(const std::string& team, double amount) {
    auto it = debt_.find(team);
    if (it == debt_.end() || it->second < amount) return false;
    it->second -= amount;
    balance_[team] -= amount;
    history_.push_back({Transaction::Type::Repay, amount, team, makeTimestamp()});
    return true;
}

double Economy::getBalance(const std::string& team) const {
    auto it = balance_.find(team);
    return it != balance_.end() ? it->second : 0.0;
}

void Economy::applyInterest(double rate) {
    for (auto& kv : debt_) {
        double interest = kv.second * rate;
        kv.second += interest;
        history_.push_back({Transaction::Type::Interest, interest, kv.first, makeTimestamp()});
    }
}

const std::vector<Transaction>& Economy::getHistory() const {
    return history_;
}

std::string Economy::makeTimestamp() const {
    return TimeUtils::now();
}
