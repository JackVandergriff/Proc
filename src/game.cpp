#include "game.hpp"

#define KEYDOWN(x) (sf::Keyboard::isKeyPressed(sf::Keyboard::x))

// Initializers

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "/Proc/");
    this->window->setView(this->view);
    tilemap->atlas = atlas;
}

Game::Game() {
    this->initWindow();
}

Game::~Game() {

}

// Main game functions

void Game::render() {
    for (auto item : drawables) {
        this->window->draw(*item);
    }
}

void Game::main() {
    tilemap->addTile("555", vector2(0, 0));
    tilemap->addTile("7400", vector2(37, 49));
    tilemap->addTile("74133", vector2(80, 140));
    tilemap->setPosition(50, 50);
    tilemap->setScale(2, 2);
    drawables.push_back(tilemap);
    while (this->window->isOpen()) {
        this->processInput();
        this->update();
        this->window->clear();
        this->render();
        this->window->display();
    }
}

void Game::update() {
    deltaTime = clock.restart().asMicroseconds();
    this->SFMLUpdate();
}

void Game::SFMLUpdate() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
        if (event.type == sf::Event::Resized) {
            // update the view to the new size of the window
            this->view.setSize(event.size.width, event.size.height);
            this->window->setView(this->view);
        }
    }
}

void Game::processInput() {
    float msdt = moveSpeed * deltaTime;

    if (KEYDOWN(W)) {
        view.move(0, -msdt);
    } else if (KEYDOWN(S)) {
        view.move(0, msdt);
    } if (KEYDOWN(A)) {
        view.move(-msdt, 0);
    } else if (KEYDOWN(D)) {
        view.move(msdt, 0);
    }

    window->setView(view);
}