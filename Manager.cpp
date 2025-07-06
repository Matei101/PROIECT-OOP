#include "Manager.h"
#include "Exception.h"
#include <iostream>
#include <iomanip>

Manager::Manager(const std::string& name, const Team& team, double budget)
    : Person(name)
    , team(team)
    , budget(budget)
{
    if (budget < 0)
        throw BudgetException(0, budget);

}

Manager::Manager(const std::string& name, const Team& team)
    : Manager(name, team, DEFAULT_BUDGET)
{}

void Manager::displayInfo() const {
    std::cout << "Manager: " << getName()
              << ", Buget: $" << std::fixed << std::setprecision(2)
              << budget << "\n";
    std::cout << team;
}

bool Manager::buyPlayer(const Player& p) {
    if (budget < p.getValue()) return false;
    team.addPlayer(p);
    budget -= p.getValue();
    return true;
}

bool Manager::sellPlayer(const std::string& name) {
    Player out("", "", 0, 0);
    if (!team.transferOutPlayer(name, out)) return false;
    budget += out.getValue();
    return true;
}

Team& Manager::getTeam() {
    return team;
}

const Team& Manager::getTeam() const {
    return team;
}
