#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Team.h"

class Manager {
public:
    Manager(const std::string& name, const Team& team, double budget);

    bool buyPlayer(const Player& p);
    bool sellPlayer(const std::string& playerName);
    void trainPlayer(const std::string& playerName);
    void showStatus() const;

    Team& getTeam();

private:
    std::string name;
    Team team;
    double budget;
};

#endif // MANAGER_H
