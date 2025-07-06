#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Person.h"
#include "Player.h"
#include "Manager.h"
#include "Coach.h"
#include "Match.h"
#include "Clasament.h"

class Game {
public:
    Game(Team& t1, Team& t2);
    Game(const Game& other);
    Game& operator=(Game other);
    friend void swap(Game& first, Game& second) noexcept;
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

    std::vector<Person*> actors;
    Person* currentActor = nullptr;
    std::vector<Player> transferList;
    Manager manager1;
    Manager manager2;
    Coach coach1;
    Clasament clasament1;
    Clasament clasament2;
};

#endif