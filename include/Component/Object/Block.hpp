#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"

class Block : public Object {
	std::string getName() {}
	std::string getType() {}

public:
	void draw(std::unique_ptr<sf::RenderWindow> &window);
};