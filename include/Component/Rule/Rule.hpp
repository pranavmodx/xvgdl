#pragma once

#include <memory>
#include <vector>
#include "Component/Object/Object.hpp"
#include "RuleType.hpp"
#include "RuleAction.hpp"

class GameContext; // forward declaration
using GameContextPtr = std::unique_ptr<GameContext>;

using ObjectPtr = std::shared_ptr<Object>;
using RuleActionPtr = std::unique_ptr<RuleAction>;

class Rule {
	std::string name;
	RuleType type;
	std::vector<RuleActionPtr> ruleActions;

public:
	Rule(std::string name, RuleType type);
	void addRuleAction(RuleActionPtr ruleAction);
	void apply(GameContext* const gameContext);
	void handleCollision(GameContext* const gameContext);
};