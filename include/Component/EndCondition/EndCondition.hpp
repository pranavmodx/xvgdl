#pragma once

#include <memory>
#include "Component/Object/Object.hpp"
#include "EndConditionType.hpp"

class GameContext; // forward declaration
using GameContextPtr = std::unique_ptr<GameContext>;

using ObjectPtr = std::shared_ptr<Object>;

class EndCondition {
	std::string name;
	EndConditionType type;

public:
	EndCondition(std::string name, EndConditionType type);
	void apply(GameContext* const gameContext, sf::Clock &clock);
	void handleTimeout(sf::Clock &clock);
};