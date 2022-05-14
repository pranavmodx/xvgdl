#include <iostream>
#include "Component/Rule/Rule.hpp"
#include "Context/GameContext.hpp" // imp to include this here (in .cpp and not .hpp to avoid circular dependency)
// https://pvigier.github.io/2018/02/09/dependency-graph.html

Rule::Rule(std::string name, RuleType type) : 
name(name), type(type) 
{
}

void Rule::addRuleAction(RuleActionPtr ruleAction) {
	ruleActions.push_back(std::move(ruleAction)); // moving ownership of ptr from function to vector
}

void Rule::apply(GameContext* gameContext) {
	if (type == RuleType::Collision) {
		handleCollision(gameContext);
	}
}

void Rule::handleCollision(GameContext* gameContext) {
	// gameContext->printDBG();
	auto objn1 = ruleActions[0]->getObjectName();
	auto objn2 = ruleActions[1]->getObjectName();

	auto obj1 = gameContext->getObject(objn1);
	auto obj2 = gameContext->getObject(objn2);

	std::cout << obj1->getName();
	std::cout << obj2->getName();

	if (obj1->getGlobalBounds().intersects(obj2->getGlobalBounds())) {
		std::cout << "collided!";
		// apply rule action
		ruleActions[0]->apply(gameContext);
		ruleActions[1]->apply(gameContext);
	}
}