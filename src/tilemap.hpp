#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include "utility.hpp"
#include "atlas.hpp"

using namespace std;

class TileMap : public sf::Drawable, public sf::Transformable {
    private:
        sf::VertexArray vertices;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    public:
        void addTile(string, vector2);
        Atlas* atlas;
};