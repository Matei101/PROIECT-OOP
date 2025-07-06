#ifndef SEASON_H
#define SEASON_H

#include <vector>
#include "Team.h"
#include "Clasament.h"

class Season {
public:
    Season(const std::vector<Team*>& teams);
    void playFullSeason();
    void printStandings() const;

private:
    std::vector<Team*> teams;
    std::vector<Clasament> standings;
};

#endif // SEASON_H
