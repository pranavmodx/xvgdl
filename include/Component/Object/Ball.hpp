#pragma once

#include <vector>
#include "Object.hpp"
#include "ObjectType.hpp"
#include "Component/ScoreBoard/ScoreBoard.hpp"

class Ball : public Object {
public:
	sf::CircleShape ball;
	float speed;
	int dirX; // can take values -1, 0, 1
	int dirY; // same
	int timer;

	static ObjectType type;
	static std::vector<int> initDirY;

public:
	Ball();
	Ball(std::string name);
	~Ball() {}

	std::string getName();
	ObjectType getType();

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

	void setName(const std::string &name);
	void setType(ObjectType type);

	inline int getDirX() { return dirX; }
	inline int getDirY() { return dirY; }
	void setDirX(int dir);
	void setDirY(int dir);

	void draw(std::unique_ptr<sf::RenderWindow> &window);
	void move(float dirX, float dirY);
	void update(const std::unique_ptr<sf::RenderWindow> &window, ScoreBoard *scoreBoard);
};