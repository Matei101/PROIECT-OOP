#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Game.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::ifstream f1("echipa1.txt"), f2("echipa2.txt");
    if (!f1.is_open() || !f2.is_open()) {
        std::cerr << "Eroare deschidere fișiere\n";
        return 1;
    }

    Team team1("Team A"), team2("Team B");
    team1.incarcaDinFisier("echipa1.txt");
    team2.incarcaDinFisier("echipa2.txt");

    Game game(team1, team2);
    game.run();

    return 0;
}
