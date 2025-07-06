#ifndef STATS_H
#define STATS_H

#include "Team.h"
#include <string>

struct TeamStats {
    double averageSkill;
    double totalValue;
    size_t injuries;
};

class Stats {
public:
    static TeamStats compute(const Team& team);
    static std::string format(const TeamStats& s);
};

#endif // STATS_H
