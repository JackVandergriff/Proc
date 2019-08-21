#include "game.hpp"

int main() {
    Game game;

    LoadSprites(game);
    game.main();

    return 0;
}