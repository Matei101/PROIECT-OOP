#include "Coach.h"

Coach::Coach(const std::string& name, Team& team)
    : Person(name)
    , team(team)
{}

void Coach::displayInfo() const {
    std::cout << "Coach: " << getName()
              << ", Team: " << team.getName() << '\n';
}

void Coach::trainTeam(int amount) {
    for (auto& p : team.getPlayers()) {
        p.train(amount);
    }
}
