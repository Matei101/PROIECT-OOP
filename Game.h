#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Team.h"
#include "Manager.h"
#include "Match.h"
#include "Clasament.h"

class Game {
public:
    Game(Team& t1, Team& t2);
    void run();

private:
    void displayMenu() const;
    void handleTransfer(Manager& manager);
    void handleSell(Manager& manager);
    void trainPlayer(Manager& manager);
    void simulateMatch();
    void filterByPosition();
    void showStatistics();
    void topJucatori();
    void editeazaJucator();
    void transferRandom();
    void aplicaAccidentari(Team& team);
    void verificaContracte();
    void oferteTransfer();

    std::vector<Player> transferList;
    Manager            manager1;
    Manager            manager2;
    Clasament          clasament1;
    Clasament          clasament2;
};

#endif // GAME_H
