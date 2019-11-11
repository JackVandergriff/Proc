#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>

#include "tilemap.hpp"
#include "config.hpp"

using namespace std;

class Game {
    private:
        sf::RenderWindow *window;
        sf::Event event;
        vector<sf::Drawable*> drawables;

        sf::View view = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(800.f, 600.f));
        sf::Clock clock;

        float moveSpeed = .00023f;
        float deltaTime;

        void initWindow();

    public:
        Game();
        virtual ~Game();

        // Main game functions
        void main();
        void update();
        void render();
        void SFMLUpdate();
        void drawSpriteArray();
        void processInput();

        Atlas* atlas = new Atlas();
        TileMap* tilemap = new TileMap(atlas);
};

void LoadSprites(Game);