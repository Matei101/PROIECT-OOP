#ifndef AIMANAGER_H
#define AIMANAGER_H

#include <vector>
#include "Team.h"

class AIManager {
public:
    std::vector<Player> suggestTransfers(const Team& team, int count);
    void adjustLineup(Team& team);
    void setFormation(Team& team, const std::vector<std::string>& positions);
};

#endif // AIMANAGER_H
