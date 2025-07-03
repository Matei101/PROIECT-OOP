#ifndef CLASAMENT_H
#define CLASAMENT_H

#include <iostream>
#include <string>

struct Clasament {
    explicit Clasament(const std::string& name);
    void actualizeaza(int scor1, int scor2);
    void afiseaza() const;

    std::string teamName;
    int puncte;
    int meciuri;
};

#endif // CLASAMENT_H
