#include "Chemistry.h"

void Chemistry::recordResult(const std::string& team, bool win) {
    form[team] += win ? 1 : -1;
    if (form[team] > 10) form[team] = 10;
    if (form[team] < -10) form[team] = -10;
}

double Chemistry::getModifier(const std::string& team) const {
    auto it = form.find(team);
    if (it == form.end()) return 0.0;
    return it->second * 0.01;
}
