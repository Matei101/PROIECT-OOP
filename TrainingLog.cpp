#include "TrainingLog.h"
#include <iostream>

void TrainingLog::addSession(const std::string& player, int amount) {
    sessions.push_back({player,amount});
}

void TrainingLog::print() const {
    std::cout << "\n=== Training Log ===\n";
    for (auto& s : sessions)
        std::cout << s.player << ": +" << s.amount << " skill\n";
    std::cout << "====================\n";
}
