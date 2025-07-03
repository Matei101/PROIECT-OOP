#include "Player.h"
#include <iomanip>

Player::Player(const std::string& name,
               const std::string& position,
               int skill,
               double value,
               int contractYears)
    : name(name)
    , position(position)
    , skill(skill)
    , value(value)
    , accidentat(false)
    , contractYears(contractYears)
{}

const std::string& Player::getName() const { return name; }
const std::string& Player::getPosition() const { return position; }
int Player::getSkill() const { return skill; }
double Player::getValue() const { return value; }
int Player::getContractYears() const { return contractYears; }
bool Player::isAccidentat() const { return accidentat; }

void Player::train(int amount) {
    skill += amount;
    value += amount * 1.5;
}

void Player::accid() { accidentat = true; }
void Player::recuperare() { accidentat = false; }
void Player::decContract() { if (contractYears > 0) --contractYears; }

std::ostream& operator<<(std::ostream& out, const Player& p) {
    out << p.name << " [" << p.position << "] - Skill: " << p.skill
        << ", Value: $" << std::fixed << std::setprecision(2) << p.value;
    if (p.accidentat) out << " [ACCIDENTAT]";
    out << ", Contract: " << p.contractYears << " ani";
    return out;
}
