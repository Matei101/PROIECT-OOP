#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Team.h"
#include "Game.h"
#include "Exception.h"
#include "FileLoader.h"
#include "BudgetManager.h"

int main() {
    try {
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        FileLoader loader1("echipa1.txt");
        FileLoader loader2("echipa2.txt");

        Team team1("Team A"), team2("Team B");
        team1.incarcaDinFisier("echipa1.txt");
        team2.incarcaDinFisier("echipa2.txt");

        Game game(team1, team2);
        game.run();

        BudgetManager mgr(200.0);
        std::cout << "Încerc o achiziție de 150.0...\n";
        mgr.purchase(150.0);
        std::cout << "Sold rămas: " << mgr.getBalance() << "\n";
    }
    catch (const FileException& e) {
        std::cerr << "Eroare de fișier: " << e.what() << "\n";
    }
    catch (const FormatException& e) {
        std::cerr << "Eroare de format: " << e.what() << "\n";
    }
    catch (const BudgetException& e) {
        std::cerr << "Eroare de buget: " << e.what() << "\n";
    }
    catch (const AppException& e) {
        std::cerr << "Eroare aplicație: " << e.what() << "\n";
    }
    return 0;
}