#include "game.hpp"

// Initializers

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "/Proc/");
    tilemap->atlas = atlas;
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
    this->window->draw(*tilemap);
}

void Game::main() {
    tilemap->addTile("7400", vector2(0, 0));
    tilemap->addTile("74133", vector2(80, 140));
    tilemap->setPosition(50, 50);
    tilemap->setScale(2, 2);
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