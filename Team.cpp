#include "Team.h"
#include <fstream>
#include <algorithm>
#include <limits>

Team::Team(const std::string& name)
    : name(name)
{}

Team::Team(const Team& other)
    : name(other.name)
    , players(other.players)
{}

Team& Team::operator=(const Team& other) {
    if (this != &other) {
        name = other.name;
        players = other.players;
    }
    return *this;
}

Team::~Team() {}

void Team::addPlayer(const Player& p) {
    players.push_back(p);
}

double Team::averageSkill() const {
    if (players.empty()) return 0;
    int total = 0;
    for (const auto& p : players) total += p.getSkill();
    return static_cast<double>(total) / players.size();
}

bool Team::transferOutPlayer(const std::string& playerName, Player& outPlayer) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (it->getName() == playerName) {
            outPlayer = *it;
            players.erase(it);
            return true;
        }
    }
    return false;
}

void Team::incarcaDinFisier(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return;
    players.clear();
    std::string line;
    std::getline(in, line);
    if (line.rfind("Nume Echipa ", 0) == 0)
        name = line.substr(12);

    std::string nume, pozitie;
    int skill;
    double valoare;
    while (in >> nume >> pozitie >> skill >> valoare) {
        players.push_back(Player(nume, pozitie, skill, valoare));
    }
}

void Team::afiseazaPePozitie(const std::string& poz) const {
    for (const auto& p : players)
        if (p.getPosition() == poz)
            std::cout << p << "\n";
}

void Team::afiseazaStatistici() const {
    if (players.empty()) {
        std::cout << "Echipa nu are jucători.\n";
        return;
    }
    double totalSkill = 0, totalValoare = 0;
    for (const auto& p : players) {
        totalSkill  += p.getSkill();
        totalValoare+= p.getValue();
    }
    std::cout << "Media skill: " << totalSkill/players.size() << "\n";
    std::cout << "Valoare totală: $" << totalValoare << "\n";
}

void Team::afiseazaTopJucatori(int n) const {
    if (players.empty()) {
        std::cout << "Nu există jucători.\n";
        return;
    }
    auto top = players;
    std::sort(top.begin(), top.end(),
              [](const Player& a, const Player& b){ return a.getSkill() > b.getSkill(); });
    for (int i = 0; i < std::min(n, (int)top.size()); ++i)
        std::cout << top[i] << "\n";
}

void Team::editeazaJucator(const std::string& nume) {
    for (auto& p : players) {
        if (p.getName() == nume) {
            std::cout << "1. Schimbă skill\n2. Schimbă valoare\n3. Reset accidentare\n4. Prelungește contract\n";
            int opt; std::cin >> opt;
            switch (opt) {
                case 1: {
                    int s; std::cin >> s;
                    p.train(s - p.getSkill());
                    break;
                }
                case 2: {
                    double v; std::cin >> v;
                    p = Player(p.getName(), p.getPosition(), p.getSkill(), v, p.getContractYears());
                    break;
                }
                case 3:
                    p.recuperare();
                    break;
                case 4: {
                    int ani; std::cin >> ani;
                    p = Player(p.getName(), p.getPosition(), p.getSkill(), p.getValue(), p.getContractYears()+ani);
                    break;
                }
            }
            return;
        }
    }
}

void Team::transferRandom(Team& other) {
    if (players.empty()) return;
    int idx = rand() % players.size();
    Player p = players[idx];
    players.erase(players.begin()+idx);
    other.addPlayer(p);
    std::cout << "🔁 " << p.getName() << " către " << other.getName() << "\n";
}

std::vector<Player>& Team::getPlayers() { return players; }
const std::string& Team::getName() const { return name; }

std::ostream& operator<<(std::ostream& out, const Team& t) {
    out << "Team: " << t.name << "\n";
    for (const auto& p : t.players)
        out << "  " << p << "\n";
    return out;
}