#include "tilemap.hpp"

// TileMap::TileMap(Atlas* new_atlas) : sf::Drawable(), sf::Transformable() {
//     atlas = new_atlas;
//     vertices.setPrimitiveType(sf::Quads);
// }

void TileMap::addTile(string name, vector2 location) {
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(vertices.getVertexCount() + 4);
    sf::Vertex* quads = &vertices[vertices.getVertexCount() - 4];
    sf::IntRect tileInfo = atlas->getRect(name);
    // printf("Location: %dx%d at (%d, %d)\n", tileInfo.width, tileInfo.height, tileInfo.left, tileInfo.top);

    quads[0].position = sf::Vector2f(location.x, location.y);
    quads[1].position = sf::Vector2f(location.x + tileInfo.width, location.y);
    quads[2].position = sf::Vector2f(location.x + tileInfo.width, location.y + tileInfo.height);
    quads[3].position = sf::Vector2f(location.x, location.y + tileInfo.height);

    quads[0].texCoords = sf::Vector2f(tileInfo.left, tileInfo.top);
    quads[1].texCoords = sf::Vector2f(tileInfo.left + tileInfo.width, tileInfo.top);
    quads[2].texCoords = sf::Vector2f(tileInfo.left + tileInfo.width, tileInfo.top + tileInfo.height);
    quads[3].texCoords = sf::Vector2f(tileInfo.left, tileInfo.top + tileInfo.height);
}

void TileMap::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderStates.transform *= getTransform();
    renderStates.texture = atlas->atlas;
    renderTarget.draw(vertices, renderStates);
}