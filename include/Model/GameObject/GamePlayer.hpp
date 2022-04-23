#pragma once

#include "GameObjectDefinition.hpp"

class GamePlayerDefinition : public GameObjectDefinition {
	int initialLives;
	int currentLives;
	int health;
};