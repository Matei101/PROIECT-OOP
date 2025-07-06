#ifndef TRAININGLOG_H
#define TRAININGLOG_H

#include <vector>
#include <string>
#include <map>

struct Session { std::string player; int amount; };

class TrainingLog {
public:
    void addSession(const std::string& player, int amount);
    void print() const;
private:
    std::vector<Session> sessions;
};

#endif // TRAININGLOG_H
