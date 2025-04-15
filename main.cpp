
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Player {
private:
    std::string name;
    std::string position;
    int skill;
    double value;

public:
    Player(const std::string& name, const std::string& position, int skill, double value)
        : name(name), position(position), skill(skill), value(value) {}

    const std::string& getName() const { return name; }
    int getSkill() const { return skill; }
    double getValue() const { return value; }
    const std::string& getPosition() const { return position; }

    void train(int amount) {
        skill += amount;
        value += amount * 1.5;
    }

    friend std::ostream& operator<<(std::ostream& out, const Player& p) {
        out << p.name << " [" << p.position << "] - Skill: " << p.skill << ", Value: $" << p.value;
        return out;
    }
};

class Team {
private:
    std::string name;
    std::vector<Player> players;

public:
    Team(const std::string& name) : name(name) {}
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
        out << "Nume Echipa " << name << " ";
        for (const auto& p : players) {
            out << p.getName() << " " << p.getPosition() << " " << p.getSkill() << " " << p.getValue() << " ";
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
            if (p.getPosition() == poz) std::cout << p << " ";
        }
    }

    std::vector<Player>& getPlayers() { return players; }

    friend std::ostream& operator<<(std::ostream& out, const Team& t) {
        out << "Team: " << t.name << " ";
        for (const auto& p : t.players) {
            out << "  " << p << " ";
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
        std::cout << "Manager: " << name << ", Buget: $" << std::fixed << std::setprecision(2) << budget << " ";
        std::cout << team;
    }

    Team& getTeam() { return team; }
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
        std::cout << "Rezultat meci: " << team1.getName() << " " << score1 << " - " << score2 << " " << team2.getName() << " ";
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

int main() {
    srand(static_cast<unsigned>(time(0)));

    std::vector<Player> transferList = {
        Player("Haaland", "ST", 91, 85),
        Player("Neymar", "LW", 90, 88),
        Player("Kane", "ST", 89, 80),
        Player("DeBruyne", "CM", 91, 90)
    };

    Team team1("FC Legend"), team2("Superstars United");
    team1.addPlayer(Player("Messi", "RW", 95, 100));
    team1.addPlayer(Player("Modric", "CM", 89, 70));
    team2.addPlayer(Player("Ronaldo", "ST", 92, 90));
    team2.addPlayer(Player("VanDijk", "CB", 88, 75));
    team2.addPlayer(Player("Mbappe", "LW", 93, 95));

    Manager manager1("Alex", team1, 200);
    Manager manager2("Chris", team2, 150);
    Clasament clasament1{"FC Legend"}, clasament2{"Superstars United"};

    int choice;
    bool running = true;

    while (running) {
        std::cout << "\n===== MENIU =====\n";
        std::cout << "1. Status manageri\n";
        std::cout << "2. Cumpără (Manager 1)\n";
        std::cout << "3. Vinde (Manager 1)\n";
        std::cout << "4. Simulează meci\n";
        std::cout << "5. Salvează echipa (Manager 1)\n";
        std::cout << "6. Încarcă echipa (Manager 1)\n";
        std::cout << "7. Antrenează jucător (Manager 1)\n";
        std::cout << "8. Cumpără (Manager 2)\n";
        std::cout << "9. Vinde (Manager 2)\n";
        std::cout << "10. Filtrare jucători după poziție (Manager 1)\n";
        std::cout << "0. Ieșire\n";
        std::cout << "Alege o opțiune: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manager1.showStatus();
                manager2.showStatus();
                break;

            case 2: {
                for (size_t i = 0; i < transferList.size(); ++i)
                    std::cout << i + 1 << ". " << transferList[i] << "\n";
                int opt;
                std::cout << "Alege jucătorul pentru Manager 1: ";
                std::cin >> opt;
                if (opt >= 1 && opt <= (int)transferList.size()) {
                    if (manager1.buyPlayer(transferList[opt - 1])) {
                        transferList.erase(transferList.begin() + (opt - 1));
                    } else {
                        std::cout << "Buget insuficient.\n";
                    }
                }
                break;
            }

            case 3: {
                std::string name;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Numele jucătorului de vândut (Manager 1): ";
                std::getline(std::cin, name);
                manager1.sellPlayer(name);
                break;
            }

            case 4: {
                Match m(team1, team2);
                m.simulate();
                m.showResult();
                clasament1.actualizeaza(m.getScore1(), m.getScore2());
                clasament2.actualizeaza(m.getScore2(), m.getScore1());
                break;
            }

            case 5:
                manager1.getTeam().salveazaInFisier("echipa1.txt");
                break;

            case 6:
                manager1.getTeam().incarcaDinFisier("tastatura.txt");
                break;

            case 7: {
                std::string name;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Numele jucătorului de antrenat (Manager 1): ";
                std::getline(std::cin, name);
                manager1.trainPlayer(name);
                break;
            }

            case 8: {
                for (size_t i = 0; i < transferList.size(); ++i)
                    std::cout << i + 1 << ". " << transferList[i] << "\n";
                int opt;
                std::cout << "Alege jucătorul pentru Manager 2: ";
                std::cin >> opt;
                if (opt >= 1 && opt <= (int)transferList.size()) {
                    if (manager2.buyPlayer(transferList[opt - 1])) {
                        transferList.erase(transferList.begin() + (opt - 1));
                    } else {
                        std::cout << "Buget insuficient.\n";
                    }
                }
                break;
            }

            case 9: {
                std::string name;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Numele jucătorului de vândut (Manager 2): ";
                std::getline(std::cin, name);
                manager2.sellPlayer(name);
                break;
            }

            case 10: {
                std::string poz;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Poziția de filtrare (ex: ST, CM, GK): ";
                std::getline(std::cin, poz);
                manager1.getTeam().afiseazaPePozitie(poz);
                break;
            }

            case 0:
                running = false;
                break;

            default:
                std::cout << "Opțiune invalidă.\n";
                break;
        }
    }

    clasament1.afiseaza();
    clasament2.afiseaza()

    return 0;
}
