#include "game.hpp"

int main() {
    Config config;
    Game game;

    LoadSprites(game);
    game.main();

    return 0;
}