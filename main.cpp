#include "Game.h"

int main(int argc, char* argv[]) {
    int init = Game::initSDL();
    if (!init) {
        cout << "Failed to initialize SDL." << endl;
        return -1;
    }
    Game game;
    game.run();
    return 0;
}