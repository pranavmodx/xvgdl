#include <iostream>
#include "Component/EndCondition/EndCondition.hpp"
// #include <sstream>

#include "Util/Debug.hpp"

EndCondition::EndCondition(std::string name, EndConditionType type) : name(name), type(type) {
    
}

void EndCondition::apply(GameContext* const gameContext, sf::Clock &clock, int score) {
    switch (type) {
        case EndConditionType::Timeout:
		    handleTimeout(clock);
            break;
        case EndConditionType::MaxScoreReached:
            handleMaxScoreReached(score);
            break;
        default:
            break;
	}
}

void EndCondition::handleTimeout(sf::Clock &clock) {
    sf::Time elapsed1 = clock.getElapsedTime();
    // std::cout << elapsed1.asSeconds() << std::endl;
    // if (elapsed1.asSeconds() > 5) {
    //     std::cout << "Game timed out!\n";
    //     exit(0);
    // }
    // std::stringstream ss;
    // ss << elapsed1.asSeconds();
}

void EndCondition::handleMaxScoreReached(int score) {
    if (score == 3) {
        std::cout << "max score ! ";
        exit(0);
    }
}