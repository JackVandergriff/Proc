#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>

#include "atlas.hpp"

using namespace std;

class Game {
    private:
        sf::RenderWindow *window;
        sf::Event event;
		sf::CircleShape shape;

        void initWindow();

    public:
        Game();
        virtual ~Game();

        // Main game functions
        void main();
        void update();
        void render(sf::Sprite*);
        void SFMLUpdate();
        void drawSpriteArray();

        Atlas atlas;
};

void LoadSprites(Game);