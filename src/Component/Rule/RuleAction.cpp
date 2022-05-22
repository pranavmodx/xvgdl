#include <iostream>
#include "Component/Rule/RuleActionType.hpp"
#include "Component/Rule/RuleAction.hpp"
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
		// std::cout << "speed added :P";
	} else if (type == RuleActionType::Bounce) {
		if (obj->getType() == ObjectType::Ball) {
			auto t_obj = std::static_pointer_cast<Ball>(obj);
			t_obj->setDirX(t_obj->getDirX() * -1);
			t_obj->setDirY(t_obj->getDirY() * -1);
		}
	}
}