#pragma once

#include <SFML/Graphics.hpp>

class Debug {
    sf::Font font;
    sf::Vector2f pos;

	sf::Text text;
    std::string textStr;

    void initFont();
    void initText();

public:
    Debug() {}
    Debug(const std::string &textStr, const sf::Vector2f &pos);
    void draw(std::unique_ptr<sf::RenderWindow> &window);
};