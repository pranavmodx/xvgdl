#pragma once

#include <utility>

class GameObjectDefinition {
	std::string name;
	std::string type;
	int height;
	int width;
	std::pair<int, int> position;
};