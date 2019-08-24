#include "atlas.hpp"

Atlas::Atlas(int width, int height) {
    this->dimensions.x = width;
    this->dimensions.y = height;
    this->atlas->create(this->size * width, this->size * height);
}

Atlas::Atlas() {
    this->dimensions.x = 16;
    this->dimensions.y = 16;
    this->atlas->create(this->size * 16, this->size * 16);
}

Atlas::~Atlas() {};

void Atlas::addImage(sf::Image image, string name) {
    sf::Vector2u image_size = image.getSize();
    // printf("Image Size: %u by %u\n", image_size.x, image_size.y);
    sf::IntRect location = findFreeRect(image_size.x / this->size, image_size.y / this->size);
    // printf("Location: %dx%d at (%d, %d)\n", location.width, location.height, location.left, location.top);

    for (int x=location.left / this->size; x < (location.left + location.width) / this->size; x++) {
        for (int y=location.top / this->size; y < (location.top + location.height) / this->size; y++) {
            this->taken.emplace(vector2(x, y));
        }
    }

    this->atlas->update(image, location.left, location.top);
    if(this->lookup->emplace(name, location).second == false) printf("Lookup update failed\n");
}

void Atlas::getSprite(sf::Sprite *sprite, string name) {
    sprite->setTexture(*(this->atlas));
    sprite->setTextureRect((*lookup)[name]);
}

sf::IntRect Atlas::getRect(string name) {
    return (*lookup)[name];
}

sf::IntRect Atlas::findFreeRect(int w, int h) {
    for (int y=0; y <= this->dimensions.y - h; y++) {
        for (int x=0; x <= this->dimensions.x - w; x++) {
            bool possible = true;
            for (int dx=0; dx < w; dx++) {
                for (int dy=0; dy < h; dy++) {
                    if (this->taken.find(vector2(x+dx, y+dy)) != taken.end()) {
                        possible = false;
                        break;
                    }
                }
                if (!possible) break;
            }
            if (possible) return sf::IntRect(x * this->size, y * this->size, w * this->size, h * this->size);
        }
    }
    // printf("You screwed up real bad - not enough space in atlas\n");
    return sf::IntRect(0, 0, 0, 0);
}