#include "History.h"
#include <iostream>

void History::add(const MatchRecord& r) {
    records.push_back(r);
}

void History::print() const {
    if (records.empty()) {
        std::cout << "No matches played yet.\n";
        return;
    }
    std::cout << "\n=== Match History ===\n";
    for (const auto& r : records) {
        std::cout
            << r.team1 << " " << r.score1
            << " - " << r.score2 << " " << r.team2
            << "\n";
    }
    std::cout << "=====================\n";
}
