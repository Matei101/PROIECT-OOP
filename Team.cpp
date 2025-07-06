#include "Team.h"
#include <numeric>
#include <algorithm>
#include <fstream>
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
    if (players.size() >= MAX_PLAYERS) {
        std::cout << "Echipa \"" << name
                  << "\" a atins capacitatea maxima ("
                  << MAX_PLAYERS << " jucatori).\n";
        return;
    }
    players.push_back(p);
}

double Team::averageSkill() const {
    if (players.empty()) return 0;
    double total = std::accumulate(
        players.begin(), players.end(), 0.0,
        [](double sum, const Player& p){ return sum + p.getSkill(); }
    );
    return total / players.size();
}

bool Team::transferOutPlayer(const std::string& playerName, Player& outPlayer) {
    auto it = std::find_if(players.begin(), players.end(),
        [&](const Player& p){ return p.getName() == playerName; });
    if (it == players.end()) return false;
    outPlayer = *it;
    players.erase(it);
    return true;
}

void Team::incarcaDinFisier(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return;
    players.clear();
    std::string line;
    std::getline(in, line);
    if (line.rfind("Nume Echipa", 0) == 0)
        name = line.substr(12);
    std::string nume, pozitie;
    int skill;
    double valoare;
    while (in >> nume >> pozitie >> skill >> valoare) {
        players.emplace_back(nume, pozitie, skill, valoare);
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
    double totalSkill = 0, totalValue = 0;
    for (const auto& p : players) {
        totalSkill  += p.getSkill();
        totalValue += p.getValue();
    }
    std::cout << "Media skill: " << totalSkill / players.size() << "\n";
    std::cout << "Valoare totală: $" << totalValue << "\n";
}

void Team::afiseazaTopJucatori(int n) const {
    if (players.empty()) return;
    auto top = players;
    std::sort(top.begin(), top.end(),
              [](const Player& a, const Player& b){
                  return a.getSkill() > b.getSkill();
              });
    for (int i = 0; i < std::min(n, (int)top.size()); ++i)
        std::cout << top[i] << "\n";
}

void Team::editeazaJucator(const std::string& nume) {
    for (auto& p : players) {
        if (p.getName() == nume) {
            std::cin >> std::ws;
            int opt; std::cin >> opt;
            switch (opt) {
                case 1: {
                    int s; std::cin >> s;
                    p.train(s - p.getSkill());
                    break;
                }
                case 2: {
                    double v; std::cin >> v;
                    p = Player(p.getName(), p.getPosition(),
                               p.getSkill(), v, p.getContractYears());
                    break;
                }
                case 3:
                    p.recuperare();
                    break;
                case 4: {
                    int ani; std::cin >> ani;
                    p = Player(p.getName(), p.getPosition(),
                               p.getSkill(), p.getValue(),
                               p.getContractYears() + ani);
                    break;
                }
            }
            return;
        }
    }
}

void Team::transferRandom(Team& other) {
    if (players.empty()) return;
    int idx = std::rand() % players.size();
    Player p = players[idx];
    players.erase(players.begin() + idx);
    other.addPlayer(p);
    std::cout << p.getName() << " transferat.\n";
}

std::vector<Player>& Team::getPlayers() {
    return players;
}

const std::vector<Player>& Team::getPlayers() const {
    return players;
}

const std::string& Team::getName() const {
    return name;
}

std::ostream& operator<<(std::ostream& out, const Team& t) {
    out << "Team: " << t.getName() << "\n";
    for (const auto& p : t.getPlayers())
        out << "  " << p << "\n";
    return out;
}

