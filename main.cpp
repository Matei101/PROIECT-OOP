#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

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
        for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
            if (it->getName() == playerName) {
                outPlayer = *it;
                players.erase(it);
                return true;
            }
        }
        return false;
    }

    const std::string& getName() const { return name; }

    friend std::ostream& operator<<(std::ostream& out, const Team& t) {
        out << "Team: " << t.name << "\n";
        for (const auto& p : t.players) {
            out << "  " << p << "\n";
        }
        return out;
    }
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

    void showStatus() const {
        std::cout << "Manager: " << name << ", Budget: $" << std::fixed << std::setprecision(2) << budget << "\n";
        std::cout << team;
    }

    friend std::ostream& operator<<(std::ostream& out, const Manager& m) {
        out << "Manager: " << m.name << ", Budget: $" << m.budget << "\n" << m.team;
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
        score1 = static_cast<int>(avg1) % 5 + std::rand() % 3;
        score2 = static_cast<int>(avg2) % 5 + std::rand() % 3;
    }

    void showResult() const {
        std::cout << "Match: " << team1.getName() << " " << score1
                  << " - " << score2 << " " << team2.getName() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const Match& m) {
        out << "Match Result: " << m.team1.getName() << " " << m.score1
            << " - " << m.score2 << " " << m.team2.getName();
        return out;
    }
};

int main() {
    std::vector<Player> transferList = {
        Player("Haaland", "ST", 91, 85),
        Player("Neymar", "LW", 90, 88),
        Player("Kane", "ST", 89, 80),
        Player("De Bruyne", "CM", 91, 90)
    };

    Team team1("FC Legend");
    team1.addPlayer(Player("Messi", "RW", 95, 100));
    team1.addPlayer(Player("Modric", "CM", 89, 70));

    Team team2("Superstars United");
    team2.addPlayer(Player("Ronaldo", "ST", 92, 90));
    team2.addPlayer(Player("Van Dijk", "CB", 88, 75));
    team2.addPlayer(Player("Mbappe", "LW", 93, 95));

    Manager manager1("Alex", team1, 200);
    Manager manager2("Chris", team2, 150);

    bool running = true;
    int choice;

    while (running) {
        std::cout << "\n===== FOOTBALL MANAGER MENU =====\n";
        std::cout << "1. Afișare status manageri\n";
        std::cout << "2. Cumpărare jucător pentru Manager 1\n";
        std::cout << "3. Vânzare jucător de la Manager 1\n";
        std::cout << "4. Simulează meci între echipe\n";
        std::cout << "5. Ieșire\n";
        std::cout << "Alege o opțiune: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\n--- STATUS MANAGER 1 ---\n";
                manager1.showStatus();
                std::cout << "\n--- STATUS MANAGER 2 ---\n";
                manager2.showStatus();
                break;

            case 2: {
                std::cout << "\n--- JUCĂTORI DISPONIBILI PENTRU TRANSFER ---\n";
                for (std::size_t i = 0; i < transferList.size(); ++i) {
                    std::cout << i + 1 << ". " << transferList[i] << "\n";
                }
                std::cout << "Introdu numărul jucătorului pe care vrei să-l cumperi: ";
                int opt;
                std::cin >> opt;
                if (opt >= 1 && static_cast<std::size_t>(opt) <= transferList.size()) {
                    Player p = transferList[opt - 1];
                    if (manager1.buyPlayer(p)) {
                        std::cout << "✅ Jucător cumpărat cu succes!\n";
                        transferList.erase(transferList.begin() + (opt - 1));
                    } else {
                        std::cout << "❌ Fonduri insuficiente pentru acest transfer.\n";
                    }
                } else {
                    std::cout << "❌ Opțiune invalidă.\n";
                }
                break;
            }

            case 3: {
                std::cout << "Introdu numele jucătorului pe care vrei să-l vinzi: ";
                std::string nume;
                std::cin.ignore();
                std::getline(std::cin, nume);
                if (manager1.sellPlayer(nume)) {
                    std::cout << "✅ Jucător vândut cu succes.\n";
                } else {
                    std::cout << "❌ Jucătorul nu a fost găsit în echipă.\n";
                }
                break;
            }

            case 4: {
                Match m(team1, team2);
                m.simulate();
                std::cout << "\n--- REZULTAT MECI ---\n";
                m.showResult();
                break;
            }

            case 5:
                std::cout << "Ieșire din joc. 👋\n";
                running = false;
                break;

            default:
                std::cout << "❌ Opțiune invalidă.\n";
                break;
        }
    }

    return 0;
}
