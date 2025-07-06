#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Person.h"
#include "Player.h"
#include "Manager.h"
#include "Coach.h"
#include "Match.h"
#include "Clasament.h"
#include "History.h"
#include "Season.h"
#include "Stats.h"
#include "Achievements.h"
#include "TrainingLog.h"
#include "Commentary.h"
#include "Chemistry.h"

class Game {
public:
    Game(Team& t1, Team& t2);
    Game(const Game& other);
    Game& operator=(Game other);
    friend void swap(Game& a, Game& b) noexcept;
    ~Game();
    void run();

private:
    void displayMenu() const;
    void handleTransfer();
    void handleSell();
    void simulateMatch();
    void handleTrain();
    void handleCoachTrain();
    void filterByPosition();
    void showStatistics();
    void topJucatori();
    void editeazaJucator();
    void transferRandom();
    void aplicaAccidentari(Team& team);
    void verificaContracte();
    void oferteTransfer();
    void showHistory() const;
    void simulateSeason();
    void showSeasonStandings() const;
    void showStats() const;
    void viewAchievements() const;
    void viewTrainingLog() const;
    void viewChemistry() const;
    void saveStandingsToFile(const std::string& filename) const;

    std::vector<Person*> actors;
    Person*            currentActor = nullptr;
    std::vector<Player> transferList;
    Manager            manager1;
    Manager            manager2;
    Coach              coach1;
    Clasament          clasament1;
    Clasament          clasament2;
    History            history;
    Season*            season = nullptr;
    Achievements       achievements;
    TrainingLog        trainLog;
    Chemistry          chemistry;
};

#endif // GAME_H
