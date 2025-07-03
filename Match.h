#ifndef MATCH_H
#define MATCH_H

#include <iostream>
#include <cstdlib>
#include "Team.h"

class Match {
public:
    Match(const Team& t1, const Team& t2);

    void simulate();
    void showResult() const;
    int getScore1() const;
    int getScore2() const;

private:
    const Team& team1;
    const Team& team2;
    int score1;
    int score2;
};

#endif // MATCH_H
