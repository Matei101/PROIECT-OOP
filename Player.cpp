#include "Player.h"

Player::Player(const std::string& name,
               const std::string& position,
               int skill,
               double value,
               int contractYears)
    : Person(name)
    , position(position)
    , skill(skill)
    , value(value)
    , accidentat(false)
    , contractYears(contractYears)
{}

void Player::displayInfo() const {
    std::cout << "Player: " << getName()
              << ", Position: " << position
              << ", Skill: " << skill << '\n';
}

void Player::train(int amount) {
    skill += amount;
    value += amount * 1.5;
}

void Player::accid() {
    accidentat = true;
}

void Player::recuperare() {
    accidentat = false;
}

void Player::decContract() {
    if (contractYears > 0) --contractYears;
}

int Player::getSkill() const {
    return skill;
}

double Player::getValue() const {
    return value;
}

std::string Player::getPosition() const {
    return position;
}

bool Player::isAccidentat() const {
    return accidentat;
}

int Player::getContractYears() const {
    return contractYears;
}

std::ostream& operator<<(std::ostream& out, const Player& p) {
    out << p.getName() << " [" << p.position << "] - Skill: " << p.skill
        << ", Value: $" << std::fixed << std::setprecision(2) << p.value;
    if (p.accidentat) out << " [ACCIDENTAT]";
    out << ", Contract: " << p.contractYears << " ani";
    return out;
}
