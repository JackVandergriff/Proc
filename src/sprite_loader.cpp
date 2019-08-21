#include "game.hpp"

const string ROOT_PATH = "/home/jack/Documents/Proc/";

void LoadSprites(Game game) {
    sf::Image image;
    image.loadFromFile(ROOT_PATH + "graphics/555.png");
    game.atlas.addImage(image, "555");
}