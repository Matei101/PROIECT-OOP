#include "Match.h"

Match::Match(const Team& t1, const Team& t2)
    : team1(t1), team2(t2), score1(0), score2(0)
{}

void Match::simulate() {
    double avg1 = team1.averageSkill();
    double avg2 = team2.averageSkill();
    score1 = static_cast<int>(avg1) % 5 + rand() % 3;
    score2 = static_cast<int>(avg2) % 5 + rand() % 3;
}

void Match::showResult() const {
    std::cout << "Rezultat meci: " << team1.getName() << " " << score1
              << " - " << score2 << " " << team2.getName() << "\n";
}

int Match::getScore1() const { return score1; }
int Match::getScore2() const { return score2; }
