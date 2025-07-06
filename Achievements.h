#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include <string>
#include <map>

class Achievements {
public:
    void recordWin(const std::string& team);
    void recordSeasonEnd(const std::string& team, int points);
    void print() const;
private:
    std::map<std::string,int> winStreak;
    std::map<std::string,bool> unlocked;
};

#endif // ACHIEVEMENTS_H
