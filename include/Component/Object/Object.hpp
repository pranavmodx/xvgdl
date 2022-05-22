#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include "ObjectType.hpp"

class Object {
protected:
	std::string name;
	ObjectType type;
	// int height;
	// int width;

	// std::pair<int, int> position;

public:
	Object() {}
	// Object(std::string name);
	Object(const std::string &name) : name(name) {} // non-inlining throws error :/
	virtual ~Object() {}
	virtual std::string getName() = 0;
	virtual ObjectType getType() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;

	virtual void setName(const std::string &name) = 0;
	virtual void setType(ObjectType type) = 0;

	virtual void move(float dirX, float dirY) = 0;
	virtual void draw(std::unique_ptr<sf::RenderWindow> &window) = 0;
};