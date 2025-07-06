#include "Stats.h"
#include <numeric>
#include <algorithm>
#include <sstream>

TeamStats Stats::compute(const Team& team) {
    const auto& players = team.getPlayers();
    TeamStats s{0.0, 0.0, 0};
    if (!players.empty()) {
        s.averageSkill = std::accumulate(
            players.begin(), players.end(), 0.0,
            [](double acc, const Player& p){ return acc + p.getSkill(); }
        ) / players.size();
        s.totalValue = std::accumulate(
            players.begin(), players.end(), 0.0,
            [](double acc, const Player& p){ return acc + p.getValue(); }
        );
        s.injuries = std::count_if(
            players.begin(), players.end(),
            [](const Player& p){ return p.isAccidentat(); }
        );
    }
    return s;
}

std::string Stats::format(const TeamStats& s) {
    std::ostringstream os;
    os << "AvgSkill=" << s.averageSkill
       << ", TotalValue=$" << s.totalValue
       << ", Injuries=" << s.injuries;
    return os.str();
}
