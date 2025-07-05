// Game.cpp
#include "Game.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>

void swap(Game& a, Game& b) noexcept {
    using std::swap;
    swap(a.actors,       b.actors);
    swap(a.currentActor, b.currentActor);
    swap(a.transferList, b.transferList);
    swap(a.manager1,     b.manager1);
    swap(a.manager2,     b.manager2);
    // coach1 holds a reference; do not swap
    swap(a.clasament1,   b.clasament1);
    swap(a.clasament2,   b.clasament2);
}

Game::Game(const Game& other)
  : actors(other.actors)
  , currentActor(other.currentActor)
  , transferList(other.transferList)
  , manager1(other.manager1)
  , manager2(other.manager2)
  , coach1(other.coach1)
  , clasament1(other.clasament1)
  , clasament2(other.clasament2)
{}

Game& Game::operator=(Game other) {
    swap(*this, other);
    return *this;
}

Game::Game(Team& t1, Team& t2)
  : transferList({
        Player("Haaland","ST",91,85),
        Player("Neymar","LW",90,88),
        Player("Kane","ST",89,80),
        Player("DeBruyne","CM",91,90)
    })
  , manager1("Alex", t1, 200)
  , manager2("Chris", t2, 150)
  , coach1("Jordan", t1)
  , clasament1(t1.getName())
  , clasament2(t2.getName())
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    actors.push_back(&manager1);
    actors.push_back(&coach1);
    for (auto& p : t1.getPlayers())
        actors.push_back(&p);
}

void Game::displayMenu() const {
    std::cout << "\n===== MENIU =====\n"
              << "1. Status manageri și jucători\n"
              << "2. Cumpără (Manager 1)\n"
              << "3. Vinde (Manager 1)\n"
              << "4. Simulează meci\n"
              << "5. Antrenează jucător (Manager 1)\n"
              << "6. Antrenează echipa (Coach)\n"
              << "7. Filtrare jucători după poziție\n"
              << "8. Afișează clasament\n"
              << "9. Statistici echipă\n"
              << "10. Top 3 jucători\n"
              << "11. Editează jucător\n"
              << "12. Transfer random între echipe\n"
              << "13. Oferte transfer\n"
              << "14. Verifică contracte\n"
              << "0. Ieșire\n"
              << "Alege opțiunea: ";
}

void Game::handleTransfer() {
    for (size_t i = 0; i < transferList.size(); ++i)
        std::cout << i+1 << ". " << transferList[i] << "\n";
    int opt;
    std::cin >> opt;
    if (opt >= 1 && opt <= static_cast<int>(transferList.size())) {
        if (manager1.buyPlayer(transferList[opt-1]))
            transferList.erase(transferList.begin() + (opt-1));
        else
            std::cout << "Buget insuficient.\n";
    }
}

void Game::handleSell() {
    std::string name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Numele jucătorului de vândut: ";
    std::getline(std::cin, name);
    if (!manager1.sellPlayer(name))
        std::cout << "Vânzare eșuată.\n";
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
    if (m.getScore1() == 0) {
        std::cout << "niciunul";
    } else {
        for (int i = 0; i < m.getScore1(); ++i)
            std::cout << p1[rand() % p1.size()].getName() << " ";
    }
    std::cout << "\n";

    std::cout << "Marcatori " << manager2.getTeam().getName() << ": ";
    if (m.getScore2() == 0) {
        std::cout << "niciunul";
    } else {
        for (int i = 0; i < m.getScore2(); ++i)
            std::cout << p2[rand() % p2.size()].getName() << " ";
    }
    std::cout << "\n";

    clasament1.actualizeaza(m.getScore1(), m.getScore2());
    clasament2.actualizeaza(m.getScore2(), m.getScore1());
}

void Game::handleTrain() {
    std::string nume;
    std::cout << "Numele jucătorului pentru antrenament: ";
    std::cin >> nume;

    currentActor = nullptr;
    for (auto* act : actors) {
        if (act->getName() == nume) {
            currentActor = act;
            break;
        }
    }
    if (!currentActor) {
        std::cout << "Actor inexistent.\n";
        return;
    }

    if (auto* pl = dynamic_cast<Player*>(currentActor)) {
        pl->train(5);
        std::cout << pl->getName() << " skill acum: " << pl->getSkill() << "\n";
    } else {
        std::cout << currentActor->getName() << " nu este jucător.\n";
    }
}

void Game::handleCoachTrain() {
    coach1.trainTeam(3);
    std::cout << coach1.getName() << " a antrenat întreaga echipă.\n";
}

void Game::filterByPosition() {
    std::string poz;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Poziția de filtrare (ST, CM, CB, GK): ";
    std::getline(std::cin, poz);

    const auto& v1 = manager1.getTeam().getPlayers();
    const auto& v2 = manager2.getTeam().getPlayers();
    bool found1 = false, found2 = false;

    for (const auto& p : v1) if (p.getPosition() == poz) { found1 = true; break; }
    for (const auto& p : v2) if (p.getPosition() == poz) { found2 = true; break; }

    std::cout << "[Manager 1] ";
    if (found1) manager1.getTeam().afiseazaPePozitie(poz);
    else std::cout << "Niciun jucător.\n";

    std::cout << "[Manager 2] ";
    if (found2) manager2.getTeam().afiseazaPePozitie(poz);
    else std::cout << "Niciun jucător.\n";
}

void Game::showStatistics() {
    std::cout << "[Manager 1] Statistici:\n";
    manager1.getTeam().afiseazaStatistici();
    std::cout << "[Manager 2] Statistici:\n";
    manager2.getTeam().afiseazaStatistici();
}

void Game::topJucatori() {
    std::cout << "[Manager 1] Top 3:\n";
    manager1.getTeam().afiseazaTopJucatori(3);
    std::cout << "[Manager 2] Top 3:\n";
    manager2.getTeam().afiseazaTopJucatori(3);
}

void Game::editeazaJucator() {
    std::string nume;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Numele jucătorului de editat: ";
    std::getline(std::cin, nume);

    manager1.getTeam().editeazaJucator(nume);
    manager2.getTeam().editeazaJucator(nume);
}

void Game::transferRandom() {
    manager1.getTeam().transferRandom(manager2.getTeam());
}

void Game::aplicaAccidentari(Team& team) {
    for (auto& p : team.getPlayers()) {
        if (!p.isAccidentat() && rand() % 100 < 10) {
            p.accid();
            std::cout << "⚠️ " << p.getName() << " s-a accidentat!\n";
        }
    }
}

void Game::verificaContracte() {
    auto check = [](Team& t) {
        auto& v = t.getPlayers();
        for (auto& p : v) p.decContract();
        v.erase(std::remove_if(v.begin(), v.end(),
            [](const Player& p) {
                if (p.getContractYears() <= 0) {
                    std::cout << "📢 " << p.getName() << " pleacă, contract expirat.\n";
                    return true;
                }
                return false;
            }), v.end());
    };
    check(manager1.getTeam());
    check(manager2.getTeam());
}

void Game::oferteTransfer() {
    auto& players = manager1.getTeam().getPlayers();
    if (players.empty()) {
        std::cout << "Niciun jucător disponibil.\n";
        return;
    }
    int idx = rand() % players.size();
    Player& p = players[idx];
    int oferta = static_cast<int>(p.getValue()) + (rand() % 20);
    std::cout << "💰 Ofertă pentru " << p.getName() << ": " << oferta
              << " (valoare actuală: " << p.getValue() << ")\n"
              << "Acceptați? (1=Da / 0=Nu): ";
    int opt; std::cin >> opt;
    if (opt == 1) {
        manager1.sellPlayer(p.getName());
        players.erase(players.begin() + idx);
        std::cout << "✅ Jucător vândut.\n";
    } else {
        std::cout << "❌ Ofertă refuzată.\n";
    }
}

void Game::run() {
    int choice;
    bool running = true;
    while (running) {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                for (auto* a : actors) a->show();
                break;
            case 2: handleTransfer();     break;
            case 3: handleSell();         break;
            case 4: simulateMatch();      break;
            case 5: handleTrain();        break;
            case 6: handleCoachTrain();   break;
            case 7: filterByPosition();   break;
            case 8: std::cout << "[Manager 1] "; manager1.getTeam().afiseazaStatistici(); break;
            case 9: std::cout << "[Manager 2] "; manager2.getTeam().afiseazaStatistici(); break;
            case 10: topJucatori();        break;
            case 11: editeazaJucator();    break;
            case 12: transferRandom();     break;
            case 13: oferteTransfer();     break;
            case 14: verificaContracte();  break;
            case 0: running = false;       break;
            default: std::cout << "Opțiune invalidă.\n"; break;
        }
    }
}
