#include "Clasament.h"

Clasament::Clasament(const std::string& name)
    : teamName(name)
    , puncte(0)
    , meciuri(0)
{}

void Clasament::actualizeaza(int s1, int s2) {
    ++meciuri;
    if (s1 > s2) puncte += 3;
    else if (s1 == s2) puncte += 1;
}

void Clasament::afiseaza() const {
    std::cout << teamName
              << " | Meciuri: " << meciuri
              << " | Puncte: " << puncte << " ";
}
