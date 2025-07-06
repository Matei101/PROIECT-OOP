
#include "Season.h"
#include "Match.h"
#include <algorithm>
#include <iostream>

Season::Season(const std::vector<Team*>& teams)
  : teams(teams), standings()
{}

void Season::playFullSeason() {
    for (auto* t : teams) {
        standings.emplace_back(t->getName());
    }
    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            Match m(*teams[i], *teams[j]);
            m.simulate();
            standings[i].actualizeaza(m.getScore1(), m.getScore2());
            standings[j].actualizeaza(m.getScore2(), m.getScore1());
        }
    }
    std::sort(standings.begin(), standings.end(),
              [](const Clasament& a, const Clasament& b) {
                  return a.puncte > b.puncte;
              });
}

void Season::printStandings() const {
    for (const auto& c : standings) {
        std::cout << c.teamName
                  << " | Meciuri: " << c.meciuri
                  << " | Puncte: "   << c.puncte
                  << "\n";
    }
}
