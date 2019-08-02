#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Game {
    private:
        sf::RenderWindow *window;
        sf::Event event;

        void initWindow();

    public:
        Game();
        virtual ~Game();

        // Main game functions
        void main();
        void update();
        void render();
        void SFMLUpdate();
};