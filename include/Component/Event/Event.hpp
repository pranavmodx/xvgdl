#pragma once

#include "Component/Event/EventType.hpp"
#include "Component/Object/ObjectType.hpp"

class GameContext; // forward decl

class Event {
	EventType type;
	ObjectType objType;
	float timer;

public:
	Event(EventType type, ObjectType objType, float timer);
	EventType getType();
	void apply(GameContext *gameContext);

	void spawnObject(ObjectType type, float timeInterval=5);
};