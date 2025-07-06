#ifndef SEASON_H
#define SEASON_H

#include <vector>
#include "Team.h"
#include "Clasament.h"

class Season {
public:
    explicit Season(const std::vector<Team*>& teams);
    void playFullSeason();
    void printStandings() const;
private:
    std::vector<Clasament> standings;
    std::vector<Team*> teams;
    void initStandings();
};

#endif // SEASON_H
