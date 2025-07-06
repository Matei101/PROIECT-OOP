#ifndef MANAGER_H
#define MANAGER_H

#include "Person.h"
#include "Team.h"
#include <string>

class Manager : public Person {
public:
    static constexpr double DEFAULT_BUDGET = 100.0;

    Manager(const std::string& name, const Team& team, double budget);
    Manager(const std::string& name, const Team& team);

    void displayInfo() const override;
    Person* clone() const override { return new Manager(*this); }

    bool buyPlayer(const Player& p);
    bool sellPlayer(const std::string& name);

    Team& getTeam();
    const Team& getTeam() const;

private:
    Team team;
    double budget;
};

#endif // MANAGER_H
