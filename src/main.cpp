#include <iostream>

#include "game.h"

int main(int argc, const char** argv) {
    game g(1000, 1000);
    g.loop();

    return 0;
}
