#pragma once

#include <memory>
#include "ObjectType.hpp"
#include "Player.hpp"

class Block : public Player {
public:
	sf::RectangleShape block;
	float speed;
	bool isAI;

public:
	Block(const std::string &name, const std::string &position = "left");
	~Block() {}
	// Block(int x, int y);

	std::string getName();
	ObjectType getType();
	bool getIsAI();
	
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

	void setName(const std::string &name);
	void setType(ObjectType type);
	void setIsAI();

	void move(float dirX, float dirY);
	void draw(std::unique_ptr<sf::RenderWindow> &window);
	void moveController(bool useAlternate=false);

	void AIController(sf::Vector2f ballPos, int id=1);
};