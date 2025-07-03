#include "Game.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>

Game::Game(Team& t1, Team& t2)
  : transferList({
        Player("Haaland","ST",91,85),
        Player("Neymar","LW",90,88),
        Player("Kane","ST",89,80),
        Player("DeBruyne","CM",91,90)
    }),
    manager1("Alex", t1, 200),
    manager2("Chris", t2, 150),
    clasament1(t1.getName()),
    clasament2(t2.getName())
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::displayMenu() const {
    std::cout << "\n===== MENIU =====\n"
              << "1. Status manageri\n"
              << "2. Cumpără (Manager 1)\n"
              << "3. Vinde (Manager 1)\n"
              << "4. Simulează meci\n"
              << "5. Antrenează jucător (Manager 1)\n"
              << "6. Cumpără (Manager 2)\n"
              << "7. Vinde (Manager 2)\n"
              << "8. Filtrare jucători după poziție\n"
              << "9. Afișează clasamentul\n"
              << "10. Statistici echipă\n"
              << "11. Top 3 jucători după skill\n"
              << "12. Editează jucător\n"
              << "13. Transfer random între echipe\n"
              << "14. Oferte transfer\n"
              << "15. Verifică contracte și elimină jucători expirați\n"
              << "0. Ieșire\n"
              << "Alege opțiunea: ";
}

void Game::handleTransfer(Manager& manager) {
    for (size_t i = 0; i < transferList.size(); ++i)
        std::cout << i+1 << ". " << transferList[i] << "\n";
    int opt; std::cin >> opt;
    if (opt >= 1 && opt <= (int)transferList.size()) {
        if (manager.buyPlayer(transferList[opt-1]))
            transferList.erase(transferList.begin() + (opt-1));
        else
            std::cout << "Buget insuficient.\n";
    }
}

void Game::handleSell(Manager& manager) {
    std::string name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Numele jucătorului de vândut: ";
    std::getline(std::cin, name);
    manager.sellPlayer(name);
}

void Game::trainPlayer(Manager& manager) {
    std::string name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Numele jucătorului de antrenat: ";
    std::getline(std::cin, name);
    manager.trainPlayer(name);
}

void Game::simulateMatch() {
    Match m(manager1.getTeam(), manager2.getTeam());
    m.simulate();
    m.showResult();

    aplicaAccidentari(manager1.getTeam());
    aplicaAccidentari(manager2.getTeam());

    const auto& p1 = manager1.getTeam().getPlayers();
    const auto& p2 = manager2.getTeam().getPlayers();

    std::cout << "Marcatori " << manager1.getTeam().getName() << ": ";
    for (int i = 0; i < m.getScore1(); ++i)
        std::cout << p1[rand() % p1.size()].getName() << " ";
    if (m.getScore1() == 0) std::cout << "niciunul";
    std::cout << "\n";

    std::cout << "Marcatori " << manager2.getTeam().getName() << ": ";
    for (int i = 0; i < m.getScore2(); ++i)
        std::cout << p2[rand() % p2.size()].getName() << " ";
    if (m.getScore2() == 0) std::cout << "niciunul";
    std::cout << "\n";

    clasament1.actualizeaza(m.getScore1(), m.getScore2());
    clasament2.actualizeaza(m.getScore2(), m.getScore1());
}

void Game::filterByPosition() {
    std::string poz;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Poziția de filtrare (ex: ST, CM, CB, GK): ";
    std::getline(std::cin, poz);

    const auto& j1 = manager1.getTeam().getPlayers();
    const auto& j2 = manager2.getTeam().getPlayers();
    bool gasit1 = false, gasit2 = false;
    for (const auto& j : j1) if (j.getPosition() == poz) gasit1 = true;
    for (const auto& j : j2) if (j.getPosition() == poz) gasit2 = true;

    std::cout << "\n[Manager 1] Jucători pe poziția " << poz << ":\n";
    if (gasit1) manager1.getTeam().afiseazaPePozitie(poz);
    else std::cout << "Nu există jucători pe această poziție în echipa 1.\n";

    std::cout << "\n[Manager 2] Jucători pe poziția " << poz << ":\n";
    if (gasit2) manager2.getTeam().afiseazaPePozitie(poz);
    else std::cout << "Nu există jucători pe această poziție în echipa 2.\n";
}

void Game::showStatistics() {
    std::cout << "[Manager 1] Statistici:\n";
    manager1.getTeam().afiseazaStatistici();
    std::cout << "[Manager 2] Statistici:\n";
    manager2.getTeam().afiseazaStatistici();
}

void Game::topJucatori() {
    std::cout << "[Manager 1] Top jucători:\n";
    manager1.getTeam().afiseazaTopJucatori(3);
    std::cout << "[Manager 2] Top jucători:\n";
    manager2.getTeam().afiseazaTopJucători(3);
}

void Game::editeazaJucător() {
    std::string nume;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Numele jucătorului de editat: ";
    std::getline(std::cin, nume);
    manager1.getTeam().editeazaJucător(nume);
    manager2.getTeam().editeazăJucător(nume);
}

void Game::transferRandom() {
    manager1.getTeam().transferRandom(manager2.getTeam());
}

void Game::aplicaAccidentări(Team& team) {
    for (auto& p : team.getPlayers()) {
        if (!p.isAccidentat() && rand() % 100 < 10) {
            p.accid();
            std::cout << "⚠️  " << p.getName() << " s-a accidentat!\n";
        }
    }
}

void Game::verificăContracte() {
    auto check = [](Team& t) {
        auto& v = t.getPlayers();
        for (auto& p : v) p.decContract();
        v.erase(std::remove_if(v.begin(), v.end(), [](const Player& p) {
            if (p.getContractYears() <= 0) {
                std::cout << "📢 " << p.getName() << " a plecat, contract expirat.\n";
                return true;
            }
            return false;
        }), v.end());
    };
    check(manager1.getTeam());
    check(manager2.getTeam());
}

void Game::oferteTransfer() {
    auto& team = manager1.getTeam();
    auto& players = team.getPlayers();
    if (players.empty()) {
        std::cout << "Echipa nu are jucători pentru ofertă.\n";
        return;
    }
    int idx = rand() % players.size();
    Player& p = players[idx];
    int oferta = p.getValue() + (rand() % 20);
    std::cout << "💰 Ofertă pentru " << p.getName() << ": " << oferta
              << " (valoare actuală: " << p.getValue() << ")\nAccepti? (1 = Da / 0 = Nu): ";
    int opt; std::cin >> opt;
    if (opt == 1) {
        manager1.sellPlayer(p.getName());
        players.erase(players.begin() + idx);
        std::cout << "✅ Jucătorul a fost vândut.\n";
    } else {
        std::cout << "❌ Oferta refuzată.\n";
    }
}

void Game::run() {
    int choice;
    bool running = true;
    while (running) {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: manager1.showStatus(); manager2.showStatus(); break;
            case 2: handleTransfer(manager1); break;
            case 3: handleSell(manager1);    break;
            case 4: simulateMatch();         break;
            case 5: trainPlayer(manager1);   break;
            case 6: handleTransfer(manager2);break;
            case 7: handleSell(manager2);    break;
            case 8: filterByPosition();      break;
            case 9: showStatistics();        break;
            case 10: topJucători();          break;
            case 11: editeazăJucător();      break;
            case 12: transferRandom();       break;
            case 13: oferteTransfer();       break;
            case 14: verificăContracte();    break;
            case 0: running = false;        break;
            default: std::cout << "Opțiune invalidă.\n"; break;
        }
    }
}
