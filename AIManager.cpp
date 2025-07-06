#include "AIManager.h"
#include <algorithm>
#include <cstdlib>

std::vector<Player> AIManager::suggestTransfers(const Team& team, int count) {
    auto players = team.getPlayers();
    std::sort(players.begin(), players.end(),
              [](auto& a, auto& b){ return a.getValue() > b.getValue(); });
    if ((int)players.size() > count) players.resize(count);
    return players;
}

void AIManager::adjustLineup(Team& team) {
    auto& p = team.getPlayers();
    if (p.size() < 2) return;
    int i = std::rand() % p.size();
    int j = std::rand() % p.size();
    std::swap(p[i], p[j]);
}

void AIManager::setFormation(Team& team, const std::vector<std::string>& positions) {
    auto& players = team.getPlayers();
    for (size_t i = 0; i < positions.size() && i < players.size(); ++i) {
        players[i] = Player(players[i].getName(),
                            positions[i],
                            players[i].getSkill(),
                            players[i].getValue());
    }
}
