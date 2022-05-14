#include <iostream>
#include "Component/RuleAction/RuleActionType.hpp"
#include "Component/RuleAction/RuleAction.hpp"
#include "Context/GameContext.hpp" // imp to include this here (in .cpp and not .hpp to avoid circular dependency)
// https://pvigier.github.io/2018/02/09/dependency-graph.html

RuleAction::RuleAction(std::string objName, RuleActionType type) {
	this->objName = objName;
	this->type = type;
}

std::string RuleAction::getObjectName() {
	return objName;
}

void RuleAction::apply(GameContext* const gameContext) {
	auto obj = gameContext->getObject(objName);

	if (type == RuleActionType::SpeedUp) {
		std::cout << "speed added :P";
	}
}