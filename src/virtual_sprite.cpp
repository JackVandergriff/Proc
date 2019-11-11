#include "virtual_sprite.hpp"

unordered_map<vector2, vector<VSprite*>> VSprite::lookup_map = unordered_map<vector2, vector<VSprite*>>();

VSprite::VSprite(sf::Vertex* quad) {
    this->quad = quad;
    pos.left = quad[0].position.x;
    pos.top = quad[0].position.y;
    pos.width = quad[2].position.x - pos.left;
    pos.height = quad[2].position.y - pos.top;
    printf("%d, %d, %d, %d", pos.left, pos.top, pos.width, pos.height);

    getBlocks();
    for (auto block : blocks) {
        if (lookup_map.count(block) == 0) {
            lookup_map.emplace(block, vector<VSprite*>());
        }
        lookup_map.at(block).push_back(this);
    }
}

VSprite::~VSprite() {}

void VSprite::move(int dx, int dy) {
    quad[0].position += sf::Vector2f(dx, dy);
    quad[1].position += sf::Vector2f(dx, dy);
    quad[2].position += sf::Vector2f(dx, dy);
    quad[3].position += sf::Vector2f(dx, dy);
    pos.left += dx;
    pos.top += dy;
}

vector2 VSprite::getBlock(sf::Vector2f pos) {
    vector2 block;
    block.x = pos.x / BLOCK_SIZE;
    block.y = pos.y / BLOCK_SIZE;
    return block;
}

unordered_set<vector2> VSprite::getBlocks() {
    blocks.clear();
    for (int i = 0; i < 3; i++) {
        vector2 block = getBlock(quad[i].position);
        if (blocks.count(block) == 0)
            blocks.emplace(block);
    }
    return blocks;
}

VSprite* VSprite::lookup(sf::Vector2f pos) {
    vector2 block = getBlock(pos);
    if (lookup_map.count(block) == 0) return nullptr;
    for (auto item : lookup_map.at(block)) {
        if (item->pos.contains(pos)) return item;
    }
    return nullptr;
}