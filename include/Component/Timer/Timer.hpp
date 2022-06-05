#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Util/Debug.hpp"

class Timer : public Debug {
    int time;

public:
    Timer() {}
    Timer(const std::string &textStr, const sf::Vector2f &pos) : Debug(textStr, pos), time(0) {
        text.setCharacterSize(100);
    }

    inline void update(float t) { 
        time = t;
        text.setString(std::string("Time lapsed : " + std::to_string(time))); 
    }
};