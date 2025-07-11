#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"

class Team {
public:
    explicit Team(const std::string& name);
    Team(const Team& other);
    Team& operator=(const Team& other);
    ~Team();

    static constexpr size_t MAX_PLAYERS = 25;

    void addPlayer(const Player& p);
    double averageSkill() const;
    bool transferOutPlayer(const std::string& playerName, Player& outPlayer);
    void incarcaDinFisier(const std::string& filename);
    void afiseazaPePozitie(const std::string& poz) const;
    void afiseazaStatistici() const;
    void afiseazaTopJucatori(int n) const;
    void editeazaJucator(const std::string& nume);
    void transferRandom(Team& other);

    std::vector<Player>& getPlayers();
    const std::vector<Player>& getPlayers() const;

    const std::string& getName() const;

private:
    std::string name;
    std::vector<Player> players;
};

std::ostream& operator<<(std::ostream& out, const Team& t);

#endif // TEAM_H
