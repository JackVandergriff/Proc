#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>

#include "tilemap.hpp"

using namespace std;

class Game {
    private:
        sf::RenderWindow *window;
        sf::Event event;
		sf::CircleShape shape;
        vector<sf::Drawable*> drawables;

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

        Atlas* atlas = new Atlas();
        TileMap* tilemap = new TileMap(atlas);
};

void LoadSprites(Game);