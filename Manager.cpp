#include "Manager.h"

Manager::Manager(const std::string& name,
                 const Team& team,
                 double budget)
    : Person(name)
    , team(team)
    , budget(budget)
{}

void Manager::displayInfo() const {
    std::cout << "Manager: " << getName()
              << ", Buget: $" << std::fixed << std::setprecision(2) << budget << '\n';
}

bool Manager::buyPlayer(const Player& p) {
    if (budget < p.getValue()) {
        std::cout << "Buget insuficient pentru " << p.getName() << '\n';
        return false;
    }
    team.addPlayer(p);
    budget -= p.getValue();
    return true;
}

bool Manager::sellPlayer(const std::string& playerName) {
    Player soldPlayer("", "", 0, 0);
    if (team.transferOutPlayer(playerName, soldPlayer)) {
        budget += soldPlayer.getValue();
        return true;
    }
    return false;
}

Team& Manager::getTeam() {
    return team;
}

const Team& Manager::getTeam() const {
    return team;
}

std::ostream& operator<<(std::ostream& out, const Manager& m) {
    out << "Manager: " << m.getName()
        << ", Buget: $" << std::fixed << std::setprecision(2) << m.budget << "\n"
        << m.team;
    return out;
}