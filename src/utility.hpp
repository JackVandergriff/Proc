#pragma once

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

using std::string;

const string ROOT_PATH("/home/jack/Documents/Proc/");
const int TILE_SIZE = 8;

typedef struct vector2{
    int x = 0;
    int y = 0;

    vector2 () {}
    vector2 (int X, int Y) {
        x = X;
        y = Y;
    }

    bool operator==(const vector2& v) const {
        return (v.x == x && v.y == y);
    }

    vector2 operator~() const {
        return vector2(x * TILE_SIZE, y * TILE_SIZE);
    }
} vector2;

namespace std {
    template <> struct hash<vector2> {
        std::size_t operator()(const vector2& v) const noexcept {
            unsigned int lower = (-1) >> (sizeof(int) * __CHAR_BIT__ / 2); // mask for lower half of int
            return (v.x & lower) | ((v.y & lower) << (sizeof(int) * __CHAR_BIT__ / 2)); 
            /* combine two lower halves of x and y components */
        }
    };
};

namespace Utility {
    std::vector<string> split_str(const std::string&, char);
};

// sf::FloatRect& operator+=(sf::FloatRect &left, sf::Vector2f &right) {
//     left.left += right.x;
//     left.top += right.y;
//     return left;
// }