#pragma once

#include "Object.hpp"

class Player : Object {
	int initialLives;
	int currentLives;
	int health;

public:
	std::string getName() {} // define later
	std::string getType() {}
};