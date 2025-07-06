#ifndef COACH_H
#define COACH_H

#include "Person.h"
#include "Team.h"
#include <string>
#include <iostream>

class Coach : public Person {
public:
    Coach(const std::string& name, Team& team);
    Coach(const Coach& other) = default;

    void displayInfo() const override;
    Person* clone() const override { return new Coach(*this); }

    void trainTeam(int amount);

private:
    Team& team;
};

#endif