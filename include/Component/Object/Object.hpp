#pragma once

#include <utility>
#include <SFML/Graphics.hpp>

class Object {
	std::string name;
	std::string type;
	int height;
	int width;
	std::pair<int, int> position;

public:
	~Object() {}
	std::string getName() {}
	std::string getType() {}
	virtual void draw(std::unique_ptr<sf::RenderWindow> &window) {}
};