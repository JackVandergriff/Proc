#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "utility.hpp"

using namespace std;

class Atlas {
    private:
        const int size = 32;
        unordered_set<vector2> taken;
        vector2 dimensions;

        sf::IntRect findFreeRect(int, int);
    public:
        Atlas(int, int);
        Atlas();
        virtual ~Atlas();

        void addImage(sf::Image, string);
        void getSprite(sf::Sprite*,string);
        sf::IntRect getRect(string);
        sf::Texture *atlas = new sf::Texture;
        unordered_map<string, sf::IntRect> *lookup = new unordered_map<string, sf::IntRect>;
};