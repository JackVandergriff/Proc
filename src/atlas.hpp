#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "utility.hpp"

using namespace std;

class Atlas {
    private:
        const int size = 32;
        unordered_map<string, vector2> lookup;

        vector2 nextPos = {0, 0};
        vector2 dimensions;
        void getNextPos();
    public:
        Atlas(int, int);
        Atlas();
        virtual ~Atlas();

        void addImage(sf::Image, string);
        void getSprite(sf::Sprite*,string);
        sf::Texture *atlas = new sf::Texture;
};