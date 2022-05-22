#pragma once

#include "ObjectType.hpp"
#include "Player.hpp"

// using std::unique_ptr<sf::RenderWindow> = RenderWindowPtr;

class Block : public Player {
public:
	sf::RectangleShape block;
	float speed;

public:
	Block(const std::string &name, const std::string &position = "left");
	~Block() {}
	// Block(int x, int y);

	std::string getName();
	ObjectType getType();
	
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

	void setName(const std::string &name);
	void setType(ObjectType type);

	void move(float dirX, float dirY);
	void draw(std::unique_ptr<sf::RenderWindow> &window);
	void moveController(bool useAlternate=false);
};