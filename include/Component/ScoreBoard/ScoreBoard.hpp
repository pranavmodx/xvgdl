#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Util/Debug.hpp"

class ScoreBoard : public Debug {
    int left, right;

public:
    ScoreBoard() {}
    ScoreBoard(const std::string &textStr, const sf::Vector2f &pos) : Debug(textStr, pos), left(0), right(0) {
        text.setCharacterSize(100);
    }

    inline void update(int l, int r) { 
        left += l; right += r; 
        text.setString(std::string(std::to_string(left) + " - " + std::to_string(right))); 
    }

    inline int getMaxScore() { return std::max(left, right); }
};