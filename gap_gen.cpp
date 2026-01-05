#include <random>


#include "gap_gen.h"
#include "constants.h"


int gapGen() {
    static std::mt19937 engine(std::random_device{}());

    int min = 50;
    int max = WINDOW_HEIGHT - 100;

    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}
