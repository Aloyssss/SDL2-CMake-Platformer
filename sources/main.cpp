#include "Core/Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init(WINDOW_CONFIG)) {
        std::cerr << "Failed to initialize game engine!" << std::endl;
        return -1;
    }

    game.run();

    return 0;
}
