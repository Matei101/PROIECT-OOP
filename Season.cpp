#include "Season.h"
#include "Match.h"
#include <algorithm>
#include <iostream>

Season::Season(const std::vector<Team*>& t)
    : teams(t)
{
    initStandings();
}

void Season::initStandings() {
    standings.clear();
    for (auto* team : teams)
        standings.emplace_back(team->getName());
}

void Season::playFullSeason() {
    int n = teams.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Match m(*teams[i], *teams[j]);
            m.simulate();
            int s1 = m.getScore1();
            int s2 = m.getScore2();
            standings[i].actualizeaza(s1, s2);
            standings[j].actualizeaza(s2, s1);
        }
    }
}

void Season::printStandings() const {
    auto sorted = standings;
    std::sort(sorted.begin(), sorted.end(),
              [](auto& a, auto& b){ return a.puncte > b.puncte; });
    std::cout << "\n=== Season Standings ===\n";
    for (const auto& e : sorted) {
        e.afiseaza();
    }
    std::cout << "\n";
}
