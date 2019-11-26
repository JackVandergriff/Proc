#include "game.hpp"

void LoadSprites(Game game) {
    sf::Image image;
    image.loadFromFile(ROOT_PATH + "graphics/555.png");
    game.atlas->addImage(image, "555");
    image.loadFromFile(ROOT_PATH + "graphics/74133.png");
    game.atlas->addImage(image, "74133");
    image.loadFromFile(ROOT_PATH + "graphics/7400.png");
    game.atlas->addImage(image, "7400");
    image.loadFromFile(ROOT_PATH + "graphics/2n2222.png");
    game.atlas->addImage(image, "2n2222");
    image.loadFromFile(ROOT_PATH + "graphics/breadboard.png");
    game.atlas->addImage(image, "bread");

    game.atlas->atlas->copyToImage().saveToFile(ROOT_PATH + "debug/atlas.png");
}