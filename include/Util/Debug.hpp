#pragma once

#include <SFML/Graphics.hpp>

class Debug {
protected:
    sf::Font font;
    sf::Vector2f pos;

	sf::Text text;
    std::string textStr;

    void initFont();
    void initText();

public:
    Debug() {}
    Debug(const std::string &textStr, const sf::Vector2f &pos);
    void draw(sf::RenderWindow *window);
};