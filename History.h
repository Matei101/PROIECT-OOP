#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <string>

struct MatchRecord {
    std::string team1;
    int score1;
    std::string team2;
    int score2;
};

class History {
public:
    void add(const MatchRecord& r);
    void print() const;
private:
    std::vector<MatchRecord> records;
};

#endif // HISTORY_H
