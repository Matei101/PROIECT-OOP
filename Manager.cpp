#include "Manager.h"

Manager::Manager(const std::string& name, const Team& team, double budget)
    : name(name), team(team), budget(budget)
{}

bool Manager::buyPlayer(const Player& p) {
    if (budget >= p.getValue()) {
        team.addPlayer(p);
        budget -= p.getValue();
        return true;
    }
    return false;
}

bool Manager::sellPlayer(const std::string& playerName) {
    Player sold("", "", 0, 0);
    if (team.transferOutPlayer(playerName, sold)) {
        budget += sold.getValue();
        return true;
    }
    return false;
}

void Manager::trainPlayer(const std::string& playerName) {
    for (auto& p : team.getPlayers()) {
        if (p.getName() == playerName) {
            p.train(5);
            return;
        }
    }
}

void Manager::showStatus() const {
    std::cout << "Manager: " << name
              << ", Buget: $" << std::fixed << std::setprecision(2) << budget << "\n"
              << team;
}

Team& Manager::getTeam() { return team; }
