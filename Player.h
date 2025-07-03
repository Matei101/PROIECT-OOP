#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player {
public:
    Player(const std::string& name,
           const std::string& position,
           int skill,
           double value,
           int contractYears = 3);

    const std::string& getName() const;
    const std::string& getPosition() const;
    int getSkill() const;
    double getValue() const;
    int getContractYears() const;
    bool isAccidentat() const;

    void train(int amount);
    void accid();
    void recuperare();
    void decContract();

    friend std::ostream& operator<<(std::ostream& out, const Player& p);

private:
    std::string name;
    std::string position;
    int skill;
    double value;
    bool accidentat;
    int contractYears;
};

#endif // PLAYER_H
