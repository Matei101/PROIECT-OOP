#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"
#include <string>
#include <iostream>
#include <iomanip>

class Player : public Person {
public:
    Player();
    Player(const std::string& name,
           const std::string& position,
           int skill,
           double value,
           int contractYears = 3);
    Player(const Player& other) = default;

    void displayInfo() const override;
    Person* clone() const override { return new Player(*this); }

    void train(int amount);
    void accid();
    void recuperare();
    void decContract();

    int getSkill() const;
    double getValue() const;
    const std::string& getPosition() const;
    bool isAccidentat() const;
    int getContractYears() const;

    friend std::ostream& operator<<(std::ostream& out, const Player& p);

private:
    std::string position;
    int skill;
    double value;
    bool accidentat;
    int contractYears;
};

#endif // PLAYER_H
