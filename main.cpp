#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>


class Player {
private:
    std::string name;
    std::string position;
    int skill;
    double value;
    bool accidentat;
    int contractYears;

public:
    Player(const std::string& name, const std::string& position, int skill, double value, int contractYears = 3)
        : name(name), position(position), skill(skill), value(value), accidentat(false), contractYears(contractYears) {}

    const std::string& getName() const { return name; }
    const std::string& getPosition() const { return position; }
    int getSkill() const { return skill; }
    double getValue() const { return value; }
    int getContractYears() const { return contractYears; }
    bool isAccidentat() const { return accidentat; }

    void train(int amount) {
        skill += amount;
        value += amount * 1.5;
    }

    void accid() { accidentat = true; }
    void recuperare() { accidentat = false; }

    void decContract() {
        if (contractYears > 0) contractYears--;
    }

    friend std::ostream& operator<<(std::ostream& out, const Player& p) {
        out << p.name << " [" << p.position << "] - Skill: " << p.skill
            << ", Value: $" << std::fixed << std::setprecision(2) << p.value;
        if (p.accidentat) out << " [ACCIDENTAT]";
        out << ", Contract: " << p.contractYears << " ani";
        return out;
    }
};


class Team {
private:
    std::string name;
    std::vector<Player> players;

public:
   explicit Team(const std::string& name) : name(name) {}
    Team(const Team& other) : name(other.name), players(other.players) {}
    Team& operator=(const Team& other) {
        if (this != &other) {
            name = other.name;
            players = other.players;
        }
        return *this;
    }
    ~Team() {}

    void addPlayer(const Player& p) {
        players.push_back(p);
    }

    double averageSkill() const {
        if (players.empty()) return 0;
        int total = 0;
        for (const auto& p : players) {
            total += p.getSkill();
        }
        return static_cast<double>(total) / players.size();
    }

    bool transferOutPlayer(const std::string& playerName, Player& outPlayer) {
        for (auto it = players.begin(); it != players.end(); ++it) {
            if (it->getName() == playerName) {
                outPlayer = *it;
                players.erase(it);
                return true;
            }
        }
        return false;
    }

    void salveazaInFisier(const std::string& filename) const {
        std::ofstream out(filename);
        if (!out.is_open()) return;
        out << "Nume Echipa " << name << "\n";
        for (const auto& p : players) {
            out << p.getName() << " " << p.getPosition() << " " << p.getSkill() << " " << p.getValue() << "\n";
        }
    }

    void incarcaDinFisier(const std::string& filename) {
        std::ifstream in(filename);
        if (!in.is_open()) return;
        players.clear();
        std::string line;
        std::getline(in, line);
        if (line.rfind("Nume Echipa ", 0) == 0) name = line.substr(12);
        std::string nume, pozitie;
        int skill;
        double valoare;
        while (in >> nume >> pozitie >> skill >> valoare) {
            players.push_back(Player(nume, pozitie, skill, valoare));
        }
    }

    void afiseazaPePozitie(const std::string& poz) const {
        for (const auto& p : players) {
            if (p.getPosition() == poz) std::cout << p << "\n";
        }
    }

    void afiseazaStatistici() const {
        if (players.empty()) {
            std::cout << "Echipa nu are jucători.\n";
            return;
        }

        double totalSkill = 0, totalValoare = 0;
        for (const auto& p : players) {
            totalSkill += p.getSkill();
            totalValoare += p.getValue();
        }

        std::cout << "Media skill: " << totalSkill / players.size() << "\n";
        std::cout << "Valoare totală: $" << totalValoare << "\n";
    }

    void afiseazaTopJucatori(int n) const {
        if (players.empty()) {
            std::cout << "Nu există jucători.\n";
            return;
        }

        std::vector<Player> top = players;
        std::sort(top.begin(), top.end(), [](const Player& a, const Player& b) {
            return a.getSkill() > b.getSkill();
        });

        for (int i = 0; i < std::min(n, (int)top.size()); ++i) {
            std::cout << top[i] << "\n";
        }
    }

    void editeazaJucator(const std::string& nume) {
        for (auto& p : players) {
            if (p.getName() == nume) {
                std::cout << "1. Schimbă skill\n2. Schimbă valoare\n3. Reset accidentare\n4. Prelungește contract\n";
                int opt;
                std::cin >> opt;
                switch (opt) {
                    case 1: {
                        int s;
                        std::cout << "Nou skill: ";
                        std::cin >> s;
                        p.train(s - p.getSkill());
                        break;
                    }
                    case 2: {
                        double v;
                        std::cout << "Nouă valoare: ";
                        std::cin >> v;
                        p = Player(p.getName(), p.getPosition(), p.getSkill(), v, p.getContractYears());
                        break;
                    }
                    case 3: {
                        p.recuperare();
                        break;
                    }
                    case 4: {
                        int ani;
                        std::cout << "Adaugă ani contract: ";
                        std::cin >> ani;
                        // Nu există direct setter pentru contract, se poate adăuga dacă vrei
                        break;
                    }
                    default:
                        std::cout << "Opțiune invalidă.\n";
                }
                return;
            }
        }
    }

    void transferRandom(Team& other) {
        if (players.empty()) {
            std::cout << "Echipa nu are jucători pentru transfer.\n";
            return;
        }

        int idx = rand() % players.size();
        Player p = players[idx];
        players.erase(players.begin() + idx);
        other.addPlayer(p);

        std::cout << "🔁 Jucător transferat aleatoriu: " << p.getName()
                  << " către " << other.getName() << "\n";
    }

    std::vector<Player>& getPlayers() { return players; }

    friend std::ostream& operator<<(std::ostream& out, const Team& t) {
        out << "Team: " << t.name << "\n";
        for (const auto& p : t.players) {
            out << "  " << p << "\n";
        }
        return out;
    }

    const std::string& getName() const { return name; }
};

class Manager {
private:
    std::string name;
    Team team;
    double budget;

public:
    Manager(const std::string& name, const Team& team, double budget)
        : name(name), team(team), budget(budget) {}

    bool buyPlayer(const Player& p) {
        if (budget >= p.getValue()) {
            team.addPlayer(p);
            budget -= p.getValue();
            return true;
        }
        return false;
    }

    bool sellPlayer(const std::string& playerName) {
        Player soldPlayer("", "", 0, 0);
        if (team.transferOutPlayer(playerName, soldPlayer)) {
            budget += soldPlayer.getValue();
            return true;
        }
        return false;
    }

    void trainPlayer(const std::string& playerName) {
        for (Player& p : team.getPlayers()) {
            if (p.getName() == playerName) {
                p.train(5);
                return;
            }
        }
    }

    void showStatus() const {
        std::cout << "Manager: " << name
                  << ", Buget: $" << std::fixed << std::setprecision(2) << getBudget() << "\n";
        std::cout << team;
    }


    Team& getTeam() { return team; }

    const std::string& getName() const { return name; }
    double getBudget() const { return budget; }

    friend std::ostream& operator<<(std::ostream& out, const Manager& m) {
        out << "Manager: " << m.name << ", Buget: $"
            << std::fixed << std::setprecision(2) << m.budget << "\n";
        out << m.team;
        return out;
    }
};

class Match {
private:
    const Team& team1;
    const Team& team2;
    int score1;
    int score2;

public:
    Match(const Team& t1, const Team& t2)
        : team1(t1), team2(t2), score1(0), score2(0) {}

    void simulate() {
        double avg1 = team1.averageSkill();
        double avg2 = team2.averageSkill();
        score1 = static_cast<int>(avg1) % 5 + rand() % 3;
        score2 = static_cast<int>(avg2) % 5 + rand() % 3;
    }

    void showResult() const {
        std::cout << "Rezultat meci: " << team1.getName() << " " << score1 << " - " << score2 << " " << team2.getName() << "\n";
    }

    int getScore1() const { return score1; }
    int getScore2() const { return score2; }
};

struct Clasament {
    std::string teamName;
    int puncte = 0;
    int meciuri = 0;
    void actualizeaza(int scor1, int scor2) {
        ++meciuri;
        if (scor1 > scor2) puncte += 3;
        else if (scor1 == scor2) puncte += 1;
    }
    void afiseaza() const {
        std::cout << teamName << " | Meciuri: " << meciuri << " | Puncte: " << puncte << " ";
    }
};

class Game {
private:
    std::vector<Player> transferList;
    Manager manager1, manager2;
    Clasament clasament1, clasament2;

public:
    Game(Team& t1, Team& t2)
        : manager1("Alex", t1, 200),
          manager2("Chris", t2, 150),
          clasament1(t1.getName()),
          clasament2(t2.getName()) {
        transferList = {
            Player("Haaland", "ST", 91, 85),
            Player("Neymar", "LW", 90, 88),
            Player("Kane", "ST", 89, 80),
            Player("DeBruyne", "CM", 91, 90)
        };
    }

    void run() {
        int choice;
        bool running = true;

        while (running) {
            displayMenu();
            std::cin >> choice;

            switch (choice) {
                case 1: manager1.showStatus(); manager2.showStatus(); break;
                case 2: handleTransfer(manager1); break;
                case 3: handleSell(manager1); break;
                case 4: simulateMatch(); break;
                case 5: trainPlayer(manager1); break;
                case 6: handleTransfer(manager2); break;
                case 7: handleSell(manager2); break;
                case 8: filterByPosition(); break;
                case 9: clasament1.afiseaza(); clasament2.afiseaza(); break;
                case 10: showStatistics(); break;
                case 11: topJucatori(); break;
                case 12: editeazaJucator(); break;
                case 13: transferRandom(); break;
                case 14: oferteTransfer(); break;
                case 15: verificaContracte(); break;
                case 0: running = false; break;
                default: std::cout << "Opțiune invalidă.\n"; break;
            }
        }
    }

    void displayMenu() const {
        std::cout << "\n===== MENIU =====\n"
                  << "1. Status manageri\n"
                  << "2. Cumpără (Manager 1)\n"
                  << "3. Vinde (Manager 1)\n"
                  << "4. Simulează meci\n"
                  << "5. Antrenează jucător (Manager 1)\n"
                  << "6. Cumpără (Manager 2)\n"
                  << "7. Vinde (Manager 2)\n"
                  << "8. Filtrare jucători după poziție (Manager 1 și 2)\n"
                  << "9. Afișează clasamentul\n"
                  << "10. Statistici echipă\n"
                  << "11. Top 3 jucători după skill\n"
                  << "12. Editează jucător\n"
                  << "13. Transfer random între echipe\n"
                  << "14. Simulează ofertă de transfer\n"
                  << "15. Verifică contracte și elimină jucători expirați\n"
                  << "0. Ieșire\n"
                  << "Alege o opțiune: ";
    }

    void handleTransfer(Manager& manager) {
        for (size_t i = 0; i < transferList.size(); ++i)
            std::cout << i + 1 << ". " << transferList[i] << "\n";
        int opt;
        std::cout << "Alege jucătorul: ";
        std::cin >> opt;
        if (opt >= 1 && opt <= static_cast<int>(transferList.size())) {
            if (manager.buyPlayer(transferList[opt - 1]))
                transferList.erase(transferList.begin() + (opt - 1));
            else
                std::cout << "Buget insuficient.\n";
        }
    }

    void handleSell(Manager& manager) {
        std::string name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Numele jucătorului de vândut: ";
        std::getline(std::cin, name);
        manager.sellPlayer(name);
    }

    void trainPlayer(Manager& manager) {
        std::string name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Numele jucătorului de antrenat: ";
        std::getline(std::cin, name);
        manager.trainPlayer(name);
    }

    void simulateMatch() {
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

    void filterByPosition() {
        std::string poz;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Poziția de filtrare (ex: ST, CM, CB, GK): ";
        std::getline(std::cin, poz);

        const auto& j1 = manager1.getTeam().getPlayers();
        const auto& j2 = manager2.getTeam().getPlayers();

        std::cout << "\n[Manager 1] Jucători pe poziția " << poz << ":\n";
        bool gasit1 = false;
        for (const auto& j : j1) {
            if (j.getPosition() == poz) { std::cout << j << "\n"; gasit1 = true; }
        }
        if (!gasit1) std::cout << "Nu există jucători pe această poziție în echipa 1.\n";

        std::cout << "\n[Manager 2] Jucători pe poziția " << poz << ":\n";
        bool gasit2 = false;
        for (const auto& j : j2) {
            if (j.getPosition() == poz) { std::cout << j << "\n"; gasit2 = true; }
        }
        if (!gasit2) std::cout << "Nu există jucători pe această poziție în echipa 2.\n";
    }

    void showStatistics() {
        std::cout << "[Manager 1] Statistici:\n";
        manager1.getTeam().afiseazaStatistici();
        std::cout << "[Manager 2] Statistici:\n";
        manager2.getTeam().afiseazaStatistici();
    }

    void topJucatori() {
        std::cout << "[Manager 1] Top jucători:\n";
        manager1.getTeam().afiseazaTopJucatori(3);
        std::cout << "[Manager 2] Top jucători:\n";
        manager2.getTeam().afiseazaTopJucatori(3);
    }

    void editeazaJucator() {
        std::string nume;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Numele jucătorului de editat: ";
        std::getline(std::cin, nume);
        manager1.getTeam().editeazaJucator(nume);
        manager2.getTeam().editeazaJucator(nume);
    }

    void transferRandom() {
        manager1.getTeam().transferRandom(manager2.getTeam());
    }

    void aplicaAccidentari(Team& team) {
        for (Player& p : team.getPlayers()) {
            if (!p.isAccidentat() && rand() % 100 < 10) {
                p.accid();
                std::cout << "⚠️  " << p.getName() << " s-a accidentat!\n";
            }
        }
    }

    void verificaContracte() {
        auto check = [](Team& team) {
            auto& players = team.getPlayers();
            for (auto& p : players) p.decContract();
            players.erase(std::remove_if(players.begin(), players.end(), [](const Player& p) {
                if (p.getContractYears() <= 0) {
                    std::cout << "📢 " << p.getName() << " a plecat, contract expirat.\n";
                    return true;
                }
                return false;
            }), players.end());
        };
        check(manager1.getTeam());
        check(manager2.getTeam());
    }

    void oferteTransfer() {
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
        int opt;
        std::cin >> opt;
        if (opt == 1) {
            manager1.sellPlayer(p.getName());
            players.erase(players.begin() + idx);
            std::cout << "✅ Jucătorul a fost vândut.\n";
        } else {
            std::cout << "❌ Oferta refuzată.\n";
        }
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Team team1("Team A"), team2("Team B");

    std::ifstream test1("echipa1.txt"), test2("echipa2.txt");
    if (!test1.is_open() || !test2.is_open()) {
        std::cerr << " Eroare: Nu s-au putut deschide fișierele echipa1.txt sau echipa2.txt.\n";
        return 1;
    }
    test1.close();
    test2.close();

    team1.incarcaDinFisier("echipa1.txt");
    team2.incarcaDinFisier("echipa2.txt");

    Game game(team1, team2);
    game.run();

    return 0;
}
