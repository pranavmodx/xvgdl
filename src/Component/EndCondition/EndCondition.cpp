#include <iostream>
#include "Component/EndCondition/EndCondition.hpp"

EndCondition::EndCondition(std::string name, EndConditionType type) : name(name), type(type) {
    
}

void EndCondition::apply(GameContext* const gameContext, sf::Clock &clock) {
    if (type == EndConditionType::Timeout) {
		handleTimeout(clock);
	}
}

void EndCondition::handleTimeout(sf::Clock &clock) {
    sf::Time elapsed1 = clock.getElapsedTime();
    // std::cout << elapsed1.asSeconds() << std::endl;
}
