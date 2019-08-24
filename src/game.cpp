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

void Game::render(sf::Sprite* IC) {
    this->window->draw(*IC);
}

void Game::main() {
    sf::Sprite *IC = new sf::Sprite;
    this->atlas.getSprite(IC, "555");
    IC->setPosition(50, 50);
    IC->setScale(2, 2);
    while (this->window->isOpen()) {
        this->update();
        this->window->clear();
        this->render(IC);
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