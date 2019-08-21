#include "game.hpp"

// Initializers

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "/Proc/");
}

Game::Game() {
    this->initWindow();
	this->shape = sf::CircleShape(100.0f);
	this->shape.setFillColor(sf::Color::Green);
}

Game::~Game() {

}

// Main game functions

void Game::render() {
    sf::Sprite IC;
    this->atlas.getSprite(&IC, "555");
    IC.setPosition(50, 50);
    IC.setScale(10, 10);
    this->window->draw(IC);
}

void Game::main() {
    while (this->window->isOpen()) {
        this->update();
        this->window->clear();
        this->render();
        this->window->display();
    }
}

void Game::update() {
    this->SFMLUpdate();
}

void Game::SFMLUpdate() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

Atlas::Atlas(int width, int height) {
    this->dimensions.x = width;
    this->dimensions.y = height;
    this->atlas->create(this->size * width, this->size * height);
}

Atlas::Atlas() {
    this->dimensions.x = 16;
    this->dimensions.y = 16;
    this->atlas->create(this->size * 16, this->size * 16);
}

Atlas::~Atlas() {};

void Atlas::addImage(sf::Image image, string name) {
    this->atlas->update(image, nextPos.x * size, nextPos.y * size);
    if(this->lookup.emplace(name, nextPos).second == false) printf("Lookup update failed\n");
    this->getNextPos();
}

void Atlas::getNextPos() {
    this->nextPos.x++;
    if (this->nextPos.x >= this->dimensions.x) {
        this->nextPos.x = 0;
        this->nextPos.y++;
    }

}

void Atlas::getSprite(sf::Sprite *sprite, string name) {
    sprite->setTexture(*(this->atlas));
    sprite->setTextureRect(sf::IntRect(lookup[name].x, lookup[name].y, size, size));
}

