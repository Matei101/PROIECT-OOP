#ifndef MANAGER_H
#define MANAGER_H

#include "Person.h"
#include "Team.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <iomanip>

class Manager : public Person {
public:
    Manager(const std::string& name, const Team& team, double budget);
    Manager(const Manager& other) = default;

    void displayInfo() const override;
    Person* clone() const override { return new Manager(*this); }

    bool buyPlayer(const Player& p);
    bool sellPlayer(const std::string& playerName);

    Team& getTeam();
    const Team& getTeam() const;

    friend std::ostream& operator<<(std::ostream& out, const Manager& m);

private:
    Team team;
    double budget;
};

#endif
