#pragma once

#include "Object.hpp"
#include "ObjectType.hpp"

class Player : public Object {
public:
	Player() {}
	Player(const std::string &name);
	virtual ~Player() {}
	virtual void moveController(bool useAlternate=false) = 0;

	void setType(ObjectType type);
	ObjectType getType();

	virtual std::string getName();
};