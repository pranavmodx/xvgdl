#include <iostream>
#include <memory>
#include "Util/Debug.hpp"

Debug::Debug(const std::string &textStr, const sf::Vector2f &pos) : textStr(textStr), pos(pos) {
    initFont();
    initText();
}

void Debug::initFont() {
    if (!font.loadFromFile("assets/fonts/PixellettersFull.ttf"))
	{
		std::cout << "DBG: Could not load font!" << "\n";
        exit(0);
	}
}

void Debug::initText() {
    text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(32);
    text.setPosition(pos);
    text.setString(textStr);
}

void Debug::draw(std::unique_ptr<sf::RenderWindow> &window) {
    window->draw(text);
}
