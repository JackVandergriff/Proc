#include "game.hpp"

// Initializers

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "/Proc/");
}

Game::Game() {
    this->initWindow();
}

Game::~Game() {

}

// Main game functions

void Game::render() {

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