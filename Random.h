#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <ctime>

struct Random {
    static void seed() {
        static bool seeded = [](){
            std::srand(static_cast<unsigned>(std::time(nullptr)));
            return true;
        }();
        (void)seeded;
    }

    static int next(int mod) {
        seed();
        return std::rand() % mod;
    }
};

#endif // RANDOM_H
