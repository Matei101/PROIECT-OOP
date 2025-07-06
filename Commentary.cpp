#include "Commentary.h"
#include <cmath>

std::string Commentary::forMatch(int s1, int s2) {
    if (s1 == s2) return "A tense draw, both sides defended well.";
    if (std::abs(s1 - s2) == 1) return "A closely fought game.";
    if (s1 > s2) return "A commanding win!";
    return "Surprise upset victory!";
}
