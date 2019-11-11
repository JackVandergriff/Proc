#include <unordered_map>
#include <unordered_set>
#include <SFML/Graphics.hpp>

#include "utility.hpp"

using namespace std;

class VSprite {
    private:
        sf::Vertex* quad;
        sf::FloatRect pos;

        unordered_set<vector2> blocks;
        static unordered_map<vector2, vector<VSprite*>> lookup_map;
        static const int BLOCK_SIZE = 32;

        static vector2 getBlock(sf::Vector2f);
        unordered_set<vector2> getBlocks();
    public:
        void move(int, int);
        static VSprite* lookup(sf::Vector2f);

        VSprite(sf::Vertex*);
        ~VSprite();
};