#include "Game.h"
#include "Economy.h"
#include "EventManager.h"
#include "AIManager.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

void swap(Game& a, Game& b) noexcept {
    using std::swap;
    swap(a.actors,       b.actors);
    swap(a.currentActor, b.currentActor);
    swap(a.transferList, b.transferList);
    swap(a.manager1,     b.manager1);
    swap(a.manager2,     b.manager2);
    swap(a.clasament1,   b.clasament1);
    swap(a.clasament2,   b.clasament2);
    swap(a.history,      b.history);
    swap(a.season,       b.season);
    swap(a.achievements, b.achievements);
    swap(a.trainLog,     b.trainLog);
    swap(a.chemistry,    b.chemistry);
    swap(a.events,       b.events);
    swap(a.economy,      b.economy);
    swap(a.ai,           b.ai);
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
  , history(other.history)
  , season(nullptr)
  , achievements(other.achievements)
  , trainLog(other.trainLog)
  , chemistry(other.chemistry)
  , events(other.events)
  , economy(other.economy)
  , ai(other.ai)
{
    if (other.season)
        season = new Season(*other.season);
}

Game& Game::operator=(Game other) {
    swap(*this, other);
    return *this;
}

Game::~Game() {
    delete season;
}

Game::Game(Team& t1,
           Team& t2,
           EventManager& em,
           Economy& econ,
           AIManager& aiMgr)
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
  , history()
  , season(nullptr)
  , achievements()
  , trainLog()
  , chemistry()
  , events(em)
  , economy(econ)
  , ai(aiMgr)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    actors = { &manager1, &coach1, &manager2 };
    for (auto& p : t1.getPlayers())
        actors.push_back(&p);
}


void Game::displayMenu() const {
    std::cout << "\n===== MENIU =====\n"
              << "1. Status\n"
              << "2. Cumpără\n"
              << "3. Vinde\n"
              << "4. Meci\n"
              << "5. Antrenare jucător\n"
              << "6. Antrenare echipă\n"
              << "7. Filtrare poziție\n"
              << "8. Statistici echipă\n"
              << "9. Top jucători\n"
              << "10. Editează jucător\n"
              << "11. Transfer random\n"
              << "12. Oferte transfer\n"
              << "13. Verifică contracte\n"
              << "14. Istoric meciuri\n"
              << "15. Sezon complet\n"
              << "16. Clasament sezon\n"
              << "17. Statistici avansate\n"
              << "18. Vezi Achievements\n"
              << "19. Vezi Training Log\n"
              << "20. Vezi Chemistry\n"
              << "21. Salvează clasament (CSV)\n"
              << "0. Ieșire\n"
              << "Alege opțiunea: ";
}

void Game::handleTransfer() {
    for (size_t i = 0; i < transferList.size(); ++i)
        std::cout << i+1 << ". " << transferList[i] << "\n";
    int opt; std::cin >> opt;
    if (opt >= 1 && opt <= static_cast<int>(transferList.size())) {
        achievements.recordWin(manager1.getTeam().getName());
        if (manager1.buyPlayer(transferList[opt-1]))
            transferList.erase(transferList.begin() + (opt-1));
        else
            std::cout << "Buget insuficient.\n";
    }
}

void Game::handleSell() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name; std::cout << "Nume jucător: ";
    std::getline(std::cin, name);
    manager1.sellPlayer(name);
}

void Game::simulateMatch() {
    Match m(manager1.getTeam(), manager2.getTeam());
    m.simulate();

    chemistry.recordResult(manager1.getTeam().getName(), m.getScore1() > m.getScore2());
    chemistry.recordResult(manager2.getTeam().getName(), m.getScore2() > m.getScore1());

    m.showResult();
    std::cout << Commentary::forMatch(m.getScore1(), m.getScore2()) << "\n";

    aplicaAccidentari(manager1.getTeam());
    aplicaAccidentari(manager2.getTeam());

    const auto& p1 = manager1.getTeam().getPlayers();
    const auto& p2 = manager2.getTeam().getPlayers();

    std::cout << "Marcatori " << manager1.getTeam().getName() << ": ";
    if (m.getScore1() == 0) {
        std::cout << "niciunul";
    } else {
        for (int i = 0; i < m.getScore1(); ++i) {
            const auto* scorer = &p1[std::rand() % p1.size()];
            std::cout << scorer->getName() << " ";
        }
    }

    std::cout << "\nMarcatori " << manager2.getTeam().getName() << ": ";
    if (m.getScore2() == 0) {
        std::cout << "niciunul";
    } else {
        for (int i = 0; i < m.getScore2(); ++i) {
            const auto* scorer = &p2[std::rand() % p2.size()];
            std::cout << scorer->getName() << " ";
        }
    }
    std::cout << "\n";

    clasament1.actualizeaza(m.getScore1(), m.getScore2());
    clasament2.actualizeaza(m.getScore2(), m.getScore1());

    history.add({ manager1.getTeam().getName(), m.getScore1(),
                  manager2.getTeam().getName(), m.getScore2() });
}

void Game::handleTrain() {
    std::string n; std::cout << "Jucător: "; std::cin >> n;
    currentActor = nullptr;
    for (auto* a : actors) if (a->getName() == n) currentActor = a;
    if (auto* pl = dynamic_cast<Player*>(currentActor)) {
        pl->train(5);
        trainLog.addSession(pl->getName(), 5);
    }
}

void Game::handleCoachTrain() {
    coach1.trainTeam(3);
    trainLog.addSession(coach1.getName(), 3);
}

void Game::filterByPosition() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string poz; std::cout << "Poziție: "; std::getline(std::cin, poz);
    manager1.getTeam().afiseazaPePozitie(poz);
    manager2.getTeam().afiseazaPePozitie(poz);
}

void Game::showStatistics() const {
    manager1.getTeam().afiseazaStatistici();
    manager2.getTeam().afiseazaStatistici();
}

void Game::topJucatori() const {
    manager1.getTeam().afiseazaTopJucatori(3);
    manager2.getTeam().afiseazaTopJucatori(3);
}

void Game::editeazaJucator() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string n; std::cout << "Nume: "; std::getline(std::cin, n);
    manager1.getTeam().editeazaJucator(n);
}

void Game::transferRandom() {
    manager1.getTeam().transferRandom(manager2.getTeam());
}

void Game::aplicaAccidentari(Team& t) {
    for (auto& p : t.getPlayers())
        if (!p.isAccidentat() && std::rand() % 100 < 10) {
            p.accid();
            std::cout << "⚠ " << p.getName() << " s-a accidentat\n";
        }
}

void Game::verificaContracte() {
    auto c = [&](Team& t) {
        auto& v = t.getPlayers();
        for (auto& p : v) p.decContract();
        v.erase(std::remove_if(v.begin(), v.end(),
            [](auto& p) { if (p.getContractYears() <= 0) { std::cout<<p.getName()<<" pleacă\n"; return true; } return false; }),
            v.end());
    };
    c(manager1.getTeam());
    c(manager2.getTeam());
}

void Game::oferteTransfer() {
    auto& v = manager1.getTeam().getPlayers();
    if (v.empty()) return;
    int i = std::rand() % v.size();
    auto& p = v[i];
    int of = static_cast<int>(p.getValue()) + std::rand() % 20;
    std::cout << "Ofertă " << of << "? "; int ok; std::cin >> ok;
    if (ok) {
        manager1.sellPlayer(p.getName());
        v.erase(v.begin() + i);
    }
}

void Game::showHistory() const {
    history.print();
}

void Game::simulateSeason() {
    delete season;
    season = new Season({ &manager1.getTeam(), &manager2.getTeam() });
    season->playFullSeason();
    achievements.recordSeasonEnd(manager1.getTeam().getName(), clasament1.puncte);
    achievements.recordSeasonEnd(manager2.getTeam().getName(), clasament2.puncte);
}

void Game::showSeasonStandings() const {
    if (season) season->printStandings();
}

void Game::showStats() const {
    auto s1 = Stats::compute(manager1.getTeam());
    auto s2 = Stats::compute(manager2.getTeam());
    std::cout << Stats::format(s1) << "\n" << Stats::format(s2) << "\n";
}

void Game::viewAchievements() const {
    achievements.print();
}

void Game::viewTrainingLog() const {
    trainLog.print();
}

void Game::viewChemistry() const {
    std::cout << "\n=== Chemistry ===\n";
    for (auto* p : actors)
        std::cout << p->getName() << ": " << chemistry.getModifier(p->getName()) << "\n";
}

void Game::saveStandingsToFile(const std::string& filename) const {
    std::ofstream out(filename);
    out << "Team,Matches,Points\n";
    out << clasament1.teamName << "," << clasament1.meciuri << "," << clasament1.puncte << "\n";
    out << clasament2.teamName << "," << clasament2.meciuri << "," << clasament2.puncte << "\n";
    std::cout << "Clasament salvat în " << filename << "\n";
}

void Game::run() {
    int ch; bool running = true;
    while (running) {
        displayMenu();
        std::cin >> ch;
        switch (ch) {
            case 1: for (const auto* a : actors) a->show(); break;
            case 2: handleTransfer();           break;
            case 3: handleSell();               break;
            case 4: simulateMatch();            break;
            case 5: handleTrain();              break;
            case 6: handleCoachTrain();         break;
            case 7: filterByPosition();         break;
            case 8: showStatistics();           break;
            case 9: topJucatori();              break;
            case 10: editeazaJucator();         break;
            case 11: transferRandom();          break;
            case 12: oferteTransfer();          break;
            case 13: verificaContracte();       break;
            case 14: showHistory();             break;
            case 15: simulateSeason();          break;
            case 16: showSeasonStandings();     break;
            case 17: showStats();               break;
            case 18: viewAchievements();        break;
            case 19: viewTrainingLog();         break;
            case 20: viewChemistry();           break;
            case 21: saveStandingsToFile("standings.csv"); break;
            case 0: running = false;            break;
        }
    }
}
