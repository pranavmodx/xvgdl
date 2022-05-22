#pragma once

#include <string>

enum class ObjectType {
	Object,
	Player,
	Ball,
	Block,
};

std::string getStringForObjectType(ObjectType type);