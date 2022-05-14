#pragma once

#include "RuleActionType.hpp"

class GameContext;
using GameContextPtr = std::unique_ptr<GameContext>;

class RuleAction {
	std::string objName;
	RuleActionType type;

public:
	RuleAction(std::string objName, RuleActionType type);
	std::string getObjectName();
	void apply(GameContext* const gameContext);
};