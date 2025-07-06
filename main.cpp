#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Team.h"
#include "Game.h"
#include "Exception.h"
#include "FileLoader.h"
#include "BudgetManager.h"
#include "Economy.h"
#include "EventManager.h"
#include "AIManager.h"
#include "TimeUtils.h"

int main() {
    try {
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        FileLoader loader1("echipa1.txt");
        FileLoader loader2("echipa2.txt");

        Team team1("Team A"), team2("Team B");
        team1.incarcaDinFisier("echipa1.txt");
        team2.incarcaDinFisier("echipa2.txt");

        Economy econ;
        EventManager events;
        AIManager ai;

        econ.addSponsor(team1.getName(), 1000);
        econ.takeLoan(team2.getName(), 500);

        auto loanHistory = econ.getHistory();
        for (auto const& t : loanHistory) {
            std::string type;
            switch (t.type) {
                case Transaction::Type::Sponsor:  type = "sponsor";  break;
                case Transaction::Type::Loan:     type = "loan";     break;
                case Transaction::Type::Repay:    type = "repay";    break;
                case Transaction::Type::Interest: type = "interest"; break;
            }
            std::cout << "[" << t.timestamp << "] "
                      << t.team << " " << type << " " << t.amount << "\n";
        }

        auto handlerId = events.subscribe("goal", [&](const std::string& data){
            std::cout << "[EVENT] goal: " << data << "\n";
        });

        Game game(team1, team2, events, econ, ai);
        game.run();

        events.unsubscribe("goal", handlerId);

        BudgetManager mgr(200.0);
        std::cout << "Încerc o achiziție de 150.0...\n";
        mgr.purchase(150.0);
        std::cout << "Sold rămas: " << mgr.getBalance() << "\n";

        auto suggestions = ai.suggestTransfers(team1, 3);
        std::cout << "AI suggests transfers for " << team1.getName() << ":\n";
        for (auto const& p : suggestions) {
            std::cout << "  " << p.getName() << "\n";
        }

        std::cout << "Current time: " << TimeUtils::now() << "\n";
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
