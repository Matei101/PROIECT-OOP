#include "Achievements.h"
#include <iostream>

void Achievements::recordWin(const std::string& team) {
    winStreak[team]++;
    if (winStreak[team] >= 5 && !unlocked[team]) {
        unlocked[team] = true;
        std::cout << "Achievement: " << team << " won 5 in a row!\n";
    }
}

void Achievements::recordSeasonEnd(const std::string& team, int points) {
    if (points >= 30 && !unlocked[team]) {
        unlocked[team] = true;
        std::cout << "Achievement: " << team << " scored 30+ points in a season!\n";
    }
}

void Achievements::print() const {
    std::cout << "\n=== Achievements ===\n";
    for (auto& p : unlocked) {
        if (p.second)
            std::cout << p.first << " achievement unlocked\n";
    }
    std::cout << "====================\n";
}
